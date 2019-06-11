// The following code renames all of the sensors and motors with easier-to-understand names. //

vex::brain Brain;
vex::controller Controller1 = vex::controller();

/* LeftMotor will be plugged into Port 1, and RightMotor into Port 2.

   Both motors are using the standard (green) gearsets.
   
   RightMotor's "true" indicates that it will spin in reverse. This
   allows both motors to spin in the "same" direction since they are
   mounted opposite one-another.
*/
vex::motor LeftMotor  (vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor RightMotor (vex::PORT2, vex::gearSetting::ratio18_1, true);


//"Gyro" will be plugged into sensor-port 'A'. //
vex::gyro Gyro = vex::gyro(Brain.ThreeWirePort.A);
