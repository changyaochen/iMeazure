#include <gpib.h>
#include <ansi_c.h>
#include "lakeshore340.h"	   

void lakeshore340_init(void)
{
	lakeshore340.handle= ibdev (0, LAKESHORE340_ADDR, NO_SAD, T1s, 1, 0);  
}


double lakeshore340_readtemp(void)
{
	char buf[20];
	ibwrt (lakeshore340.handle, LAKESHORE340_READT, strlen(LAKESHORE340_READT));
	ibrd (lakeshore340.handle, &buf, 20); 
	return atof(buf);
}

