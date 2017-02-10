#include "iMeazure_logic.h"
#include "iMeazure_interface.h"
#include "AMI_magnet.h"
#include "IPS120_magnet.h"
#include "AMI_2D_magnet.h"
#include "KEITHLEY_2000.h"
#include "YOKO.h"
#include "lakeshore340.h"   
#include "KE2400#1.h"
#include "KE2400#2.h"
#include "TWO_KE2400s.h"
#include "HP34401A.h"
#include "CS4_magnet.h"
#include "fl6060.h"
#include "SR830.h"
#include "ppms.h"
#include "SIM928.h"
#include "Anritsu_68369.h"  
#include "E5062.h"
#include <formatio.h>
#include <stdio.h>  
#include <stdlib.h> 
//#include <dataacq.h>
//#include <easyio.h>
#include <string.h>
#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <time.h>
#include "SIM970.h"	
#include "E4402B.h"
#include "Agilent33220A.h" 
//#include "DAC.h"
#include "SIM965.h" 


/* 
This program will ramp up the voltage until the wire starts to break
The ramp will stop and retreat when the resistance is below the threshold
1/04/05
*/
#define DEFAULT_CONFIG 101 // to know when we load real config when default
#define TIME (double)clock()/CLOCKS_PER_SEC
#define TIMING_LENGTH 0.1 // The length of bin for calculating POINTS_PER_SEC
#define ACQ_TYPE_NUMBER 28
#define CH_TYPE_NUMBER 31
char *ACQ_TYPE_NAME[] ={"NONE","FAKE","TIME","ADC0","ADC1","ADC2","ADC3","CH1 sweep","CH2 sweep","CH3 sweep","HP34401A#1","HP34401A#2(HP53131A)","KEITHLEY2000","SR830(CH1)","SR850 (X)","SR850 (Y)","Lakeshore 340","2Dmag_theta","2Dmag_X","2Dmag_Y","2Dmag_R","E5062_CH1_Amp","E5062_CH1_Phase","SIM970#1","SIM970#2","SIM970#3","SIM970#4","E4402B_Amp"};
char *CH_TYPE_NAME[]={"none","DAC0","DAC1","magnet","m_theta","YOKO","KE2400#1","KE2400#2","TWO KE2400s","IPS120 magnet supply","CS4 magnet supply","PPMS magnet supply","FL6060","fake","SIM928#1","Anritsu_68369","E5062","SIM928#2","SIM928#3","SIM928#4","E4402B","SR850 Freq","SR850 Amp","SR850 AUX1","SR850 AUX2","SR850 AUX3","SR850 AUX4","33220A Freq (CH1)","33220A Amp (CH2)","SIM965N1","SIM965N2"};
static int panelHandle;
static int extrasHandle;
char data_filename[MAX_PATHNAME_LEN];
char configuration_filename[MAX_PATHNAME_LEN];// global to remember the path next time
double old_y, old_y1, old_x=0;
int old_points_num=1;
void InterfaceInit(void);

int main (int argc, char *argv[])
{
	Init();
	extrasHandle=LoadPanel (0, "iMeazure_interface.uir", EXTRAS);
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "iMeazure_interface.uir", MAIN)) < 0)
		return -1;
    DisplayPanel (panelHandle);  
	InterfaceInit();
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

void InterfaceInit(void)
{
int i;
config.draging_cursor=0 ;
//load_settings(0,0,EVENT_COMMIT,0,0,DEFAULT_CONFIG);
//SetCtrlAttribute(MAIN,MAIN_GRAPH,ATTR_ACTIVE_YAXIS,VAL_LEFT_YAXIS);
// Reset the stuff loaded by load_settings
ResetTextBox (MAIN, MAIN_MESSAGES, "");
ClearListCtrl(MAIN,MAIN_Y_TYPE);ClearListCtrl(MAIN,MAIN_Y1_TYPE);ClearListCtrl(MAIN,MAIN_X_TYPE);
ClearListCtrl(MAIN,MAIN_CH1_TYPE);ClearListCtrl(MAIN,MAIN_CH2_TYPE);
Message(" iMeazure started.");
for (i=0;i<ACQ_TYPE_NUMBER;i++){
	InsertListItem(MAIN,MAIN_Y_TYPE,i,ACQ_TYPE_NAME[i],i);
	InsertListItem(MAIN,MAIN_Y1_TYPE,i,ACQ_TYPE_NAME[i],i);
	InsertListItem(MAIN,MAIN_Y2_TYPE,i,ACQ_TYPE_NAME[i],i); 
	}
for (i=0;i<10;i++){
	InsertListItem(MAIN,MAIN_X_TYPE,i,ACQ_TYPE_NAME[i],i); 
	};
for (i=0;i<CH_TYPE_NUMBER;i++) InsertListItem(MAIN,MAIN_CH1_TYPE,i,CH_TYPE_NAME[i],i);
for (i=0;i<CH_TYPE_NUMBER;i++)InsertListItem(MAIN,MAIN_CH2_TYPE,i,CH_TYPE_NAME[i],i);   // kill the last item in channel 2, i.e. E5062
for (i=0;i<CH_TYPE_NUMBER;i++)InsertListItem(EXTRAS,EXTRAS_CH3_TYPE,i,CH_TYPE_NAME[i],i);  //displaying channel 3 in EXTRAS	

}
int CVICALLBACK Quit (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			if (ConfirmPopup("Quit iMeazure?", "You are about to quit iMeazure. Do you want to continue?")) { 
				data.acquiring=0;
				QuitUserInterface(0);
			}
			break;
		}
	return 0;
}



int CVICALLBACK update (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int i;
	int temp;
	double temp1,temp2;
	double min,max;
	//temp1=TIME;  
	switch (event)
		{
		case EVENT_TIMER_TICK:
				temp1=TIME;//  
			if (!data.acquiring)  {	get_x(); get_y(); get_y1();get_y2(); Update_ch1_Sweep(); Update_ch2_Sweep();Update_ch3_Sweep(); UpdateMegaSweep();}
			if (!config.draging_cursor) {  // when draging cursors show its value instead
			SetCtrlVal(MAIN,MAIN_Y,now.y);
			SetCtrlVal(MAIN,MAIN_Y1,now.y1);  
			SetCtrlVal(MAIN,MAIN_Y2,now.y2); 
			SetCtrlVal(MAIN,MAIN_X,now.x);
			}
			// show all the values
			SetCtrlVal(MAIN,MAIN_CH1_SWEEP_NOW,sweep_ch1.x);	// CH1 update
			SetCtrlVal(MAIN,MAIN_CH2_SWEEP_NOW,sweep_ch2.x);	// CH2 update
			SetCtrlVal(EXTRAS,EXTRAS_CH3_SWEEP_NOW,sweep_ch3.x);	// CH3 update 
			SetCtrlVal(MAIN,MAIN_DATA, (double)(100*data.points_num/MAX_POINTS)); // "Memory" indicator
			// update interface - buttons and colors
			SetCtrlVal(MAIN,MAIN_CH1_DIRECTION, sweep_ch1.direction);
			SetCtrlVal(MAIN,MAIN_CH2_DIRECTION, sweep_ch2.direction); 
			SetCtrlVal(EXTRAS,EXTRAS_CH3_DIRECTION, sweep_ch3.direction); 
			/* Update stuff related to 2D magnet 	*/
			if (data.acquiring) { 
				SetCtrlAttribute(MAIN,MAIN_ACQUIRE, ATTR_LABEL_TEXT, "Stop"); SetCtrlAttribute(MAIN,MAIN_ACQUIRE_FRAME, ATTR_FRAME_COLOR, VAL_RED);
			} else { 		SetCtrlAttribute(MAIN,MAIN_ACQUIRE, ATTR_LABEL_TEXT,"Acquire");SetCtrlAttribute(MAIN,MAIN_ACQUIRE_FRAME, ATTR_FRAME_COLOR, VAL_OFFWHITE);}
			if (sweep_ch1.on) { 
				SetCtrlAttribute(MAIN,MAIN_SWEEP_CH1, ATTR_LABEL_TEXT, "Stop"); SetCtrlAttribute(MAIN,MAIN_SWEEP_CH1_FRAME, ATTR_FRAME_COLOR, VAL_RED);   
			} else { 		SetCtrlAttribute(MAIN,MAIN_SWEEP_CH1, ATTR_LABEL_TEXT,"Sweep"); SetCtrlAttribute(MAIN,MAIN_SWEEP_CH1_FRAME, ATTR_FRAME_COLOR, VAL_OFFWHITE);}
			
			if (sweep_ch2.on) { 
				SetCtrlAttribute(MAIN,MAIN_SWEEP_CH2, ATTR_LABEL_TEXT, "Stop"); SetCtrlAttribute(MAIN,MAIN_SWEEP_CH2_FRAME, ATTR_FRAME_COLOR, VAL_RED);   
			} else { 		SetCtrlAttribute(MAIN,MAIN_SWEEP_CH2, ATTR_LABEL_TEXT,"Sweep"); SetCtrlAttribute(MAIN,MAIN_SWEEP_CH2_FRAME, ATTR_FRAME_COLOR, VAL_OFFWHITE);}
			
			if (sweep_ch3.on) { 
				SetCtrlAttribute(EXTRAS,EXTRAS_SWEEP_CH3, ATTR_LABEL_TEXT, "Stop"); SetCtrlAttribute(EXTRAS,EXTRAS_SWEEP_CH3_FRAME, ATTR_FRAME_COLOR, VAL_RED);   
			} else { 		SetCtrlAttribute(EXTRAS,EXTRAS_SWEEP_CH3, ATTR_LABEL_TEXT,"Sweep"); SetCtrlAttribute(EXTRAS,EXTRAS_SWEEP_CH3_FRAME, ATTR_FRAME_COLOR, VAL_OFFWHITE);}
			
			if (MegaSweep.on) { 
				if (sweep_ch1.type==SW_E4402B) {E4402B_Mega();} 
				else if (sweep_ch1.type==SW_E5062) {E5062_Mega();}
				SetCtrlAttribute(MAIN,MAIN_MEGASWEEP, ATTR_LABEL_TEXT, "MegaStop!"); SetCtrlAttribute(MAIN,MAIN_MEGASWEEP_FRAME, ATTR_FRAME_COLOR, VAL_RED);   
			} else { 		SetCtrlAttribute(MAIN,MAIN_MEGASWEEP, ATTR_LABEL_TEXT,"MegaSweep!"); SetCtrlAttribute(MAIN,MAIN_MEGASWEEP_FRAME, ATTR_FRAME_COLOR, VAL_OFFWHITE);}
			if (autobreak.on) SetCtrlVal(EXTRAS,EXTRAS_CRIT_RESISTANCE,autobreak.critical_resistance);
			if (data.acquiring) {
				GetAxisScalingMode (MAIN, MAIN_GRAPH,VAL_XAXIS, &temp, &min, &max);
				SetCtrlVal(MAIN,MAIN_XMIN,min);
				SetCtrlVal(MAIN,MAIN_XMAX,max);
				GetAxisScalingMode (MAIN, MAIN_GRAPH,VAL_LEFT_YAXIS, &temp, &min, &max);
				SetCtrlVal(MAIN,MAIN_YMIN,min);
				SetCtrlVal(MAIN,MAIN_YMAX,max); 
			}
				
			if ((data.acquiring)&&(old_points_num>0)&&(old_points_num<data.points_num)) //plot data depending on config.display_type
			
			{

						 	PlotXY(MAIN,MAIN_GRAPH,data.x+old_points_num-1,data.y+old_points_num-1,data.points_num-old_points_num+1,VAL_DOUBLE,VAL_DOUBLE,VAL_THIN_LINE, VAL_X,VAL_SOLID, 1,config.y_color);
						 	if (config.y1_axis_active) {
								SetCtrlAttribute(MAIN,MAIN_GRAPH,ATTR_ACTIVE_YAXIS,VAL_RIGHT_YAXIS);  
						 		PlotXY(MAIN,MAIN_GRAPH,data.x+old_points_num-1,data.y1+old_points_num-1,data.points_num-old_points_num+1,VAL_DOUBLE,VAL_DOUBLE,VAL_THIN_LINE,  VAL_X,VAL_SOLID, 1,config.y1_color);
								SetCtrlAttribute(MAIN,MAIN_GRAPH,ATTR_ACTIVE_YAXIS,VAL_LEFT_YAXIS); 
						 	}
						
				
			}
			old_x=data.x[data.points_num]; old_y=data.y[data.points_num]; old_y1=data.y1[data.points_num];
			old_points_num=data.points_num;
			break;
		}	   
	return 0;
}


