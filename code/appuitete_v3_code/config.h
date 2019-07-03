#ifndef __CONFIG_H
#define __CONFIG_H

#include <AccelStepper.h>
#include <MultiStepper.h>

///
///
/// Default values
///
///
#define MOTOR_MS1 11 // EASY DRIVER MS1 IO FROM ARDUINO
#define  MOTOR_MS2  10 // Easy Driver MS2 IO From Arduino

#define MOTOR_STEP 9 // EasyDriver STEP IO from Arduino (single step command)
#define MOTOR_DIR 8  // EasyDriver DIR IO from arduino (move direction)

#define LED 13 // Onboard arduino led for signaling

#define BTN_RIGHT 4 // Input for right movement
#define BTN_LEFT 5 // Input for left movement

#define BTN_RIGHT_ACTIVE_STATE LOW // Input state to consider BTN active
#define BTN_LEFT_ACTIVE_STATE LOW // Input state to consider BTN active


#define MAX_SPEED 50 // max speed in step/s
#define MAX_ACCEL 2500 // max acceleration in step / s / s

#define ENDSTOP_LEFT 7
#define ENDSTOP_RIGHT 6
#define ENDSTOP_LEFT_STATE LOW
#define ENDSTOP_RIGHT_STATE LOW


// global accessor
void set_speed (int s);
int get_speed (void);
void set_accel (int a);
int get_accel (void);
int get_force_left (void);
void set_force_left (int f);
int get_force_right (void);
void set_force_right (int r);
long get_eeprom_magic (void);

AccelStepper* get_stepper ();

void save_config ();
int load_config ();

  

#endif
