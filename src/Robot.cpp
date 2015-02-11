#include "WPILib.h"
#include "JoystickPorts.h"
#include "MainDefines.h"

class Robot: public SampleRobot
{

	LiveWindow *lw;
	RobotDrive robotDrive;
	Joystick leftJoystick;
	Joystick rightJoystick;
	Compressor compressor;
	DoubleSolenoid armSolenoid;

public:

	/**
	 * Robot Constructor
	 * C++ initialization list
	 */
	Robot() :
		lw(NULL),
		robotDrive(LEFT_DRIVE_MOTOR_1, LEFT_DRIVE_MOTOR_2, RIGHT_DRIVE_MOTOR_1, RIGHT_DRIVE_MOTOR_2),
		leftJoystick(LEFT_JOYSTICK_USB_PORT),
		rightJoystick(RIGHT_JOYSTICK_USB_PORT),
		compressor(COMPRESSOR_PORT),
		armSolenoid(ARM_SOLENOID_1, ARM_SOLENOID_2)
	{
		robotDrive.SetExpiration(0.1);
		lw = LiveWindow::GetInstance();
		compressor.Start();
	}

	/**
	 * Autonomous mode
	 */
	void Autonomous()
	{
	}

	/**
	 * Teleop mode
	 */
	void OperatorControl()
	{
		robotDrive.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled())
		{
			/*
			 * Robot drive system
			 */
			robotDrive.TankDrive(
				-leftJoystick.GetRawAxis(JoystickPorts::Y_AXIS),
				-rightJoystick.GetRawAxis(JoystickPorts::Y_AXIS)
			);

			/*
			 * Operate the arm
			 */
			if(BTN_ARM_UP == true) {
				armSolenoid.Set(DoubleSolenoid::kForward);
			}
			else if(BTN_ARM_DOWN == true) {
				armSolenoid.Set(DoubleSolenoid::kReverse);
			}
			else {
				armSolenoid.Set(DoubleSolenoid::kOff);
			}

		} // end while
	}

	/**
	 * Test mode
	 */
	void Test()
	{
		while(IsTest() && IsEnabled()) {
			lw->Run();
		}
	}
};

START_ROBOT_CLASS(Robot);
