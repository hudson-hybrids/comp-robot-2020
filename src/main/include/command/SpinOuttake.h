#pragma once

#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

#include <frc/Encoder.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/SimpleMotorFeedforward.h>

#include <units/units.h>

#include "RobotMap.h"
#include "GlobalConstants.h"
#include "command/Command.h"

using ctre::phoenix::motorcontrol::can::WPI_VictorSPX;

class SpinOuttake: Command {
	private:
		const static double S;
		const static double V;
		const static double A;

		const double TARGET_SPEED_IN_PER_S;
		const double SPEED_TOLERANCE_IN_PER_S;
		
		//static frc::SimpleMotorFeedforward<units::inches> feedForwardController;

		static frc::Encoder outtakeEncoder;
		static bool encoderInitialized;

		WPI_VictorSPX *outtakeMotor;

		void InitEncoder();

	public:
		SpinOuttake(WPI_VictorSPX *outtakeMotor, const double TARGET_SPEED_IN_PER_S, const double SPEED_TOLERANCE_IN_PER_S);

		void Run() override;
		void Stop();
};