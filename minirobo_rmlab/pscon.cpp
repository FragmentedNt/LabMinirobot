// 
// 
// 

#include "pscon.h"


void PsconClass::init(HardwareSerial& hs)
{
	serial = &hs;
	serial->setTimeout(0);

	memset(buf, 0x00, bufsize);
	ps.Clear();
	psOld.Clear();

	error = 1;
	errorCount = 255;
}

unsigned char PsconClass::getData()
{
	memset(buf, 0x00, bufsize);
	if ((readsize = serial->readBytes(buf, (int)bufsize)) >= packetSize)
	{
		for (int readindex = readsize-1; readindex >= packetSize - 1; readindex--)
		{
			if (buf[readindex] == 0x7c && buf[readindex-1] == 0x7c)
			{
				byte *b = &buf[readindex - packetSize + 1];
				unsigned char chk = 0x00;
				for (int i = 0; i < datasize; i++) chk ^= b[i];
				if (chk == b[datasize])
				{
					psOld = ps;
					memcpy(ps.Packet, b, packetSize);
					clearError();
					calculate();
					return error;
				}
			}
		}
	}
	if (!error)
	{
		if (++errorCount > errorCountThreshold)
		{
			error = 1;
			ps.Clear();
			psOld.Clear();
		}
	}
	return error;
}

void PsconClass::rx2tx()
{
	static int cnt = 0;
	int inputchar = serial->read();
	if (inputchar != -1)
	{
		serial->print(inputchar, HEX);
		cnt++;
	}
	if (cnt >= packetSize)
	{
		serial->println("");
		cnt = 0;
	}
}

String PsconClass::toString()
{
	String str = "";

	str.concat(D_Left_X());
	str.concat(" ");
	str.concat(D_Left_Y());
	str.concat(" ");
	str.concat(D_Right_X());
	str.concat(" ");
	str.concat(D_Right_Y());
	str.concat(" ");

	if (Up())		str.concat("U");	else	str.concat("-");
	if (Down())		str.concat("D");	else	str.concat("-");
	if (Right())	str.concat("R");	else	str.concat("-");
	if (Left())		str.concat("L");	else	str.concat("-");
	str.concat(" ");
	if (Triangle())	str.concat("N");	else	str.concat("-");
	if (Cross()	)	str.concat("S");	else	str.concat("-");
	if (Circle())	str.concat("E");	else	str.concat("-");
	if (Square())	str.concat("W");	else	str.concat("-");
	str.concat(" ");
	if (L1())		str.concat("L1");	else	str.concat("--");
	if (L2())		str.concat("L2");	else	str.concat("--");
	if (L3())		str.concat("L3");	else	str.concat("--");
	str.concat(" ");
	if (R1())		str.concat("R1");	else	str.concat("--");
	if (R2())		str.concat("R2");	else	str.concat("--");
	if (R3())		str.concat("R3");	else	str.concat("--");
	str.concat(" ");
	if (Start())	str.concat("St");	else	str.concat("--");
	if (Select())	str.concat("Se");	else	str.concat("--");
	if (Home())		str.concat("Ho");	else	str.concat("--");
	return str;
}

size_t PsconClass::debug()
{
	return Serial.println(Pscon.toString());
}

void PsconClass::clearError()
{
	errorCount = 0;
	error = 0;
}

void PsconClass::calculate()
{
	if (ps.Btn.Left_Y == 0)		ps.Btn.Left_Y = 1;
	if (ps.Btn.Left_X == 0)		ps.Btn.Left_X = 1;
	if (ps.Btn.Right_Y == 0)	ps.Btn.Right_Y = 1;
	if (ps.Btn.Right_X == 0)	ps.Btn.Right_X = 1;
}


PsconClass Pscon;