int CVICALLBACK cleargraph (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			DeleteGraphPlot (MAIN, MAIN_GRAPH, -1, VAL_IMMEDIATE_DRAW);
			data.points_num=0;
			old_points_num=1;
			break;
		}
	return 0;
}

int CVICALLBACK save (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int i;
	FILE *out;
	switch (event)
		{
		case EVENT_COMMIT:
		if (FileSelectPopup (data_filename,"*.dat", "*.dat","Save data", VAL_SAVE_BUTTON, 0, 0, 1, 1, data_filename))
			{
				out=fopen(data_filename,"w");
				if ((sweep_ch1.type=SW_E5062)||(sweep_ch2.type=SW_E5062))   // save function for E5062
				{
					if (config.y1_axis_active )
					{
						for(i=0;i<data.points_num;i++) fprintf( out , "%12.12e%s%12.12e%s%12.12e%s", data.x[i], "\t",data.y[i], "\t",data.y1[i],"\n");	// save both channels
					}
					else
						for (i=0;i<data.points_num;i++) fprintf( out , "%12.12e%s%12.12e%s", data.x[i], "\t",data.y[i],"\n");
				 	Message (" E5062 data saved");
				}
				
				else  // save function for non-E5062 
				{
				if (config.y1_axis_active ) // when acquire two variables, y1 and y
				  if (config.y2_axis_active)   // when acqurie three variables, y, y1 and y2
				  		for(i=0;i<data.points_num;i++) {fprintf( out , "%12.12e%s%12.12e%s%12.12e%s%12.12e%s", data.x[i], "\t",data.y[i], "\t",data.y1[i],"\t",data.y2[i],"\n");	Message(" Data saved, 3 channels");}			
				  	else 
						for(i=0;i<data.points_num;i++) {fprintf( out , "%12.12e%s%12.12e%s%12.12e%s", data.x[i], "\t",data.y[i], "\t",data.y1[i],"\n");	Message(" Data saved, 2 channels");	}		
				else  // if only y is acquired
					for(i=0;i<data.points_num;i++) {fprintf( out , "%12.12e%s%12.12e%s", data.x[i], "\t",data.y[i],"\n");  Message(" Data saved, Only 1 channel"); }
				}
				fclose(out);   Message(" Data saved");
			}
			break;
		}
	return 0;
}									  

int CVICALLBACK start_sweep_ch1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int temp;
	double theta_to,r_to;
	switch (event)
		{
		case EVENT_COMMIT:
			if (!sweep_ch1.on) {
				SetCtrlAttribute(MAIN,MAIN_SWEEP_CH1,ATTR_LABEL_TEXT,"Stop");
				GetCtrlVal(MAIN,MAIN_CH1_LOW,&sweep_ch1.lower_limit);
				GetCtrlVal(MAIN,MAIN_CH1_UP,&sweep_ch1.upper_limit);
				GetCtrlVal(MAIN,MAIN_CH1_DIRECTION,&sweep_ch1.direction); 
				GetCtrlVal(MAIN,MAIN_CH1_RATE_UP,&sweep_ch1.rate_up); 
				GetCtrlVal(MAIN,MAIN_CH1_RATE_DOWN,&sweep_ch1.rate_down); 
				sweep_ch1.starting_time=TIME;
				sweep_ch1.starting_x=sweep_ch1.x;
				sweep_ch1.on=1;
				if (sweep_ch1.type==SW_IPS120)  // if sweepeing IPS120 magnet start the ramp 
				{ 
				 	if (sweep_ch1.direction==1)  {ips120_ramp(sweep_ch1.upper_limit,sweep_ch1.rate_up);}
					if (sweep_ch1.direction==-1) {ips120_ramp(sweep_ch1.lower_limit,sweep_ch1.rate_down);}				 
				}
				if (sweep_ch1.type==SW_PPMS) 
				{ // PPMS
				 	if (sweep_ch1.direction==1)  {ppms_ramp(sweep_ch1.upper_limit,sweep_ch1.rate_up);}
					if (sweep_ch1.direction==-1) {ppms_ramp(sweep_ch1.lower_limit,sweep_ch1.rate_down);}				 
				}
				if (sweep_ch1.type==SW_CS4) 
				{ // if sweepeing CS4 magnet start the ramp
					if (sweep_ch1.direction==1) cs4_ramp(sweep_ch1.lower_limit,sweep_ch1.upper_limit,sweep_ch1.rate_up,sweep_ch1.direction);				 
					if (sweep_ch1.direction==-1) cs4_ramp(sweep_ch1.lower_limit,sweep_ch1.upper_limit,sweep_ch1.rate_down,sweep_ch1.direction);				 
				}
				if (sweep_ch1.type==SW_E5062)  // if E5062 is selected   
				{	 
					GetCtrlVal(MAIN,MAIN_CH1_LOW,&sweep_ch1.lower_limit);
					GetCtrlVal(MAIN,MAIN_CH1_UP,&sweep_ch1.upper_limit);
					E5062_set_low(sweep_ch1.lower_limit);
					E5062_set_high(sweep_ch1.upper_limit);
					GetCtrlVal(MAIN,MAIN_VNA_average,&timing.VNA_average);
					E5062_average(timing.VNA_average); // set average cycles and restart average
					GetCtrlVal(MAIN,MAIN_VNA_points,&data.points_num); 
					E5062_points(data.points_num);   // set sweep points
					GetCtrlVal(MAIN,MAIN_VNA_time,&timing.VNA);
					E5062_time(timing.VNA);  // set sweep time and average cycles
					E5062_autoscale();
					sweep_ch1.on=0;
				}
				if (sweep_ch1.type==SW_E4402B)  // if E4402B is selected   
				{	 
					GetCtrlVal(MAIN,MAIN_CH1_LOW,&sweep_ch1.lower_limit);
					GetCtrlVal(MAIN,MAIN_CH1_UP,&sweep_ch1.upper_limit);
					E4402B_set_low(sweep_ch1.lower_limit);
					E4402B_set_high(sweep_ch1.upper_limit);
					GetCtrlVal(MAIN,MAIN_VNA_average,&timing.VNA_average);
					E4402B_average(timing.VNA_average); // set average cycles and restart average
					GetCtrlVal(MAIN,MAIN_VNA_points,&data.points_num); 
					E4402B_points(data.points_num);   // set sweep points 
					GetCtrlVal(MAIN,MAIN_VNA_time,&timing.VNA);
					E4402B_time(timing.VNA);  // set sweep time and average cycles
					sweep_ch1.on=0;
				}
			}
			
			else 
			{
				SetCtrlAttribute(MAIN,MAIN_SWEEP_CH1,ATTR_LABEL_TEXT,"Sweep");
				sweep_ch1.on=0;
				if (sweep_ch1.type==SW_IPS120) ips120_stop_sweep(); // if sweepeing IPS120 magnet stop the ramp
				if (sweep_ch1.type==SW_CS4) cs4_stop_sweep(); // if sweepeing IPS120 magnet stop the ramp
				if (sweep_ch1.type==SW_PPMS) ppms_stop_sweep(); // if sweepeing PPMS magnet stop the ramp
			}
			
			break;
		}
		
	return 0;
}


