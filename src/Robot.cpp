#include "WPILib.h"
#include "JoystickPorts.h"
#include "MainDefines.h"

/*
 * Autonomous Mode Selection
 * 0 = does nothing
 * 1 = DriveForwardAuton
 * 2 = OneToteAuton
 */
#define AUTON_MODE 2

class Robot: public SampleRobot
{

	LiveWindow *lw;
	RobotDrive robotDrive;
	Joystick leftJoystick;
	Joystick rightJoystick;
	Compressor compressor;
	DoubleSolenoid armSolenoid;
	Timer autonTimer;

	int autonStage = 0;

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
		compressor.Start();
		lw = LiveWindow::GetInstance();
	}

	/**
	 * Autonomous mode
	 */
	void Autonomous()
	{
		AutonInit();
		while(IsAutonomous() && IsEnabled()) {
			SelectAuton(AUTON_MODE);
			Wait(0.04);
		}
	}

	/**
	 * Every time autonomous starts
	 */
	void AutonInit() {
		autonStage = 0;
		SmartDashboard::PutNumber("Autonomous Mode", AUTON_MODE);
	}

	/**
	 * Select auton
	 */
	void SelectAuton(int AutonMode) {
		switch(AutonMode) {
			case 0:
				// do nothing
			break;
			case 1:
				DriveForwardAuton();
			break;
			case 2:
				OneToteAuton();
			break;
		}
	}

	/**
	 * Restarts the timer for auton
	 */
	void RestartAutonTimer() {
		autonTimer.Reset();
		autonTimer.Stop();
		autonTimer.Start();
	}

	/**
	 * DriveForwardAuton
	 * Drives forward into the auto zone and pivots 90 degrees right
	 */
	void DriveForwardAuton()
	{
		int time = autonTimer.Get();
		switch(autonStage) {
			case 0:
				ArmDown();
				autonTimer.Reset();
				autonTimer.Stop();
				autonStage = 1;
			break;
			case 1:
				autonTimer.Start();
				if(time < 1.5) {
					robotDrive.TankDrive(0.55, 0.55);
				}
				else {
					autonTimer.Reset();
					autonTimer.Stop();
					robotDrive.TankDrive(0.0, 0.0);
					autonStage = 2;
				}
			break;
			case 2:
				autonTimer.Start();
				if(time < 0.97) {
					robotDrive.TankDrive(0.6, -0.6);
				}
				else {
					robotDrive.TankDrive(0.0, 0.0);
					autonTimer.Reset();
					autonTimer.Stop();
					autonStage = 3;
				}
			break;
		}

	}

	/**
	 * Picks up first auton (yellow) tote and brings it into the auto zone
	 */
	void OneToteAuton()
	{
		int time = autonTimer.Get();
		switch(autonStage) {
			case 0:
				ArmDown();
				RestartAutonTimer();
				autonStage = 1;
			break;
			// lift arm
			case 1:
				if(time < 0.5) {
					ArmUp();
				}
				else {
					RestartAutonTimer();
					autonStage = 2;
				}
			break;
			// back up
			case 2:
				if(time < 0.5) {
					robotDrive.TankDrive(-0.5, -0.5);
				}
				else {
					RestartAutonTimer();
					autonStage = 3;
				}
			break;
			// turn 90 right
			case 3:
				if(time < 1.01) {
					robotDrive.TankDrive(0.57, -0.57);
				}
				else {
					RestartAutonTimer();
					autonStage = 4;
				}
			break;
			// drive forward
			case 4:
				if(time < 5) {
					robotDrive.TankDrive(0.65, 0.65);
				}
				else {
					RestartAutonTimer();
					autonStage = 5;
				}
			break;
			// turn 90 left
			case 5:
				if(time < 1.4) {
					robotDrive.TankDrive(0.5, -0.5);
				}
				else {
					RestartAutonTimer();
					autonStage = 6;
				}
			break;
			// lower arm
			case 6:
				ArmDown();
				RestartAutonTimer();
				autonStage = 7;
			break;
		}

	}

	/**
	 * Teleop mode
	 */
	void OperatorControl()
	{
		robotDrive.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled())
		{
			robotDrive.TankDrive(
				-leftJoystick.GetRawAxis(JoystickPorts::Y_AXIS),
				-rightJoystick.GetRawAxis(JoystickPorts::Y_AXIS)
			);
			ArmControl();
			Wait(0.04);
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
			ArmSolenoidOff();
		}
	}

	void ArmUp() {
		armSolenoid.Set(DoubleSolenoid::kForward);
	}

	void ArmDown() {
		armSolenoid.Set(DoubleSolenoid::kReverse);
	}

	void ArmSolenoidOff() {
		armSolenoid.Set(DoubleSolenoid::kOff);
	}

	/**
	 * Test mode
	 */
	void Test()
	{
		lw->Run();
		while(IsTest() && IsEnabled()) {
		}
	}
};

START_ROBOT_CLASS(Robot);
