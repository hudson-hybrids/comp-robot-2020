#pragma once

class RobotMap {
	public:
		const static int FRONT_RIGHT_MOTOR = 4;
		const static int BACK_RIGHT_MOTOR = 0;
		const static int FRONT_LEFT_MOTOR = 5;
		const static int BACK_LEFT_MOTOR = 6;

		const static int PI_RESET_PIN = 0;
		const static int LIGHT_PIN = 1;

		const static int TOP_SONAR_SENSOR = 0;
		const static int BOTTOM_SONAR_SENSOR = 1;

		const static int LEFT_DRIVE_ENCODER_A = 2;
		const static int LEFT_DRIVE_ENCODER_B = 3;
		const static int RIGHT_DRIVE_ENCODER_A = 4;
		const static int RIGHT_DRIVE_ENCODER_B = 5;
};