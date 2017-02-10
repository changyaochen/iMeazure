#include <utility.h>
#include <gpib.h>
#include <ansi_c.h>
#include "KE2400#2.h"

void KE2400N2_initialize(void)       
{
	char buf[100];
	KE2400N2.handle= ibdev (0, KE2400N2_ADDR, NO_SAD, T100ms, 1, 0);   
//	sprintf(buf,"%s%s",KE2400N2_RANGE,"\n"); /* set the range */
//	ibwrt (KE2400N2.handle, buf, strlen(buf));
	sprintf(buf,"%s%s%f%s",KE2400N2_SET," ",+0.0,"\n"); /* set to zero voltage */
	ibwrt (KE2400N2.handle, buf, strlen(buf));
	sprintf(buf,"%s%s%s%s",KE2400N2_OUTPUT," ","ON","\n"); /* output on */
	ibwrt (KE2400N2.handle, buf, strlen(buf));

}

void KE2400N2_set(double voltage)
{
	char buf[100];
	sprintf(buf,"%s%s%f%s",KE2400N2_SET," ",voltage,"\n");
	ibwrt (KE2400N2.handle, buf, strlen(buf));
	//sprintf(buf,"%s",":READ?\n"); 
	//ibwrt (KE2400N2.handle, buf, strlen(buf));
}
