#include "Drivetrain.h"

void Drivetrain::InitEncoders() {
	const double COUNTS_PER_REV = 360/* * 10.75*/;
	const double WHEEL_DIAMETER_in = 6;
	const double WHEEL_CIRCUMFERENCE = GlobalConstants::PI * WHEEL_DIAMETER_in;
	const double DISTANCE_PER_PULSE = WHEEL_CIRCUMFERENCE / COUNTS_PER_REV;

	leftEncoder.SetDistancePerPulse(DISTANCE_PER_PULSE);
	rightEncoder.SetDistancePerPulse(DISTANCE_PER_PULSE);
}

Drivetrain::Drivetrain(void): 
frontLeftMotor(RobotMap::FRONT_LEFT_MOTOR), 
frontRightMotor(RobotMap::FRONT_RIGHT_MOTOR), 
backLeftMotor(RobotMap::BACK_LEFT_MOTOR), 
backRightMotor(RobotMap::BACK_RIGHT_MOTOR), 
leftDrive(frontLeftMotor, backLeftMotor), 
rightDrive(frontRightMotor, backRightMotor), 
differentialDrive(leftDrive, rightDrive),
leftEncoder(RobotMap::LEFT_DRIVE_ENCODER_A, RobotMap::LEFT_DRIVE_ENCODER_B),
rightEncoder(RobotMap::RIGHT_DRIVE_ENCODER_A, RobotMap::RIGHT_DRIVE_ENCODER_B) {
	InitEncoders();
}