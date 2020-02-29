#pragma once

#include <cmath>

class VisionProcessingData {
	public:
		const double ROBOT_X_TRANSLATION;
		const double ROBOT_Y_TRANSLATION;
		const double ROBOT_Z_TRANSLATION;

		const double ROBOT_X_ROTATION;
		const double ROBOT_Y_ROTATION;
		const double ROBOT_Z_ROTATION;

		VisionProcessingData(
			const double ROBOT_X_TRANSLATION, 
			const double ROBOT_Y_TRANSLATION, 
			const double ROBOT_Z_TRANSLATION,
			const double ROBOT_X_ROTATION,
			const double ROBOT_Y_ROTATION,
			const double ROBOT_Z_ROTATION
		);

		double GetDistanceFromTarget();
};