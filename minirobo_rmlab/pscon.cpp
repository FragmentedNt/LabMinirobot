// 
// 
// 

#include "pscon.h"



void PsconClass::init(HardwareSerial hs)
{
	serial = &hs;
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
					return error;
				}
			}
		}
	}
	if (!error)
	{
		if (++errorCount > errorCountThreshold)
			error = 1;
	}
	return error;
}


void PsconClass::clearError()
{
	errorCount = 0;
	error = 0;
}


PsconClass Pscon;

