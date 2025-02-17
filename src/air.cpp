#include "main.h" // IWYU pragma: keep
#include "../include/subsystems/initbot.hpp"
#include "../include/subsystems/air.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/misc.h"


bool mogoToggle = false;
bool doinkToggle = false;
pros::adi::DigitalOut mogoMech('B');
pros::adi::DigitalOut doinker('A');


void grab(){
      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        mogoToggle = !mogoToggle;
        mogoMech.set_value(mogoToggle);
  }
}

void doink(){
      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        doinkToggle = !doinkToggle;
        doinker.set_value(doinkToggle);
  }
}