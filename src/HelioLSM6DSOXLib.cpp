

#include "ProtoLSM6DSOXLib.h"

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

short EMB_FUNC_STATUS_MAINPAGE = 0x35;
short FSM_STATUS_A_MAINPAGE = 0x36;
short FSM_STATUS_B_MAINPAGE = 0x37;
short MLC_STATUS_MAINPAGE = 0x38;
short STATUS_MASTER_MAINPAGE = 0x39;
short FIFO_STATUS1 = 0x3A;
short FIFO_STATUS2 = 0x3B;
short TIMESTAMP0 = 0x40;
short TIMESTAMP1 = 0x41;
short TIMESTAMP2 = 0x42;
short TIMESTAMP3 = 0x43;
short UI_STATUS_REG_OIS = 0x49;
short UI_OUTX_L_G_OIS = 0x4A;
short UI_OUTX_H_G_OIS = 0x4B;
short UI_OUTY_L_G_OIS = 0x4C;
short UI_OUTY_H_G_OIS = 0x4D;
short UI_OUTZ_L_G_OIS = 0x4E;
short UI_OUTZ_H_G_OIS = 0x4F;
short UI_OUTX_L_A_OIS = 0x50;
short UI_OUTX_H_A_OIS = 0x51;
short UI_OUTY_L_A_OIS = 0x52;
short UI_OUTY_H_A_OIS = 0x53;
short UI_OUTZ_L_A_OIS = 0x54;

int hoursPassed = 0;

float InitalVelocityX = 0;
float InitalVelocityY = 0;
float InitalVelocityZ = 0;

const float GravitationalConstant = 9.8;




ProtoLSM6DSOXLib :: ProtoLSM6DSOXLib(int address) {

	Wire.begin(address);
	_address = address;

}


void ProtoLSM6DSOXLib :: readAccelX() {
	typedef union ACCELX {
		uint8_t DaX_8[2];
		uint16_t DaX_16;
	};

	ACCELX accelx;

	Wire.beginTransmission(_address);
	Wire.write(0x28);
	Wire.requestFrom(_address, 1);
	accelx.DaX_8[0] = Wire.read();

	Wire.write(0x29);	
	Wire.requestFrom(_address, 1);
	accelx.DaX_8[1] = Wire.read();


	String BinAx = String(accelx.DaX_16);

	long NotAx = BinAx.toInt();

	long StillNotAx = map(NotAx, 0, 65536, 0, 20000);

	long FinAx = StillNotAx * 9.8;

	Wire.endTransmission();

	return FinAx;
}

void ProtoLSM6DSOXLib :: readAccelY() {
	typedef union ACCELY {
		uint8_t DaY_8[2];
		uint16_t DaY_16;
	};

	ACCELY accely;
	Wire.beginTransmission(_address);
	Wire.write(0x2A);
	Wire.requestFrom(_address, 1);
	accely.DaY_8[0] = Wire.read();

	Wire.write(0x2B);
	Wire.requestFrom(_address, 1);
	accely.DaY_8[1] = Wire.read();


	String BinAy = String(accely.DaY_16);

	long NotAy = BinAy.toInt();

	long StillNotAy = map(NotAy, 0, 65536, 0, 20000);

	float FinAy = StillNotAy * 9.8;

	Wire.endTransmission();

	return FinAy;
}

void ProtoLSM6DSOXLib :: readAccelZ() {

	typedef union ACCELZ{
		uint8_t DaZ_8[2];
		uint16_t DaZ_16;
	};

	ACCELZ accelz;
	Wire.beginTransmission(_address);
	Wire.write(0x2C);
	Wire.requestFrom(_address, 1)
	accelz.DaZ_8[0] = Wire.read();

	Wire.write(0x2D);
	Wire.requestFrom(_address, 1);
	accelz.DaZ_8[1] = Wire.read();
	
	String BinAz = String(accelz.DaZ_16);

	long NotAz = BinAz.toInt();

	long StillNotAz = map(NotAz, 0, 65536, 0, 20000);

	float FinAz = StillNotAz * 9.8;

	Wire.endTransmission();

	return FinAz;
}

