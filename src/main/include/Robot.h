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
		const std::string DEFAULT_AUTO_MODE_NAME = "default";
		const std::string CUSTOM_AUTO_MODE_NAME = "custom";

		frc::SendableChooser<std::string> autoModeChooser;
		std::string selectedAutoMode;

		WPI_VictorSPX frontLeftMotor{RobotMap::FRONT_LEFT_MOTOR_ID};
		WPI_VictorSPX backLeftMotor{RobotMap::BACK_LEFT_MOTOR_ID};
		WPI_VictorSPX frontRightMotor{RobotMap::FRONT_RIGHT_MOTOR_ID};
		WPI_VictorSPX backRightMotor{RobotMap::BACK_RIGHT_MOTOR_ID};

		frc::SpeedControllerGroup leftGroup{frontLeftMotor, backLeftMotor};
		frc::SpeedControllerGroup rightGroup{frontRightMotor, backRightMotor};

		frc::DifferentialDrive differentialDrive{leftGroup, rightGroup};

		frc::Joystick joystick{JoystickMap::JOYSTICK_ID};

		double ySpeedMultiplier = 0.6;
		double zSpeedMultiplier = 0.48;

		void Drive();
};
