#include "WPILib.h"
#include "XboxController.h"
#include "MainDefines.h"

class Robot: public SampleRobot
{

	LiveWindow *lw;
	RobotDrive robotDrive;
	Joystick controller;
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
		controller(CONTROLLER_USB_PORT),
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
			DriveRobot();
			ArmControl();
		} // end while
	}


	void DriveRobot() {
		robotDrive.TankDrive(
			-controller.GetRawAxis(XboxController::LEFT_JOYSTICK_Y),
			-controller.GetRawAxis(XboxController::RIGHT_JOYSTICK_Y)
		);
		robotDrive.ArcadeDrive();
	}

	void ArmControl() {
		if(controller.GetRawButton(BTN_ARM_UP) == true) {
			ArmUp();
		}
		else if(controller.GetRawButton(BTN_ARM_DOWN) == true) {
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
