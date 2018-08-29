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
	 const unsigned char packetSize = 10;
	 const unsigned char datasize = 7;
	 const unsigned char errorCountThreshold = 10;
	 const int bufsize = 64;
	 char buf[64];
	 int readsize;
	 typedef union {
		 unsigned char Packet[10];
		 struct {

			 unsigned char Up : 1;		//packet[0]
			 unsigned char Down : 1;
			 unsigned char Right : 1;
			 unsigned char Left : 1;
			 unsigned char Triangle : 1;
			 unsigned char Cross : 1;
			 unsigned char Circle : 1;
			 unsigned char Square : 1;

			 unsigned char L1 : 1;		//packet[1]
			 unsigned char L2 : 1;
			 unsigned char L3 : 1;
			 unsigned char R1 : 1;
			 unsigned char R2 : 1;
			 unsigned char R3 : 1;
			 unsigned char Start : 1;
			 unsigned char Select : 1;

			 unsigned char Home : 1;	//packet[2]
			 unsigned char fill : 7;

			 unsigned char Left_Y;	//packet[3]
			 unsigned char Left_X;	//packet[4]
			 unsigned char Right_Y;	//packet[5]
			 unsigned char Right_X;	//packet[6]
			 unsigned char Chk;	//packet[7]	

			 unsigned char Fotter1; //packet[8]	0x7c |
			 unsigned char Fotter2; //packet[9] 0x7c |
									// パケットとのデータ共用部分ここまで


			 double Degree_L;
			 unsigned char Duty_L;

			 double Degree_R;
			 unsigned char Duty_R;

			 unsigned char Error_Count;
			 unsigned char Error;
		 }Btn;

		 void Clear()
		 {
			 memset(&Packet[0], 0x00, 3);
			 memset(&Packet[3], 0x80, 4);
			 Btn.Degree_L = Btn.Degree_R = 0;
			 Btn.Duty_L = Btn.Duty_R = 0;
			 Btn.Error = 1;
			 Btn.Error_Count = 255;
		 }
	 }ControllerUnion;

	 ControllerUnion Ps, PsOld;

	 void Calcurate();
 protected:


 public:
	unsigned char Up()		{ return Ps.Btn.Up; }
	unsigned char Down()	{ return Ps.Btn.Down; }
	unsigned char Right()	{ return Ps.Btn.Right; }
	unsigned char Left()	{ return Ps.Btn.Left; }
	unsigned char Triangle(){ return Ps.Btn.Triangle; }
	unsigned char Cross()	{ return Ps.Btn.Cross; }
	unsigned char Circle()	{ return Ps.Btn.Circle; }
	unsigned char Square()	{ return Ps.Btn.Square; }
	unsigned char L1()		{ return Ps.Btn.L1; }
	unsigned char L2()		{ return Ps.Btn.L2; }
	unsigned char L3()		{ return Ps.Btn.L3; }
	unsigned char R1()		{ return Ps.Btn.R1; }
	unsigned char R2()		{ return Ps.Btn.R2; }
	unsigned char R3()		{ return Ps.Btn.R3; }
	unsigned char Start()	{ return Ps.Btn.Start; }
	unsigned char Select()	{ return Ps.Btn.Select; }
	unsigned char Home()	{ return Ps.Btn.Home; }
	signed char Left_Y()	{ return Ps.Btn.Left_Y - 127; }
	signed char Left_X()	{ return Ps.Btn.Left_X - 127; }
	signed char Right_Y()	{ return Ps.Btn.Right_Y - 127; }
	signed char Right_X()	{ return Ps.Btn.Right_X - 127; }
	
	unsigned char Rise_Up() { return Ps.Btn.Up && !PsOld.Btn.Up; }
	unsigned char Rise_Down() { return Ps.Btn.Down && !PsOld.Btn.Down; }
	unsigned char Rise_Right() { return Ps.Btn.Right && !PsOld.Btn.Right; }
	unsigned char Rise_Left() { return Ps.Btn.Left && !PsOld.Btn.Left; }
	unsigned char Rise_Triangle() { return Ps.Btn.Triangle && !PsOld.Btn.Triangle; }
	unsigned char Rise_Cross() { return Ps.Btn.Cross && !PsOld.Btn.Cross; }
	unsigned char Rise_Circle() { return Ps.Btn.Circle && !PsOld.Btn.Circle; }
	unsigned char Rise_Square() { return Ps.Btn.Square && !PsOld.Btn.Square; }
	unsigned char Rise_L1() { return Ps.Btn.L1 && !PsOld.Btn.L1; }
	unsigned char Rise_L2() { return Ps.Btn.L2 && !PsOld.Btn.L2; }
	unsigned char Rise_L3() { return Ps.Btn.L3 && !PsOld.Btn.L3; }
	unsigned char Rise_R1() { return Ps.Btn.R1 && !PsOld.Btn.R1; }
	unsigned char Rise_R2() { return Ps.Btn.R2 && !PsOld.Btn.R2; }
	unsigned char Rise_R3() { return Ps.Btn.R3 && !PsOld.Btn.R3; }
	unsigned char Rise_Start() { return Ps.Btn.Start && !PsOld.Btn.Start; }
	unsigned char Rise_Select() { return Ps.Btn.Select && !PsOld.Btn.Select; }
	unsigned char Rise_Home() { return Ps.Btn.Home && !PsOld.Btn.Home; }

	unsigned char Fall_Up() { return !Ps.Btn.Up && PsOld.Btn.Up; }
	unsigned char Fall_Down() { return !Ps.Btn.Down && PsOld.Btn.Down; }
	unsigned char Fall_Right() { return !Ps.Btn.Right && PsOld.Btn.Right; }
	unsigned char Fall_Left() { return !Ps.Btn.Left && PsOld.Btn.Left; }
	unsigned char Fall_Triangle() { return !Ps.Btn.Triangle && PsOld.Btn.Triangle; }
	unsigned char Fall_Cross() { return !Ps.Btn.Cross && PsOld.Btn.Cross; }
	unsigned char Fall_Circle() { return !Ps.Btn.Circle && PsOld.Btn.Circle; }
	unsigned char Fall_Square() { return !Ps.Btn.Square && PsOld.Btn.Square; }
	unsigned char Fall_L1() { return !Ps.Btn.L1 && PsOld.Btn.L1; }
	unsigned char Fall_L2() { return !Ps.Btn.L2 && PsOld.Btn.L2; }
	unsigned char Fall_L3() { return !Ps.Btn.L3 && PsOld.Btn.L3; }
	unsigned char Fall_R1() { return !Ps.Btn.R1 && PsOld.Btn.R1; }
	unsigned char Fall_R2() { return !Ps.Btn.R2 && PsOld.Btn.R2; }
	unsigned char Fall_R3() { return !Ps.Btn.R3 && PsOld.Btn.R3; }
	unsigned char Fall_Start() { return !Ps.Btn.Start && PsOld.Btn.Start; }
	unsigned char Fall_Select() { return !Ps.Btn.Select && PsOld.Btn.Select; }
	unsigned char Fall_Home() { return !Ps.Btn.Home && PsOld.Btn.Home; }

	void Init(HardwareSerial hs);
	void GetData();


};

extern PsconClass Pscon;

#endif

