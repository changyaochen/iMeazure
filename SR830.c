#include <gpib.h>
#include <ansi_c.h>
#include "SR830.h"	   

void sr830_initialize_1(void)
{
	sr830.handle_1= ibdev (0, SR830_1_ADDR, NO_SAD, T1s, 1, 0);  
}

void sr830_initialize_2(void)
{
	sr830.handle_2= ibdev (0, SR830_2_ADDR, NO_SAD, T1s, 1, 0);  
}

void sr850_initialize(void)
{
	sr830.handle_2= ibdev (0, SR830_2_ADDR, NO_SAD, T1s, 1, 0);  
}

double sr830_readch1_1(void)
{
	char buf[20];
	ibwrt (sr830.handle_1, SR830_OUTPUTX, strlen(SR830_OUTPUTX));
	ibrd (sr830.handle_1, &buf, 20); 
	return atof(buf);
}

double sr830_readch1_2(void)
{
	char buf[20];
	ibwrt (sr830.handle_2, SR830_OUTPUTX, strlen(SR830_OUTPUTX));
	ibrd (sr830.handle_2, &buf, 20); 
	return atof(buf);
}

double sr830_readch2_2(void)
{
	char buf[20];
	ibwrt (sr830.handle_2, SR830_OUTPUTY, strlen(SR830_OUTPUTX));
	ibrd (sr830.handle_2, &buf, 20); 
	return atof(buf);
}

void sr850_set_freq(double frequency)
{
	char buf[20];
	sprintf(buf,"%s%f%s", FREQ, frequency, "\n");  //set frequency in Hz 
	ibwrt(sr830.handle_2, buf, strlen(buf));

}

void sr850_set_amp(double amplitude)
{
	char buf[20];
	sprintf(buf,"%s%f%s", AMP, amplitude, "\n");  //set rms amplitude in V
	ibwrt(sr830.handle_2, buf, strlen(buf));

}

void sr850_set_aux1_volt(double voltage)
{
	char buf[20];
	sprintf(buf,"%s%f%s", AUXV1, voltage, "\n");  //set voltage in V
	ibwrt(sr830.handle_2, buf, strlen(buf));	
}

void sr850_set_aux2_volt(double voltage)
{
	char buf[20];
	sprintf(buf,"%s%f%s", AUXV2, voltage, "\n");  //set voltage in V
	ibwrt(sr830.handle_2, buf, strlen(buf));	
}

void sr850_set_aux3_volt(double voltage)
{
	char buf[20];
	sprintf(buf,"%s%f%s", AUXV3, voltage, "\n");  //set voltage in V
	ibwrt(sr830.handle_2, buf, strlen(buf));	
}

void sr850_set_aux4_volt(double voltage)
{
	char buf[20];
	sprintf(buf,"%s%f%s", AUXV4, voltage, "\n");  //set voltage in V
	ibwrt(sr830.handle_2, buf, strlen(buf));	
}
	