int CVICALLBACK Acquire (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{   //int poolHandle;
	switch (event)
	{
		case EVENT_COMMIT:
			if (!data.acquiring) 
			{
				GetCtrlVal(MAIN,MAIN_BIN_SIZE,&data.bin_size);
				data.acquiring=1;

				
				if ((sweep_ch1.type == SW_E5062)&&(!sweep_ch2.on)&&(config.x_axis_type == ACQ_CH1)) 
				{   // channel 1 is E5062 and channel 2 is not sweeping
					
					Message(" E5062 acquisition starts."); 
					GetCtrlVal(MAIN,MAIN_VNA_points,&data.points_num);  
					E5062_Loop();
					data.acquiring=0;
					Message(" E5062 Acquisition is finished.");  
					SetCtrlAttribute(MAIN,MAIN_ACQUIRE,ATTR_LABEL_TEXT,"Acquire");
					break;

				}
			
				if ((sweep_ch1.type == SW_E4402B)&&(!sweep_ch2.on)&&(config.x_axis_type == ACQ_CH1)) 
				{   // channel 1 is E4402B and channel 2 is not sweeping
					
					Message(" E4402B acquisition starts."); 
					GetCtrlVal(MAIN,MAIN_VNA_points,&data.points_num);  
					E4402B_Loop();
					data.acquiring=0;
					Message(" E4402B Acquisition is finished.");  
					SetCtrlAttribute(MAIN,MAIN_ACQUIRE,ATTR_LABEL_TEXT,"Acquire");
					break;

				}
				
				else  
				{
					Message(" Acquisition starts.");
					MainLoop();
				}

				//CmtNewThreadPool (1, &poolHandle);
				//CmtSetThreadPoolAttribute (poolHandle, ATTR_TP_THREAD_PRIORITY, THREAD_PRIORITY_HIGHEST);
				//CmtScheduleThreadPoolFunction (poolHandle,(ThreadFunctionPtr)MainLoop, 0, 0); 

			} 
			else 
			{
				data.acquiring=0;
				Message(" Acquisition is stopped.");  
				SetCtrlAttribute(MAIN,MAIN_ACQUIRE,ATTR_LABEL_TEXT,"Acquire"); 
			}
		break;
	}
	return 0;
}

int CVICALLBACK ch1_direction_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int temp;
	GetCtrlVal(MAIN,MAIN_CH1_DIRECTION,&temp);
	sweep_ch1.direction=temp;
	sweep_ch1.starting_time=TIME;
	sweep_ch1.starting_x=sweep_ch1.x;
	magnet.ramping=0; // to update the sweep of the magnet, to tell it we changed the direction of the sweep
	return 0;
}

int CVICALLBACK y_axis_offset_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
switch (event)
		{
		case EVENT_COMMIT:
		GetCtrlVal(MAIN,MAIN_Y_AXIS_OFFSET,&config.y_axis_offset);
		break;
		}
	return 0;
}

int CVICALLBACK y_axis_factor_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_Y_AXIS_FACTOR,&config.y_axis_factor);
			break;
		}
	return 0;
}

int CVICALLBACK x_axis_factor_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_X_AXIS_FACTOR,&config.x_axis_factor); 
			break;
		}
	return 0;
}

int CVICALLBACK x_axis_offset_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{	
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_X_AXIS_OFFSET,&config.x_axis_offset); 
		break;
		}
	return 0;
}

int CVICALLBACK y1_axis_factor_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_Y1_AXIS_FACTOR,&config.y1_axis_factor); 
			break;
		}
	return 0;
}



int CVICALLBACK y2_axis_factor_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_Y1_AXIS_FACTOR,&config.y2_axis_factor); 
			break;
		}
	return 0;
}


int CVICALLBACK y1_axis_offset_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{	
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_Y1_AXIS_OFFSET,&config.y1_axis_offset); 
		break;
		}
	return 0;
}

int CVICALLBACK y2_axis_offset_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{	
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_Y1_AXIS_OFFSET,&config.y2_axis_offset); 
		break;
		}
	return 0;
}


int CVICALLBACK y_axis_type_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlIndex(MAIN,MAIN_Y_TYPE,&config.y_axis_type);
				if (config.y_axis_type==ACQ_KEITHLEY) keithley_initialize(); else keithley.initialized=0;
				if (config.y_axis_type==ACQ_HP34401A_1) hp34401A_1_initialize();
				if (config.y_axis_type==ACQ_HP34401A_2) hp34401A_2_initialize();
				if (config.y_axis_type==ACQ_SIM970_CH1) SIM970_CH1_initialize();
				if (config.y_axis_type==ACQ_SIM970_CH2) SIM970_CH2_initialize(); 
				if (config.y_axis_type==ACQ_SIM970_CH3) SIM970_CH3_initialize(); 
				if (config.y_axis_type==ACQ_SIM970_CH4) SIM970_CH4_initialize(); 
				if (config.y_axis_type==ACQ_SR830_1) {sr830_initialize_1();}
				if (config.y_axis_type==ACQ_SR830_2) {sr830_initialize_2();}
				if (config.y_axis_type==ACQ_LAKESHORE340) {lakeshore340_init();}   
				//if (config.y_axis_type==ACQ_PPMS_TEMP) {ppms_initialize();} 
			break;
		}
	return 0;
}

int CVICALLBACK y1_axis_type_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		GetCtrlIndex(MAIN,MAIN_Y1_TYPE,&config.y1_axis_type);
		if (config.y1_axis_type==ACQ_KEITHLEY) keithley_initialize(); else keithley.initialized=0;  
		if (config.y1_axis_type==ACQ_HP34401A_1) hp34401A_1_initialize();
		if (config.y1_axis_type==ACQ_HP34401A_2) hp34401A_2_initialize();
		if (config.y1_axis_type==ACQ_SR830_1) {sr830_initialize_1();}
		if (config.y1_axis_type==ACQ_SR830_2) {sr830_initialize_2();}
		if (config.y1_axis_type==ACQ_LAKESHORE340) {lakeshore340_init();}
		if (config.y1_axis_type==ACQ_SIM970_CH1) SIM970_CH1_initialize();
		if (config.y1_axis_type==ACQ_SIM970_CH2) SIM970_CH2_initialize(); 
		if (config.y1_axis_type==ACQ_SIM970_CH3) SIM970_CH3_initialize(); 
		if (config.y1_axis_type==ACQ_SIM970_CH4) SIM970_CH4_initialize(); 
		//if (config.y1_axis_type==ACQ_PPMS_TEMP) {ppms_initialize();}

		if (config.y1_axis_type==ACQ_NONE) {
		 SetCtrlAttribute(MAIN,MAIN_Y1,ATTR_DIMMED,1);
		 SetCtrlAttribute(MAIN,MAIN_Y1_AXIS_FACTOR,ATTR_DIMMED,1); 
		 SetCtrlAttribute(MAIN,MAIN_Y1_AXIS_OFFSET,ATTR_DIMMED,1); 
		 SetCtrlAttribute(MAIN,MAIN_GRAPH, ATTR_ACTIVE_YAXIS, VAL_RIGHT_YAXIS); 
		 SetCtrlAttribute(MAIN,MAIN_GRAPH, ATTR_YLABEL_VISIBLE , 0);
		 SetCtrlAttribute(MAIN,MAIN_GRAPH, ATTR_ACTIVE_YAXIS, VAL_LEFT_YAXIS);
		 config.y1_axis_active=0;
		 } else {
		 SetCtrlAttribute(MAIN,MAIN_Y1,ATTR_DIMMED,0);
		 SetCtrlAttribute(MAIN,MAIN_Y1_AXIS_FACTOR,ATTR_DIMMED,0); 
		 SetCtrlAttribute(MAIN,MAIN_Y1_AXIS_OFFSET,ATTR_DIMMED,0); 
		 SetCtrlAttribute(MAIN,MAIN_GRAPH, ATTR_ACTIVE_YAXIS, VAL_RIGHT_YAXIS); 
		 SetCtrlAttribute(MAIN,MAIN_GRAPH, ATTR_YLABEL_VISIBLE , 1);
		 SetCtrlAttribute(MAIN,MAIN_GRAPH, ATTR_ACTIVE_YAXIS, VAL_LEFT_YAXIS);   
		  config.y1_axis_active=1;
		 }
			break;
		}
	return 0;
}


int CVICALLBACK y2_axis_type_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		GetCtrlIndex(MAIN,MAIN_Y2_TYPE,&config.y2_axis_type);
		config.y2_axis_active=1;    
		if (config.y2_axis_type==ACQ_KEITHLEY) keithley_initialize(); else keithley.initialized=0;  
		if (config.y2_axis_type==ACQ_HP34401A_1) hp34401A_1_initialize();
		if (config.y2_axis_type==ACQ_HP34401A_2) hp34401A_2_initialize();
		if (config.y2_axis_type==ACQ_SR830_1) {sr830_initialize_1();}
		if (config.y2_axis_type==ACQ_SR830_2) {sr830_initialize_2();}
		if (config.y2_axis_type==ACQ_LAKESHORE340) {lakeshore340_init();}
		if (config.y2_axis_type==ACQ_SIM970_CH1) SIM970_CH1_initialize();
		if (config.y2_axis_type==ACQ_SIM970_CH2) SIM970_CH2_initialize(); 
		if (config.y2_axis_type==ACQ_SIM970_CH3) SIM970_CH3_initialize(); 
		if (config.y2_axis_type==ACQ_SIM970_CH4) SIM970_CH4_initialize();
		//if (config.y2_axis_type==ACQ_PPMS_TEMP) {ppms_initialize();}
			break;
		}
	return 0;
}


