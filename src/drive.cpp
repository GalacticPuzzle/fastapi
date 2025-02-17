#include "main.h"// IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "../include/subsystems/drive.hpp"
#include "pros/misc.h"
#include "../include/subsystems/initbot.hpp"


void tankDrive(){
        // get left y and right y positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        // move the robot
        chassis.tank(leftY, rightY);

        // delay to save resources
    
}

void arcadeDrive(){
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot
        chassis.arcade(leftY, rightX);

        // delay to save resources
}
