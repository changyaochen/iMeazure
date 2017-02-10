#include <utility.h>
#include <gpib.h>
#include <ansi_c.h>
#include "YOKO.h"

void YOKO_initialize(void)       
{
	char buf[100];
	YOKO.handle= ibdev (0, YOKO_ADDR, NO_SAD, T100ms, 1, 0);   
	sprintf(buf,"%s",":SOURce:FUNCtion VOLTage\n"); /* set source voltage */
	ibwrt (YOKO.handle, buf, strlen(buf));
	sprintf(buf,"%s%s%f%s",YOKO_SET," ",+0.0,"\n"); /* set to zero voltage */
	ibwrt (YOKO.handle, buf, strlen(buf));
	sprintf(buf,"%s%s%i%s",YOKO_OUTPUT," ",1,"\n"); /* output on */
	ibwrt (YOKO.handle, buf, strlen(buf));
	//sprintf(buf,"%s%s",YOKO_TRIGGER, "\n"); /* start */
	//ibwrt (YOKO.handle, buf, strlen(buf));

}

void YOKO_set(double voltage)
{
	char buf[100];
	sprintf(buf,"%s%s%f%s",YOKO_SET," ",voltage,"\n");
	ibwrt (YOKO.handle, buf, strlen(buf));
	//sprintf(buf,"%s%s",YOKO_TRIGGER, "\n"); /* start */
	//ibwrt (YOKO.handle, buf, strlen(buf));

}