int CVICALLBACK x_axis_type_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlIndex(MAIN,MAIN_X_TYPE,&config.x_axis_type); 
				if (config.x_axis_type==ACQ_KEITHLEY) keithley_initialize(); else keithley.initialized=0;
				if (config.x_axis_type==ACQ_HP34401A_1) hp34401A_1_initialize();
				if (config.x_axis_type==ACQ_HP34401A_2) hp34401A_2_initialize(); 
				if (config.x_axis_type==ACQ_LAKESHORE340) {lakeshore340_init();}
				//if (config.x_axis_type==ACQ_PPMS_TEMP) {ppms_initialize();} 
			break;
		}
	return 0;
}

int CVICALLBACK rescale (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			DeleteGraphPlot (MAIN, MAIN_GRAPH, -1, VAL_IMMEDIATE_DRAW); 
			PlotXY(MAIN,MAIN_GRAPH,data.x+1,data.y+1,data.points_num-1,VAL_DOUBLE,VAL_DOUBLE,VAL_CONNECTED_POINTS,  VAL_X,VAL_SOLID, 1,VAL_BLUE);
			break;
		}
	return 0;
}



// manual change of scale
int CVICALLBACK axis_scale_changed (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{	double xmax,ymax,xmin,ymin;   
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_XMAX,&xmax);
			GetCtrlVal(MAIN,MAIN_YMAX,&ymax);
			GetCtrlVal(MAIN,MAIN_XMIN,&xmin);
			GetCtrlVal(MAIN,MAIN_YMIN,&ymin);
			if ((xmax>xmin)&&(ymin<ymax))
			{
				//SetAxisScalingMode (MAIN, MAIN_GRAPH, VAL_XAXIS, VAL_MANUAL, xmin, xmax);
				//SetAxisScalingMode (MAIN, MAIN_GRAPH, VAL_LEFT_YAXIS, VAL_MANUAL, ymin, ymax);
			}
			break;
		}
	return 0;
}



int CVICALLBACK change_ch1_sweep_type (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_CH1_SWEEP_TYPE,&sweep_ch1.stop);
			break;
		}
	return 0;
}

int CVICALLBACK ch1_rate_up_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_CH1_RATE_UP,&sweep_ch1.rate_up);
			sweep_ch1.starting_time=TIME;
			sweep_ch1.starting_x=sweep_ch1.x;
			magnet.ramping=0; // to update the rate of the magnet
			break;
		}
	return 0;
}

int CVICALLBACK ch1_rate_down_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_CH1_RATE_DOWN,&sweep_ch1.rate_down);
			sweep_ch1.starting_time=TIME;
			sweep_ch1.starting_x=sweep_ch1.x;
			magnet.ramping=0;
			break;
		}
	return 0;
}

int CVICALLBACK ch1_type_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_CH1_TYPE,&sweep_ch1.type); 
			if ((sweep_ch1.type==SW_NONE)||(sweep_ch1.type==sweep_ch2.type)) {
				SetCtrlAttribute(MAIN,MAIN_CH1_SWEEP_NOW,ATTR_DIMMED,1);
				SetCtrlAttribute(MAIN,MAIN_CH1_LOW,ATTR_DIMMED,1); 
				SetCtrlAttribute(MAIN,MAIN_CH1_UP,ATTR_DIMMED,1);
				SetCtrlAttribute(MAIN,MAIN_CH1_UP,ATTR_DIMMED,1); 
				SetCtrlAttribute(MAIN,MAIN_CH1_RATE_UP,ATTR_DIMMED,1); 
				SetCtrlAttribute(MAIN,MAIN_CH1_RATE_DOWN,ATTR_DIMMED,1); 
				SetCtrlAttribute(MAIN,MAIN_CH1_SWEEP_TYPE,ATTR_DIMMED,1);  
				SetCtrlAttribute(MAIN,MAIN_CH1_DIRECTION,ATTR_DIMMED,1);  
				SetCtrlAttribute(MAIN,MAIN_SWEEP_CH1,ATTR_DIMMED,1);
				return 0;
				} 
				if ((sweep_ch1.type!=SW_NONE)&&(sweep_ch1.type!=sweep_ch2.type)) {
				SetCtrlAttribute(MAIN,MAIN_CH1_SWEEP_NOW,ATTR_DIMMED,0);
				SetCtrlAttribute(MAIN,MAIN_CH1_LOW,ATTR_DIMMED,0); 
				SetCtrlAttribute(MAIN,MAIN_CH1_UP,ATTR_DIMMED,0);
				SetCtrlAttribute(MAIN,MAIN_CH1_UP,ATTR_DIMMED,0); 
				SetCtrlAttribute(MAIN,MAIN_CH1_RATE_UP,ATTR_DIMMED,0); 
				SetCtrlAttribute(MAIN,MAIN_CH1_RATE_DOWN,ATTR_DIMMED,0); 
				SetCtrlAttribute(MAIN,MAIN_CH1_SWEEP_TYPE,ATTR_DIMMED,0);  
				SetCtrlAttribute(MAIN,MAIN_CH1_DIRECTION,ATTR_DIMMED,0);  
				SetCtrlAttribute(MAIN,MAIN_SWEEP_CH1,ATTR_DIMMED,0);  
			} 
			if (sweep_ch1.type == SW_FAKE) {
				return 0;
			}
			// if E5062 VNA is selected
			if (sweep_ch1.type==SW_E5062){
				SetCtrlAttribute(MAIN,MAIN_CH1_SWEEP_NOW,ATTR_DIMMED,1); 
				SetCtrlAttribute(MAIN,MAIN_CH1_RATE_UP,ATTR_DIMMED,1); 
				SetCtrlAttribute(MAIN,MAIN_CH1_RATE_DOWN,ATTR_DIMMED,1); 
				SetCtrlAttribute(MAIN,MAIN_CH1_SWEEP_TYPE,ATTR_DIMMED,1); 
				E5062_initialize();
				return 0;
			}
			if (sweep_ch1.type==SW_E4402B)
			{   // if E4402B is selected
				SetCtrlAttribute(MAIN,MAIN_CH1_SWEEP_NOW,ATTR_DIMMED,1); 
				SetCtrlAttribute(MAIN,MAIN_CH1_RATE_UP,ATTR_DIMMED,1); 
				SetCtrlAttribute(MAIN,MAIN_CH1_RATE_DOWN,ATTR_DIMMED,1); 
				SetCtrlAttribute(MAIN,MAIN_CH1_SWEEP_TYPE,ATTR_DIMMED,1); 
				E4402B_initialize();
				return 0;
			}
			if (sweep_ch1.type==SW_MAGNET) {
				magnet_initialize();
				sweep_ch1.x=magnet_get_field();
				return 0;
			}  
			
			if (sweep_ch1.type==SW_IPS120) {
				ips120_initialize();
				sweep_ch1.x=ips120_get_field();
				return 0;
			}  
			if (sweep_ch1.type==SW_CS4) {
				cs4_initialize();
				sweep_ch1.x=cs4_get_field();
				return 0;
			}  
			if (sweep_ch1.type==SW_YOKO) {
				YOKO_initialize();
				return 0;
			}
			if (sweep_ch1.type==SW_KE2400N1) {
				KE2400N1_initialize();
				return 0;
			}
			if (sweep_ch1.type==SW_KE2400N2) {
				KE2400N2_initialize();
				return 0;
			}
			if (sweep_ch1.type==SW_KE2400s) {
				KE2400s_initialize();
				return 0;
			}
			if (sweep_ch1.type==SW_PPMS) {
				ppms_initialize();
				sweep_ch1.x=ppms_get_field();
				return 0;
			}

			if (sweep_ch1.type==SW_FL6060) {
				fl6060_initialize();
				sweep_ch1.x=1;
			}
			if (sweep_ch1.type==SW_SIM928N1) {
				SIM928_initializeN1();
				sweep_ch1.x=0;
				return 0;
			}
			if (sweep_ch1.type==SW_SIM928N2) {
				SIM928_initializeN2();
				sweep_ch1.x=0;
				return 0;
			}
			if (sweep_ch1.type==SW_SIM928N3) {
				SIM928_initializeN3();
				sweep_ch1.x=0;
				return 0;
			}
			if (sweep_ch1.type==SW_SIM928N4) {
				SIM928_initializeN4();
				sweep_ch1.x=0;
				return 0;
			}
			if (sweep_ch1.type==SW_Anritsu_68369){
				Anritsu_68369_initialize();
				sweep_ch1.x=1;
				return 0;
      		}
			if ((sweep_ch1.type== SW_33220A_Freq)||(sweep_ch1.type==SW_33220A_Amp))  {
				ag33220a_1_initialize();
				sweep_ch1.x = 0.01;
				return 0;
			}
			if (sweep_ch1.type==SW_SR850_Freq)  {
				sr850_initialize();
				sweep_ch1.x=10000.0; // set frequency to 10 kHz
				return 0;
			}
			if (sweep_ch1.type==SW_SR850_Amp)  {
				sr850_initialize();
				sweep_ch1.x=0.01; // set rms voltage to 10 mV
				return 0;
			}
			if ((sweep_ch1.type == SW_SR850_AUX1)||(sweep_ch1.type == SW_SR850_AUX2)||(sweep_ch1.type == SW_SR850_AUX3)||(sweep_ch1.type == SW_SR850_AUX4))  {
				sr850_initialize();
				sweep_ch1.x=0; // set voltage to 0 V
				return 0;
			}
			if (sweep_ch1.type==SW_SIM965N1) {
				SIM965_initializeN1();
				sweep_ch1.x=1000;
				return 0;
			}
			if (sweep_ch1.type==SW_SIM965N2) {
				SIM965_initializeN2();
				sweep_ch1.x=1000;
				return 0;
			}

		  	break;
		}
	return 0;
}

