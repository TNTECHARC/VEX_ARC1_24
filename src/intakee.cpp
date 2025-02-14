#include "intakee.h"



double intakeTarget = 0;
bool intakeOn = false;


double kP = 0.08;  // Proportional gain
double kI = 0.0; // Integral gain
double kD = 0.1; // Derivative gain

// Variables for PID control
double error = 0;
double previousError = 0;
double integral = 0;
double derivative = 0;

// Target velocity for the motor

// Function to calculate PID output
void intakeePID() {
    error = intakeTarget - inrot.position(deg);
    integral += error;
    derivative = error - previousError;
    previousError = error;

    // Calculate PID output
    double output = (kP * error) + (kI * integral) + (kD * derivative);
    intake.spin(fwd, output, voltageUnits::volt);
}


double oneRot = 2310.18;
void intakee()
{
  bool stuck = false;
  while(1)
  {
    
    if(intakeOn)
    {
      intake.spin(fwd,100,pct);
      wait(300,msec);
      do 
      {              
        if(intake.velocity(pct) < 20)
        {
          stuck = !stuck;
          intakeOn = false;
        }
        wait(5, msec);                                                             
      } while (!(intakeOn == false));
      //waitUntil(intakeOn == false);
      intake.stop();
      if(!stuck)
        intakeTarget = ((((int)(inrot.position(deg) / oneRot))+1)*oneRot);
      else
        intakeTarget = (((int)(inrot.position(deg) / oneRot))*oneRot);
    }
    else
      intakeePID();


    wait(10,msec);
  }
}