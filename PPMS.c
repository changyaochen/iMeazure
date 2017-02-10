#include <formatio.h>
#include <utility.h>
#include <gpib.h>
#include <ansi_c.h>
#include "PPMS.h"	   

void ppms_initialize(void)
{
	char buf[100]="";
	ppms.handle= ibdev (0, PPMS_ADDR, NO_SAD, T1s, 1,0);
	ppms.initialized=1;
	ppms.ramping=0;
}

double ppms_get_temp(void)
{
	int i;
	char buf[100]="";
	char buf1[100]="";
	float answer=0;
	ibwrt(ppms.handle,PPMS_GET_TEMP,strlen(PPMS_GET_TEMP));  	
	if (!(ibrd (ppms.handle, &buf, 100)&ERR)) { // only process if not error!
		buf[ibcnt]=0;
		i=FindPattern (buf, 0, ibcnt, ",", 0, 1); // strarting from the right, find comma
		CopyBytes (buf1, 0, buf,i+1, ibcnt-i-2);
		answer=atof(buf1);
	}

	else printf("You suck : error in get_temp! \n");
	return answer;

}

double ppms_get_field(void)
{
	int i;
	char buf[100]="";
	char buf1[100]="";
	float answer=0;   
	ibwrt(ppms.handle,PPMS_GET_FIELD,strlen(PPMS_GET_FIELD));  		
	if (!(ibrd (ppms.handle, &buf, 100)&ERR)) { // only process if not error!   
		buf[ibcnt]=0;
		i=FindPattern (buf, 0, ibcnt, ",", 0, 1); // strarting from the right, find comma
		CopyBytes (buf1, 0, buf,i+1, ibcnt-i-2);
		answer=atof(buf1)/10000; //To convert from Oersted to tesla
		if (fabs(answer-ppms.target_field)<0.0001) {ppms.ramping=0;} //stop the sweep when at the end     
	}
	else printf("error in get_field");
	return answer;
	
}

void ppms_stop_sweep(void)
{
	ppms.ramping=0;
}

void ppms_ramp(double target, double rate)
{
	char buf[100];
	ppms.ramping=1;
	ppms.target_field=target;
	// factors 1000, 16 is to convert from Tesla->Oe, Tesla/min ->Oe/sec
	sprintf(buf,"%s%s%f%s%f%s",PPMS_SET_FIELD," ",target*10000," ",rate*166.6666," 0 1\n"); //linear approach driven mode
	ibwrt (ppms.handle, buf, strlen(buf));
}
