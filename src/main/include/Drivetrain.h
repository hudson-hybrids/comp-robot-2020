/*
Make class called Drivetrain that contains:
	-Four WPI_VictorSPX motor controller objects
	-Two SpeedControllerGroup objects
	-One DifferentialDrive object
	-A constructor that sets the four motor controller IDs
*/

#pragma once

#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>
#include "RobotMap.h"

using ctre::phoenix::motorcontrol::can::WPI_VictorSPX;

class Drivetrain {
	
	public:

		WPI_VictorSPX frontLeftMotor;
		WPI_VictorSPX frontRightMotor;
		WPI_VictorSPX backLeftMotor;
		WPI_VictorSPX backRightMotor;

		frc::SpeedControllerGroup leftDrive;
		frc::SpeedControllerGroup rightDrive;

		frc::DifferentialDrive differentialDrive; 
	
		Drivetrain();
	
};
