#include <gpib.h>
#include <ansi_c.h>
#include "Agilent33220A.h"	   

void ag33220a_1_initialize(void)
{
	ag33220a.handle_1= ibdev (0, ag33220a_1_ADDR, NO_SAD, T1s, 1, 0); 
	// ibwrt(ag33220a.handle_1,"APPL:SIN 1e5, 5e-3 VRMS, 0\n",strlen("APPL:SIN 1e5, 5e-3 VRMS, 0\n"));	   //set waveform to sine, 1kHz, 5mVRMS, 0V DC offset 
	ibwrt(ag33220a.handle_1,"OUTP ON\n", strlen("OUTP ON\n"));  //turn output on       
	
	/*
	char buf[20];
	char buf2[20];
	
	sprintf(buf,"%s", "APPL:SIN 1E+3, 5e-3 VRMS, 0\n");  //set waveform to sine, 1kHz, 5mVRMS, 0V DC offset
	ibwrt(ag33220a.handle_1, buf, strlen(buf));
	
	
	sprintf(buf2,"%s", "OUTP ON\n");  //turn output on
	ibwrt(ag33220a.handle_1, buf2, strlen(buf2));
	*/
}

void ag33220a_set_freq(double frequency) // set frequency on ag33220a
{
	char buf[20];
	sprintf(buf,"%s%f%s", FREQ, frequency, "\n");  //set frequency in Hz 
	ibwrt(ag33220a.handle_1, buf, strlen(buf));

}

void ag33220a_set_amp(double amplitude)
{
	char buf[20];
	sprintf(buf,"%s%f%s", AMP, amplitude, " VRMS\n");  //set frequency in Hz 
	ibwrt(ag33220a.handle_1, buf, strlen(buf));
}

