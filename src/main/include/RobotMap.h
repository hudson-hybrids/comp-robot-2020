#pragma once

class RobotMap {
	public:
		const static int FRONT_RIGHT_MOTOR = 4;
		const static int BACK_RIGHT_MOTOR = 0;
		const static int FRONT_LEFT_MOTOR = 5;
		const static int BACK_LEFT_MOTOR = 6;
		const static int OUTTAKE_MOTOR_TALON = 9;
		const static int OUTTAKE_MOTOR_VICTOR = 2;
		const static int HANG_MOTOR = 9;
		const static int INTAKE_MOTOR = 1;
		const static int CONVEYOR_MOTOR = 3;

		const static int PI_RESET_PIN = 0;
		const static int LIGHT_PIN = 1;

		const static int TOP_SONAR_SENSOR = 0;
		const static int BOTTOM_SONAR_SENSOR = 1;

		const static int LEFT_DRIVE_ENCODER_A = 8;
		const static int LEFT_DRIVE_ENCODER_B = 9;
		const static int RIGHT_DRIVE_ENCODER_A = 6;
		const static int RIGHT_DRIVE_ENCODER_B = 7;
		const static int OUTTAKE_ENCODER_A = 4;
		const static int OUTTAKE_ENCODER_B = 5;

		const static int HANG_SOLENOID_FORWARD = 0;
		const static int HANG_SOLENOID_REVERSE = 3;
		const static int INTAKE_SOLENOID_FORWARD = -1;
		const static int INTAKE_SOLENOID_REVERSE = -1;
};