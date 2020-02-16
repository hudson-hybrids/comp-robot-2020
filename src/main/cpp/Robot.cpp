/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

void Robot::RobotInit() {
	autoModeChooser.SetDefaultOption(DEFAULT_AUTO_MODE_NAME, DEFAULT_AUTO_MODE_NAME);
	autoModeChooser.AddOption(CUSTOM_AUTO_MODE_NAME, CUSTOM_AUTO_MODE_NAME);
	frc::SmartDashboard::PutData("auto_modes", &autoModeChooser);

	frc::SmartDashboard::PutBoolean("reset_pin", false);

	frc::CameraServer::GetInstance()->StartAutomaticCapture("rear_camera", 0);
}

void Robot::RobotPeriodic() {
	frc::Color blue = frc::Color(.12, .42, .45);
	frc::Color green = frc::Color(.17, .57, .25);
	frc::Color red = frc::Color(.52, .35, .13);
	frc::Color yellow = frc::Color(.32, .56, .12);
	
	rev::ColorMatch colorMatch;
	double confidence = 1.0;
	std::string color;
	colorMatch.AddColorMatch(blue);
	colorMatch.AddColorMatch(green);
	colorMatch.AddColorMatch(red);
	colorMatch.AddColorMatch(yellow);
	
	frc::Color detectedColor = colorSensor.GetColor();
	frc::Color currentColor = colorMatch.MatchClosestColor(detectedColor, confidence);
	if (currentColor == blue) {
		color = "blue";
	}
	else if (currentColor == green) {
		color = "green";
	}
	else if (currentColor == red) {
		color = "red";
	}
	else if (currentColor == yellow) {
		color = "yellow";
	}
	else {
		color = "no recognizable color";
	}

	frc::SmartDashboard::PutNumber("red", detectedColor.red);
	frc::SmartDashboard::PutNumber("green", detectedColor.green);
	frc::SmartDashboard::PutNumber("blue", detectedColor.blue);
	frc::SmartDashboard::PutString("current_color", color);

	frc::SmartDashboard::PutNumber("distance_0", distanceSensor0.GetValue());
	frc::SmartDashboard::PutNumber("distance_1", distanceSensor1.GetValue());

	bool resetPi = frc::SmartDashboard::GetBoolean("reset_pin", false);
	resetPin.Set(resetPi); 
}

void Robot::AutonomousInit() {
	selectedAutoMode = autoModeChooser.GetSelected();
	std::cout << "> BEGINNING " << selectedAutoMode << " AUTO MODE" << std::endl;
}

void Robot::AutonomousPeriodic() {
	if (selectedAutoMode == DEFAULT_AUTO_MODE_NAME) {
		
	}
	else if (selectedAutoMode == CUSTOM_AUTO_MODE_NAME) {

	}
	else {
		std::cout << "> ERROR: " << selectedAutoMode << " IS NOT A VALID AUTO MODE" << std::endl;
	}
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
	Drive();
}

void Robot::TestPeriodic() {}

void Robot::Drive() {
	const double MAXIMUM_Y_SPEED_MULTIPLIER = 0.9;
	const double MAXIMUM_Z_SPEED_MULTIPLIER = 0.72;

	const double MINIMUM_Y_SPEED_MULTIPLIER = 0.48;
	const double MINIMUM_Z_SPEED_MULTIPLIER = 0.35;

	const double NORMAL_Y_SPEED_MULTIPLIER = 0.6;
	const double NORMAL_Z_SPEED_MULTIPLIER = 0.48;

	const double ACCELERATION = 0.004;

	if (joystick.GetRawButton(JoystickMap::INCREASE_SPEED_BUTTON_ID)) {
		if (ySpeedMultiplier <= MAXIMUM_Y_SPEED_MULTIPLIER) {
			ySpeedMultiplier += ACCELERATION;
		}
		if (zSpeedMultiplier <= MAXIMUM_Z_SPEED_MULTIPLIER) {
			zSpeedMultiplier += ACCELERATION;
		}
	}
	else if (joystick.GetRawButton(JoystickMap::DECREASE_SPEED_BUTTON_ID)) {
		if (ySpeedMultiplier >= MINIMUM_Y_SPEED_MULTIPLIER) {
			ySpeedMultiplier -= ACCELERATION;
		}
		if (zSpeedMultiplier >= MINIMUM_Z_SPEED_MULTIPLIER) {
			zSpeedMultiplier -= ACCELERATION;
		}
	}
	else {
		if (ySpeedMultiplier > NORMAL_Y_SPEED_MULTIPLIER) {
			ySpeedMultiplier -= ACCELERATION;
		}
		else if (ySpeedMultiplier < NORMAL_Y_SPEED_MULTIPLIER) {
			ySpeedMultiplier += ACCELERATION;
		}
		
		if (zSpeedMultiplier > NORMAL_Z_SPEED_MULTIPLIER){
			zSpeedMultiplier -= ACCELERATION;

		}
		else if (zSpeedMultiplier < NORMAL_Z_SPEED_MULTIPLIER){
			zSpeedMultiplier += ACCELERATION;
		}
	}

	if (joystick.GetRawAxis(JoystickMap::INVERT_AXIS_ID) <= 0) {
		differentialDrive.ArcadeDrive(joystick.GetY() * ySpeedMultiplier, joystick.GetZ() * zSpeedMultiplier);
	}
	else {
		differentialDrive.ArcadeDrive(joystick.GetY() * -ySpeedMultiplier, joystick.GetZ() * zSpeedMultiplier);
	}
	
}