#include <utility.h>
#include <gpib.h>
#include <ansi_c.h>
#include "Anritsu_68369.h"
#include <visa.h>

void Anritsu_68369_initialize(void)       
{
	char buf[100];
	Anritsu_68369.handle= ibdev (0, Anritsu_68369_ADDR, NO_SAD, T100ms, 1, 0);   
	//sprintf(buf,"%s","conn 1, '1'\n");
	//ibwrt (SIM928.handle, buf, strlen(buf)); /* talk to slot 1*/
	//sprintf(buf,"%s%s%s%s%s","sndt 1, ","'","*rst","'","\n");  //reset
	//ibwrt (SIM928.handle, buf, strlen(buf)); // rest output
	//sprintf(buf,"%s%s%s%s%s","sndt 1, ","'", SIM928_OUTPUT,"'","\n");  // output on 
	//ibwrt (SIM928.handle, buf, strlen(buf));
	/*sprintf(buf,"%s%s",SIM928_TRIGGER, "\n"); /* start */
	/*ibwrt (SIM928.handle, buf, strlen(buf));*/

}

void Anritsu_68369_set(double frequency)
{
	char buf[100];
	sprintf(buf,"%s%s%f%s%s", Anritsu_68369_SET," ",frequency," MH", "\n");  //set frequency in MHz
	ibwrt (Anritsu_68369.handle, buf, strlen(buf));
	/*sprintf(buf,"%s%s",SIM928_TRIGGER, "\n"); /* start */
	/*ibwrt (SIM928.handle, buf, strlen(buf));*/  

}
