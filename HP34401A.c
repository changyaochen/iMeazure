#include <utility.h>
#include <gpib.h>
#include <ansi_c.h>
#include "HP34401A.h"	 
// HP-Agilent 34401A Voltmeter 
void hp34401A_1_initialize(void)
{
	hp34401A_1.handle=ibdev (0, HP34401A_1_ADDRESS, NO_SAD, T1s, 1, 0); 		
	//Delay(0.5);
	ibwrt(hp34401A_1.handle,"*RST\n",strlen("*RST\n")); 
	ibwrt(hp34401A_1.handle,"TRIG:DEL:AUTO OFF\n",strlen("TRIG:DEL:AUTO OFF\n"));
	ibwrt(hp34401A_1.handle,"VOLT:DC:NPLC MIN\n",strlen("VOLT:DC:NPLC MIN\n"));	
	ibwrt(hp34401A_1.handle,"SENS:ZERO:AUTO ONCE\n",strlen("SENS:ZERO:AUTO ONCE\n"));
	//ibwrt(hp34401A_1.handle,"DISP OFF\n",strlen("DISP OFF\n"));
}
void hp34401A_2_initialize(void)
{
	hp34401A_2.handle=ibdev (0, HP34401A_2_ADDRESS, NO_SAD, T1s, 1, 0); 		
	//ibwrt(hp34401A_2.handle,"*RST\n",strlen("*RST\n"));
	//ibwrt(hp34401A_2.handle,":ROSC:SOURCE INT\n",strlen(":ROSC:SOURCE INT\n"));  //  Use internal oscillator. 
	//ibwrt(hp34401A_2.handle,":DIAG:CAL:INT:AUTO OFF\n",strlen(":DIAG:CAL:INT:AUTO OFF\\n")); //  Disable automatic interpolater calibration.	
	ibwrt(hp34401A_2.handle,":CALC:MATH:STATE OFF\n",strlen(":CALC:MATH:STATE OFF\n"));   //   Disable any post processing
	ibwrt(hp34401A_2.handle,"*DDT #15FETC\n",strlen("*DDT #15FETC\n"));  //  Define the Trigger command. This  means the command FETC? does not need to be sent for every measurement, decreasing the number of bytes transferred over the bus
	ibwrt(hp34401A_2.handle,":INIT CONT ON\n",strlen(":INIT CONT ON\n"));  // Set the counter on run mode
	//ibwrt(hp34401A_2.handle,":EVENT1:LEVEL:AUTO OFF\n",strlen(":EVENT1:LEVEL:AUTO OFF\n"));  //  set trigger level OFF
	ibwrt(hp34401A_2.handle,":SENSe:FREQuency:ARM:SOURce IMMediate\n",strlen(":SENSe:FREQuency:ARM:SOURce IMMediate\n")); // set to auto arm
	ibwrt(hp34401A_2.handle,":HCOPy:CONTinuous OFF\n",strlen(":HCOPy:CONTinuous OFF\n"));  //  set printing off
	//ibwrt(hp34401A_2.handle,":CALCulate2:LIMit:STATe OFF\n",strlen(":CALCulate2:LIMit:STATe OFF\n")); // set limit testing off
	ibwrt(hp34401A_2.handle,":CALCulate3:AVERage OFF\n",strlen(":CALCulate3:AVERage OFF\n"));   // set statistic off
	ibwrt(hp34401A_2.handle,":FORM ASCii\n",strlen(":FORM ASCii\n"));   //  set data format to ASCII
	//ibwrt(hp34401A_2.handle,":DISP:ENAB OFF",strlen(":DISP:ENAB OFF"));   //  Turn off the counter display   
	//ibwrt(hp34401A_2.handle,":FREQ:EXP1 1000",strlen(":FREQ:EXP1 1000"));   // expected frequency value
	
}

long double  hp34401A_1_Measure(void)
{	long double result;
	char buf[200]; 
	char b;
	sprintf(buf,"%s",HP34401A_Measure);
	ibwrt (hp34401A_1.handle, buf, strlen(buf));
	ibrd (hp34401A_1.handle, &buf, 150);
	ibrsp(hp34401A_1.handle,&b); // hack! So that it does not break after read.
	result=atof(buf);
	if ((result<12)&&(result>-12)) return result;  else return 0;

}

double  hp34401A_2_Measure(void)
{	double result;
	char buf[100]; 
	//char b;
	sprintf(buf,"%s","INIT");
	sprintf(buf,"%s","FETC?");
	ibwrt (hp34401A_2.handle, buf, strlen(buf));
	ibrd (hp34401A_2.handle, &buf, 100);
	//ibrsp(hp34401A_2.handle,&b); // hack! So that it does not break after read.
	result=atof(buf);
	return result;

}
