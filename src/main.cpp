#include "main.h"// IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "../include/subsystems/drive.hpp"
#include "../include/subsystems/initbot.hpp"
#include "../include/subsystems/intake.hpp"
#include "../include/subsystems/air.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "../include/subsystems/lb.hpp"



pros::Controller controller(pros::E_CONTROLLER_MASTER);

// void armControlTask() {
//     while (true) {
//         // Check for controller input to change arm state
//         if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
//             nextState(); // Change the target state of the arm
//         }

//         // Call liftControl to adjust the arm based on the current target
//         liftControl();

//         // Add a small delay to prevent overwhelming the CPU
//         pros::delay(10);
//     }
// }
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.

 
 */


void initialize() {
	pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate();


    // chassis.calibrate(); // calibrate sensors
    IntakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
     pros::Task screen_task([&]() {
        while (true) {
            // Combine position data onto one line
            pros::lcd::print(1, "X:%.1f Y:%.1f T:%.1f", 
                           chassis.getPose().x,
                           chassis.getPose().y,
                           chassis.getPose().theta);
        
            pros::delay(25);
        }
    });
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    mogoMech.set_value(false);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    chassis.setPose(-58.135,42.876,90);

    chassis.turnToHeading(300,1500,{},false);
    chassis.moveToPoint(-25.721, 24.717, 1500,{.forwards=false,.maxSpeed=50},false);
    chassis.waitUntilDone();
    pros::delay(500);
    mogoMech.set_value(true);
    pros::delay(1000);
    //chassis.turnToHeading(14, 1000,{},false);
    IntakeMotor.move(127);
    ConveyorMotor.move(127);

    pros::delay(1750);


    // chassis.turnToPoint(-23.451, 42.372, 1000,{},false);
    // chassis.waitUntilDone();
    // pros::delay(500);
    // chassis.moveToPoint(-23.451, 42.372, 1500,{},false);
    // chassis.waitUntilDone();
    // pros::delay(500);
    IntakeMotor.move(0);
    ConveyorMotor.move(0);
    // chassis.moveToPoint(-23.199, 8.071, 1500,{.forwards=false},false);

    // pros::delay(600);
    // chassis.turnToHeading(0, 1500,{},false);
    // chassis.moveToPoint(-25.221, 42.246, 1500,{},false);
    // chassis.turnToHeading(82, 1500,{},false);
    // chassis.moveToPoint(-9.962, 43.759, 1500,{},false);
    // chassis.moveToPoint(-16.262, 43.507, 1500,{.forwards=false},false);
    // chassis.turnToHeading(56.8, 1500,{},false);
    // chassis.moveToPoint(-10.971, 48.173, 1500,{},false);
    // chassis.moveToPoint(-16.262, 43.507, 1500,{.forwards=false},false);
    // chassis.turnToHeading(175.6, 1000);
    // chassis.turnToPoint(-13.493, 13.62, 1500,{},false);

    

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 
 */


void opcontrol() {
    pros::Task armTask(armDriver); 
	while (true) {
    pros::lcd::print(1, "X:%.1f Y:%.1f T:%.1f", 
                           chassis.getPose().x,
                           chassis.getPose().y,
                           chassis.getPose().theta);
    tankDrive();
    Intakerun();
    grab();
	doink();
    /*if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
			nextState();
	}*/

    armDriver();

    pros::delay(20); 
	}
}
