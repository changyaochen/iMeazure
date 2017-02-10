#include <utility.h>
#include <gpib.h>
#include <ansi_c.h>
#include "AMI_2D_magnet.h"	 
#define TIME (double)clock()/CLOCKS_PER_SEC // time in seconds
//#define DELAY_BETWEEN_COMMANDS 0.03 // delay between commands sent to mag. - dies otherwise
#undef TESTING // use this to emulate the real magnet in software

void XYmagnet_initialize(void)
{
	//printf("%s","Initializing...");   
#ifndef TESTING 
	XYmagnet.handle_X= ibdev (0, X_MAGNET_ADDR, NO_SAD, T100ms, 1, 0); 
	XYmagnet.handle_Y= ibdev (0, Y_MAGNET_ADDR, NO_SAD, T100ms, 1, 0);
#else
	XYmagnet.test_rampstart_x=0;XYmagnet.test_rampstart_y=0;XYmagnet.test_xramping=0;XYmagnet.test_yramping=0;
#endif
	XYmagnet.initialized=1;
	XYmagnet.sweeping=0;
	XYmagnet.ramping=0;   
	//printf("%s%i%s%i%s","ok. handleX=",XYmagnet.handle_X,"    handleY=",XYmagnet.handle_Y,"\n");   
	
}

double XYmagnet_update(void)
{
	
#ifndef TESTING
	char buf[20];
	double x,y,r, theta;
	int status,stateX,stateY; // the current state of X and Y magnets (ramping/holding)
	//printf("%s","Updating...");   
	ibwrt (XYmagnet.handle_X, MAG_GET_STATE, strlen(MAG_GET_STATE));
	//Delay(DELAY_BETWEEN_COMMANDS);
	ibrd (XYmagnet.handle_X, &buf, 20);//problem 
	//Delay(DELAY_BETWEEN_COMMANDS);  
	if (!(ibsta & 0x8000)) stateX=atof(buf);  // so that we do not update if error
	ibwrt (XYmagnet.handle_Y, MAG_GET_STATE, strlen(MAG_GET_STATE));
	//Delay(DELAY_BETWEEN_COMMANDS);  
	ibrd (XYmagnet.handle_Y, &buf, 20);//problem? 
	//Delay(DELAY_BETWEEN_COMMANDS);  
	if (!(ibsta & 0x8000)) stateY=atof(buf);
	if (stateX==1 || stateY==1) XYmagnet.ramping=1; else XYmagnet.ramping=0; // If one of the magnets is ramping the ramp is not done
	/* now lets get the field */
	ibwrt (XYmagnet.handle_X, MAG_GET_FIELD, strlen(MAG_GET_FIELD));
	//Delay(DELAY_BETWEEN_COMMANDS);  
	ibrd (XYmagnet.handle_X, &buf, 20); 
	//Delay(DELAY_BETWEEN_COMMANDS);  
	if (!(ibsta & 0x8000)) XYmagnet.x = atof(buf);
	ibwrt (XYmagnet.handle_Y, MAG_GET_FIELD, strlen(MAG_GET_FIELD));
	//Delay(DELAY_BETWEEN_COMMANDS);  
	ibrd (XYmagnet.handle_Y, &buf, 20); 
	//Delay(DELAY_BETWEEN_COMMANDS);  
	if (!(ibsta & 0x8000)) XYmagnet.y = atof(buf);
	//printf("%s%i%s%f%s%i%s%f%s","stateX=",stateX, "  Hx",XYmagnet.x, "  stateY=",stateY,"  Hy",XYmagnet.y,"\n");
#else
	if (XYmagnet.test_xramping) {	
			XYmagnet.x=XYmagnet.test_rampstart_x+XYmagnet.test_rate_x*(TIME-XYmagnet.test_rampstarttime_x);
			//printf("%f%s",XYmagnet.x,"\n");
			if ((TIME-XYmagnet.test_rampstarttime_x)>XYmagnet.test_timetorampx) {XYmagnet.test_xramping=0;}
	} 
	if (XYmagnet.test_yramping) {
			XYmagnet.y=XYmagnet.test_rampstart_y+XYmagnet.test_rate_y*(TIME-XYmagnet.test_rampstarttime_y);
			if ((TIME-XYmagnet.test_rampstarttime_y)>XYmagnet.test_timetorampy) {XYmagnet.test_yramping=0;}
	}																		  
	if (XYmagnet.test_xramping||XYmagnet.test_yramping) {XYmagnet.ramping=1;} else {XYmagnet.ramping=0;}
#endif	
	XYmagnet.r=sqrt(XYmagnet.x*XYmagnet.x+XYmagnet.y*XYmagnet.y);
	if (XYmagnet.r>0) { if (XYmagnet.y>0){XYmagnet.theta=acos(XYmagnet.x/XYmagnet.r);} else  // to return values from 0 to 2PI
								{XYmagnet.theta=2*3.14159265-acos(XYmagnet.x/XYmagnet.r);}} else
		{XYmagnet.theta=0;} // so that we dont err at zero
	return 0;
}