void ProtoLSM6DSOXLib :: getVx(){
	typedef union VELOCITYX1 {
		uint8_t DxV1_8[2];
		uint16_t DxV1_16;
	};

	VELOCITYX1 velocityx1
	Wire.beginTransmission(_address);
	Wire.write(0x28);
	Wire.requestFrom(_address, 1);
	velocityx1.DxV1_8[0] = Wire.read();
	
	Wire.write(0x29);
	Wire.requestFrom(_address, 1);
	velocityx1.DxV1_8[1] = Wire.write();
	
	String BinVx1 = String(velocityx1.DxV1_16);

	long NotVx1 = BinVx1.toInt();

	long stillNotVx1 = map(NotVx1, 65536, 0, 20000);

	long almostVx1 = stillNotVx1 * 9.8;

	delay(5000);

	typedef union VELOCITYX2 {
		uint8_t DxV2_8[2];
		uint16_t DxV2_16;
	};

	VELOCITYX2 velocityx2;
	
	Wire.write(0x28);
	Wire.requestFrom(_address, 1);
	velocityx2.DxV2_8[0] = Wire.read();
	
	Wire.write(0x28);
	Wire.requestFrom(_address, 1);
	velocityx2.DxV2_8[1] = Wire.read();

	String BinVx2 = String(velocityx1.DxV2_16);

	long NotVx2 = BinVx2.toInt(); 
	long stillNotVx2 = map(NotVx2, 0, 65536, 0, 20000);
	float almostVx2 = stillNotVx2 * 9.8;
	float VelocityX = InitalVelocityX + (((almostVx2 + almostVx1) / 2) * 5);
	float InitalVelocityX = VelocityX;

	Wire.endTransmission();

	return VelocityX;
}

void ProtoLSM6DSOXLib :: getVy(){
	

	typedef union VELOCITYY1 {
		uint8_t DvY1_8[2];
		uint16_t DvY1_16;
	};

	VELOCITYY1 velocityy1;
	Wire.beginTransmission(_address);
	Wire.write(0x2A);
	Wire.requestFrom(_address, 1);
	velocityy1.DvY1_8[0] = Wire.read();
	
	Wire.write(0x2B);
	Wire.requestFrom(_address, 1);
	velocityy1.DvY1_8[0] = Wire.read();

	String BinVy1 = String(velocityy1.DvY1_16);

	long NotVy1 = BinVy1.toInt();
	long stillNotVy1 = map(NotVy1, 0, 65536, 0, 20000);
	float almostVy1 = stillNotVy1 * 9.8 

	delay(5000);

	typedef union VELOCITYY2 {
		uint8_t DvY2_8[2];
		uint16_t DvY2_16;
	};

	VELOCITYY2 velocityy2;
	Wire.write(0x2A);
	Wire.requestFrom(_address, 1);
	velocityy2.DvY2_8[0] = Wire.read();
	
	Wire.write(0x2B);
	Wire.requestFrom(_address, 1);
	velocityy2.DvY2_8[1] = Wire.read();
	

	String BinVy2 = String(velocityy2.DvY2_16);

	long NotVy2 = BinVy2.toInt();
	long stillNotVy2 = map(NotVy1, 0, 65536, 0, 20000);
	float almostVy2 =  stillNotVy2 * 9.8;
	float VelocityY = InitalVelocityY + (((almostVy2 + almostVy1) / 2) * 5);
	float InitalVelocityY = VelocityY

	Wire.endTransmission();
}

void ProtoLSM6DSOXLib :: getVz(){
	typedef union VELOCITYZ1 {
		uint8_t DvZ1_8[2];
		uint16_t DvZ1_16;
	};

	VELOCITYZ1 velocityz1;
	Wire.beginTransmission(_address);
	Wire.write(0x2C);
	Wire.requestFrom(_address, 1);
	velocityz1.DvZ1_8[0] = Wire.read();
	
	Wire.write(0x2D);
	Wire.requestFrom(_address, 1);
	velocityz1.DvZ1_8[1] = Wire.read();

	String BinVz1 = String(velocityz1.DvZ1_16);

	long NotVz1 = BinVz1.toInt();
	long stillNotVz1 = map(NotVz1, 0, 65536, 0, 20000);
	float almostVz1 = stillNotVz1 * 9.8;

	delay(5000);

	typedef union VELOCITYZ2 {
		uint8_t DvZ2_8[2];
		uint16_t DvZ2_16;	
	};

	VELOCITYZ2 velocityz2;
	Wire.write(0x2C);
	Wire.requestFrom(_address, 1);
	velocityz2.DvZ2_8[0] = Wire.read();
	
	Wire.write(0x2D);
	Wire.requestFrom(_address, 1);
	velocityz2.DvZ2_8[1] = Wire.read();
	
	String BinVz2 = String(velocityz2.DvZ2_16);

	long NotVz2 = BinVz2.toInt();
	long stillNotVz2 = map(NotVz2, 0, 65536, 0, 20000);
	float almostVz2 = stillNotVz2 * 9.8;
	float VelocityZ = InitalVelocityZ + ((almostVz1 + almostVz2) * 5);
	float InitalVelocityZ = VelocityZ;

	Wire.endTransmission();

	return VelocityZ;
}

