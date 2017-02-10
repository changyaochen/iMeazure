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

char one_shot[300000];
double E5062_data[30000];

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

void E5062_autoscale(void)
{
	char buf[100];
	sprintf(buf,"%s", ":DISP:WIND1:TRAC1:Y:AUTO\n");  //autoscale channel 1, trace 1
	ibwrt (E5062.handle, buf, strlen(buf));
}
	

void E5062_points(int points)
{
	char buf[100];
	sprintf(buf,"%s%i%s", ":SENS1:SWE:POIN ",points, "\n");  //set start frequency in MHz
	ibwrt (E5062.handle, buf, strlen(buf));
}

void E5062_measure_ch1(void)
{
	int i;
	char buf[300000], xfer[300000];
	char *token;
	const char delimiter[] = ",";
	double test;
	ibwrt (E5062.handle, E5062_READ1, strlen(E5062_READ1));
	ibrd (E5062.handle, &buf, 300000);
	sprintf(one_shot,"%s",buf);   // fetch the data in string format, in a row, into one_shot
	sprintf(xfer,"%s",one_shot);  // copy one_shot to xfer
	token = strtok(xfer,delimiter);
	/*data.y[0] = atof(token);
	for (i=1;i<=data.points_num;i++)
	{
		token = strtok(NULL, delimiter);
		E5062_data[i] = atof(token);
	} */
	
	
}

double E5062_measure_ch1_single(int point)
{
	/*int i=0, j, length;
	char *split, *foo="+", buf[100];
	char xfer[30000], new[30000];
	char temp_data;
	sprintf(xfer,"%s",one_shot);
	length = strlen(xfer);
	sprintf(foo,"%s",xfer);
	// need to replace all the "," with space
	for (j=0;j<length;j++)
	{
		if (*foo = ',') new[j] = ' ';
		else {new[j] = *foo; *foo++;}
	}
	
    temp_data = strtod (new,&split);
	if (point == 0) { return temp_data;}
	else 
	{
		for (i=0;i<point;i++)
		{
			temp_data = strtod (split,NULL);
		}
	return temp_data;	

	}  */
	return 0;		 
	
}