void XYmagnet_stop_sweep(void)
{
#ifndef TESTING
	ibwrt (XYmagnet.handle_X, MAG_PAUSE, strlen(MAG_PAUSE));
	ibwrt (XYmagnet.handle_Y, MAG_PAUSE, strlen(MAG_PAUSE)); 
	XYmagnet.ramping=0;
#else
	XYmagnet.test_xramping=0;XYmagnet.test_yramping=0;
	XYmagnet.ramping=0;
#endif
}

void XYmagnet_ramp(double X_target,double Y_target, double ramp_rate_x,double ramp_rate_y)
{
#ifndef TESTING
	char buf[100];
	//printf("%s%f%s%f%s","ramping to X=",X_target,"    Y=",Y_target,"");  
	// X magnet
	sprintf(buf,"%s%s%f%s",MAG_SET_FIELD," ",X_target,"\n");
	ibwrt (XYmagnet.handle_X, buf, strlen(buf));
	//Delay(DELAY_BETWEEN_COMMANDS);  
	sprintf(buf,"%s%s%f%s",MAG_SET_RATE," ",ramp_rate_x,"\n");
	ibwrt (XYmagnet.handle_X, buf, strlen(buf));
	//Delay(DELAY_BETWEEN_COMMANDS);  
	ibwrt (XYmagnet.handle_X, MAG_RAMP, strlen(MAG_RAMP)); 
	//Delay(DELAY_BETWEEN_COMMANDS);  
	// Y magnet
	sprintf(buf,"%s%s%f%s",MAG_SET_FIELD," ",Y_target,"\n");
	ibwrt (XYmagnet.handle_Y, buf, strlen(buf));
	//Delay(DELAY_BETWEEN_COMMANDS);  
	sprintf(buf,"%s%s%f%s",MAG_SET_RATE," ",ramp_rate_y,"\n");
	ibwrt (XYmagnet.handle_Y, buf, strlen(buf));
	//Delay(DELAY_BETWEEN_COMMANDS);  
	ibwrt (XYmagnet.handle_Y, MAG_RAMP, strlen(MAG_RAMP)); 
	//Delay(DELAY_BETWEEN_COMMANDS);  
#else
	XYmagnet.test_xramping=1;XYmagnet.test_yramping=1;
	XYmagnet.test_rampstarttime_x=TIME;XYmagnet.test_rampstarttime_y=TIME;
	if (X_target>XYmagnet.x) {XYmagnet.test_rate_x=rate;} else {XYmagnet.test_rate_x=-rate;}
	XYmagnet.test_rampstart_x=XYmagnet.x;XYmagnet.test_rampstart_y=XYmagnet.y;
	XYmagnet.test_timetorampx=fabs(XYmagnet.x-X_target)/rate;
	XYmagnet.test_timetorampy=fabs(XYmagnet.y-Y_target)/rate;
	//printf("%s%f%s%f%s","tx=",XYmagnet.test_timetorampx,"    ty=",XYmagnet.test_timetorampy,"\n"); 
	if (Y_target>XYmagnet.y) {XYmagnet.test_rate_y=rate;} else {XYmagnet.test_rate_y=-rate;}
#endif
	//printf("\n");      
}