int CVICALLBACK save_settings (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		 if (FileSelectPopup (configuration_filename, "*.icf", "*.icf", "Save program state", VAL_SAVE_BUTTON, 0,0,1, 1,configuration_filename))
				SavePanelState(MAIN, configuration_filename, 0);
				SavePanelState(EXTRAS, configuration_filename, 1);
			break;
		}
	return 0;
}

int CVICALLBACK load_settings (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int temp=0;
	switch (event)
		{
		case EVENT_COMMIT:
			if (eventData2!=DEFAULT_CONFIG) temp=FileSelectPopup (configuration_filename, "*.icf", "*.icf", "Recall program state", VAL_LOAD_BUTTON, 0,0,1, 1,configuration_filename);
			if ((temp==VAL_EXISTING_FILE_SELECTED)||(eventData2==DEFAULT_CONFIG)) // eventData2=101 means load default
				{
					if (eventData2!=DEFAULT_CONFIG) {
					RecallPanelState(MAIN, configuration_filename, 0);
					RecallPanelState(EXTRAS, configuration_filename, 1);  }
					else  { //load default
					RecallPanelState(MAIN, "default.icf", 0);
					RecallPanelState(EXTRAS, "default.icf", 1);  }
					//here we need to update the interface - call all the callbacks
					y_color_change(0,0,EVENT_COMMIT,&temp,0,0); 
					y1_color_change(0,0,EVENT_COMMIT,&temp,0,0);  
					x_axis_type_change(0,0,EVENT_COMMIT,&temp,0,0);
					y_axis_type_change(0,0,EVENT_COMMIT,&temp,0,0); 
					y1_axis_type_change(0,0,EVENT_COMMIT,&temp,0,0);   
					x_axis_factor_change(0,0,EVENT_COMMIT,&temp,0,0);  
					y_axis_factor_change(0,0,EVENT_COMMIT,&temp,0,0);  
					y1_axis_factor_change(0,0,EVENT_COMMIT,&temp,0,0); 
					x_axis_offset_change(0,0,EVENT_COMMIT,&temp,0,0);  
					y_axis_offset_change(0,0,EVENT_COMMIT,&temp,0,0); 
					y1_axis_offset_change(0,0,EVENT_COMMIT,&temp,0,0); 
					ch1_type_change(0,0,EVENT_COMMIT,&temp,0,0);  
					ch1_rate_up_change(0,0,EVENT_COMMIT,&temp,0,0);  
					ch1_rate_down_change(0,0,EVENT_COMMIT,&temp,0,0);  
					ch1_direction_change(0,0,EVENT_COMMIT,&temp,0,0);  
					change_ch1_sweep_type(0,0,EVENT_COMMIT,&temp,0,0); 
					ch2_type_change(0,0,EVENT_COMMIT,&temp,0,0);  
					ch2_rate_up_change(0,0,EVENT_COMMIT,&temp,0,0);  
					ch2_rate_down_change(0,0,EVENT_COMMIT,&temp,0,0);  
					ch2_direction_change(0,0,EVENT_COMMIT,&temp,0,0);  
					change_ch2_sweep_type(0,0,EVENT_COMMIT,&temp,0,0); 
					Message(" Recalled.");
		
				}
			break;
		}
	return 0;
}

int CVICALLBACK hide_extras (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			HidePanel(EXTRAS);
			autobreak.on=0;// not really nice
			break;
		}
	return 0;
}

int CVICALLBACK extensions (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			DisplayPanel(EXTRAS);
			break;
		}
	return 0;
}

int CVICALLBACK do_autobreak (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			autobreak.on=1;
			autobreak.first_time=1;
			GetCtrlVal(EXTRAS,EXTRAS_TARGET_RESISTANCE,&autobreak.target_resistance);
			GetCtrlVal(EXTRAS,EXTRAS_SAFE_VOLTAGE,&autobreak.safe_voltage);  
		 	GetCtrlVal(EXTRAS,EXTRAS_WITHDRAW_VOLTAGE,&autobreak.withdraw_voltage);
			GetCtrlVal(EXTRAS,EXTRAS_CRIT_RESISTANCE_INC,&autobreak.critical_resistance_increase);
			start_sweep_ch1(0,0,EVENT_COMMIT,0,0,0);
			break;
		}
	return 0;
}

int CVICALLBACK graph (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	double x,y;
	switch (event)
		{
		case EVENT_VAL_CHANGED:
			config.draging_cursor=1;
			GetGraphCursor (MAIN, MAIN_GRAPH, 1, &x, &y);
			SetCtrlAttribute(MAIN,MAIN_X,ATTR_TEXT_BGCOLOR,VAL_MAGENTA);
			SetCtrlAttribute(MAIN,MAIN_Y,ATTR_TEXT_BGCOLOR,VAL_MAGENTA); 
			SetCtrlVal(MAIN,MAIN_X,x);
			SetCtrlVal(MAIN,MAIN_Y,y);

			break;
		case EVENT_COMMIT:
			config.draging_cursor=0;
			SetCtrlAttribute(MAIN,MAIN_X,ATTR_TEXT_BGCOLOR,VAL_OFFWHITE);
			SetCtrlAttribute(MAIN,MAIN_Y,ATTR_TEXT_BGCOLOR,VAL_OFFWHITE); 
		
		}
	return 0;
}

int CVICALLBACK ch2_type_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_CH2_TYPE,&sweep_ch2.type);
			if ((sweep_ch2.type==SW_NONE)||(sweep_ch2.type==sweep_ch1.type)) {
				SetCtrlAttribute(MAIN,MAIN_CH2_SWEEP_NOW,ATTR_DIMMED,1);
				SetCtrlAttribute(MAIN,MAIN_CH2_LOW,ATTR_DIMMED,1); 
				SetCtrlAttribute(MAIN,MAIN_CH2_UP,ATTR_DIMMED,1);
				SetCtrlAttribute(MAIN,MAIN_CH2_UP,ATTR_DIMMED,1); 
				SetCtrlAttribute(MAIN,MAIN_CH2_RATE_UP,ATTR_DIMMED,1); 
				SetCtrlAttribute(MAIN,MAIN_CH2_RATE_DOWN,ATTR_DIMMED,1); 
				SetCtrlAttribute(MAIN,MAIN_CH2_SWEEP_TYPE,ATTR_DIMMED,1);  
				SetCtrlAttribute(MAIN,MAIN_CH2_DIRECTION,ATTR_DIMMED,1);  
				SetCtrlAttribute(MAIN,MAIN_SWEEP_CH2,ATTR_DIMMED,1);
				return 0;
				} 
			if ((sweep_ch2.type!=SW_NONE)&&(sweep_ch2.type!=sweep_ch1.type)) {
				SetCtrlAttribute(MAIN,MAIN_CH2_SWEEP_NOW,ATTR_DIMMED,0);
				SetCtrlAttribute(MAIN,MAIN_CH2_LOW,ATTR_DIMMED,0); 
				SetCtrlAttribute(MAIN,MAIN_CH2_UP,ATTR_DIMMED,0);
				SetCtrlAttribute(MAIN,MAIN_CH2_UP,ATTR_DIMMED,0); 
				SetCtrlAttribute(MAIN,MAIN_CH2_RATE_UP,ATTR_DIMMED,0); 
				SetCtrlAttribute(MAIN,MAIN_CH2_RATE_DOWN,ATTR_DIMMED,0); 
				SetCtrlAttribute(MAIN,MAIN_CH2_SWEEP_TYPE,ATTR_DIMMED,0);  
				SetCtrlAttribute(MAIN,MAIN_CH2_DIRECTION,ATTR_DIMMED,0);  
				SetCtrlAttribute(MAIN,MAIN_SWEEP_CH2,ATTR_DIMMED,0); 
			} 
			if (sweep_ch2.type==SW_YOKO) {
				YOKO_initialize(); 
				return 0;
			}
				
			if (sweep_ch2.type==SW_IPS120) {
				ips120_initialize();
				sweep_ch2.x=ips120_get_field();
				return 0;
			}  
			if (sweep_ch2.type==SW_CS4) {
				cs4_initialize();
				sweep_ch2.x=cs4_get_field();
				return 0;
			}  
			if (sweep_ch2.type==SW_KE2400N1) {
				KE2400N1_initialize();sweep_ch2.x=0;
				return 0;
			}
			if (sweep_ch2.type==SW_KE2400N2) {
				KE2400N2_initialize();sweep_ch2.x=0;
				return 0;
			}
			if (sweep_ch2.type==SW_KE2400s) {
				KE2400s_initialize();
				return 0;
			}	
			if (sweep_ch2.type==SW_FL6060) {
				fl6060_initialize();
				sweep_ch2.x=1;
				return 0;
			}
			if (sweep_ch2.type==SW_PPMS) {
				ppms_initialize();
				sweep_ch2.x=ppms_get_field();
				return 0;
			}
			if (sweep_ch2.type==SW_SIM928N1) {
				SIM928_initializeN1();
				sweep_ch2.x=0;
				return 0;
			}
			if (sweep_ch2.type==SW_SIM928N2) {
				SIM928_initializeN2();
				sweep_ch2.x=0;
				return 0;
			}
			if (sweep_ch2.type==SW_SIM928N3) {
				SIM928_initializeN3();
				sweep_ch2.x=0;
				return 0;
			}
			if (sweep_ch2.type==SW_SIM928N4) {
				SIM928_initializeN4();
				sweep_ch2.x=0;
				return 0;
			}
			if (sweep_ch2.type==SW_Anritsu_68369){
				Anritsu_68369_initialize();
				sweep_ch2.x=1;
				return 0;
      		}
			
			if (sweep_ch2.type==SW_E4402B) {   // if E4402B is selected
				SetCtrlAttribute(MAIN,MAIN_CH2_SWEEP_NOW,ATTR_DIMMED,1); 
				SetCtrlAttribute(MAIN,MAIN_CH2_RATE_UP,ATTR_DIMMED,1); 
				SetCtrlAttribute(MAIN,MAIN_CH2_RATE_DOWN,ATTR_DIMMED,1); 
				SetCtrlAttribute(MAIN,MAIN_CH2_SWEEP_TYPE,ATTR_DIMMED,1); 
				E4402B_initialize();
				return 0;
			}
			
			if ((sweep_ch2.type==SW_33220A_Freq)||(sweep_ch2.type==SW_33220A_Amp))  {
				ag33220a_1_initialize();
				sweep_ch2.x = 0.01;
				return 0;
			}
			if (sweep_ch2.type==SW_SR850_Freq)  {
				sr850_initialize();
				sweep_ch2.x=10000.0; // set frequency to 10 kHz
				return 0;
			}
			if (sweep_ch2.type==SW_SR850_Amp)  {
				sr850_initialize();
				sweep_ch2.x=0.01; // set rms voltage to 10 mV
				return 0;
			}
			if ((sweep_ch2.type == SW_SR850_AUX1)||(sweep_ch2.type == SW_SR850_AUX2)||(sweep_ch2.type == SW_SR850_AUX3)||(sweep_ch2.type == SW_SR850_AUX4))  {
				sr850_initialize();
				sweep_ch2.x=0; // set voltage to 0 V
				return 0;
			}
			if (sweep_ch2.type==SW_SIM965N1) {
				SIM965_initializeN1();
				sweep_ch2.x=1000;
				return 0;
			}
			if (sweep_ch2.type==SW_SIM965N2) {
				SIM965_initializeN2();
				sweep_ch2.x=1000;
				return 0;
			}
			break;
		}
	return 0;
}

