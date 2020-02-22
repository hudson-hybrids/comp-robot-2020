#pragma once

#include <string>

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"

#include "VisionProcessingData.h"

class NetworkTablesManager {
	private:
		std::shared_ptr<nt::NetworkTable> visionProcessingTable;

	public:
		NetworkTablesManager();

		VisionProcessingData GetVisionProcessingData();
};