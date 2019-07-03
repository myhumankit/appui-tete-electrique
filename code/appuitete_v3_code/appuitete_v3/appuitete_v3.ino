
#include "cli.h"
#include "config.h"


#include "command.h"


// task definition for periodic scheduling 1ms
//void motorControl(Task* me);
//Task schedule (1, motorControl);



void setup() {

  // intialize command
  cli_open ();
  
  // initialize motor
  load_config ();
  get_stepper()->setMaxSpeed (get_speed());
  get_stepper()->setAcceleration (get_accel());
  // initialize led
  pinMode(LED, OUTPUT);
  digitalWrite (LED, LOW);

  // initialize buttons
  pinMode(BTN_RIGHT, INPUT);
  pinMode(BTN_LEFT, INPUT);

  // stepper microstep
  pinMode (MOTOR_MS1, OUTPUT),
  pinMode (MOTOR_MS2, OUTPUT);
  digitalWrite (MOTOR_MS1, LOW); // todo place config in config.h
  digitalWrite (MOTOR_MS2, LOW);

  //endstop
  pinMode (ENDSTOP_LEFT, INPUT),
  pinMode (ENDSTOP_RIGHT, INPUT);
  
  
  // run scheduler
  //SoftTimer.add(&schedule);

}

// function :SensorLeft
//
// Description :
// return te logic state of the left sensor
//
// Return :
// true if the left sensor is active. Otherwise false
boolean SensorLeft ()
{
  if (get_force_left () > 0)
    return (true);
  return (digitalRead (BTN_LEFT)== BTN_LEFT_ACTIVE_STATE ? true : false);
}

// function :SensorRight
//
// Description :
// return te logic state of the right sensor
//
// Return :
// true if the right sensor is active. Otherwise false
boolean SensorRight()
{
  if (get_force_right () > 0)
    return (true);
  return (digitalRead (BTN_RIGHT) == BTN_RIGHT_ACTIVE_STATE ? true : false);
}

// function :EndStopLeft
//
// Description :
// return the logic state of the left endstop sensor
//
// Return :
// true if the left endstop is active. Otherwise false
boolean EndStopLeft ()
{
  return (digitalRead (ENDSTOP_LEFT) == ENDSTOP_LEFT_STATE ? true : false); 
}

// function :EndStopRight
//
// Description :
// return the logic state of the right endstop sensor
//
// Return :
// true if the right endstop is active. Otherwise false
boolean EndStopRight ()
{
  return (digitalRead (ENDSTOP_RIGHT) == ENDSTOP_RIGHT_STATE ?  true : false); 
}

int RIGHT_MOVE = 1;
int LEFT_MOVE = -1;
int STOP_MOVE = 0;

//void turnOn(Task* me)
//{

//}


// Function: motorControl
//
// Description :
// The function is called every 1 ms. check command sensor and enstop and control the motor
//
// 
//void motorControl(Task* me)
void loop ()
{
  AccelStepper *pstepper = get_stepper ();
  
  // put your main code here, to run repeatedly:

  int step = 0;
  // decide move
  int move = STOP_MOVE;

  boolean right = SensorRight ();
  boolean left = SensorLeft ();
  
  boolean endl = EndStopLeft ();
  boolean endr = EndStopRight ();

 
  
 if (endr || endl)
  digitalWrite (LED, HIGH);
  else
  digitalWrite (LED,LOW);
 
 //endr = false;
 //endl=false;
  if (right == left)
  {
    move = STOP_MOVE;
    
    //digitalWrite(LED, LOW);
  }
  else if (right==true)
  {
    if (endr)
    {
      move=STOP_MOVE;
    }
    else
    {
      move = RIGHT_MOVE;
      pstepper->move (20000);
      //digitalWrite(LED, HIGH);
    }
  }
  else if (left == true)
  {
    if (endl)
    {
      move=STOP_MOVE;
    }
    else
    {
      move = LEFT_MOVE;
      pstepper->move(-20000);
      //digitalWrite(LED, HIGH);
    }
  }

  // motor control
  if (move != STOP_MOVE)
  {
    pstepper->run();
  }
  else
  {
    //stepper1.disableOutputs();
    pstepper->setSpeed(0);
    pstepper->setCurrentPosition (0);
  }

  // process command
   CLI.process();
}


