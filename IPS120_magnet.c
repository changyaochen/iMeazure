#include <utility.h>
#include <gpib.h>
#include <ansi_c.h>
#include "IPS120_magnet.h"	   

/* 	This is to control the magnet while keeeping it persistent as long as possible 	*/
/* 	Saves helium but takes more time 												*/
/* But helium is more important - right?											*/

void ips120_initialize(void)
{
	char buf[100]="";
	ips120.handle= ibdev (0, 25, NO_SAD, T1s, 0, 1037); // 1037 (1024+13) - means stop the readout when reach symbol 13, CR
	ips120.initialized=1;
	ips120.ramping=0;
	ibrd (ips120.handle, &buf, 100); // Hack!!! Clear read buffer
	ibwrt(ips120.handle,"C3\r",3); // Send remote unlocked
	ibrd (ips120.handle, &buf, 100); 
	ibwrt(ips120.handle,"A0\r",3); // Say HOLD before doing anything
	ibrd (ips120.handle, &buf, 100); 
	ibwrt(ips120.handle,"Q4\r",3); // Demand extended resolution
	ibrd (ips120.handle, &buf, 100); 
//	ibwrt(ips120.handle,"X\r",2);
//	ibrd (ips120.handle, &buf, 100); 
//	buf[ibcntl]=0; 
//	if (buf[8]==*"0") { // If heater is off and magnet at zero field
//		ibwrt(ips120.handle,"H1\r",3);	   // Turn on the heater
//		ibrd (ips120.handle, &buf, 100); 
//	}
}

double ips120_get_field(void)
{
	char buf[100]="";
	int persistent=0;
	
	ibwrt(ips120.handle,"X\r",2);   // read status 
	ibrd (ips120.handle, &buf, 100); 
	if (buf[8]!=*"1") persistent=1; // check if the heater is on
	// If just finished ramping lets turn off the heater and go to zero current
	if ((buf[11]==*"0")&&(ips120.ramping)) { // 11th byte is 0 magnet finished sweeping and now holding 
		ips120.ramping=0;
		Delay(5);// wait to make sure current is stable
		ibwrt(ips120.handle,"H0\r",3);	   // Turn off the heater
		ibrd (ips120.handle, &buf, 100); 
		Delay(30);// Wait for the heater to cool down
		ibwrt(ips120.handle,"A2\r",3);	   // Go to zero 
		ibrd (ips120.handle, &buf, 100); 
	}
	if  (!persistent) { // if persistent read output field, if not - persistent field
		ibwrt (ips120.handle, "R7\r", 3);
		ibrd (ips120.handle, &buf, 100); 
	} else {
		ibwrt (ips120.handle, "R18\r", 4);
		ibrd (ips120.handle, &buf, 100);
	}
	buf[0]=*" ";// First returned symbol is echo;
	buf[ibcnt]=0;// last symbol is zero, to make string zero-terminated
	return atof(buf);
}

void ips120_stop_sweep(void)
{
	char buf[100]="";                
	ibwrt (ips120.handle, "A0\r", 3); // Send "Hold"
	ibrd (ips120.handle, &buf, 100); 
}

void ips120_ramp(double target,double rate)
{
	char buf[100];
	int done;
	double field;
	
	ips120.ramping=1;
	ibwrt(ips120.handle,"X\r",2);   // read status, 8th byte - heater status
	ibrd (ips120.handle, &buf, 100); 
	/* if heater is off - magnet persistent we need to ramp up current and turn on heater */
	if (buf[8]!=*"1") { // heater us off, magnet at field
		ibwrt (ips120.handle, "R18\r", 4);
		ibrd (ips120.handle, &buf, 100);
		buf[0]=*" ";// First returned symbol is echo;
		buf[ibcnt]=0;// last symbol is zero, to make string zero-terminated
		field=atof(buf);
		sprintf(buf,"%s%s%f%s","J"," ",field,"\r");  // So setpoint is persistent field
		ibwrt (ips120.handle, buf, strlen(buf));
		ibrd (ips120.handle, &buf, 100); 							 
		ibwrt(ips120.handle,"A1\r",3);	   // Go to setpoint
		ibrd (ips120.handle, &buf, 100); 
		done=0;
		while (!done) { //wait for the current to ramp up
			Delay(0.5); // so that we dont ask all the time
			ibwrt(ips120.handle,"X\r",2);   // read status, hold until done 
			ibrd (ips120.handle, &buf, 100); 
			if (buf[11]==*"0") done=1;
		}	
		Delay(2); // wait for the current to settle little
		ibwrt(ips120.handle,"H1\r",3);	   // Turn on the heater when at setpoint
		ibrd (ips120.handle, &buf, 100); 
		Delay(0.5); // lets do it twice so that the fuckin'thing works
		ibwrt(ips120.handle,"H1\r",3);	   // Turn on the heater when at setpoint
		ibrd (ips120.handle, &buf, 100); 

		Delay(5); // wait to heater to warm up
	}
	/* now magent is at field, heater is on -- continue */
	sprintf(buf,"%s%s%f%s","J"," ",target,"\r");  // Target field
	ibwrt (ips120.handle, buf, strlen(buf));
	ibrd (ips120.handle, &buf, 100); 							 
	sprintf(buf,"%s%s%f%s","T"," ",rate,"\r");					 //rate
	ibwrt (ips120.handle, buf, strlen(buf));
	ibrd (ips120.handle, &buf, 100); 
	ibwrt (ips120.handle, "A1\r", 3); // Send Ramp to setpoint 
	ibrd (ips120.handle, &buf, 100); 
}


