#include <utility.h>
#include <gpib.h>
#include <ansi_c.h>
#include "SIM965.h"
#include <visa.h>   
#include <time.h> 
#include "iMeazure_logic.h"


int reest_time_1min(void)
{ 
	return (int)TIME % 3;		 //reset the SIM965 every 600 seconds, why?(11/5/2014), to "wake" up the tool (12/2/14) 
}


void SIM965_initializeN1(void)       
{
	char buf[100];
	SIM965.handle= ibdev (0, SIM965_ADDR, NO_SAD, T100ms, 1, 0);   
	// sprintf(buf,"%s%s%s%s%s","sndt 1, ","'","*rst","'","\n term LF\n");  //reset
	// ibwrt (SIM965.handle, buf, strlen(buf)); // rest output
	

}

void SIM965_initializeN2(void)       
{
	char buf[100];
	SIM965.handle= ibdev (0, SIM965_ADDR, NO_SAD, T100ms, 1, 0);   
	// sprintf(buf,"%s%s%s%s%s","sndt 1, ","'","*rst","'","\n term LF\n");  //reset
	// ibwrt (SIM965.handle, buf, strlen(buf)); // rest output
	

}

/*
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
*/

void SIM965N1_set(double frequency)
{
	char buf[128];
	char buf1[128];
	sprintf(buf,"%s%i%s","FLSh ", slot1, "\n" );
	ibwrt (SIM965.handle, buf, strlen(buf));
	sprintf(buf1,"%s%i%s%i%s%s%s%f%s%s","FLSh ", slot1, " \n sndt ", slot1, ", '", SIM965_SET," ",frequency,"'","\n");	    //flush the host queue and port buffer first
	ibwrt (SIM965.handle, buf1, strlen(buf1));
	
	/*
	if ( reest_time_1min() == 0)
	{	  
		char buf[128];
		sprintf(buf,"%s%i%s","srst ",slot1," \n");	    //reset the SIM965
		ibwrt (SIM965.handle, buf, strlen(buf));
	}  
	
	Message (" SIM965 srst command sent!");  */

}

void SIM965N2_set(double frequency)
{
	char buf[128];
	char buf1[128];
	sprintf(buf,"%s%i%s","FLSh ", slot2, "\n" );
	ibwrt (SIM965.handle, buf, strlen(buf));
	sprintf(buf1,"%s%i%s%i%s%s%s%f%s%s","FLSh ", slot2, " \n sndt ", slot2, ", '", SIM965_SET," ",frequency,"'","\n");	    //flush the host queue and port buffer first
	ibwrt (SIM965.handle, buf1, strlen(buf1));

	
	/*if ( reest_time_1min() == 0)
	{	  
		char buf[128];
		sprintf(buf,"%s","srst 2 \n");	    //reset the SIM965
		ibwrt (SIM965.handle, buf, strlen(buf));
	}
	  

	// Message ("SIM965 command sent!");   */

}

