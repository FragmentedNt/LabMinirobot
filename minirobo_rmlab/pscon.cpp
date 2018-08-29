// 
// 
// 

#include "pscon.h"



void PsconClass::Init(HardwareSerial hs)
{
	serial = &hs;
	memset(buf, 0x00, bufsize);
	Ps.Clear();
	PsOld.Clear();
}

void PsconClass::GetData()
{
	memset(buf, 0x00, bufsize);
	//if ((readsize = serial->readBytes(buf, (int)bufsize)) == -1)
	if ((readsize = serial->readBytes(buf, (int)bufsize)) >= packetSize)
	{
		if (!Ps.Btn.Error)
			if (++Ps.Btn.Error_Count > errorCountThreshold)
				Ps.Clear();
	}
	else
	{
		for (int readindex = readsize-1; readindex >= packetSize - 1; readindex--)
		{
			if (buf[readindex] == 0x7c && buf[readindex-1] == 0x7c)
			{
				char *b = &buf[readindex - packetSize + 1];
				unsigned char chk = 0x00;
				for (int i = 0; i < datasize; i++) chk ^= b[i];
				if (chk == b[datasize])
				{
					PsOld = Ps;
					memcpy(Ps.Packet, b, packetSize);
					Calcurate();
					return;
				}
			}
		}
		Ps.Btn.Error_Count++;
	}
}

void PsconClass::Calcurate()
{
	Ps.Btn.Error_Count = 0;
	Ps.Btn.Error = 0;
}


PsconClass Pscon;

