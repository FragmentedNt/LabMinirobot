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
 protected:


 public:
	void init();
};

extern PsconClass Pscon;

#endif

