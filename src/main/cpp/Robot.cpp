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

	TestController();
}

void Robot::RobotPeriodic() {
	/*
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
		color = "unknown_color";
	}

	frc::SmartDashboard::PutNumber("red", detectedColor.red);
	frc::SmartDashboard::PutNumber("green", detectedColor.green);
	frc::SmartDashboard::PutNumber("blue", detectedColor.blue);
	frc::SmartDashboard::PutString("current_color", color);

	frc::SmartDashboard::PutNumber("distance_0", topSonarSensor.GetValue());
	frc::SmartDashboard::PutNumber("distance_1", bottomSonarSensor.GetValue());
	*/
	bool resetPi = frc::SmartDashboard::GetBoolean("reset_pin", false);
	resetPin.Set(resetPi); 

	bool lightOn = frc::SmartDashboard::GetBoolean("light_pin", true);
	lightPin.Set(lightOn);

	TestController();
}

void Robot::AutonomousInit() {
	selectedAutoMode = autoModeChooser.GetSelected();
	std::cout << "> BEGINNING " << selectedAutoMode << " AUTO MODE" << std::endl;

	if (selectedAutoMode == DEFAULT_AUTO_MODE_NAME) {
		std::vector<Command*> *commands = new std::vector<Command*> {
			new RotateToAngle(&drivetrain, GlobalConstants::PI / 2, 1)
		};
		autoScheduler = CommandScheduler(commands);
	}
	else if (selectedAutoMode == CUSTOM_AUTO_MODE_NAME) {

	}
	else {
		std::cout << "ERROR > " << selectedAutoMode << " IS NOT A VALID AUTO MODE" << std::endl;
	}
}

void Robot::AutonomousPeriodic() {
	if (selectedAutoMode == DEFAULT_AUTO_MODE_NAME) {
		if (!autoScheduler.GetIsFinished()) {
			autoScheduler.Run();
		}
	}
	else if (selectedAutoMode == CUSTOM_AUTO_MODE_NAME) {

	}
	else {
		std::cout << "ERROR > " << selectedAutoMode << " IS NOT A VALID AUTO MODE" << std::endl;
	}
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
	ControlDrive();
	ControlOuttake();
	ControlIntake();
	ControlConveyor();
	ControlHangPistons();
	ControlHangArm();
}

void Robot::TestPeriodic() {}

//END OVERRIDES

void Robot::JoystickDrive() {
	const double MAXIMUM_Y_SPEED_MULTIPLIER = 0.9;
	const double MAXIMUM_Z_SPEED_MULTIPLIER = 0.72;

	const double MINIMUM_Y_SPEED_MULTIPLIER = 0.48;
	const double MINIMUM_Z_SPEED_MULTIPLIER = 0.4;

	const double NORMAL_Y_SPEED_MULTIPLIER = 0.6;
	const double NORMAL_Z_SPEED_MULTIPLIER = 0.58;

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
		drivetrain.differentialDrive.ArcadeDrive(joystick.GetY() * ySpeedMultiplier, joystick.GetZ() * zSpeedMultiplier);
	}
	else {
		drivetrain.differentialDrive.ArcadeDrive(joystick.GetY() * -ySpeedMultiplier, joystick.GetZ() * zSpeedMultiplier);
	}
}

void Robot::ControlDrive() {
	if (joystick.GetRawButton(JoystickMap::ACCURATE_AIM_BUTTON)) {
		//PerformAccurateAim();
		TestPID();
		prevAccurateAimButtonPressed = true;
	}
	else {
		prevAccurateAimButtonPressed = false;
	}

	if (joystick.GetRawButton(JoystickMap::QUICK_AIM_BUTTON)) {
		if (!joystick.GetRawButton(JoystickMap::ACCURATE_AIM_BUTTON)) {
			//PerformQuickAim();
		}
		prevQuickAimButtonPressed = true;
	}
	else {
		prevQuickAimButtonPressed = false;
	}

	if (!joystick.GetRawButton(JoystickMap::ACCURATE_AIM_BUTTON) && !joystick.GetRawButton(JoystickMap::QUICK_AIM_BUTTON)) {
		JoystickDrive();
	}
}

