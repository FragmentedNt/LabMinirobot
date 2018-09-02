// MotorDriverTA8428K.h

#ifndef _MOTORDRIVERTA8428K_h
#define _MOTORDRIVERTA8428K_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MotorDriverTA8428KClass
{
 private:
	 byte pinA, pinB;
	 bool inverse;
	 bool brake;
 protected:


 public:
	void init(byte pinA, byte pinB, bool brake = false, bool inverse = false );
	void set(short power);
	void set(short power, byte brake);
};

extern MotorDriverTA8428KClass MD0, MD1, MD2;

#endif
