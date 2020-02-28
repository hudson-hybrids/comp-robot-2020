#include "command/AccurateAim.h"

AccurateAim::AccurateAim(NetworkTablesManager *networkTablesManager, Drivetrain *drivetrain, const double LINEAR_TOLERANCE_in, const double ANGULAR_TOLERANCE_in):
LINEAR_TOLERANCE_in(LINEAR_TOLERANCE_in),
ANGULAR_TOLERANCE_in(ANGULAR_TOLERANCE_in) {
	this->networkTablesManager = networkTablesManager;
}

AccurateAim::~AccurateAim() {
	delete moveToPosition;
}

void AccurateAim::Run() {
	if (isFinished) {
		std::cout << "WARNING > CALL TO Run ON FINISHED AccurateAim" << std::endl;
	}
	else {
		if (isCollectingVisionData) {
			if (moveToPosition != nullptr) {
				delete moveToPosition;
				moveToPosition = nullptr;
			}

			visionDataSet.push_back(networkTablesManager->GetVisionProcessingData());

			if (visionDataSet.size() > 50) {
				isCollectingVisionData = false;

				const double VISION_DATA_TO_INCHES = 0;
				
				const double IDEAL_SHOOTING_X_TRANSLATION = 0;
				const double IDEAL_SHOOTING_Z_TRANSLATION = 0;

				const double IDEAL_SHOOTING_Y_ROTATION = 0;

				double totalTranslationX = 0;
				double totalTranslationZ = 0;
				double totalRotationY = 0;

				for (unsigned int i = 0; i < visionDataSet.size(); i++) {
					totalTranslationX += visionDataSet[i].ROBOT_X_TRANSLATION;
					totalTranslationZ += visionDataSet[i].ROBOT_Z_TRANSLATION;
					totalRotationY += visionDataSet[i].ROBOT_Y_ROTATION;
				}

				double avgTranslationX = totalTranslationX / visionDataSet.size();
				double avgTranslationZ = totalTranslationZ / visionDataSet.size();
				double avgRotationY = totalRotationY / visionDataSet.size();

				double displacementX_in = VISION_DATA_TO_INCHES * (IDEAL_SHOOTING_X_TRANSLATION - avgTranslationX);
				double displacementZ_in = VISION_DATA_TO_INCHES * (IDEAL_SHOOTING_Z_TRANSLATION - avgTranslationZ);

				moveToPosition = new MoveToPosition(
					drivetrain, 
					displacementX_in,
					displacementZ_in,
					-avgRotationY,
					LINEAR_TOLERANCE_in,
					ANGULAR_TOLERANCE_in
				);
			}
		}
		else {
			moveToPosition->Run();

			if (moveToPosition->GetIsFinished()) {
				isFinished = true;
			}
		}
	}
}