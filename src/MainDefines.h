/*
 * MainDefines.h
 *
 *  Created on: Feb 7, 2015
 *      Author: nathan
 */

#ifndef SRC_MAINDEFINES_
#define SRC_MAINDEFINES_

// Motor PWM Ports
#define LEFT_DRIVE_MOTOR_1       0
#define LEFT_DRIVE_MOTOR_2       1
#define RIGHT_DRIVE_MOTOR_1      2
#define RIGHT_DRIVE_MOTOR_2      3

// Controller USB Ports
#define LEFT_JOYSTICK_USB_PORT   0
#define RIGHT_JOYSTICK_USB_PORT  1

// Buttons
#define BTN_ARM_UP               rightJoystick.GetRawButton(JoystickPorts::TRIGGER)
#define BTN_ARM_DOWN             leftJoystick.GetRawButton(JoystickPorts::TRIGGER)

// Pneumatics
#define COMPRESSOR_PORT          1
#define ARM_SOLENOID_1           0
#define ARM_SOLENOID_2           1


#endif /* SRC_MAINDEFINES_ */
