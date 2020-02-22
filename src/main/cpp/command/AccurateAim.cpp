#include "command/AccurateAim.h"

AccurateAim::AccurateAim(NetworkTablesManager *networkTablesManager, Drivetrain *drivetrain, const double LINEAR_TOLERANCE_in, const double ANGULAR_TOLERANCE_in) {
	const double IDEAL_SHOOTING_X_TRANSLATION = 0;
	const double IDEAL_SHOOTING_Z_TRANSLATION = 0;

	const double IDEAL_SHOOTING_Y_ROTATION = 0;

	VisionProcessingData visionProcessingData = networkTablesManager->GetVisionProcessingData();
	moveToPosition = MoveToPosition(
		drivetrain, 
		IDEAL_SHOOTING_X_TRANSLATION - visionProcessingData.ROBOT_X_TRANSLATION,
		IDEAL_SHOOTING_Z_TRANSLATION - visionProcessingData.ROBOT_Z_TRANSLATION,
		-visionProcessingData.ROBOT_Y_ROTATION,
		LINEAR_TOLERANCE_in,
		ANGULAR_TOLERANCE_in
	);
}

void AccurateAim::Run() {
	if (isFinished) {
		std::cout << "WARNING > CALL TO Run ON FINISHED AccurateAim" << std::endl;
	}
	else {
		moveToPosition.Run();

		if (moveToPosition.GetIsFinished()) {
			isFinished = true;
		}
	}
}