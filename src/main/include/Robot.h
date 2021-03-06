/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <iostream>

#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/Joystick.h>
#include <frc/AnalogInput.h>
#include <frc/DigitalOutput.h>
#include <frc/Encoder.h>
#include <frc/controller/PIDController.h>

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"

#include <cameraserver/CameraServer.h>

#include <rev/ColorSensorV3.h>
#include <rev/ColorMatch.h>

#include "RobotMap.h"
#include "JoystickMap.h"

using ctre::phoenix::motorcontrol::can::WPI_VictorSPX;

class Robot : public frc::TimedRobot {
	public:
		void RobotInit() override;
		void RobotPeriodic() override;
		void AutonomousInit() override;
		void AutonomousPeriodic() override;
		void TeleopInit() override;
		void TeleopPeriodic() override;
		void TestPeriodic() override;

	private:
		static constexpr frc::I2C::Port i2cPort = frc::I2C::Port::kOnboard;

		const double PI = 3.14159265;

		const std::string DEFAULT_AUTO_MODE_NAME = "default";
		const std::string CUSTOM_AUTO_MODE_NAME = "custom";

		frc::SendableChooser<std::string> autoModeChooser;
		std::string selectedAutoMode;

		WPI_VictorSPX frontLeftMotor{RobotMap::FRONT_LEFT_MOTOR};
		WPI_VictorSPX backLeftMotor{RobotMap::BACK_LEFT_MOTOR};
		WPI_VictorSPX frontRightMotor{RobotMap::FRONT_RIGHT_MOTOR};
		WPI_VictorSPX backRightMotor{RobotMap::BACK_RIGHT_MOTOR};

		frc::SpeedControllerGroup leftGroup{frontLeftMotor, backLeftMotor};
		frc::SpeedControllerGroup rightGroup{frontRightMotor, backRightMotor};

		frc::DifferentialDrive differentialDrive{leftGroup, rightGroup};

		frc::Joystick joystick{JoystickMap::JOYSTICK_ID};

		rev::ColorSensorV3 colorSensor{i2cPort};

		nt::NetworkTableInstance ntInstance;
		std::shared_ptr<NetworkTable> processingDataTable;
        nt::NetworkTableEntry runPi;

		double ySpeedMultiplier = 0.6;
		double zSpeedMultiplier = 0.48;

		frc::AnalogInput topSonarSensor{RobotMap::TOP_SONAR_SENSOR};
		frc::AnalogInput bottomSonarSensor{RobotMap::BOTTOM_SONAR_SENSOR};
		frc::DigitalOutput resetPin{RobotMap::PI_RESET_PIN};

		frc::Encoder leftDriveEncoder{RobotMap::LEFT_DRIVE_ENCODER_A, RobotMap::LEFT_DRIVE_ENCODER_B};
		frc::Encoder rightDriveEncoder{RobotMap::RIGHT_DRIVE_ENCODER_A, RobotMap::RIGHT_DRIVE_ENCODER_B};

		void Drive();
		void InitEncoders();
		void MoveToPosition(double x, double z, double finalAngle);
		void RotateToAngle(double angle, frc2::PIDController* pidController, double tolerance); 
		void MoveLength(double length, frc2::PIDController* pidController, double tolerance);
};
