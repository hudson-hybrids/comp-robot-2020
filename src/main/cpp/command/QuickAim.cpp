#include "command/QuickAim.h"

QuickAim::QuickAim(NetworkTablesManager *networkTablesManager, Drivetrain *drivetrain, const double ANGULAR_TOLERANCE_in) {
	const double IDEAL_SHOOTING_Y_ROTATION = 0;

	VisionProcessingData visionProcessingData = networkTablesManager->GetVisionProcessingData();

	rotateToAngle = new RotateToAngle(
		drivetrain,
		IDEAL_SHOOTING_Y_ROTATION - visionProcessingData.ROBOT_Y_ROTATION,
		1
	);
}

void QuickAim::Run() {
	if (isFinished) {
		std::cout << "WARNING > CALL TO Run ON FINISHED QuickAim" << std::endl;
	}
	else {
		rotateToAngle->Run();

		if (rotateToAngle->GetIsFinished()) {
			isFinished = true;
			delete rotateToAngle;
		}
	}
}