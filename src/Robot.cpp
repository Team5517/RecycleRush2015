#include "WPILib.h"
#include "XboxController.h"
#include "MainDefines.h"

class Robot: public IterativeRobot
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
	}

	/**
	 * Robot initialization method
	 * Called when robot is enabled
	 */
	void RobotInit() {
		lw = LiveWindow::GetInstance();
		compressor.Start();
	}

	/**
	 * Autonomous init
	 * Called when autonomous starts
	 */
	void AutonomousInit()
	{

	}

	/**
	 * Autonomous periodic
	 * Called every ~20ms on a loop during autonomous
	 */
	void AutonomousPeriodic()
	{

	}

	/**
	 * Teleop init
	 * Called when teleop starts
	 */
	void TeleopInit()
	{

	}

	/**
	 * Teleop periodic
	 * Called every ~20ms during teleop
	 */
	void TeleopPeriodic()
	{

		/*
		 * Robot drive system
		 */
		robotDrive.TankDrive(
			-controller.GetRawAxis(XboxController::LEFT_JOYSTICK_X),
			-controller.GetRawAxis(XboxController::RIGHT_JOYSTICK_X)
		);

		/*
		 * Operate the arm
		 */
		if(controller.GetRawButton(BTN_ARM_UP) == true) {
			armSolenoid.Set(DoubleSolenoid::kForward);
		}
		else if(controller.GetRawButton(BTN_ARM_DOWN) == true) {
			armSolenoid.Set(DoubleSolenoid::kReverse);
		}
		else {
			armSolenoid.Set(DoubleSolenoid::kOff);
		}

	}

	/**
	 * Called during test mode
	 */
	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
