#pragma once

#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

#include <frc/Encoder.h>
#include <frc/Timer.h>

#include <units/units.h>

#include "RobotMap.h"
#include "GlobalConstants.h"
#include "command/Command.h"

using namespace ctre::phoenix::motorcontrol;

class SpinOuttake: Command {
	private:
		double targetSpeed_unitsPer100ms = 0;
		bool timerStarted = false;
		frc::Timer timer;

		can::WPI_TalonSRX *outtakeMotor_Talon = nullptr;
		can::WPI_VictorSPX *outtakeMotor_Victor = nullptr;

	public:
		SpinOuttake(can::WPI_TalonSRX *outtakeMotor_Talon, can::WPI_VictorSPX *outtakeMotor_Victor);
		SpinOuttake(can::WPI_TalonSRX *outtakeMotor_Talon, can::WPI_VictorSPX *outtakeMotor_Victor, double targetSpeed_RPM);

		void SetSpeed(double targetSpeed_RPM);
		void Run() override;
		void Stop();
};