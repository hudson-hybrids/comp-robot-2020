#include "command/Command.h"

class RotateToAngle: public Command {
	private:
		PIDController 

	public:
		RotateToAngle(const double P, const double I, const double D);

		void Run() override;
};