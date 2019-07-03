#include "command.h"
#include "cli.h"
#include "config.h"

CLI_COMMAND(AccelFunc);
CLI_COMMAND(SpeedFunc);
CLI_COMMAND(ForceCommandFunc);
CLI_COMMAND(EndStopFunc);
CLI_COMMAND(SaveFunc);
CLI_COMMAND(helpFunc);
CLI_COMMAND(connectFunc);

CLI_COMMAND(connectFunc) {
    dev->println("Welcome to the CLI test.");
    dev->println("Type 'help' to list commands.");
    dev->print ("EEPROM MAGIC:");
    dev->println (get_eeprom_magic(), HEX);
    dev->println();
    dev->printPrompt();
}

CLI_COMMAND(helpFunc) {
    dev->println("help - display command list");
    dev->println("accel [250,5000] - set acceleration (step/s/s");
    dev->println("speed [100, 3000] - set speed (step/s)");
    dev->println("save  - save options in EEPROM");
    dev->println("force  - force right/left command state");
    
    
    return 0;
}

CLI_COMMAND(AccelFunc) {
    if (argc == 1) {
        dev->print("Accel:");
        dev->println(get_accel());
        return 0;
    }  
    else if (argc == 2)
    {
        int accel = atoi (argv[1]);
        set_accel (accel);
        get_stepper ()->setAcceleration (accel);
        dev->print("Accel:");
        dev->println(get_accel());
        return (0);  
    }
    else
    {
       dev->println("Usage: accel - display current acceleration");
       dev->println("Usage: accel 1000- set current acceleration to 1000");
        return 10;
    }
    
  return (0);
}
CLI_COMMAND(SpeedFunc) {
    if (argc == 1) {
        dev->print("Speed:");
        dev->println(get_speed());
        return 0;
    }  
    else if (argc == 2)
    {
        int speed = atoi (argv[1]);
        set_speed (speed);
        get_stepper()->setMaxSpeed (speed);
        dev->print("Speed:");
        dev->println(get_speed());
        return (0);  
    }
    else
    {
       dev->println("Usage: speed - display current speed");
       dev->println("Usage: speed 100- set current speed to 100");
        return 10;
    }
    
  return (0);
    
}

CLI_COMMAND(SaveFunc)
{
  if (argc != 1)
  {
      dev->println("Usage: save - Save options in EEPROM");
      return 10;
  }
  else
  {
    save_config ();
    dev->println("options saved");
  }
  return (0);
}

CLI_COMMAND(ForceCommandFunc)
{
  if (argc == 2)
  {
    int dir = atoi(argv[1]);
    if (dir == 0)
    {
      set_force_right (0);
      set_force_left (0);
    }
    else 
    {
      set_force_right (dir > 0 ? 1:0);
      set_force_left (dir > 0 ? 0:1);
    }
    return (0);   
  }
  else
  {
    dev->println("Usage: force [-1:0:1]- force right/left input command");
      return 10;
  }
}


void cli_open ()
{
    Serial.begin(9600);
    CLI.setDefaultPrompt("> ");
    CLI.onConnect(connectFunc);

    
    CLI.addCommand("help", helpFunc);
    CLI.addCommand("accel", AccelFunc);
    CLI.addCommand("speed", SpeedFunc);
    CLI.addCommand("save", SaveFunc);
    CLI.addCommand("force", ForceCommandFunc);
    

    CLI.addClient(Serial);
}

void cli_close ()
{
}


