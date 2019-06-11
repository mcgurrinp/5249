/* The line below includes the robot's pragma code, which 
   intializes all of the sensorsand motors to the correct ports. */
#include "robot-config.h"

// The turn90 method will point turn the robot left 90°. //
void turn90(){
    // The gyro is given 3 seconds to calibrate. //
    Gyro.startCalibration();
    double gyroVal = 0;
    vex::task::sleep(3000);
    
    /* 
       While the robot's turn is less than 90°, the robot will keep turning left. 
       The degree value below is written as 900, since the gyroscope measures in tenths of degrees.
    */                                      
    while(Gyro.value(vex::analogUnits::range12bit) <= 900){
        // Prints gyroscope value on the screen. //
        gyroVal = Gyro.value(vex::analogUnits::range12bit);
        Brain.Screen.printAt(50,50,"%f",gyroVal);
        
        LeftMotor.spin(vex::directionType::fwd, 10, vex::velocityUnits::pct);
        RightMotor.spin(vex::directionType::rev, 10, vex::velocityUnits::pct);
    }
    // After the gyroscope reaches 90°, both motors will stop. //
    LeftMotor.stop();
    RightMotor.stop(); 
}

void move2(){
    // Both motor's encoder readings are reset to 0. //
    LeftMotor.resetRotation();
    RightMotor.resetRotation();
    
    /* 
       The equivalent rotational distance (in degrees) of 2 feet was found to be
       982.81°. This was calculated by finding the wheels' circumphrence (2.8*PI),
       dividing it from 24 in, and then multiplying the result by 360°.
    */
    double twoFtDeg = (24/(3.14*2.5))*360;
    
    while(LeftMotor.rotation(vex::rotationUnits::deg) < twoFtDeg  || RightMotor.rotation(vex::rotationUnits::deg) < twoFtDeg){
        LeftMotor.spin(vex::directionType::fwd, 10, vex::velocityUnits::pct);
        RightMotor.spin(vex::directionType::fwd, 10, vex::velocityUnits::pct);
    }

    // After any of the encoders have spun for 
    LeftMotor.stop(vex::brakeType::brake);
    RightMotor.stop(vex::brakeType::brake);  
}


int main() {
    // Allows the main method to always run in an infinite loop. //
    while (true) {
        // 90 Degree Turn --> 'Y' Button //
        Controller1.ButtonY.pressed(turn90);
        
        // Dual stick control. Left stick goes forward + back. Right stick yaw. //
        LeftMotor.spin(vex::directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value()/2), vex::velocityUnits::pct); //(Axis3+Axis4)/2;
        RightMotor.spin(vex::directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis1.value()/2), vex::velocityUnits::pct);//(Axis3-Axis4)/2;

        // Forward 2 ft --> 'Front Arrow' Button //
        Controller1.ButtonUp.pressed(move2);
    } 
}
