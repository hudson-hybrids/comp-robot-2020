#include <frc/controller/PIDController.h>
#include <frc/Encoder.h>

#include "command/Command.h"
#include "RobotMap.h"
#include "GlobalConstants.h"

class Drive: public Command {
	private:
		static frc::Encoder leftDriveEncoder;
		static frc::Encoder rightDriveEncoder;

		frc2::PIDController pidController;

	protected:
		Drive(const double P, const double I, const double D);

	public:
		static void InitEncoders();
};