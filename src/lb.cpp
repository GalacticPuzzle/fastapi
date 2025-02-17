#include "subsystems\lb.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "main.h" // IWYU pragma: keep
#include "../include/subsystems/initbot.hpp"
#include "pros/misc.h" // IWYU pragma: keep
#include "pros/rtos.hpp" // IWYU pragma: keep

// LADY BROWN CODE
// U change the position of each state by changing the number in states[numstates] = {};
const int numStates = 3;
// make sure these are in centidegrees (1 degree = 100 centidegrees)
int states[numStates] = {30000, 26800, 14000};  // Bigger number = closer to stowed
int currState = 0;                              // current state (index of the array)
int target = 30000;                             // this must be the same as whatever the stow state is!
// PID constants => should be left alone
double kP = 2;    //"Gas" pedal


// PID variables
double error = 0;        // difference between target and current position

double output = 0;       // final output to the lady brown

// moves the state back 1
void backState() {
  currState = (currState - 1 + numStates) % numStates;
  target = states[currState];
  // setting them to true "resets" the toggles
}

// moves the state forward 1
void nextState() {
  currState = (currState + 1) % numStates;
  target = states[currState];
  // setting them to true "resets" the toggles
}

// Actual logic for lady brown
void armDriver() {
    while (true) {
    // basically the button logic
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
            nextState();
        } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            backState();
        }

        error = target - arm_sensor.get_position();            
        output = (kP * error); // final output to the lady brown

        arm.move_voltage(output);  // actually move the arm

        pros::delay(20);
  }
}