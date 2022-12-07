
// _addresses that correspond to the different abilities of this device

//Temp outputs
  short OUT_TEMP_L = 0x20;
  short OUT_TEMP_H = 0x21;

//IMU data
  short OUTX_L_G = 0x22;
  short OUTX_H_G = 0x23;
  short OUTY_L_G = 0x24;
  short OUTY_H_G = 0x25;
  short OUTZ_L_G = 0x26;
  short OUTZ_H_G = 0x27;
  short OUTX_L_A = 0x28;
  short OUTX_H_A = 0x29;
  short OUTY_L_A = 0x2A;
  short OUTY_H_A = 0x2B;
  short OUTZ_L_A = 0x2C;
  short OUTZ_H_A = 0x2D;

// First In, First Out addresses. These are used for advanced features. 
short FIFO_STATUS1 = 0x3A;
short FIFO_STATUS2 = 0x3B;

// Timestamp addresses. This uses Unix time, which is a 32 bit feature that counts the seconds that have ellapsed since January 1, 1970 at 00:00 UTC 
  short TIMESTAMP0 = 0x40;
  short TIMESTAMP1 = 0x41;
  short TIMESTAMP2 = 0x42;
  short TIMESTAMP3 = 0x43;

// these had to be a global variables because these are the only variables that are really used multiple times in different Void functions
  int hoursPassed = 0;
  int TimeZone = 0; 

//defining the library call 
#ifndef ProtoLSM6DSOXLib_h
#define ProtoLSM6DSOXLib_h

// libraries that are used in this other library  

// this is the main arduino library. It defines all of the pins, as well as all the functions that are unique to the microcontroller
#include <Arduino.h>

// this enables the I2C interface. It brings the Wire. functions into play
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
    
    // these functions read the First in, First out byte buffer, which means the first byte to get there gets processed first and the newest byte gets processed last 
    void GetFIFOStat();
    void GetFIFOStat2(int thresh);
    
    // these both are time functions the first is the time, the second is if you want to 
    void getTime();
    void setTimeZone(int TimeZone);
    
    // these are private variables that can only be used or modified in the class function (this function)
    private:
    int _address;
    int _thresh;
    int _TimeZone;
};

#endif

// initializer function that will look like this : ProtoLSM6DSOXLib accel(your address); 
ProtoLSM6DSOXLib :: ProtoLSM6DSOXLib(int address) {

  Wire.begin(address);
  _address = address;

}

//accerometer data
void ProtoLSM6DSOXLib :: readAccelX() {
  Wire.beginTransmission(_address);
  Wire.requestFrom(_address, 0x02);

  typedef union ACCELX {
    uint8_t DaX_8[2];
    uint16_t DaX_16;
  };

  ACCELX accelx;
  accelx.DaX_8[0] = Wire.write(byte(0x28));
  accelx.DaX_8[1] = Wire.write(byte(0x29));

  String BinAx = String(accelx.DaX_16);
  
  long FinAx = BinAx.toInt();
  
  return FinAx;
}

//accerometer data
void ProtoLSM6DSOXLib :: readAccelY() {
  Wire.beginTransmission(_address);
  Wire.requestFrom(_address, 0x02);
  
  typedef union ACCELY {
    uint8_t DaY_8[2];
    uint16_t DaY_16;
  };
  
  ACCELY accely;
  
  accely.DaY_8[0] = Wire.write(byte(0x2A));
  accely.DaY_8[1] = Wire.write(byte(0x2B));
  
  String BinAy = String(accely.DaY_16);
  
  long FinAy = BinAy.toInt();
  
  Wire.endTransmission();
  
  return FinAy;
}