int CVICALLBACK start_sweep_ch2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int temp;
	double theta_to,r_to;
	switch (event)
		{
		case EVENT_COMMIT:
			if (!sweep_ch2.on) {
				SetCtrlAttribute(MAIN,MAIN_SWEEP_CH2,ATTR_LABEL_TEXT,"Stop");
				GetCtrlVal(MAIN,MAIN_CH2_LOW,&sweep_ch2.lower_limit);
				GetCtrlVal(MAIN,MAIN_CH2_UP,&sweep_ch2.upper_limit);
					if (MegaSweep.on) {sweep_ch2.upper_limit=MegaSweep.z;}// hack to make megasweep work with CS4
				GetCtrlVal(MAIN,MAIN_CH2_DIRECTION,&sweep_ch2.direction); 
				GetCtrlVal(MAIN,MAIN_CH2_RATE_UP,&sweep_ch2.rate_up); 
				GetCtrlVal(MAIN,MAIN_CH2_RATE_DOWN,&sweep_ch2.rate_down); 
				sweep_ch2.starting_time=TIME;
				sweep_ch2.starting_x=sweep_ch2.x;
				sweep_ch2.on=1;
				if (sweep_ch2.type==SW_IPS120) { // if sweepeing IPS120 magnet start the ramp
				 	if (sweep_ch2.direction==1)  {ips120_ramp(sweep_ch2.upper_limit,sweep_ch2.rate_up);}
					if (sweep_ch2.direction==-1) {ips120_ramp(sweep_ch2.lower_limit,sweep_ch2.rate_down);}	
				}
				if (sweep_ch2.type==SW_PPMS) { // PPMS
				 	if (sweep_ch2.direction==1)  {ppms_ramp(sweep_ch2.upper_limit,sweep_ch2.rate_up);}
					if (sweep_ch2.direction==-1) {ppms_ramp(sweep_ch2.lower_limit,sweep_ch2.rate_down);}				 
				}
				if (sweep_ch2.type==SW_CS4) { // if sweepeing CS4 magnet start the ramp
					if (sweep_ch2.direction==1) cs4_ramp(sweep_ch2.lower_limit,sweep_ch2.upper_limit,sweep_ch2.rate_up,sweep_ch2.direction);				 
					if (sweep_ch2.direction==-1) cs4_ramp(sweep_ch2.lower_limit,sweep_ch2.upper_limit,sweep_ch2.rate_down,sweep_ch2.direction);				 
				}
			}
			else {
				SetCtrlAttribute(MAIN,MAIN_SWEEP_CH2,ATTR_LABEL_TEXT,"Sweep");
				sweep_ch2.on=0;
				if (sweep_ch2.type==SW_CS4) cs4_stop_sweep(); // if sweepeing IPS120 magnet stop the ramp       
				if (sweep_ch2.type==SW_IPS120) ips120_stop_sweep(); // if sweepeing IPS120 magnet stop the ramp
				if (sweep_ch2.type==SW_PPMS) ppms_stop_sweep(); // if sweepeing PPMS magnet stop the ramp
			}
			break;
		}
	return 0;
}

int CVICALLBACK change_ch2_sweep_type (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_CH2_SWEEP_TYPE,&sweep_ch2.stop);
			break;
		}
	return 0;
}

int CVICALLBACK ch2_rate_up_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_CH2_RATE_UP,&sweep_ch2.rate_up);
			sweep_ch2.starting_time=TIME;
			sweep_ch2.starting_x=sweep_ch2.x;
			magnet.ramping=0; // to update the rate of the magnet
			break;
		}
	return 0;
}

int CVICALLBACK ch2_rate_down_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_CH1_RATE_DOWN,&sweep_ch2.rate_down);
			sweep_ch2.starting_time=TIME;
			sweep_ch2.starting_x=sweep_ch2.x;
			magnet.ramping=0;
			break;
		}
	return 0;
}

int CVICALLBACK ch2_direction_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int temp;
	GetCtrlVal(MAIN,MAIN_CH2_DIRECTION,&temp);
	sweep_ch2.direction=temp;
	sweep_ch2.starting_time=TIME;
	sweep_ch2.starting_x=sweep_ch2.x;
	magnet.ramping=0; // to update the sweep of the magnet, to tell it we changed the direction of the sweep
	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// /////////////////////////////////////
//start of definition of Channel 3////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CVICALLBACK change_ch3_sweep_type (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(EXTRAS,EXTRAS_CH3_SWEEP_TYPE,&sweep_ch3.stop);
			break;
		}
	return 0;
}

int CVICALLBACK ch3_rate_up_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(EXTRAS,EXTRAS_CH3_RATE_UP,&sweep_ch3.rate_up);
			sweep_ch3.starting_time=TIME;
			sweep_ch3.starting_x=sweep_ch3.x;
			break;
		}
	return 0;
}

int CVICALLBACK ch3_rate_down_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(EXTRAS,EXTRAS_CH3_RATE_DOWN,&sweep_ch3.rate_down);
			sweep_ch1.starting_time=TIME;
			sweep_ch1.starting_x=sweep_ch3.x;
			break;
		}
	return 0;
}

int CVICALLBACK ch3_direction_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int temp;
	GetCtrlVal(EXTRAS,EXTRAS_CH3_DIRECTION,&temp);
	sweep_ch3.direction=temp;
	sweep_ch3.starting_time=TIME;
	sweep_ch3.starting_x=sweep_ch3.x;
	magnet.ramping=0; // to update the sweep of the magnet, to tell it we changed the direction of the sweep
	return 0;
}

