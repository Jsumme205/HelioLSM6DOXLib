//defining the library call 
#ifndef ProtoLSM6DSOXLib_h
#define ProtoLSM6DSOXLib_h

// libraries that are used in this other library  

// this is the main arduino library. It defines all of the pins, as well as all the functions that are unique to the microcontroller
 #include <Arduino.h>

// this enables the I2C interface. It brings the Wire functions into play
  #include <Wire.h>

// creates a class, where all of the LSM6DSOX functions are contained in. Use this for easy reference to all of the functions.
class ProtoLSM6DSOXLib {
  
  // public functions and variables, which can be acsessed from anywhere
  public:
    
    //this function initiallizes the library  
    ProtoLSM6DSOXLib(int _address);
    
    // these functions reads the acceleraton on the axes 
    void readAccelX();
    void readAccelY();
    void readAccelZ();
    
    // these functions read the rotation on their respective axes
    void readGyroX();
    void readGyroY();
    void readGyroZ();
    
    //these functions read the temperature in fahrenheit and celsius, respectively 
    void readTempF();
    void readTempC();
    
    // this function reads the First in, First out byte buffer, which means the first byte to get there gets processed first and the newest byte gets processed last 
    void GetFIFOStat();
    
    // these both are time functions the first is the time, the second is if you want to set it to your timezone (-12 to 12) 
    void getTime();
    void setTimeZone(int TimeZone);
    
    // these are private variables that can only be used or modified in the class function (this function)
    private:
    int _address;
    int _TimeZone;
};

#endif
