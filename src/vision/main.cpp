		
/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <cstdio>
#include <string>
#include <thread>
#include <vector>
#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTableInstance.h>
#include <vision/VisionPipeline.h>
#include <vision/VisionRunner.h>
#include <wpi/StringRef.h>
#include <wpi/json.h>
#include <cscore.h>
#include <opencv2/opencv.hpp>
#include <wpi/raw_istream.h>
#include <wpi/raw_ostream.h>

#include "cameraserver/CameraServer.h"

/*
   JSON format:
   {
	   "team": <team number>,
	   "ntmode": <"client" or "server", "client" if unspecified>
	   "cameras": [
		   {
			   "name": <camera name>
			   "path": <path, e.g. "/dev/video0">
			   "pixel format": <"MJPEG", "YUYV", etc>   // optional
			   "width": <video mode width>              // optional
			   "height": <video mode height>            // optional
			   "fps": <video mode fps>                  // optional
			   "brightness": <percentage brightness>    // optional
			   "white balance": <"auto", "hold", value> // optional
			   "exposure": <"auto", "hold", value>      // optional
			   "properties": [                          // optional
				   {
					   "name": <property name>
					   "value": <property value>
				   }
			   ],
			   "stream": {                              // optional
				   "properties": [
					   {
						   "name": <stream property name>
						   "value": <stream property value>
					   }
				   ]
			   }
		   }
	   ]
	   "switched cameras": [
		   {
			   "name": <virtual camera name>
			   "key": <network table key used for selection>
			   // if NT value is a string, it's treated as a name
			   // if NT value is a double, it's treated as an integer index
		   }
	   ]
   }
 */

static const char* configFile = "/boot/frc.json";

unsigned int team;

struct CameraConfig {
	std::string name;
	std::string path;
	wpi::json config;
	wpi::json streamConfig;
};

std::vector<CameraConfig> cameraConfigs;
std::vector<cs::VideoSource> cameras;

wpi::raw_ostream& ParseError() {
	return wpi::errs() << "config error in '" << configFile << "': ";
}

bool ReadCameraConfig(const wpi::json& config) {
	CameraConfig c;

	// name
	try {
		c.name = config.at("name").get<std::string>();
	}
	catch (const wpi::json::exception& e) {
		ParseError() << "could not read camera name: " << e.what() << '\n';
		return false;
	}

	// path
	try {
		c.path = config.at("path").get<std::string>();
	}
	catch (const wpi::json::exception& e) {
		ParseError() << "camera '" << c.name
			<< "': could not read path: " << e.what() << '\n';
		return false;
	}

	// stream properties
	if (config.count("stream") != 0) c.streamConfig = config.at("stream");

	c.config = config;

	cameraConfigs.emplace_back(std::move(c));
	return true;
}

bool ReadConfig() {
	// open config file
	std::error_code ec;
	wpi::raw_fd_istream is(configFile, ec);
	if (ec) {
		wpi::errs() << "could not open '" << configFile << "': " << ec.message()
			<< '\n';
		return false;
	}

	// parse file
	wpi::json j;
	try {
		j = wpi::json::parse(is);
	}
	catch (const wpi::json::parse_error& e) {
		ParseError() << "byte " << e.byte << ": " << e.what() << '\n';
		return false;
	}

	// top level must be an object
	if (!j.is_object()) {
		ParseError() << "must be JSON object\n";
		return false;
	}

	// team number
	try {
		team = j.at("team").get<unsigned int>();
	}
	catch (const wpi::json::exception& e) {
		ParseError() << "could not read team number: " << e.what() << '\n';
		return false;
	}

	// cameras
	try {
		for (auto&& camera : j.at("cameras")) {
			if (!ReadCameraConfig(camera)) return false;
		}
	}
	catch (const wpi::json::exception& e) {
		ParseError() << "could not read cameras: " << e.what() << '\n';
		return false;
	}

	return true;
}

cs::UsbCamera StartCamera(const CameraConfig& config) {
	wpi::outs() << "Starting camera '" << config.name << "' on " << config.path
		<< '\n';
	auto inst = frc::CameraServer::GetInstance();
	cs::UsbCamera camera{ config.name, config.path };
	auto server = inst->StartAutomaticCapture(camera);

	camera.SetConfigJson(config.config);
	camera.SetConnectionStrategy(cs::VideoSource::kConnectionKeepOpen);

	if (config.streamConfig.is_object())
		server.SetConfigJson(config.streamConfig);

	return camera;
}

