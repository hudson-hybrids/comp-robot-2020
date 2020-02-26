#include "VisionProcessingData.h"

VisionProcessingData::VisionProcessingData(
	const double ROBOT_X_TRANSLATION, 
	const double ROBOT_Y_TRANSLATION, 
	const double ROBOT_Z_TRANSLATION,
	const double ROBOT_X_ROTATION,
	const double ROBOT_Y_ROTATION,
	const double ROBOT_Z_ROTATION
):
ROBOT_X_TRANSLATION(ROBOT_X_TRANSLATION),
ROBOT_Y_TRANSLATION(ROBOT_Y_TRANSLATION),
ROBOT_Z_TRANSLATION(ROBOT_Z_TRANSLATION),
ROBOT_X_ROTATION(ROBOT_X_ROTATION),
ROBOT_Y_ROTATION(ROBOT_Y_ROTATION),
ROBOT_Z_ROTATION(ROBOT_Z_ROTATION) {}