void Robot::ControlOuttake() {
	const double SPEED_MULTIPLIER = 1;
	double stickValue = gamepad.GetRawAxis(GamepadMap::OUTTAKE_AXIS_ID);
	double speed = SPEED_MULTIPLIER * stickValue;
	if (abs(stickValue) > 0.1) {
		outtakeMotor1.Set(speed);
		outtakeMotor2.Set(-speed);
	}
	else {
		outtakeMotor1.Set(0);
		outtakeMotor2.Set(0);
	}
}

void Robot::ControlIntake() {
	double triggerValue = gamepad.GetRawAxis(GamepadMap::INTAKE_OUT_TRIGGER_AXIS);
	if (triggerValue > 0.1) {
		intakeMotor.Set(0.3);
	}
	else if (gamepad.GetRawButton(GamepadMap::INTAKE_IN_BUTTON_ID)) {
		intakeMotor.Set(-0.3);
	}
	else {
		intakeMotor.Set(0);
	}
}

void Robot::ControlConveyor() {
	const double SPEED_MULTIPLIER = 0.3;
	double stickValue = gamepad.GetRawAxis(GamepadMap::CONVEYOR_AXIS_ID);
	double speed = SPEED_MULTIPLIER * stickValue;
	if (abs(stickValue) > 0.1) {
		conveyorMotor.Set(-speed);
	}
	else {
		conveyorMotor.Set(0);
	}
}

void Robot::ControlHangPistons() {
	if (gamepad.GetPOV() == 0) {
		hangPistonsExtended = true;
		hangSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
	}
	else if (gamepad.GetPOV() == 180) {
		hangPistonsExtended = false;
		hangSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
	}
	else {
		hangSolenoid.Set(frc::DoubleSolenoid::Value::kOff);
	}
}

void Robot::ControlHangArm() {
	double speed = hangPistonsExtended ? 0.35 : 0.25;
	if (joystick.GetRawButton(JoystickMap::HANG_ARM_UP_BUTTON_ID)) {
		hangMotor.Set(-speed);
	}
	else if (joystick.GetRawButton(JoystickMap::HANG_ARM_DOWN_BUTTON_ID)) {
		hangMotor.Set(speed);
	}
	else {
		hangMotor.Set(0);
	}
}

void Robot::PerformAccurateAim() {
	if (!prevAccurateAimButtonPressed) {
		if (accurateAim != nullptr) {
			delete accurateAim;
		}
		accurateAim = new AccurateAim(&networkTablesManager, &drivetrain, 1, 1);
	}

	if (!accurateAim->GetIsFinished()) {
		accurateAim->Run();
	}
}

void Robot::PerformQuickAim() {

}

void Robot::TestPID() {
	if (!prevAccurateAimButtonPressed) {
		if (testRotate != nullptr) {
			delete testRotate;
		}
		testRotate = new RotateToAngle(&drivetrain, GlobalConstants::PI / 2, 1);
	}

	if (!testRotate->GetIsFinished()) {
		testRotate->Run();
	}
}

void Robot::TestController() {
	frc::SmartDashboard::PutBoolean("intake in", gamepad.GetRawButton(GamepadMap::INTAKE_IN_BUTTON_ID));
	frc::SmartDashboard::PutBoolean("shoot", gamepad.GetRawButton(GamepadMap::SHOOT_BUTTON_ID));
	frc::SmartDashboard::PutBoolean("accurate aim", gamepad.GetRawButton(GamepadMap::ACCURATE_AIM_BUTTON_ID));
	frc::SmartDashboard::PutBoolean("quick aim", gamepad.GetRawButton(GamepadMap::QUICK_AIM_BUTTON_ID));

	frc::SmartDashboard::PutNumber("outtake", gamepad.GetRawAxis(GamepadMap::OUTTAKE_AXIS_ID));
	frc::SmartDashboard::PutNumber("conveyor", gamepad.GetRawAxis(GamepadMap::CONVEYOR_AXIS_ID));
	frc::SmartDashboard::PutNumber("intake out", gamepad.GetRawAxis(GamepadMap::INTAKE_OUT_TRIGGER_AXIS));

	frc::SmartDashboard::PutNumber("POV", gamepad.GetPOV());
}