//accerometer data
void ProtoLSM6DSOXLib :: readAccelZ() {
  Wire.beginTransmission(_address);
  Wire.requestFrom(_address, 0x02);
  
  typedef union ACCELZ{
    uint8_t DaZ_8[2];
    uint16_t DaZ_16;
  };
  
  ACCELZ accelz;
  
  accelz.DaZ_8[0] = Wire.write(byte(0x2C));
  accelz.DaZ_8[1] = Wire.write(byte(0x2D));
  
  String BinAz = String(accelz.DaZ_16);
  
  long FinAz = BinAz.toInt();
  
  Wire.endTransmission();
  
  return FinAz;
}
//Gyroscope data
void ProtoLSM6DSOXLib :: readGyroX() {
  Wire.beginTransmission(_address);
  Wire.requestFrom(_address, 0x02);
  
  typedef union GYROX {
    uint8_t DgX_8[2];
    uint16_t DgX_16;
  };
  
  GYROX gyrox;
  
  gyrox.DgX_8[0] = Wire.write(byte(0x22));
  gyrox.DgX_8[1] = Wire.write(byte(0x23));

  String BinGx = String(gyrox.DgX_16);  
  
  long FinGx = BinGx.toInt();
  
  Wire.endTransmission();
  
  return FinGx;
}

//Gyroscope data
void ProtoLSM6DSOXLib :: readGyroY() {
  Wire.beginTransmission(_address);
  Wire.requestFrom(_address, 0x02);
  
  typedef union GYROY {
    uint8_t DgY_8[2];
    uint16_t DgY_16;
  };
  
  GYROY gyroy;
  
  gyroy.DgY_8[0] = Wire.write(byte(0x24));
  gyroy.DgY_8[1] = Wire.write(byte(0x25));
  
  String BinGy = String(gyroy.DgY_16);
  
  long FinGy = BinGy.toInt();
  
  Wire.endTransmission();
  
  return FinGy;
}

//Gyroscope data
void ProtoLSM6DSOXLib :: readGyroZ() {
  Wire.beginTransmission(_address);
  Wire.requestFrom(_address, 0x02);
  
  typedef union GYROZ {
    uint8_t DgZ_8[2];
    uint16_t DgZ_16;
  };
  
  GYROZ gyroz;
  
  gyroz.DgZ_8[0] = Wire.write(byte(0x26));
  gyroz.DgZ_8[1] = Wire.write(byte(0x27));
  
  String BinGz = String(gyroz.DgZ_16);
  
  long FinGz = BinGz.toInt();
  
  Wire.endTransmission();
  
  return FinGz;
}
// temperature data -- in F
void ProtoLSM6DSOXLib :: readTempF() {
  
  Wire.beginTransmission(_address);
  Wire.requestFrom(_address, 0x02);
  
  typedef union TEMPF {
    uint8_t DtF_8[2];
    uint16_t DtF_16;
  };

  TEMPF tempf;
  
  tempf.DtF_8[0] = Wire.write(byte(OUT_TEMP_L));
  tempf.DtF_8[1] = Wire.write(byte(OUT_TEMP_H));
  
  String BinTf = String(tempf.DtF_16);
  
  long FinTf = BinTf.toInt();
  
  float CtoFConv = (FinTf * 1.8) + 32;
  
  Wire.endTransmission();
  
  return CtoFConv;
}

// temperature data --  in C
void ProtoLSM6DSOXLib :: readTempC() {
 
  Wire.beginTransmission(_address);
  Wire.requestFrom(_address, 0x02);
 
  typedef union TEMPC {
   uint8_t DtC_8[2];
   uint16_t DtC_16; 
 };
  
  TEMPC tempc;
  
  tempc.DtC_8[0] = Wire.write(byte(OUT_TEMP_L));
  tempc.DtC_8[1] = Wire.write(byte(OUT_TEMP_H));
  
  String BinTc = String(tempc.DtC_16);
  
  long FinTc = BinTc.toInt();
  
  Wire.endTransmission();
  
  return FinTc;
  }
  
// FIFO function 
void ProtoLSM6DSOXLib :: GetFIFOStat() {
  Wire.beginTransmission(_address);
  Wire.requestFrom(_address, 0x01);
  int FIFONum = 0;
  if (sizeof(Wire.write(byte(FIFO_STATUS1))) >= 7) {
    FIFONum ++;
  }

  Wire.endTransmission();
  
  return FIFONum;
}

