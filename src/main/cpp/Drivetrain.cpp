#include "Drivetrain.h"

Drivetrain::Drivetrain(void): 
frontLeftMotor(RobotMap::FRONT_LEFT_MOTOR), 
frontRightMotor(RobotMap::FRONT_RIGHT_MOTOR), 
backLeftMotor(RobotMap::BACK_LEFT_MOTOR), 
backRightMotor(RobotMap::BACK_RIGHT_MOTOR), 
leftDrive(frontLeftMotor, backLeftMotor), 
rightDrive(frontRightMotor, backRightMotor), 
differentialDrive(leftDrive, rightDrive) {}