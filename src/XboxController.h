// Xbox Controller Buttons

class XboxController {

	static const int LEFT_JOYSTICK_X = 1;
	static const int LEFT_JOYSTICK_Y = 2;
	static const int RIGHT_JOYSTICK_X = 4;
	static const int RIGHT_JOYSTICK_Y = 5;
	
	static const int BTN_A = 1;
	static const int BTN_B = 2;
	static const int BTN_X = 3;
	static const int BTN_Y = 4;
	static const int BTN_RB = 5;
	static const int BTN_LB = 6;
	static const int BTN_BACK = 7;
	static const int BTN_START = 8;

};

/* XBox controller info:
		Button A: 1
	    Button B: 2
	    Button X: 3
	    Button Y: 4
	    Button LB: 5
	    Button RB: 6
	    Button LT: Range 0 to 1.000 (stick.GetTrigger())
	    Button RT: Range 0 to -1.000 (stick.GetTrigger())
	    Button Back: 7
	    Button Start: 8
	    Left Axis press: 9
	       X-Axis: -1.000 to 1.000 (stick.GetX())
	       Y-Axis: -1.000 to 1.000 (stick.GetY())
	    Right Axis press: 10
	       X-Axis: -1.000 to 1.000 (stick.GetTwist())
	       Y-Axis:
*/
