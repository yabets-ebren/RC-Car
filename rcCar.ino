/*
-- EGEN 310 - project --
A simple graphical user interface made using remotexy library and source code. A title and 4 buttons each representing the direction for the vehicle movement. */
//////////////////////////////////////////////
// RemoteXY include library // //////////////////////////////////////////////
//used Adafruit motor shield so must import the Adafruit’s v2 library #include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
 Adafruit_MotorShield AFMS = Adafruit_MotorShield(); Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4); ///////////////////////////////////////////////
// RemoteXY select connection mode and include library
// used HC-05 bluetooth module for the remote connectionof the app and the vehicle.
//Note HC-05 bluetooth module only works with Android devices. If you have IOS device, must //use HM-10 (BLE) modules
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>
#include <RemoteXY.h>
// RemoteXY connection settings
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600
// RemoteXY configurate
// Designs for UI
#pragma pack(push, 1) uint8_t RemoteXY_CONF[] =
{ 255,4,0,0,0,72,0,13,200,0, 1,0,12,21,14,14,133,31,226,150, 178,0,1,0,12,40,14,14,133,31, 226,150,188,0,1,0,60,30,14,14, 133,31,226,151,132,0,1,0,79,30, 14,14,133,31,226,150,186,0,129,0, 29,6,41,6,31,69,71,69,78,32, 51,49,48,58,32,69,52,32,0 };
// this structure defines all the variables and events of your control interface struct {
// input variables
uint8_t forwards; // =1 if button pressed, else =0

 uint8_t left; // =1 if button pressed, else =0
uint8_t right; // =1 if button pressed, else =0 uint8_t backwards; // =1 if button pressed, else =0
// other variable
uint8_t connect_flag; // =1 if wire connected, else =0
} RemoteXY; #pragma pack(pop)
/////////////////////////////////////////////
// END RemoteXY include // /////////////////////////////////////////////
#define PIN_FORWARDS 8 #define PIN_LEFT 6
#define PIN_RIGHT 7 #define PIN_BACKWARDS 9
void setup() {
RemoteXY_Init (); ///// AFMS.begin(); /////
pinMode (PIN_FORWARDS, OUTPUT); pinMode (PIN_LEFT, OUTPUT); pinMode (PIN_RIGHT, OUTPUT); pinMode (PIN_BACKWARDS, OUTPUT);
// TODO you setup code }
void loop() {
RemoteXY_Handler ();
digitalWrite(PIN_FORWARDS, (RemoteXY.forwards==0)?LOW:HIGH); digitalWrite(PIN_LEFT, (RemoteXY.left==0)?LOW:HIGH); digitalWrite(PIN_RIGHT, (RemoteXY.right==0)?LOW:HIGH); digitalWrite(PIN_BACKWARDS, (RemoteXY.backwards==0)?LOW:HIGH);

 // use the RemoteXY structure for data transfer // do not call delay()
if (digitalRead(8) == HIGH) {
myMotor1->setSpeed(200); myMotor1->run(FORWARD); myMotor2->setSpeed(200); myMotor2->run(BACKWARD); myMotor3->setSpeed(200); myMotor3->run(FORWARD); myMotor4->setSpeed(200); myMotor4->run(BACKWARD);
} else if (digitalRead(6) == HIGH) { myMotor1->setSpeed(200); myMotor1->run(BACKWARD); myMotor2->setSpeed(200); myMotor2->run(FORWARD); myMotor3->setSpeed(200); myMotor3->run(BACKWARD); myMotor4->setSpeed(200); myMotor4->run(FORWARD);
} else if (digitalRead(7) == HIGH) { myMotor1->setSpeed(200); myMotor1->run(FORWARD); myMotor2->setSpeed(200); myMotor2->run(FORWARD); myMotor3->setSpeed(200); myMotor3->run(BACKWARD); myMotor4->setSpeed(200); myMotor4->run(BACKWARD);
} else if (digitalRead(9) == HIGH) { myMotor1->setSpeed(200); myMotor1->run(BACKWARD); myMotor2->setSpeed(200); myMotor2->run(BACKWARD); myMotor3->setSpeed(200); myMotor3->run(FORWARD); myMotor4->setSpeed(200); myMotor4->run(FORWARD);
} else { myMotor1->setSpeed(200); myMotor1->run(RELEASE); myMotor2->setSpeed(200); myMotor2->run(RELEASE);

myMotor3->setSpeed(200); myMotor3->run(RELEASE); myMotor4->setSpeed(200); myMotor4->run(RELEASE);
} }
