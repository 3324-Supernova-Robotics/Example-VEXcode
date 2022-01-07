/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
/*
int AutonNumber = 1; // Current autonomous routine

void pre_auton() {

  // . . .
  // Put more pre auton code here!
  // . . .

  // Setup
  color unselected_color = blue;
  color selected_color = red;
  Brain.Screen.setFont(monoM);
  Brain.Screen.setPenColor(purple);

  // Box variables
  int dist = 60;
  int start = 5;
  int y1 = 50; 
  int x2 = 50; 
  int y2 = 175;

  // Print 8 rectangles, shift each square alomg Y axis in multiples of dist
  for (int i = 0; i < 8; i++) {
    // Check what the currently selected autonomous mode is to change its color
    color box_color;
    if (AutonNumber-1 == i) box_color = selected_color;
    else box_color = unselected_color;
    
    // Print rectangle
    Brain.Screen.setPenColor(box_color);
    Brain.Screen.drawRectangle(start+(dist*i), y1, x2, y2, box_color);
  }

  while (true) {
    // Selected position
    int x = Brain.Screen.xPosition();
    int y = Brain.Screen.yPosition();

    // If your finger is within the y axis of the rectangles...
    if (y1 < y && y < y1+y2) {
      for (int i = 0; i < 8; i++) {
        // Check which x value your finger is within...
        if (start+(dist*i)<x && x<(dist*(i+1))-start) {
          Brain.Screen.setPenColor(unselected_color);
          Brain.Screen.drawRectangle(start+(dist*(AutonNumber-1)), y1, x2, y2, unselected_color); // Make the previously selected square unselected
          AutonNumber = i+1; // Update AutonNumber
          Brain.Screen.setPenColor(selected_color);
          Brain.Screen.drawRectangle(start+(dist*(AutonNumber-1)), y1, x2, y2, selected_color); // Change color of the new selected square 
        }
      }
    }

    // Print text
    Brain.Screen.setPenColor(selected_color);
    Brain.Screen.printAt(start, 30, "Current Auto: %d", AutonNumber);
    wait(20, msec);
    Brain.Screen.clearLine(1);
  }
}*/

int AutonNumber = 1;

void pre_auton() {

  // . . .
  // Put your pre auton code here!
  // . . .

  // Print 8 rectangles 
  for (int i = 0; i < 8; i++) {
    Brain.Screen.setPenColor(blue);
    Brain.Screen.drawRectangle(5+(60*i), 50, 50, 175, blue);
  }

  // Set font to monoM
  Brain.Screen.setFont(monoM); 

  while (true) {

    // Autonomous Selector
    // Selected position
    int x = Brain.Screen.xPosition(); // X position of finger
    int y = Brain.Screen.yPosition(); // Y position of finger

    // Check if finger is within vertical selection of the boxes
    if (50 < y && y < 50+175) {
      for (int i = 0; i < 8; i++) {
        // Check which x value the finger is within
        if (5+(60*i) < x && x < (60*(i+1))-5) {
          AutonNumber = i+1;
        }
      }
    }

    // Print AutonNumber to brain
    Brain.Screen.printAt(5, 30, "Current Auto: %d", AutonNumber); // %d is a formatting character that gets replaced with AutonNumber
    wait(20, msec);
    Brain.Screen.clearLine(1);
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  if (AutonNumber == 1) {
    // Call Auton 
  }
  else if (AutonNumber == 2) {
    // Call Auton 
  }
  else if (AutonNumber == 3) {
    // Call Auton 
  }
  else if (AutonNumber == 4) {
    // Call Auton 
  }
  else if (AutonNumber == 5) {
    // Call Auton 
  }
  else if (AutonNumber == 6) {
    // Call Auton 
  }
  else if (AutonNumber == 7) {
    // Call Auton 
  }
  else if (AutonNumber == 8) {
    // Call Auton 
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
