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
		robotDrive.SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
		robotDrive.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
		robotDrive.SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
		robotDrive.SetInvertedMotor(RobotDrive::kRearRightMotor, true);
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
			robotDrive.ArcadeDrive(rightJoystick);
			ArmControl();
		} // end while
	}

	void ArmControl() {
		if(BTN_ARM_UP == true) {
			ArmUp();
		}
		else if(BTN_ARM_DOWN == true) {
			ArmDown();
		}
		else {
			armSolenoid.Set(DoubleSolenoid::kOff);
		}
	}

	void ArmUp() {
		armSolenoid.Set(DoubleSolenoid::kForward);
	}

	void ArmDown() {
		armSolenoid.Set(DoubleSolenoid::kReverse);
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
