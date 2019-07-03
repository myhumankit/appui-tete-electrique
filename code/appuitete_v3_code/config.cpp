
#include <EEPROM.h>
#include "config.h"

static int _speed = MAX_SPEED;
static int _accel = MAX_ACCEL;

// stepper configuration
AccelStepper _stepper1(AccelStepper::DRIVER, MOTOR_STEP, MOTOR_DIR);

void set_speed (int s)
{
	_speed = s;
}
int get_speed (void)
{
	return (_speed);
}

void set_accel (int a)
{
	_accel = a;
}
int get_accel (void)
{
	return (_accel);
}

AccelStepper* get_stepper ()
{
	return &_stepper1;
}

static int _fr = 0;
static int _fl = 0;
int get_force_left ()
{
  return (_fl);
}
void set_force_left (int f)
{
  _fl =f;
}
int get_force_right ()
{
  return (_fr);
}
void set_force_right (int r)
{
  _fr = r;
}

void save_config ()
{
  long magic = 0x1234FF00;
  int eeAddress = 0;

  EEPROM.put(eeAddress, magic);
  eeAddress += sizeof(magic);
  EEPROM.put(eeAddress, _speed);
  eeAddress += sizeof(_speed);
  EEPROM.put(eeAddress, _accel);
  eeAddress += sizeof(_accel);
}

static long _magic =0;

int  load_config ()
{
  
  int eeAddress = 0;
  EEPROM.get(eeAddress, _magic);  
  if (_magic != 0x1234FF00)
    return (0);
  eeAddress += sizeof(_magic);
  EEPROM.get(eeAddress, _speed);  
  eeAddress += sizeof(_speed);
  EEPROM.get(eeAddress, _accel);  
  eeAddress += sizeof(_accel);

  return (1);
}

long get_eeprom_magic ()
{
  return (_magic);
}

