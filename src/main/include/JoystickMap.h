#pragma once

class JoystickMap {
	private:
		//Button IDs
		const static int TRIGGER_BUTTON_ID = 1;
		const static int SIDE_BUTTON_ID = 2;
		const static int UPPER_LEFT_BUTTON_ID = 5;
		const static int LOWER_LEFT_BUTTON_ID = 3;
		const static int UPPER_RIGHT_BUTTON_ID = 6;
		const static int LOWER_RIGHT_BUTTON_ID = 4;
		const static int BASE_UPPER_LEFT_BUTTON_ID = 7;
		const static int BASE_UPPER_RIGHT_BUTTON_ID = 8;
		
		//Axis IDs
		const static int SLIDER_AXIS_ID = 3;

	public:
		const static int JOYSTICK_ID = 0;

		//Button function IDs
		const static int INCREASE_SPEED_BUTTON_ID = TRIGGER_BUTTON_ID;
		const static int DECREASE_SPEED_BUTTON_ID = SIDE_BUTTON_ID;

		//Axis function IDs
		const static int INVERT_AXIS_ID = SLIDER_AXIS_ID;
};