int CVICALLBACK ch3_type_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(EXTRAS,EXTRAS_CH3_TYPE,&sweep_ch3.type); 
			if ((sweep_ch3.type==SW_NONE)||(sweep_ch3.type==sweep_ch1.type)||(sweep_ch3.type==sweep_ch2.type)||(sweep_ch3.type==SW_E5062)||(sweep_ch3.type==SW_E4402B)) {
				SetCtrlAttribute(EXTRAS,EXTRAS_CH3_LOW,ATTR_DIMMED,1); 
				SetCtrlAttribute(EXTRAS,EXTRAS_CH3_UP,ATTR_DIMMED,1);
				SetCtrlAttribute(EXTRAS,EXTRAS_CH3_UP,ATTR_DIMMED,1); 
				SetCtrlAttribute(EXTRAS,EXTRAS_CH3_RATE_UP,ATTR_DIMMED,1); 
				SetCtrlAttribute(EXTRAS,EXTRAS_CH3_RATE_DOWN,ATTR_DIMMED,1); 
				SetCtrlAttribute(EXTRAS,EXTRAS_CH3_SWEEP_TYPE,ATTR_DIMMED,1);  
				SetCtrlAttribute(EXTRAS,EXTRAS_CH3_DIRECTION,ATTR_DIMMED,1);  
				SetCtrlAttribute(EXTRAS,EXTRAS_SWEEP_CH3,ATTR_DIMMED,1);
				return 0;
				} 
				if ((sweep_ch3.type!=SW_NONE)&&(sweep_ch3.type!=sweep_ch1.type)&&(sweep_ch3.type!=sweep_ch2.type)) {
				SetCtrlAttribute(EXTRAS,EXTRAS_CH3_SWEEP_NOW,ATTR_DIMMED,0);
				SetCtrlAttribute(EXTRAS,EXTRAS_CH3_LOW,ATTR_DIMMED,0); 
				SetCtrlAttribute(EXTRAS,EXTRAS_CH3_UP,ATTR_DIMMED,0);
				SetCtrlAttribute(EXTRAS,EXTRAS_CH3_UP,ATTR_DIMMED,0); 
				SetCtrlAttribute(EXTRAS,EXTRAS_CH3_RATE_UP,ATTR_DIMMED,0); 
				SetCtrlAttribute(EXTRAS,EXTRAS_CH3_RATE_DOWN,ATTR_DIMMED,0); 
				SetCtrlAttribute(EXTRAS,EXTRAS_CH3_SWEEP_TYPE,ATTR_DIMMED,0);  
				SetCtrlAttribute(EXTRAS,EXTRAS_CH3_DIRECTION,ATTR_DIMMED,0);  
				SetCtrlAttribute(EXTRAS,EXTRAS_SWEEP_CH3,ATTR_DIMMED,0);  
			} 
				
			if (sweep_ch3.type==SW_MAGNET) {
				magnet_initialize();
				sweep_ch3.x=magnet_get_field();
				return 0;
			}  
			if (sweep_ch3.type==SW_IPS120) {
				ips120_initialize();
				sweep_ch3.x=ips120_get_field();
				return 0;
			}  
			if (sweep_ch3.type==SW_CS4) {
				cs4_initialize();
				sweep_ch3.x=cs4_get_field();
				return 0;
			}  
			if (sweep_ch3.type==SW_YOKO) {
				YOKO_initialize();
				return 0;
			}
			if (sweep_ch3.type==SW_KE2400N1) {
				KE2400N1_initialize();
				return 0;
			}
			if (sweep_ch3.type==SW_KE2400N2) {
				KE2400N2_initialize();
				return 0;
			}
			if (sweep_ch3.type==SW_KE2400s) {
				KE2400s_initialize();
				return 0;
			}
			if (sweep_ch3.type==SW_PPMS) {
				ppms_initialize();
				sweep_ch3.x=ppms_get_field();
				return 0;
			}

			if (sweep_ch3.type==SW_FL6060) {
				fl6060_initialize();
				sweep_ch3.x=1;
				return 0;
			}
			if (sweep_ch3.type==SW_SIM928N1) {
				SIM928_initializeN1();
				sweep_ch3.x=0;
				return 0;
			}
			if (sweep_ch3.type==SW_SIM928N2) {
				SIM928_initializeN2();
				sweep_ch3.x=0;
				return 0;
			}
			if (sweep_ch3.type==SW_SIM928N3) {
				SIM928_initializeN3();
				sweep_ch3.x=0;
				return 0;
			}
			if (sweep_ch3.type==SW_SIM928N4) {
				SIM928_initializeN4();
				sweep_ch3.x=0;
				return 0;
			}
			if (sweep_ch3.type==SW_Anritsu_68369){
				Anritsu_68369_initialize();
				sweep_ch3.x=1;
				return 0;
      		}
			if ((sweep_ch3.type== SW_33220A_Freq)||(sweep_ch3.type==SW_33220A_Amp))  {
				ag33220a_1_initialize();
				sweep_ch3.x = 0.01;
				return 0;
			}
			if (sweep_ch3.type==SW_SR850_Freq)  {
				sr850_initialize();
				sweep_ch3.x=10000.0; // set frequency to 10 kHz
				return 0;
			}
			if (sweep_ch3.type==SW_SR850_Amp)  {
				sr850_initialize();
				sweep_ch3.x=0.01; // set rms voltage to 10 mV
				return 0;
			}
			if ((sweep_ch3.type == SW_SR850_AUX1)||(sweep_ch3.type == SW_SR850_AUX2)||(sweep_ch3.type == SW_SR850_AUX3)||(sweep_ch3.type == SW_SR850_AUX4))  {
				sr850_initialize();
				sweep_ch3.x=0; // set voltage to 0 V
				return 0;
			}
			if (sweep_ch3.type==SW_SIM965N2) {
				SIM965_initializeN2();
				sweep_ch3.x=1000;
				return 0;
			}

			break;
		}
	return 0;
}

int CVICALLBACK start_sweep_ch3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int temp;
	double theta_to,r_to;
	int ch3_direction;
	GetCtrlVal(EXTRAS,EXTRAS_CH3_DIRECTION,&ch3_direction);
	switch (event)
		{
		case EVENT_COMMIT:
			if (!sweep_ch3.on) {
				SetCtrlAttribute(EXTRAS,EXTRAS_SWEEP_CH3,ATTR_LABEL_TEXT,"Stop");
				GetCtrlVal(EXTRAS,EXTRAS_CH3_LOW,&sweep_ch3.lower_limit);
				GetCtrlVal(EXTRAS,EXTRAS_CH3_UP,&sweep_ch3.upper_limit);
					if ((MegaSweep.on)&&(sweep_ch3.mega ==1)&&(ch3_direction == 1))// if channel 3 is in mega and sweeping up
						{
						    sweep_ch3.upper_limit=MegaSweep.z3high;
						}
					if ((MegaSweep.on)&&(sweep_ch3.mega ==1)&&(ch3_direction == -1))// if channel 3 is in mega and sweeping down
						{
						    sweep_ch3.lower_limit=MegaSweep.z3low;
						}
				GetCtrlVal(EXTRAS,EXTRAS_CH3_DIRECTION,&sweep_ch3.direction); 
				GetCtrlVal(EXTRAS,EXTRAS_CH3_RATE_UP,&sweep_ch3.rate_up); 
				GetCtrlVal(EXTRAS,EXTRAS_CH3_RATE_DOWN,&sweep_ch3.rate_down); 
				sweep_ch3.starting_time=TIME;
				sweep_ch3.starting_x=sweep_ch3.x;
				sweep_ch3.on=1;
				if (sweep_ch3.type==SW_IPS120) { // if sweepeing IPS120 magnet start the ramp
				 	if (sweep_ch3.direction==1)  {ips120_ramp(sweep_ch3.upper_limit,sweep_ch3.rate_up);}
					if (sweep_ch3.direction==-1) {ips120_ramp(sweep_ch3.lower_limit,sweep_ch3.rate_down);}	
				}
				if (sweep_ch3.type==SW_PPMS) { // PPMS
				 	if (sweep_ch3.direction==1)  {ppms_ramp(sweep_ch3.upper_limit,sweep_ch3.rate_up);}
					if (sweep_ch3.direction==-1) {ppms_ramp(sweep_ch3.lower_limit,sweep_ch3.rate_down);}				 
				}
				if (sweep_ch3.type==SW_CS4) { // if sweepeing CS4 magnet start the ramp
					if (sweep_ch3.direction==1) cs4_ramp(sweep_ch3.lower_limit,sweep_ch3.upper_limit,sweep_ch3.rate_up,sweep_ch3.direction);				 
					if (sweep_ch3.direction==-1) cs4_ramp(sweep_ch3.lower_limit,sweep_ch3.upper_limit,sweep_ch3.rate_down,sweep_ch3.direction);				 
				}
			}
			else {
				SetCtrlAttribute(EXTRAS,EXTRAS_SWEEP_CH3,ATTR_LABEL_TEXT,"Sweep");
				sweep_ch3.on=0;
				if (sweep_ch3.type==SW_CS4) cs4_stop_sweep(); // if sweepeing IPS120 magnet stop the ramp       
				if (sweep_ch3.type==SW_IPS120) ips120_stop_sweep(); // if sweepeing IPS120 magnet stop the ramp
				if (sweep_ch3.type==SW_PPMS) ppms_stop_sweep(); // if sweepeing PPMS magnet stop the ramp
			}
			break;
		}
	return 0;
}

int  CVICALLBACK ch3_mega(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	GetCtrlVal(EXTRAS,EXTRAS_megaButton,&sweep_ch3.mega);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// /////////////////////////////////////
//end of definition of Channel 3////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int CVICALLBACK y_color_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_Y_COLOR,&config.y_color);
			break;
		}
	return 0;
}

int CVICALLBACK y1_color_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_Y1_COLOR,&config.y1_color);   
			break;
		}
	return 0;
}

int CVICALLBACK y2_color_change (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_Y1_COLOR,&config.y2_color);   
			break;
		}
	return 0;
}

int CVICALLBACK Magnet2D_Init (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			XYmagnet_initialize();
			XYmagnet_update();
			SetCtrlAttribute(EXTRAS,EXTRAS_THETA,ATTR_DIMMED,0); 
			SetCtrlAttribute(EXTRAS,EXTRAS_R,ATTR_DIMMED,0);    
			SetCtrlAttribute(EXTRAS,EXTRAS_THETA_TO,ATTR_DIMMED,0); 
			SetCtrlAttribute(EXTRAS,EXTRAS_R_TO,ATTR_DIMMED,0);    
			SetCtrlAttribute(EXTRAS,EXTRAS_SWEEP2DMAG,ATTR_DIMMED,0);
			SetCtrlAttribute(EXTRAS,EXTRAS_X,ATTR_DIMMED,0);
			SetCtrlAttribute(EXTRAS,EXTRAS_Y,ATTR_DIMMED,0);
			SetCtrlAttribute(EXTRAS,EXTRAS_MAXRATE,ATTR_DIMMED,0);
			SetCtrlAttribute(EXTRAS,EXTRAS_STEPS,ATTR_DIMMED,0);

			break;
		}
	return 0;
}

