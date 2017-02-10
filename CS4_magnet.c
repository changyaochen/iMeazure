#include <utility.h>
#include <gpib.h>
#include <ansi_c.h>
#include "CS4_magnet.h"	   

void cs4_initialize(void)
{
	char buf[100]="";
	cs4.handle= ibdev (0, CS4_ADDRESS, NO_SAD, T1s, 1, 0);
	cs4.initialized=1;
	cs4.ramping=0;
	ibwrt (cs4.handle, "*ESE 255\n", 9);   
	//init commands
	ibwrt(cs4.handle,"UNITS T\n",8); // our units are Tesla
	//ibrd (cs4.handle, &buf, 100); 
	ibwrt(cs4.handle,"SWEEP PAUSE\n",12); // Say HOLD before doing anything
	// HEATER SHOULD BE ON MANUALLY
}

double cs4_get_field(void)
{
	char buf[100]="";  
	int i;		 
	double field,f;
	ibwrt(cs4.handle,CS4_GET_STATE,strlen(CS4_GET_STATE)); 
	ibrd (cs4.handle, &buf, 100); 
	ibwrt(cs4.handle,CS4_GET_FIELD,strlen(CS4_GET_FIELD));  
	ibrd (cs4.handle, &buf, 100); 					 
	buf[ibcnt-2]=0; //cut out the final letter T reported by the magnet
	field=atof(buf);
	if (fabs(field-cs4.target_field)<0.0001) {cs4.ramping=0;} //stop the sweep when at the end
	return field;
}

void cs4_stop_sweep(void)
{
	char buf[100]="";    
	cs4.ramping=0;
	ibwrt (cs4.handle, CS4_PAUSE,strlen(CS4_PAUSE)); // Send "Hold"
}

void cs4_ramp(double llimit,double ulimit, double rate, int direction)
{
	char buf[100];
	cs4.ramping=1;
	sprintf(buf,"%s%s%f%s",CS4_SET_LLIMIT," ",llimit,"\n");
	ibwrt (cs4.handle, buf, strlen(buf));
	sprintf(buf,"%s%s%f%s",CS4_SET_ULIMIT," ",ulimit,"\n");
	ibwrt (cs4.handle, buf, strlen(buf));
	sprintf(buf,"%s%s%i%s%f%s",CS4_SET_RATE," ",0," ",rate,"\n"); // set ramp rate for ranges 0,1,2 the same
	ibwrt (cs4.handle, buf, strlen(buf));
	sprintf(buf,"%s%s%i%s%f%s",CS4_SET_RATE," ",1," ",rate,"\n");
	ibwrt (cs4.handle, buf, strlen(buf));
	sprintf(buf,"%s%s%i%s%f%s",CS4_SET_RATE," ",2," ",rate,"\n");
	ibwrt (cs4.handle, buf, strlen(buf));
	if (direction==1) { // depending on direction start sweep up or down
			sprintf(buf,"%s%s",CS4_SWEEP_UP,"\n");
			ibwrt (cs4.handle, buf, strlen(buf));
			cs4.target_field=ulimit;
		} else 
		{
			sprintf(buf,"%s%s",CS4_SWEEP_DOWN,"\n");
			ibwrt (cs4.handle, buf, strlen(buf));
			cs4.target_field=llimit;
		}

}