// FIFO function 2
void ProtoLSM6DSOXLib :: GetFIFOStat2(int THRESH) {
  Wire.beginTransmission(_address);
  Wire.requestFrom(_address, 0x01);
  int FIFONum2 = 0;
  bool FIFOSt;
  if (sizeof(Wire.write(byte(FIFO_STATUS2))) >= 7) {
    FIFONum2 ++;
    FIFOSt = false;
  }
  if (FIFONum2 > THRESH) {
    FIFOSt = true;
  }

  _thresh = THRESH;
  Wire.endTransmission();
  
  return FIFOSt;
}

// time function 1
void ProtoLSM6DSOXLib :: getTime() {
  Wire.beginTransmission(_address);
  Wire.requestFrom(_address, 0x04);

  typedef union COMBO {
    uint32_t data_32;
    uint8_t data_8[4];
  };

  COMBO combo;
  combo.data_8[0] = Wire.write(byte(TIMESTAMP0));
  combo.data_8[1] = Wire.write(byte(TIMESTAMP1));
  combo.data_8[2] = Wire.write(byte(TIMESTAMP2));
  combo.data_8[3] = Wire.write(byte(TIMESTAMP3));

  String unix_time = String(combo.data_32);

  long UT = unix_time.toInt();

  #define secondsInYear 31556952
  #define secondsInLeap 31643352
  #define secondsInMonth 2592000
  #define secondsInDay 86400
  #define secondsInHour 3600
  #define secondsInMinute 60
  
  int newValY = UT - secondsInYear;
  int newValL = newValY - secondsInLeap;
  int newValM = newValY - secondsInMonth;
  int newValD = newValM - secondsInDay;
  int newValH = newValD - secondsInHour;
  int newValS = newValD - secondsInMinute;
  
  int yearsPassed = 0;
  int monthsPassed = 0;
  int daysPassed = 0;
  int minutesPassed = 0;
  
  for (UT > 0; secondsInYear <= UT; UT - secondsInYear) {
    int newValY = UT - secondsInYear;
    int i = 0;
    i++;
    yearsPassed++;
    for (i = 4; secondsInLeap <= newValY ; newValY - secondsInLeap) {
      int newValL = newValY - secondsInLeap;
      int i = 0;
      yearsPassed++;
    }
  }

  for (newValY > 0 && secondsInYear > newValY; secondsInMonth <= newValY && secondsInMonth <= newValL; newValY - secondsInMonth) {
    int newValM = newValY - secondsInMonth;
    monthsPassed++;
    if (monthsPassed > 12) {
      monthsPassed = 0;
      yearsPassed++;
    }
  }

  for (newValM > 0 && secondsInMonth > newValM; secondsInDay <= newValM; newValM - secondsInMonth) {
    int newValD = newValM - secondsInDay;
    daysPassed++;
    if (daysPassed > 30) {
      monthsPassed++;
    }
    daysPassed = 0;
    monthsPassed++;

  }

  for (newValD > 0 && secondsInDay > newValD; secondsInHour <= newValD; newValD - secondsInHour) {
    int hoursPassed = 0;
    int newValH = newValD - secondsInHour;
    hoursPassed++;
    if (hoursPassed > 24) {
      daysPassed++;
    }
    hoursPassed = 0;
    daysPassed++;

  }

  for (newValH > 0 && secondsInHour > newValH; secondsInMinute <= newValH; newValD - secondsInMinute) {
    int newValS = newValD - secondsInMinute;
    minutesPassed++;
    if (minutesPassed > 60) {
      minutesPassed = 0;
      hoursPassed++;
    }
  }
  
  Wire.endTransmission();
  
  
}

// time function 2
void setTimeZone(int TimeZone) {
  int TimeZoneShift = 0;
  if (-13 > TimeZone > 13) {
    TimeZone == false;
  }
  
  else {
    int TimeZoneShift = hoursPassed + TimeZone;
  }

  return TimeZoneShift;
}
