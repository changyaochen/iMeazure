#include <gpib.h>
#include <ansi_c.h>
#include "AMI_magnet.h"	   

void magnet_initialize(void)
{
	magnet.handle= ibdev (0, 23, NO_SAD, T100ms, 1, 0);  
	magnet.initialized=1;
}

double magnet_get_field(void)
{
	char buf[20];
	ibwrt (magnet.handle, MAG_GET_FIELD, strlen(MAG_GET_FIELD));
	ibrd (magnet.handle, &buf, 20); 
	return atof(buf);
}

void magnet_stop_sweep(void)
{
	ibwrt (magnet.handle, MAG_PAUSE, strlen(MAG_PAUSE));
}

void magnet_ramp(double target,double rate)
{
	char buf[100];
	sprintf(buf,"%s%s%f%s",MAG_SET_FIELD," ",target,"\n");
	ibwrt (magnet.handle, buf, strlen(buf));
	sprintf(buf,"%s%s%f%s",MAG_SET_RATE," ",rate,"\n");
	ibwrt (magnet.handle, buf, strlen(buf));
	ibwrt (magnet.handle, MAG_RAMP, strlen(MAG_RAMP));  
}