void  ProtoLSM6DSOXLib :: setTerminalVelocity (float Mass, float Density, float Area){

	float dragForce = (0.5 * Density * pow(GravitationalConstant, 2) * Area);
	float dragCoeficient = ((2 * dragForce) / Density * pow(GravitationalConstant, 2) * Area);
	float TerminalVelocity = sqrt((2 * Mass * GravitationalConstant) / (Density * Area * dragCoeficient));

	_Mass = Mass;
	_Density = Density;
	_Area = Area;

	return TerminalVelocity;
}

void ProtoLSM6DSOXLib :: readGyroX() {
	typedef union GYROX {
		uint8_t DgX_8[2];
		uint16_t DgX_16;
	};

	GYROX gyrox;
	
	Wire.beginTransmission(_address);
	Wire.write(0x22);
	Wire.requestFrom(_address, 1);
	gyrox.DgX_8[0] = Wire.read();
	
	Wire.write(0x23);
	Wire.requestFrom(_address, 1);
	gyrox.DgX_8[1] = Wire.read();
	
	String BinGx = String(gyrox.DgX_16);  

	long NotGx = BinGx.toInt();

	long FinGx = map(NotGx, 0, 65536, 0, 36000);

	Wire.endTransmission();

	return FinGx;
}

void ProtoLSM6DSOXLib :: readGyroY() {
	typedef union GYROY {
		uint8_t DgY_8[2];
		uint16_t DgY_16;
	};

	GYROY gyroy;

	Wire.beginTransmission(_address);
	Wire.write(0x24);
	Wire.requestFrom(_address, 1);
	gyroy.DgY_8[0] = Wire.read();
	
	Wire.write(0x25);
	Wire.requestFrom(_address, 1);
	gyroy.DgY_8[1] = Wire.read();
	
	String BinGy = String(gyroy.DgY_16);

	long NotGy = BinGy.toInt();

	long FinGy = map(NotGy, 0, 65536, 0, 36000);

	Wire.endTransmission();

	return FinGy;
}

void ProtoLSM6DSOXLib :: readGyroZ() {
	typedef union GYROZ {
		uint8_t DgZ_8[2];
		uint16_t DgZ_16;
	};

	GYROZ gyroz;

	Wire.beginTransmission(_address);
	Wire.write(0x26);
	Wire.requestFrom(_address, 1);
	gyroz.DgZ_8[0] = Wire.read();
	
	Wire.write(0x27);
	Wire.requestFrom(_address);
	gyroz.DgZ_8[1] = Wire.read();
	
	String BinGz = String(gyroz.DgZ_16);

	long NotGz = BinGz.toInt();

	long FinGz = map(NotGz, 0, 65536, 0, 36000);

	Wire.endTransmission();

	return FinGz;
}

void ProtoLSM6DSOXLib :: readTempF() {
	typedef union TEMPF {
		uint8_t DtF_8[2];
		uint16_t DtF_16;
	};

	TEMPF tempf;
	Wire.beginTransmission(_address);
	Wire.write(OUT_TEMP_L);
	Wire.requestFrom(_address, 1);

	String BinTf = String(tempf.DtF_16);

	long FinTf = BinTf.toInt();

	float CtoFConv = (FinTf * 1.8) + 32;

	Wire.endTransmission();

	return CtoFConv;
}

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

// FIFO stats are on page 38
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

void ProtoLSM6DSOXLib :: GetFIFOStat2(int THRESH) {
	Wire.beginTransmission(_address);
	Wire.requestFrom(_address, 0x01);
	int FIFONum2 = 0;
	bool FIFOSt;
	if (sizeof(Wire.write(byte(FIFO_STATUS2))) >= 7) {
		FIFONum2 ++;
		FIFOSt = false;
	}
	else if (FIFONum2 > THRESH) {
		FIFOSt = true;
	}

	_thresh = THRESH;
	Wire.endTransmission();

	return FIFOSt;
}
// page 39 gives info on connections
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

void ProtoLSM6DSOXLib :: setTimeZone(int TimeZone) {
	int TimeZoneShift = 0;
	if (-13 > TimeZone > 13) {
		return NULL;
	}

	else {
		int TimeZoneShift = hoursPassed + TimeZone;
	}

	return TimeZoneShift;
}

void ProtoLSM6DSOXLib :: getTimeRaw(){

	Wire.beginTransmission(_address);	
	Wire.requestFrom(_address, 0x04);

	typedef union RAWTIME {
		uint32_t rawTime_32;
		uint8_t rawTime_8[4];
	};

	RAWTIME rawTime;
	rawTime.rawTime_8[0] = Wire.write(byte(TIMESTAMP0));
	rawTime.rawTime_8[1] = Wire.write(byte(TIMESTAMP1));
	rawTime.rawTime_8[2] = Wire.write(byte(TIMESTAMP2));
	rawTime.rawTime_8[3] = Wire.write(byte(TIMESTAMP3));

	String RaTime = String(rawTime.rawTime_32);

	long ratime = RaTime.toInt();

	return ratime;
}
