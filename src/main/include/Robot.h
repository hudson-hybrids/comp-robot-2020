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
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>

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
#include <frc/DoubleSolenoid.h>
#include <frc/Timer.h>

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"

#include <cameraserver/CameraServer.h>

#include <rev/ColorSensorV3.h>
#include <rev/ColorMatch.h>

#include "RobotMap.h"
#include "JoystickMap.h"
#include "GamepadMap.h"
#include "command/Drive.h"
#include "CommandScheduler.h"
#include "command/MoveToPosition.h"
#include "command/MoveLength.h"
#include "command/RotateToAngle.h"
#include "command/AccurateAim.h"
#include "command/QuickAim.h"
#include "command/SpinOuttake.h"
#include "command/MoveIntake.h"
#include "NetworkTablesManager.h"
#include "AutoControl.h"

using namespace ctre::phoenix::motorcontrol;

class Robot: public frc::TimedRobot {
	private:
		static constexpr frc::I2C::Port i2cPort = frc::I2C::Port::kOnboard;

		const std::string DEFAULT_AUTO_MODE_NAME = "default";
		const std::string CUSTOM_AUTO_MODE_NAME = "custom";

		double maxOuttakeSpeed = 1.0;
		const double CONVEYOR_SPEED = 0.3;
		const double INTAKE_SPEED = 0.21;
		const double MAX_HANG_ARM_SPEED = 0.4;

		frc::SendableChooser<std::string> autoModeChooser;
		std::string selectedAutoMode;

		frc::Timer autoTimer;
		frc::Timer outtakeTimer;

		Drivetrain drivetrain;

		can::WPI_TalonSRX outtakeMotor_Talon{RobotMap::OUTTAKE_MOTOR_TALON};
		can::WPI_VictorSPX outtakeMotor_Victor{RobotMap::OUTTAKE_MOTOR_VICTOR};
		can::WPI_VictorSPX hangMotor{RobotMap::HANG_ARM_MOTOR};
		can::WPI_VictorSPX intakeMotor{RobotMap::INTAKE_MOTOR};
		can::WPI_VictorSPX hangPullMotor1{RobotMap::HANG_PULL_MOTOR_1};
		can::WPI_VictorSPX hangPullMotor2{RobotMap::HANG_PULL_MOTOR_2};
		can::WPI_VictorSPX conveyorMotor{RobotMap::CONVEYOR_MOTOR};

		frc::Joystick joystick{JoystickMap::ID};
		frc::Joystick gamepad{GamepadMap::ID};

		//rev::ColorSensorV3 colorSensor{i2cPort};

		NetworkTablesManager networkTablesManager;

		frc::DoubleSolenoid hangSolenoid{RobotMap::HANG_SOLENOID_FORWARD, RobotMap::HANG_SOLENOID_REVERSE};
		frc::DoubleSolenoid intakeSolenoid{RobotMap::INTAKE_SOLENOID_FORWARD, RobotMap::INTAKE_SOLENOID_REVERSE};

		double ySpeedMultiplier = 0.6;
		double zSpeedMultiplier = 0.48;

		//frc::AnalogInput topSonarSensor{RobotMap::TOP_SONAR_SENSOR};
		//frc::AnalogInput bottomSonarSensor{RobotMap::BOTTOM_SONAR_SENSOR};
		frc::DigitalOutput resetPin{RobotMap::PI_RESET_PIN};
		frc::DigitalOutput lightPin{RobotMap::LIGHT_PIN};

		CommandScheduler *autoScheduler = nullptr;

		RotateToAngle *testRotate = nullptr;
		MoveLength *testMove = nullptr;
		AccurateAim *accurateAim = nullptr;
		QuickAim *quickAim = nullptr;

		bool prevAccurateAimButtonPressed = false;
		bool prevQuickAimButtonPressed = false;
		bool prevShootButtonPressed = false;

		void JoystickDrive();
		void ControlDrive();

		void ControlOuttake();

		void ControlIntake();
		void ControlIntakePistons();

		void ControlConveyor();

		void ControlHangPistons();
		void ControlHangArm();
		void ControlHangPull();

		void ControlShoot();
		void PerformAccurateAim();
		void PerformQuickAim();

		void AutoMoveIntake();

		void TestRotatePID();
		void TestMovePID();
		void TestController();

		void PerformSafeAutoInit();
		void PerformSafeAutoPeriodic();
		void PerformUntestedAutoInit();
		void PerformUntestedAutoPeriodic();

	public:
		void RobotInit() override;
		void RobotPeriodic() override;
		void AutonomousInit() override;
		void AutonomousPeriodic() override;
		void TeleopInit() override;
		void TeleopPeriodic() override;
		void TestPeriodic() override;
};
