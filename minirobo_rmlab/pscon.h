// pscon.h

#ifndef _PSCON_h
#define _PSCON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class PsconClass
{
 private:
	 HardwareSerial *serial;
	 const byte packetSize = 10;
	 const byte datasize = 7;
	 const int bufsize = 64;
	 byte buf[64];
	 int readsize;

	 const byte errorCountThreshold = 10;
	 byte errorCount;
	 byte error;

	 typedef union {
		 byte Packet[10];
		 struct {

			 byte Up : 1;		//packet[0]
			 byte Down : 1;
			 byte Right : 1;
			 byte Left : 1;
			 byte Triangle : 1;
			 byte Cross : 1;
			 byte Circle : 1;
			 byte Square : 1;

			 byte L1 : 1;		//packet[1]
			 byte L2 : 1;
			 byte L3 : 1;
			 byte R1 : 1;
			 byte R2 : 1;
			 byte R3 : 1;
			 byte Start : 1;
			 byte Select : 1;

			 byte Home : 1;	//packet[2]
			 byte fill : 7;

			 byte Left_Y;	//packet[3]
			 byte Left_X;	//packet[4]
			 byte Right_Y;	//packet[5]
			 byte Right_X;	//packet[6]
			 byte Chk;	//packet[7]	

			 byte Fotter1; //packet[8]	0x7c |
			 byte Fotter2; //packet[9] 0x7c |
									// パケットとのデータ共用部分ここまで
		 }Btn;

		 void Clear()
		 {
			 memset(&Packet[0], 0x00, 3);
			 memset(&Packet[3], 0x80, 4);
		 }
	 }ControllerUnion;

	 ControllerUnion ps, psOld;

	 void clearError();
 protected:


 public:
	bool Up()		{ return ps.Btn.Up; }
	bool Down()	{ return ps.Btn.Down; }
	bool Right()	{ return ps.Btn.Right; }
	bool Left()	{ return ps.Btn.Left; }
	bool Triangle(){ return ps.Btn.Triangle; }
	bool Cross()	{ return ps.Btn.Cross; }
	bool Circle()	{ return ps.Btn.Circle; }
	bool Square()	{ return ps.Btn.Square; }
	bool L1()		{ return ps.Btn.L1; }
	bool L2()		{ return ps.Btn.L2; }
	bool L3()		{ return ps.Btn.L3; }
	bool R1()		{ return ps.Btn.R1; }
	bool R2()		{ return ps.Btn.R2; }
	bool R3()		{ return ps.Btn.R3; }
	bool Start()	{ return ps.Btn.Start; }
	bool Select()	{ return ps.Btn.Select; }
	bool Home()	{ return ps.Btn.Home; }
	char Left_Y()	{ return ps.Btn.Left_Y - 127; }
	char Left_X()	{ return ps.Btn.Left_X - 127; }
	char Right_Y()	{ return ps.Btn.Right_Y - 127; }
	char Right_X()	{ return ps.Btn.Right_X - 127; }
	
	float D_Left_Y()	{ return (float)(ps.Btn.Left_Y  - 127) / 127; }
	float D_Left_X()	{ return (float)(ps.Btn.Left_X  - 127) / 127; }
	float D_Right_Y()	{ return (float)(ps.Btn.Right_Y - 127) / 127; }
	float D_Right_X()	{ return (float)(ps.Btn.Right_X - 127) / 127; }

	bool Rise_Up() { return ps.Btn.Up && !psOld.Btn.Up; }
	bool Rise_Down() { return ps.Btn.Down && !psOld.Btn.Down; }
	bool Rise_Right() { return ps.Btn.Right && !psOld.Btn.Right; }
	bool Rise_Left() { return ps.Btn.Left && !psOld.Btn.Left; }
	bool Rise_Triangle() { return ps.Btn.Triangle && !psOld.Btn.Triangle; }
	bool Rise_Cross() { return ps.Btn.Cross && !psOld.Btn.Cross; }
	bool Rise_Circle() { return ps.Btn.Circle && !psOld.Btn.Circle; }
	bool Rise_Square() { return ps.Btn.Square && !psOld.Btn.Square; }
	bool Rise_L1() { return ps.Btn.L1 && !psOld.Btn.L1; }
	bool Rise_L2() { return ps.Btn.L2 && !psOld.Btn.L2; }
	bool Rise_L3() { return ps.Btn.L3 && !psOld.Btn.L3; }
	bool Rise_R1() { return ps.Btn.R1 && !psOld.Btn.R1; }
	bool Rise_R2() { return ps.Btn.R2 && !psOld.Btn.R2; }
	bool Rise_R3() { return ps.Btn.R3 && !psOld.Btn.R3; }
	bool Rise_Start() { return ps.Btn.Start && !psOld.Btn.Start; }
	bool Rise_Select() { return ps.Btn.Select && !psOld.Btn.Select; }
	bool Rise_Home() { return ps.Btn.Home && !psOld.Btn.Home; }

	bool Fall_Up() { return !ps.Btn.Up && psOld.Btn.Up; }
	bool Fall_Down() { return !ps.Btn.Down && psOld.Btn.Down; }
	bool Fall_Right() { return !ps.Btn.Right && psOld.Btn.Right; }
	bool Fall_Left() { return !ps.Btn.Left && psOld.Btn.Left; }
	bool Fall_Triangle() { return !ps.Btn.Triangle && psOld.Btn.Triangle; }
	bool Fall_Cross() { return !ps.Btn.Cross && psOld.Btn.Cross; }
	bool Fall_Circle() { return !ps.Btn.Circle && psOld.Btn.Circle; }
	bool Fall_Square() { return !ps.Btn.Square && psOld.Btn.Square; }
	bool Fall_L1() { return !ps.Btn.L1 && psOld.Btn.L1; }
	bool Fall_L2() { return !ps.Btn.L2 && psOld.Btn.L2; }
	bool Fall_L3() { return !ps.Btn.L3 && psOld.Btn.L3; }
	bool Fall_R1() { return !ps.Btn.R1 && psOld.Btn.R1; }
	bool Fall_R2() { return !ps.Btn.R2 && psOld.Btn.R2; }
	bool Fall_R3() { return !ps.Btn.R3 && psOld.Btn.R3; }
	bool Fall_Start() { return !ps.Btn.Start && psOld.Btn.Start; }
	bool Fall_Select() { return !ps.Btn.Select && psOld.Btn.Select; }
	bool Fall_Home() { return !ps.Btn.Home && psOld.Btn.Home; }

	unsigned char Error() {	return error; }

	void init(HardwareSerial hs);
	unsigned char getData();
};

extern PsconClass Pscon;

#endif

