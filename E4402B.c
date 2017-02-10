#include <time.h>
#include <userint.h>
#include <utility.h>
#include <gpib.h>
#include <ansi_c.h>
#include "E4402B.h"
#include <visa.h>
#include <iMeazure_interface.h>
#include <iMeazure_logic.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>  


long double E4402B_data_amp[3000000], E4402B_data_phase[3000000];  

/*************** Define function for delay***************/
void E4402delay(double mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
/*************** End ***************/ 

void E4402B_initialize(void)       
{
	char buf[100];
	E4402B.handle = ibdev (0, E4402B_ADDR, NO_SAD, T100ms, 1, 0);   
}

void E4402B_set_low(double frequency)
{
	char buf[100];
	sprintf(buf,"%s%s%s%f%s", ":", E4402B_SET,":STAR ",frequency*1000, "\n");  //set start frequency in MHz
	int debug;
	debug = ibwrt (E4402B.handle, buf, strlen(buf));
	//Message(" Paused...");
	return;
}

void E4402B_set_high(double frequency)
{
	char buf[100];
	sprintf(buf,"%s%s%s%f%s", ":", E4402B_SET,":STOP ",frequency*1000, "\n");  //set stop frequency in MHz
	ibwrt (E4402B.handle, buf, strlen(buf));
	return;
}

void E4402B_average(int average)
{
	char buf[1000];
	sprintf(buf,"%s%s%i%s", ":AVER ON\n:","AVER:COUN ", average, "\n:AVER:CLE\n");  // set average cycles, restart averaging on channel 1
	ibwrt (E4402B.handle, buf, strlen(buf));
	return;
}

/*void E4402B_autoscale(void)
{
	char buf[100];
	sprintf(buf,"%s", ":DISP:WIND1:TRAC1:Y:AUTO\n");  //autoscale channel 1, trace 1
	ibwrt (E4402B.handle, buf, strlen(buf));
} */

void E4402B_points(int points)
{
	char buf[100];
	sprintf(buf,"%s%i%s", ":SENS1:SWE:POIN ",points, "\n");  //set sweep points
	ibwrt (E4402B.handle, buf, strlen(buf));
	return;
}

void E4402B_time(double time)
{
	char buf[100];
	sprintf(buf,"%s%f%s", ":SWE:TIME:AUTO OFF\n:SWE:TIME ",time, "\n");  //set auto sweep time off, then set sweep time, in unit of second
	ibwrt (E4402B.handle, buf, strlen(buf));
	return;
}



void E4402B_measure_ch1(void)
{
	int j, debug;
	char buf1[900000];
	const char delimiter[] = ",";
	double test;
	data.acquiring = 1;
	GetCtrlVal(MAIN,MAIN_VNA_time,&timing.VNA);  
	GetCtrlVal(MAIN,MAIN_VNA_average,&timing.VNA_average); 
	E4402delay (1000*timing.VNA_average*timing.VNA);  // wait for set cycles to complete
	debug = ibwrt (E4402B.handle, E4402B_READ1, strlen(E4402B_READ1));
	E4402delay(100);   
	Message(" Paused..."); 
	ibrd (E4402B.handle, &buf1, 900000);
	sprintf(one_shot,"%s",buf1);   // fetch the data in string format, in a row, into one_shot
	
	token = strtok(one_shot, delimiter);
	E4402B_data_amp [0] = atof (token);  // set first amp value

	for (j=1;j<data.points_num;j++)
	{
		
		token = strtok(NULL, delimiter); 
		E4402B_data_amp [j]= atof (token);   // set next amp value

	}
	
	
}

double E4402B_measure_ch1_single_amp(int point)
{
	
	return E4402B_data_amp[point];

	
}

