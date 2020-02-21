#include "NetworkTablesManager.h"

NetworkTablesManager::NetworkTablesManager() {
	nt::NetworkTableInstance ntInst = nt::NetworkTableInstance::GetDefault();
	ntInst.StartClientTeam(7486);
	visionProcessingTable = ntInst.GetTable("vision_processing");
}

VisionProcessingData NetworkTablesManager::GetVisionProcessingData() {
	const double ROBOT_X_TRANSLATION = visionProcessingTable->GetEntry("robot_x").GetDouble(0);
	const double ROBOT_Y_TRANSLATION = visionProcessingTable->GetEntry("robot_y").GetDouble(0);
	const double ROBOT_Z_TRANSLATION = visionProcessingTable->GetEntry("robot_z").GetDouble(0);

	const double ROBOT_X_ROTATION = visionProcessingTable->GetEntry("robot_x_rotation").GetDouble(0);
	const double ROBOT_Y_ROTATION = visionProcessingTable->GetEntry("robot_y_rotation").GetDouble(0);
	const double ROBOT_Z_ROTATION = visionProcessingTable->GetEntry("robot_z_rotation").GetDouble(0);

	return VisionProcessingData(
		ROBOT_X_TRANSLATION,
		ROBOT_Y_TRANSLATION,
		ROBOT_Z_TRANSLATION,
		ROBOT_X_ROTATION,
		ROBOT_Y_ROTATION,
		ROBOT_Z_ROTATION
	);
}