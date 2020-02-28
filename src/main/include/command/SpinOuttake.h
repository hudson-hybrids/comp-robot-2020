#pragma once

#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

#include <frc/Encoder.h>
#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <units/units.h>

#include "RobotMap.h"
#include "GlobalConstants.h"
#include "command/Command.h"

using namespace ctre::phoenix::motorcontrol;

class SpinOuttake {
	public:
		static void Run(can::WPI_TalonSRX *outtakeMotor_Talon, can::WPI_VictorSPX *outtakeMotor_Victor, double targetSpeed_unitsPer100ms);
		static void Stop(can::WPI_TalonSRX *outtakeMotor_Talon, can::WPI_VictorSPX *outtakeMotor_Victor);
};