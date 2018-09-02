// 
// 
// 

#include "MotorDriverTA8428K.h"


void MotorDriverTA8428KClass::init(byte pinA, byte pinB, bool brake = false, bool inverse = false)
{
	this->pinA = pinA;
	this->pinB = pinB;
	pinMode(pinA, OUTPUT);
	pinMode(pinB, OUTPUT);
	this->brake = brake;
	this->inverse = inverse;
	prev_power = 0;
	analogWrite(pinA, 0);
	analogWrite(pinB, 0);
	delayMicroseconds(100);
	set(0);
	delay(10);
	delayMicroseconds(10);
	millis();
	micros();
}

void MotorDriverTA8428KClass::set(short power)
{
	if (inverse)
		power *= -1;
	
	if (prev_power != power)
	{
		prev_power = power;
		analogWrite(pinA, 0);
		analogWrite(pinB, 0);
		delayMicroseconds(100);
	}

	if (power > 0)
	{
		if (power > 255)	power = 255;
		analogWrite(pinA, power);
		analogWrite(pinB, 0);
	}
	else if (power < 0)
	{
		if (power < -255)	power = -255;
		analogWrite(pinA, 0);
		analogWrite(pinB, -power);
	}
	else
	{
		if (brake)
		{
			analogWrite(pinA, 255);
			analogWrite(pinB, 255);
		}
		else 
		{
			analogWrite(pinA, 0);
			analogWrite(pinB, 0);
		}
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="power"></param>
/// <param name="brake"></param>
void MotorDriverTA8428KClass::set(short power, byte brake)
{
	this->brake = brake;
	set(power);
}

MotorDriverTA8428KClass MD0, MD1, MD2;

