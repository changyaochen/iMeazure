#include <time.h>
#include <userint.h>
#include <utility.h>
#include <gpib.h>
#include <ansi_c.h>
#include "E5062.h"
#include <visa.h>
#include <iMeazure_interface.h>
#include <iMeazure_logic.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>  


 long double E5062_data_amp[30000], E5062_data_phase[30000];  

/*************** Define function for delay***************/
void delay(double mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
/*************** End ***************/ 

void E5062_initialize(void)       
{
	char buf[100];
	E5062.handle= ibdev (0, E5062_ADDR, NO_SAD, T100ms, 1, 0);   
}

void E5062_set_low(double frequency)
{
	char buf[100];
	sprintf(buf,"%s%s%s%f%s", "SENS1:", E5062_SET,":STAR ",frequency*1000000, "\n");  //set start frequency in MHz
	ibwrt (E5062.handle, buf, strlen(buf));
}

void E5062_set_high(double frequency)
{
	char buf[100];
	sprintf(buf,"%s%s%s%f%s", "SENS1:", E5062_SET,":STOP ",frequency*1000000, "\n");  //set stop frequency in MHz
	ibwrt (E5062.handle, buf, strlen(buf));
}

void E5062_average(int average)
{
	char buf[100];
	sprintf(buf,"%s%i%s", ":SENS1:AVER:COUN ", average, "\n:SENS1:AVER:CLE\n");  // set average cycles, restart averaging on channel 1
	ibwrt (E5062.handle, buf, strlen(buf));
}

void E5062_autoscale(void)
{
	char buf[100];
	sprintf(buf,"%s", ":DISP:WIND1:TRAC1:Y:AUTO\n");  //autoscale channel 1, trace 1
	ibwrt (E5062.handle, buf, strlen(buf));
}

void E5062_points(int points)
{
	char buf[100];
	sprintf(buf,"%s%i%s", ":SENS1:SWE:POIN ",points, "\n");  //set sweep points
	ibwrt (E5062.handle, buf, strlen(buf));
}

void E5062_time(double time)
{
	char buf[100];
	sprintf(buf,"%s%f%s", ":SENS1:SWE:TIME:AUTO OFF\n:SENS1:SWE:TIME ",time, "\n");  //set auto sweep time off, then set sweep time
	ibwrt (E5062.handle, buf, strlen(buf));
}



void E5062_measure_ch1(void)
{
	int j;
	char buf[900000];
	const char delimiter[] = ",";
	double test;
	data.acquiring = 1;
	GetCtrlVal(MAIN,MAIN_VNA_time,&timing.VNA);  
	GetCtrlVal(MAIN,MAIN_VNA_average,&timing.VNA_average); 
	delay (1000*timing.VNA_average*timing.VNA);  // wait for set cycles to complete
	ibwrt (E5062.handle, E5062_READ1, strlen(E5062_READ1));
	ibrd (E5062.handle, &buf, 900000);
	sprintf(one_shot,"%s",buf);   // fetch the data in string format, in a row, into one_shot
	
	token = strtok(one_shot, delimiter);
	E5062_data_amp [0] = atof (token);  // set first amp value
	token = strtok(NULL,delimiter);
	E5062_data_phase[0] = atof(token);  // set first phase value

	for (j=1;j<data.points_num;j++)
	{
		
		token = strtok(NULL, delimiter); 
		E5062_data_amp [j]= atof (token);   // set next amp value
		token = strtok(NULL, delimiter);
		E5062_data_phase [j] = atof(token);   // set next phase value
		
	}
	
	
}

double E5062_measure_ch1_single_amp(int point)
{
	
	return E5062_data_amp[point];

	
}

double E5062_measure_ch1_single_phase(int point)
{
	
	return E5062_data_phase[point];

	
}
