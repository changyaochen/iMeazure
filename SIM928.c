#include <utility.h>
#include <gpib.h>
#include <ansi_c.h>
#include "SIM928.h"
#include <visa.h>   
#include <time.h> 
#include "iMeazure_logic.h"

int reest_time(void)
{ 
	return (int)TIME % 600;		 //reset the SIM928 every 5 minutes 
}

void SIM928_initializeN1(void)       
{
	char buf[100];
	SIM928.handle= ibdev (0, SIM928_ADDR, NO_SAD, T100ms, 1, 0);   
	//sprintf(buf,"%s","conn 1, '1'\n");
	//ibwrt (SIM928.handle, buf, strlen(buf)); /* talk to slot 1*/
	sprintf(buf,"%s%s%s%s%s","sndt 1, ","'","*rst","'","\n term LF\n");  //reset
	ibwrt (SIM928.handle, buf, strlen(buf)); // rest output
	sprintf(buf,"%s%s%s%s%s","sndt 1, ","'", SIM928_OUTPUT,"'","\n");  // output on 
	ibwrt (SIM928.handle, buf, strlen(buf));
	/*sprintf(buf,"%s%s",SIM928_TRIGGER, "\n"); /* start */
	/*ibwrt (SIM928.handle, buf, strlen(buf));*/

}

void SIM928_initializeN2(void)       
{
	char buf[100];
	SIM928.handle= ibdev (0, SIM928_ADDR, NO_SAD, T100ms, 1, 0);   
	sprintf(buf,"%s%s%s%s%s","sndt 2, ","'","*rst","'","\n term LF\n");  //reset
	ibwrt (SIM928.handle, buf, strlen(buf)); // rest output
	sprintf(buf,"%s%s%s%s%s","sndt 2, ","'", SIM928_OUTPUT,"'","\n");  // output on 
	ibwrt (SIM928.handle, buf, strlen(buf));
}

void SIM928_initializeN3(void)       
{
	char buf[100];
	SIM928.handle= ibdev (0, SIM928_ADDR, NO_SAD, T100ms, 1, 0);   
	sprintf(buf,"%s%s%s%s%s","sndt 3, ","'","*rst","'","\n");  //reset
	ibwrt (SIM928.handle, buf, strlen(buf)); // rest output
	sprintf(buf,"%s%s%s%s%s","sndt 3, ","'", SIM928_OUTPUT,"'","\n");  // output on 
	ibwrt (SIM928.handle, buf, strlen(buf));
}

void SIM928_initializeN4(void)       
{
	char buf[100];
	SIM928.handle= ibdev (0, SIM928_ADDR, NO_SAD, T100ms, 1, 0);   
	sprintf(buf,"%s%s%s%s%s","sndt 4, ","'","*rst","'","\n");  //reset
	ibwrt (SIM928.handle, buf, strlen(buf)); // rest output
	sprintf(buf,"%s%s%s%s%s","sndt 4, ","'", SIM928_OUTPUT,"'","\n");  // output on 
	ibwrt (SIM928.handle, buf, strlen(buf));
}

void SIM928N1_set(double voltage)
{
	char buf1[128];
	sprintf(buf1,"%s%s%s%s%f%s%s","FLSh 1 \n sndt 1, ","'", SIM928_SET," ",voltage,"'","\n");	    //flush the host queue and port buffer first
	ibwrt (SIM928.handle, buf1, strlen(buf1));
	if ( reest_time() == 0)
	{	  
		char buf[128];
		sprintf(buf,"%s","srst 1 \n");	    //reset the SIM928
		ibwrt (SIM928.handle, buf, strlen(buf));
	}


}
void SIM928N2_set(double voltage)
{
	char buf2[128];
	sprintf(buf2,"%s%s%s%s%f%s%s","FLSH 2\n sndt 2, ","'", SIM928_SET," ",voltage,"'","\n");
	ibwrt (SIM928.handle, buf2, strlen(buf2));
	if ( reest_time() == 0)
	{	  
		char buf[128];
		sprintf(buf,"%s","srst 2 \n");	    //reset the SIM928
		ibwrt (SIM928.handle, buf, strlen(buf));
	}
}

void SIM928N3_set(double voltage)
{
	char buf3[128];
	sprintf(buf3,"%s%s%s%s%f%s%s","FLSH 3\n sndt 3, ","'", SIM928_SET," ",voltage,"'","\n");
	ibwrt (SIM928.handle, buf3, strlen(buf3));
	if ( reest_time() == 0)
	{	  
		char buf[128];
		sprintf(buf,"%s","srst 3 \n");	    //reset the SIM928
		ibwrt (SIM928.handle, buf, strlen(buf));
	}
}

void SIM928N4_set(double voltage)
{
	char buf4[128];
	sprintf(buf4,"%s%s%s%s%f%s%s","FLSH 4\n sndt 4, ","'", SIM928_SET," ",voltage,"'","\n");
	ibwrt (SIM928.handle, buf4, strlen(buf4));
	if ( reest_time() == 0)
	{	  
		char buf[128];
		sprintf(buf,"%s","srst 4 \n");	    //reset the SIM928
		ibwrt (SIM928.handle, buf, strlen(buf));
	}
}
