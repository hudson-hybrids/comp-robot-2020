/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

//BEGIN OVERRIDES

void Robot::RobotInit() {
	frc::CameraServer::GetInstance()->StartAutomaticCapture("rear_camera", 0);

	autoModeChooser.SetDefaultOption(DEFAULT_AUTO_MODE_NAME, DEFAULT_AUTO_MODE_NAME);
	autoModeChooser.AddOption(CUSTOM_AUTO_MODE_NAME, CUSTOM_AUTO_MODE_NAME);
	frc::SmartDashboard::PutData("auto_modes", &autoModeChooser);

	frc::SmartDashboard::PutBoolean("reset_pin", false);

	frc::SmartDashboard::PutBoolean("light_pin", true);

	InitEncoders();
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

	frc::SmartDashboard::PutNumber("distance_0", topSonarSensor.GetValue());
	frc::SmartDashboard::PutNumber("distance_1", bottomSonarSensor.GetValue());

	bool resetPi = frc::SmartDashboard::GetBoolean("reset_pin", false);
	resetPin.Set(resetPi); 

	bool lightOn = frc::SmartDashboard::GetBoolean("light_pin", true);
	lightPin.Set(lightOn);
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

//END OVERRIDES






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

void Robot::InitEncoders() {
	const double PI = 3.14159265;
	const double COUNTS_PER_REV = 360;
	const double WHEEL_DIAMETER_in = 4;
	const double WHEEL_CIRCUMFERENCE = PI * WHEEL_DIAMETER_in;
	const double DISTANCE_PER_PULSE = WHEEL_CIRCUMFERENCE / COUNTS_PER_REV;

	leftDriveEncoder.SetDistancePerPulse(DISTANCE_PER_PULSE);
	rightDriveEncoder.SetDistancePerPulse(DISTANCE_PER_PULSE);
}

void Robot::MoveToPosition(double xTarget_in, double zTarget_in) {
	const double TOLERANCE = 0.1;
	const double P = 0;
	const double I = 0;
	const double D = 0;

	frc2::PIDController pidController(P, I, D);
	const double LEFT_START_Z_in = leftDriveEncoder.GetDistance();
	const double RIGHT_START_Z_in = rightDriveEncoder.GetDistance();

	while (true) {
		const double CURRENT_LEFT_Z_in = leftDriveEncoder.GetDistance() - LEFT_START_Z_in;
		const double CURRENT_RIGHT_Z_in = rightDriveEncoder.GetDistance() - RIGHT_START_Z_in;

		if (CURRENT_LEFT_Z_in - zTarget_in < TOLERANCE && CURRENT_RIGHT_Z_in - zTarget_in < TOLERANCE) {
			break;
		}

		const double LEFT_SPEED = pidController.Calculate(CURRENT_LEFT_Z_in, zTarget_in);
		leftGroup.Set(LEFT_SPEED);

		const double RIGHT_SPEED = pidController.Calculate(CURRENT_RIGHT_Z_in, zTarget_in);
		rightGroup.Set(RIGHT_SPEED);
	}
}