std::string getCommandOutput(const char *command) {
	char buffer[16];
	std::string result = "";
	FILE *pipe = popen(command, "r");
	if (!pipe) {
		std::cout << "Failed to execute command: " << command << std::endl;
		return result;
	}
	try {
		while (fgets(buffer, sizeof(buffer), pipe)) {
			result += buffer;
		}
	}
	catch(...) {
		std::cout << "Failed to read pipe after command: " << command << std::endl;
	}
	pclose(pipe);
	return result;
}

void processImage(nt::NetworkTableInstance *ntinst) {
	for (unsigned int i = 0; i < cameras.size(); i++) {
		cameras[i].SetResolution(160, 120);
	}

	std::shared_ptr<NetworkTable> processingDataTable = ntinst->GetTable("vision_processing");

	nt::NetworkTableEntry minH = processingDataTable->GetEntry("min_h");
	minH.SetDouble(30);
	nt::NetworkTableEntry minS = processingDataTable->GetEntry("min_s");
	minS.SetDouble(70);
	nt::NetworkTableEntry minV = processingDataTable->GetEntry("min_v");
	minV.SetDouble(26);

	nt::NetworkTableEntry maxH = processingDataTable->GetEntry("max_h");
	maxH.SetDouble(110);
	nt::NetworkTableEntry maxS = processingDataTable->GetEntry("max_s");
	maxS.SetDouble(255);
	nt::NetworkTableEntry maxV = processingDataTable->GetEntry("max_v");
	maxV.SetDouble(255);

	cv::Mat frame_raw, frame_HSV, frame_blur, frame_threshold, frame_edges, frame_rectangles;

	cs::CvSink rawVideo = frc::CameraServer::GetInstance()->GetVideo();
	cs::CvSource rectangleStream = frc::CameraServer::GetInstance()->PutVideo("rectangles_front_camera", 160, 120);

	long testCounter = 0;
	while (ntinst->IsConnected()) {
		//std::cout << "Running (test counter: " << ++testCounter << ")" << std::endl;
		bool pinIsHigh = (getCommandOutput("cat /sys/class/gpio/gpio26/value")[0] == '1');
		std::cout << "Pin 26 input: " << pinIsHigh << std::endl;
		if (pinIsHigh) {
			std::cout << "Pin 26 read as HIGH, stopping program..." << std::endl;
			break;
		}

		nt::NetworkTableEntry runPi = processingDataTable->GetEntry("run_pi");
		bool runPiVal = runPi.GetBoolean(true);
		if (!runPiVal) {
			std::cout << "Ending processing..." << std::endl;
			break;
		}

		rawVideo.GrabFrame(frame_raw);
		frame_rectangles = frame_raw;

		cvtColor(frame_raw, frame_HSV, cv::COLOR_RGB2HSV);
		cv::GaussianBlur(frame_HSV, frame_blur, cv::Size(15, 15), 0, 0);
		inRange(frame_blur, cv::Scalar(minH.GetDouble(0), minS.GetDouble(0), minV.GetDouble(0)), cv::Scalar(maxH.GetDouble(0), maxS.GetDouble(0), maxV.GetDouble(0)), frame_threshold);
		cv::Canny(frame_threshold,frame_edges,100,300);

		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;

		cv::findContours(frame_edges, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

		std::vector<cv::RotatedRect> rects;

		for (int i = 0; i < contours.size(); i++) {
			rects.push_back(cv::minAreaRect(contours[i]));
		}

		double maxArea = 0;
		int maxAreaRectIndex = -1;
		for (int i = 0; i < rects.size(); i++) {
			double currentArea = rects[i].size.width * rects[i].size.height;
			if (currentArea > maxArea) {
				maxArea = currentArea;
				maxAreaRectIndex = i;
			}
		}

		cv::Point2f points[4];

		if (maxAreaRectIndex >= 0) {
			rects[maxAreaRectIndex].points(points);
			for (int i = 0; i < 4; i++) {
				int firstPointIndex = i;
				int secondPointIndex = i + 1;
				if (secondPointIndex == 4) {
					secondPointIndex = 0;
				}

				cv::line(frame_rectangles, points[firstPointIndex], points[secondPointIndex], cv::Scalar(255, 0, 0), 2);
			}
		}

		int leftMost = 0;
		int secondLeftMost = 0;
		for (int i = 1; i < 4; i++) {
			if (points[i].x < points[leftMost].x) {
				leftMost = i;
			}
		}
		if (leftMost == 0) {
			secondLeftMost++;
		}
		for (int i = 0; i < 4; i++) {
			if (i != leftMost && points[i].x < points[secondLeftMost].x) {
				secondLeftMost = i;
			}
		}

		int rightIndex1 = -1;
		int rightIndex2 = -1;
		for (int i = 0; i < 4; i++) {
			if (leftMost != i && secondLeftMost != i) {
				if (rightIndex1 == -1) {
					rightIndex1 = i;
				}
				else if (rightIndex2 == -1) {
					rightIndex2 = i;
					break;
				}
			}
		}

		int topLeftIndex, topRightIndex, bottomLeftIndex, bottomRightIndex;
		if (points[leftMost].y < points[secondLeftMost].y) {
			topLeftIndex = leftMost;
			bottomLeftIndex = secondLeftMost;
		}
		else {
			topLeftIndex = secondLeftMost;
			bottomLeftIndex = leftMost;
		}

		if (points[rightIndex1].y < points[rightIndex2].y) {
			topRightIndex = rightIndex1;
			bottomRightIndex = rightIndex2;
		}
		else {
			topRightIndex = rightIndex2;
			bottomRightIndex = rightIndex1;
		}

		std::vector<cv::Point2d> imagePoints;
		imagePoints.push_back(points[topLeftIndex]);
		imagePoints.push_back(points[topRightIndex]);
		imagePoints.push_back(points[bottomLeftIndex]);
		imagePoints.push_back(points[bottomRightIndex]);

		std::vector<cv::Point3d> objectPoints;
		objectPoints.push_back(cv::Point3d(-50, -22, 0));
		objectPoints.push_back(cv::Point3d(50, -22, 0));
		objectPoints.push_back(cv::Point3d(-50, 22, 0));
		objectPoints.push_back(cv::Point3d(50, 22, 0));

		double cameraMatrixData[9] = {1175.957148, 0, 412.991058, 0, 1138.651452, 326.985259, 0, 0, 1};
		double distCoefficientData[5] = {-0.144313, 0.917655, -0.006346, -0.055340, -1.646086};

		cv::Mat cameraMatrix = cv::Mat(3, 3, CV_64F, cameraMatrixData);
		cv::Mat distCoefficients = cv::Mat(4, 1, CV_64F, distCoefficientData);

		cv::Mat robotTranslation;
		cv::Mat robotRotation;
		cv::Mat robotRotationMatrix;

		cv::solvePnP(objectPoints, imagePoints, cameraMatrix, distCoefficients, robotRotation, robotTranslation);
		cv::Rodrigues(robotRotation,robotRotationMatrix);
		double Matrix1_3 = robotRotationMatrix.at<double>(0,2);

		nt::NetworkTableEntry robotX = processingDataTable->GetEntry("robot_x");
		robotX.SetDouble(robotTranslation.at<double>(0, 0));
		nt::NetworkTableEntry robotY = processingDataTable->GetEntry("robot_y");
		robotY.SetDouble(robotTranslation.at<double>(1, 0));
		nt::NetworkTableEntry robotZ = processingDataTable->GetEntry("robot_z");
		robotZ.SetDouble(robotTranslation.at<double>(2, 0));

		double RobotYTheta=asin(robotRotationMatrix.at<double>(0,2));
		double RotationMatrix2_3=(robotRotationMatrix.at<double>(1,2));
		double RobotXTheta=asin(RotationMatrix2_3/-cos(RobotYTheta));
		double RotationMatrix1_2=(robotRotationMatrix.at<double>(0,1));
		double RobotZTheta=asin(RotationMatrix1_2/-cos(RobotYTheta));

		nt::NetworkTableEntry robotYThetaNetworkTable = processingDataTable->GetEntry("robot_y_theta");
		robotYThetaNetworkTable.SetDouble(Matrix1_3);
		nt::NetworkTableEntry robotXThetaNetworkTable = processingDataTable->GetEntry("robot_x_theta");
		robotXThetaNetworkTable.SetDouble(RobotXTheta);
		nt::NetworkTableEntry robotZThetaNetworkTable = processingDataTable->GetEntry("robot_z_theta");
		robotZThetaNetworkTable.SetDouble(RobotZTheta);

		rectangleStream.PutFrame(frame_rectangles);
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
}

int main() {
	system("echo \"26\" > /sys/class/gpio/export");
	system("echo \"in\" > /sys/class/gpio/gpio26/direction");

	// read configuration
	if (!ReadConfig()) return 1;

	// start NetworkTables
	nt::NetworkTableInstance ntinst = nt::NetworkTableInstance::GetDefault();
	wpi::outs() << "Setting up NetworkTables client for team " << team << '\n';
	ntinst.StartClientTeam(team);

	// start cameras
	for (const auto& config : cameraConfigs) {
		cameras.emplace_back(StartCamera(config));
	}

	processImage(&ntinst);

	return 0;
}
