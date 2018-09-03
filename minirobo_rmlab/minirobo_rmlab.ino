#include "TM0.h"
#include "MotorDriverTA8428K.h"
#include "pscon.h"
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
	blinkLED();
	Pscon.getData();
	//Pscon.debug();
	MD0.set(2 * Pscon.Left_Y());
	MD1.set(2 * Pscon.Right_Y());
	if (Pscon.R1())
		MD2.set(100);
	else if (Pscon.R2())
		MD2.set(-100);
	else
		MD2.set(0);
	TM0.Delay(9); 
	//printTimeSpan();
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