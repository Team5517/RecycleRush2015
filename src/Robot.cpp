#include "WPILib.h"
#include "XboxController.h"

class Robot: public SampleRobot
{

	LiveWindow *lw;
	RobotDrive robot;
	Joystick controller;
	Compressor compressor;
	DoubleSolenoid armSolenoid;

	// Motor PWM Ports
	int const LEFT_DRIVE_MOTOR_1 = 0;
	int const LEFT_DRIVE_MOTOR_2 = 1;
	int const RIGHT_DRIVE_MOTOR_1 = 2;
	int const RIGHT_DRIVE_MOTOR_2 = 3;

	// Controller USB Port
	int const XBOX_CONTROLLER_PORT = 1;

	// Buttons
	int const BTN_ARM_UP = XboxController::BTN_B;
	int const BTN_ARM_DOWN = XboxController::BTN_A;

	// Pneumatics
	int const COMPRESSOR_PORT = 1;
	int const ARM_SOLENOID_1 = 0;
	int const ARM_SOLENOID_2 = 1;

public:

	Robot() :
		lw(NULL),
		robot(LEFT_DRIVE_MOTOR_1, LEFT_DRIVE_MOTOR_2, RIGHT_DRIVE_MOTOR_1, RIGHT_DRIVE_MOTOR_1),
		controller(XBOX_CONTROLLER_PORT),
		compressor(COMPRESSOR_PORT),
		armSolenoid(ARM_SOLENOID_1, ARM_SOLENOID_2)
	{
		robot.SetExpiration(0.1);
	}

	void RobotInit() {
		lw = LiveWindow::GetInstance();
		compressor.Start();
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{

		robot.TankDrive(
			controller.GetRawAxis(XboxController::LEFT_JOYSTICK_X),
			controller.GetRawAxis(XboxController::RIGHT_JOYSTICK_X)
		);

		if(controller.GetRawButton(BTN_ARM_UP) == true) {
			armSolenoid.Set(DoubleSolenoid::kForward);
		}
		else if(controller.GetRawButton(BTN_ARM_UP) == true) {
			armSolenoid.Set(DoubleSolenoid::kReverse);
		}
		else {
			armSolenoid.Set(DoubleSolenoid::kOff);
		}

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
