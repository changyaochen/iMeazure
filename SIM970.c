#include <utility.h>
#include <gpib.h>
#include <ansi_c.h>
#include "SIM970.h"

// SIM970 4 channel voltmeter in SIM900 

void SIM970_CH1_initialize(void)
{
	SIM970.handle= ibdev (0, SIM970_ADDR, NO_SAD, T100ms, 1, 0);  		
	Delay(0.5);
	ibwrt(SIM970.handle,"TRIG:DEL:AUTO OFF\n",strlen("TRIG:DEL:AUTO OFF\n"));
}


void SIM970_CH2_initialize(void)
{
	SIM970.handle= ibdev (0, SIM970_ADDR, NO_SAD, T100ms, 1, 0);  		
	Delay(0.5);
	ibwrt(SIM970.handle,"TRIG:DEL:AUTO OFF\n",strlen("TRIG:DEL:AUTO OFF\n"));
}

void SIM970_CH3_initialize(void)
{
	SIM970.handle= ibdev (0, SIM970_ADDR, NO_SAD, T100ms, 1, 0);  		
	Delay(0.5);
	ibwrt(SIM970.handle,"TRIG:DEL:AUTO OFF\n",strlen("TRIG:DEL:AUTO OFF\n"));
}

void SIM970_CH4_initialize(void)
{
	SIM970.handle= ibdev (0, SIM970_ADDR, NO_SAD, T100ms, 1, 0);  		
	Delay(0.5);
	ibwrt(SIM970.handle,"TRIG:DEL:AUTO OFF\n",strlen("TRIG:DEL:AUTO OFF\n"));
}

double SIM970_CH1_Measure(void)
{
	double result1;
	char buf1[200], number1[200]; 
	int i;
	sprintf(buf1,"%s","FLSh 1 \n sndt 5, 'volt? 1' \n getn? 5,30");
	ibwrt (SIM970.handle, buf1, strlen(buf1));
	ibrd (SIM970.handle, &buf1, 150);

	for (i = 0; i < 25; i++)	//to read out the proper value, i.e., kill the header
	{
		number1[i] = buf1[i+6];
	}
	result1=atof(number1);
	if ((result1<20)&&(result1>-20)) return result1; else return 0;
	return result1;
	
}

double SIM970_CH2_Measure(void)
{
	double result2;
	char buf2[200], number2[200]; 
	int i;
	sprintf(buf2,"%s","FLSh 2 \n sndt 5, 'volt? 2' \n getn? 5,30");
	ibwrt (SIM970.handle, buf2, strlen(buf2));
	ibrd (SIM970.handle, &buf2, 150);

	for (i = 0; i < 25; i++)	//to read out the proper value, i.e., kill the header
	{
		number2[i] = buf2[i+6];
	}
	result2=atof(number2);
	if ((result2<20)&&(result2>-20)) return result2; else return 0;
	return result2;
	
}

long double SIM970_CH3_Measure(void)
{
	double result;
	char buf[200], number[200]; 
	int i;
	sprintf(buf,"%s","FLSh 3 \n sndt 5, 'volt? 3' \n getn? 5,30");
	ibwrt (SIM970.handle, buf, strlen(buf));
	ibrd (SIM970.handle, &buf, 150);

	for (i = 0; i < 25; i++)	//to read out the proper value, i.e., kill the header
	{
		number[i] = buf[i+6];
	}
	result=atof(number);
	if ((result<20)&&(result>-20)) return result; else return 0;
	return result;
	
}

long double SIM970_CH4_Measure(void)
{
	double result;
	char buf[200], number[200]; 
	int i;
	sprintf(buf,"%s","FLSh 4 \n sndt 5, 'volt? 4' \n getn? 5,30");
	ibwrt (SIM970.handle, buf, strlen(buf));
	ibrd (SIM970.handle, &buf, 150);

	for (i = 0; i < 25; i++)	//to read out the proper value, i.e., kill the header
	{
		number[i] = buf[i+6];
	}
	result=atof(number);
	if ((result<20)&&(result>-20)) return result; else return 0;
	return result;
	
}

