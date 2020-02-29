#pragma once

class GamepadMap {
	private:
		//Button IDs
		const static int A_BUTTON_ID = 1;
		const static int B_BUTTON_ID = 2;
		const static int X_BUTTON_ID = 3;
		const static int Y_BUTTON_ID = 4;
		const static int LEFT_SHOULDER_BUTTON_ID = 5;
		const static int RIGHT_SHOULDER_BUTTON_ID = 6;
		const static int BACK_BUTTON_ID = 7;
		const static int START_BUTTON_ID = 8;
		const static int LEFT_JOYSTICK_BUTTON_ID = 9;
		const static int RIGHT_JOYSTICK_BUTTON_ID = 10;

		//Axis IDs
		const static int LEFT_JOYSTICK_X_AXIS_ID = 0;
		const static int LEFT_JOYSTICK_Y_AXIS_ID = 1;
		const static int LEFT_TRIGGER_AXIS_ID = 2;
		const static int RIGHT_TRIGGER_AXIS_ID = 3;
		const static int RIGHT_JOYSTICK_X_AXIS_ID = 4;
		const static int RIGHT_JOYSTICK_Y_AXIS_ID = 5;
	
	public:
		const static int ID = 1;

		//Button function IDs
		const static int SHOOT_BUTTON_ID = Y_BUTTON_ID;
		const static int INTAKE_IN_BUTTON_ID = LEFT_SHOULDER_BUTTON_ID;
		const static int HANG_ARM_HOLD_BUTTON_ID = LEFT_JOYSTICK_BUTTON_ID;
		const static int PUSH_HANG_BUTTON_ID = A_BUTTON_ID;
		const static int PULL_HANG_BUTTON_ID = X_BUTTON_ID;
		const static int COORD_HANG_BUTTON_ID = B_BUTTON_ID;

		//Axis function IDs
		const static int OUTTAKE_AXIS_ID = RIGHT_JOYSTICK_Y_AXIS_ID;
		const static int HANG_ARM_AXIS_ID = LEFT_JOYSTICK_Y_AXIS_ID;
		const static int INTAKE_OUT_TRIGGER_AXIS = LEFT_TRIGGER_AXIS_ID;
};