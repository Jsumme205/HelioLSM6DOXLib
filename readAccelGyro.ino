
#include <Wire.h>
#include <ProtoLSM6DSOXLib.h>

#define IMUADD 0x6A

ProtoLSM6DSOXLib IMU(IMUADD);



void setup(){

serial.begin(9600);
MyInitializer();
  
}

void loop() {

}

void MyInitializer(){
  serial.begin(9600);
  serial.printIn("initializing ProtoLSM6DSOXLib library, this will take a second");
  delay(500);
  serial.printIn("initializing...");
  delay(500); 
  serial.printIn("initializing...");
  delay(500);
  serial.printIn("initializing...");
  delay(500);
  serial.printIn("initialization complete");
  delay(250);
  serial.printIn("Welcome to ProtoLSM6DSOXLib");
}