int CVICALLBACK Sweep_2DMAG (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{   double r_to,theta_to;
	switch (event)
		{
		case EVENT_COMMIT:
		if (!XYmagnet.sweeping) { //starting a XY sweep
				XYmagnet.sweeping=1;
				XYmagnet.timing_start=TIME; // start timers
				GetCtrlVal(EXTRAS,EXTRAS_STEPS,&XYmagnet.Nstep);    
				XYmagnet.step=0;
				GetCtrlVal(EXTRAS,EXTRAS_THETA_TO,&theta_to);
				theta_to=2*3.1415*theta_to/360; // from degrees to radians
				GetCtrlVal(EXTRAS,EXTRAS_R_TO,&r_to);
				GetCtrlVal(EXTRAS,EXTRAS_MAXRATE,&XYmagnet.maxrate);
				XYmagnet.r_start=XYmagnet.r;
				XYmagnet.theta_start=XYmagnet.theta;
				XYmagnet.r_step=(r_to-XYmagnet.r)/XYmagnet.Nstep;
				XYmagnet.theta_step=(theta_to-XYmagnet.theta)/XYmagnet.Nstep; 
			} else {  // stopping a XY sweep
				XYmagnet_stop_sweep();
				XYmagnet.sweeping=0; 
			}
			break;
		}
	return 0;
}

int CVICALLBACK Start_Megasweep (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{   
	int nsteps;
	switch (event)
		{
		case EVENT_COMMIT:
		if (!MegaSweep.on) {
			if (FileSelectPopup (MegaSweep.filename,"*.dat", "*.dat","Save data", VAL_SAVE_BUTTON, 0, 0, 1, 1, MegaSweep.filename)) {
				GetCtrlVal(MAIN,MAIN_UPDOWN,&MegaSweep.updown);  
				GetCtrlVal(MAIN,MAIN_CH1_LOW,&sweep_ch1.lower_limit);
				GetCtrlVal(MAIN,MAIN_CH1_UP,&sweep_ch1.upper_limit);
				GetCtrlVal(MAIN,MAIN_CH1_RATE_UP,&sweep_ch1.rate_up);
				GetCtrlVal(MAIN,MAIN_CH1_RATE_DOWN,&sweep_ch1.rate_down); 
				GetCtrlVal(MAIN,MAIN_CH2_LOW,&sweep_ch2.lower_limit);
				GetCtrlVal(MAIN,MAIN_CH2_UP,&sweep_ch2.upper_limit);
				GetCtrlVal(MAIN,MAIN_CH2_RATE_UP,&sweep_ch2.rate_up);
				GetCtrlVal(MAIN,MAIN_CH2_RATE_DOWN,&sweep_ch2.rate_down);
				GetCtrlVal(EXTRAS,EXTRAS_CH3_LOW,&sweep_ch3.lower_limit);
				GetCtrlVal(EXTRAS,EXTRAS_CH3_UP,&sweep_ch3.upper_limit);
				GetCtrlVal(EXTRAS,EXTRAS_CH3_RATE_UP,&sweep_ch3.rate_up);
				GetCtrlVal(EXTRAS,EXTRAS_CH3_RATE_DOWN,&sweep_ch3.rate_down);
				GetCtrlVal(MAIN,MAIN_BIN_SIZE,&data.bin_size); // fixed     
				MegaSweep.z=sweep_ch2.lower_limit;
				MegaSweep.z3low=sweep_ch3.lower_limit;
				MegaSweep.z3high=sweep_ch3.upper_limit;
				MegaSweep.upperlimit=sweep_ch2.upper_limit;
				GetCtrlVal(MAIN,MAIN_MEGA_STEP_NUMBER,&nsteps);
				MegaSweep.step=(MegaSweep.upperlimit-MegaSweep.z)/nsteps;
				MegaSweep.nstep = nsteps;
				MegaSweep.step3=(sweep_ch3.upper_limit-sweep_ch3.lower_limit)/nsteps; 
				MegaSweep.on=1;
				MegaSweep.state=STARTING;
				data.acquiring=1;
				if ((sweep_ch1.type == SW_E5062)&&(!sweep_ch2.on)&&(config.x_axis_type == ACQ_CH1)) {E5062_Mega();}
				if ((sweep_ch1.type == SW_E4402B)&&(!sweep_ch2.on)&&(config.x_axis_type == ACQ_CH1)) {E4402B_Mega();}
				else MainLoop();
				}
			}
			else {
				MegaSweep.on=0;
				sweep_ch1.on=0;
				sweep_ch2.on=0;
				}
			break;
		}
	return 0;
}

int  CVICALLBACK mega_time(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	int nsteps;
	double total_time;	  // calculate total time of megasweep
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_CH1_LOW,&sweep_ch1.lower_limit);
			GetCtrlVal(MAIN,MAIN_CH1_UP,&sweep_ch1.upper_limit);
			GetCtrlVal(MAIN,MAIN_CH1_RATE_UP,&sweep_ch1.rate_up);
			GetCtrlVal(MAIN,MAIN_CH1_RATE_DOWN,&sweep_ch1.rate_down); 
			GetCtrlVal(MAIN,MAIN_CH2_LOW,&sweep_ch2.lower_limit);
			GetCtrlVal(MAIN,MAIN_CH2_UP,&sweep_ch2.upper_limit);
			GetCtrlVal(MAIN,MAIN_CH2_RATE_UP,&sweep_ch2.rate_up);
			GetCtrlVal(MAIN,MAIN_CH2_RATE_DOWN,&sweep_ch2.rate_down);
			GetCtrlVal(MAIN,MAIN_MEGA_STEP_NUMBER,&nsteps);
			total_time = ((sweep_ch2.upper_limit-sweep_ch2.lower_limit)/sweep_ch2.rate_up+nsteps * (sweep_ch1.upper_limit - sweep_ch1.lower_limit)/sweep_ch1.rate_up + (sweep_ch1.upper_limit - sweep_ch1.lower_limit)/sweep_ch1.rate_up)/3600;
			SetCtrlVal(MAIN,MAIN_MEGA_TIME,total_time);
		case EVENT_VAL_CHANGED:
			GetCtrlVal(MAIN,MAIN_CH1_LOW,&sweep_ch1.lower_limit);
			GetCtrlVal(MAIN,MAIN_CH1_UP,&sweep_ch1.upper_limit);
			GetCtrlVal(MAIN,MAIN_CH1_RATE_UP,&sweep_ch1.rate_up);
			GetCtrlVal(MAIN,MAIN_CH1_RATE_DOWN,&sweep_ch1.rate_down); 
			GetCtrlVal(MAIN,MAIN_CH2_LOW,&sweep_ch2.lower_limit);
			GetCtrlVal(MAIN,MAIN_CH2_UP,&sweep_ch2.upper_limit);
			GetCtrlVal(MAIN,MAIN_CH2_RATE_UP,&sweep_ch2.rate_up);
			GetCtrlVal(MAIN,MAIN_CH2_RATE_DOWN,&sweep_ch2.rate_down);
			GetCtrlVal(MAIN,MAIN_MEGA_STEP_NUMBER,&nsteps);
			total_time = ((sweep_ch2.upper_limit-sweep_ch2.lower_limit)/sweep_ch2.rate_up+nsteps * (sweep_ch1.upper_limit - sweep_ch1.lower_limit)/sweep_ch1.rate_up + (sweep_ch1.upper_limit - sweep_ch1.lower_limit)/sweep_ch1.rate_up)/3600;
			SetCtrlVal(MAIN,MAIN_MEGA_TIME,total_time);
		case EVENT_LEFT_CLICK:
			GetCtrlVal(MAIN,MAIN_CH1_LOW,&sweep_ch1.lower_limit);
			GetCtrlVal(MAIN,MAIN_CH1_UP,&sweep_ch1.upper_limit);
			GetCtrlVal(MAIN,MAIN_CH1_RATE_UP,&sweep_ch1.rate_up);
			GetCtrlVal(MAIN,MAIN_CH1_RATE_DOWN,&sweep_ch1.rate_down); 
			GetCtrlVal(MAIN,MAIN_CH2_LOW,&sweep_ch2.lower_limit);
			GetCtrlVal(MAIN,MAIN_CH2_UP,&sweep_ch2.upper_limit);
			GetCtrlVal(MAIN,MAIN_CH2_RATE_UP,&sweep_ch2.rate_up);
			GetCtrlVal(MAIN,MAIN_CH2_RATE_DOWN,&sweep_ch2.rate_down);
			GetCtrlVal(MAIN,MAIN_MEGA_STEP_NUMBER,&nsteps);
			total_time = ((sweep_ch2.upper_limit-sweep_ch2.lower_limit)/sweep_ch2.rate_up+nsteps * (sweep_ch1.upper_limit - sweep_ch1.lower_limit)/sweep_ch1.rate_up + (sweep_ch1.upper_limit - sweep_ch1.lower_limit)/sweep_ch1.rate_up)/3600;
			SetCtrlVal(MAIN,MAIN_MEGA_TIME,total_time);  
		break;
		}
	return 0;
}

int  CVICALLBACK VNA_points(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(MAIN,MAIN_VNA_points,&data.points_num); 
			GetCtrlVal(MAIN,MAIN_CH1_LOW,&sweep_ch1.lower_limit);
			GetCtrlVal(MAIN,MAIN_CH1_UP,&sweep_ch1.upper_limit);
			break;
		}
	return 0;	
}
int  CVICALLBACK VNA_time(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	return 0;
}
