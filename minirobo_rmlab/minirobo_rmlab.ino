#include "TM0.h"
#include "MotorDriverTA8428K.h"
#include "pscon.h"
#include <math.h>

void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200);
	Pscon.init(Serial);
	pinMode(13, OUTPUT);
	TCCR0B = (TCCR0B & 0b11111000) | 0x02;
	TCCR1B = (TCCR1B & 0b11111000) | 0x02;
	TCCR2B = (TCCR2B & 0b11111000) | 0x02;
	TM0.init();
	MD0.init(5,  6, true);
	MD1.init(9, 10, true, true);
	MD2.init(3, 11, true);
}


void loop() {
  // put your main code here, to run repeatedly:
	float forward = 0, turn = 0; 
	static bool indivisualTwoWheel = false;

	blinkLED();
	Pscon.getData();
	//Pscon.debug();

	if(Pscon.Fall_L3())
		indivisualTwoWheel = !indivisualTwoWheel;
	if(Pscon.Fall_Select())
		MD0.inversion();
	if(Pscon.Fall_Start())
		MD1.inversion();
		
	if(indivisualTwoWheel)
	{
		MD0.set(2 * Pscon.Left_Y());
		MD1.set(2 * Pscon.Right_Y());
	}
	else
	{
		if(abs(Pscon.D_Left_Y()) > 0.3)
			forward = Pscon.D_Left_Y();
		if(abs(Pscon.D_Right_X()) > 0.3)
			turn = Pscon.D_Right_X();
		MD0.set(255 * forward + 255 * turn);
		MD1.set(255 * forward - 255 * turn);
	}
	
	if (Pscon.R1())
		MD2.set(100);
	else if (Pscon.R2())
		MD2.set(-100);
	else
		MD2.set(0);
	TM0.Delay(9); 
	//printTimeSpan();
	//demo();
}

void printTimeSpan()
{
	static unsigned long prev_time = 0, current_time = 0;
	current_time = TM0.Micros();
	Serial.println(current_time - prev_time);
	prev_time = TM0.Micros();
}

void blinkLED()
{
	static int ms = 0;
	int mi = TM0.Millis();
	if (mi - ms > 500)
	{
		ms = mi;
		PINB |= _BV(5);	// Arduino nanoのPB5(D13番)に接続されているLEDを操作
						// AVRの仕様でPINxに書き込むと出力が反転する(通常の出力レジスタはPORTx)
	}
}

void demo()
{
	static int ms = 0;
	int mi = TM0.Millis();
	if (mi - ms < 2000)
	{
		MD0.set(0);
		MD1.set(0);
		MD2.set(0);
	}
	else if (mi - ms < 4000)
	{
		MD0.set(100);
		MD1.set(100);
		MD2.set(100);
	}
	else if (mi - ms < 6000)
	{
		MD0.set(0);
		MD1.set(0);
		MD2.set(0);
	}
	else if (mi - ms < 8000)
	{
		MD0.set(-100);
		MD1.set(-100);
		MD2.set(-100);
	}
	else
	{
		ms = mi;
	}
}