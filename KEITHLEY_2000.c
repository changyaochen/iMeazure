#include <gpib.h>
#include <ansi_c.h>
#include "KEITHLEY_2000.h"	   

void keithley_initialize(void)
{
	keithley.handle= ibdev (0, KEITHLEY_ADDRESS, NO_SAD, T10s, 1, 0);  
	keithley.initialized=1;
}

double keithley_get_data(void)
{
	char buf[20];
	ibwrt (keithley.handle, KEITHLEY_FETCH, strlen(KEITHLEY_FETCH));
	ibrd (keithley.handle, &buf, 20); 
	return atof(buf);
}

