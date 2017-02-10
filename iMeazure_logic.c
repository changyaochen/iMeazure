#include <utility.h>
#include <stdio.h>
#include "iMeazure_interface.h"
#include <userint.h>
#include <ansi_c.h> 
#include <stdlib.h>
//#include <dataacq.h>
//#include <easyio.h>		 /* changed to  easyio 2006 */
#include "iMeazure_logic.h"
#include "AMI_magnet.h"
#include "IPS120_magnet.h"     
#include "AMI_2D_magnet.h"
#include "KEITHLEY_2000.h"
#include "YOKO.h"
#include "KE2400#1.h" 
#include "KE2400#2.h" 
#include "HP34401A.h"
#include "CS4_magnet.h"
#include "TWO_KE2400s.h"    
#include "SR830.h"
#include "ppms.h"
#include "lakeshore340.h"
#include "FL6060.h"
#include "SIM928.h"
#include "Anritsu_68369.h"
#include "E5062.h"
#include "SIM970.h"	
#include "E4402B.h" 
#include "Agilent33220A.h" 
#include "DAC.h"
#include "SIM965.h" 
//#include "ziAPI.h"

// public global vars

//****************************	
// get x coordinate	
void get_x(void) 
{
	switch (config.x_axis_type) {
		case ACQ_NONE	:  now.x=0; break ;
		case ACQ_TIME	:  now.x=TIME ; break ;	
		//case ACQ_ADC0	:  AISampleChannel (1,  "0",0.0,0.0, &now.x); break ;
		//case ACQ_ADC1	:  AISampleChannel (1,  "1",0.0,0.0, &now.x); break ;
		//case ACQ_ADC2	:  AISampleChannel (1,  "2",0.0,0.0, &now.x); break ;
		case ACQ_CH1	:  now.x=sweep_ch1.x; break ;
		case ACQ_CH2	:  now.x=sweep_ch2.x; break ;
		case ACQ_CH3	:  now.x=sweep_ch3.x; break ;
		case ACQ_HP34401A_1	:  now.x=hp34401A_1_Measure(); break ;
		case ACQ_HP34401A_2	:  now.x=hp34401A_2_Measure(); break ;   
		case ACQ_KEITHLEY	:  now.x=keithley_get_data();  break ;  
		case ACQ_XYMAG_THETA:  now.x=ips120_get_field();  break ;  
		case ACQ_XYMAG_X:  now.x=XYmagnet.x;  break ;      
		case ACQ_XYMAG_Y:  now.x=XYmagnet.y;  break ; 
		case ACQ_XYMAG_R: 	now.x=cs4_get_field(); break;
		case ACQ_LAKESHORE340:  now.x=lakeshore340_readtemp();  break ; 
		//case ACQ_PPMS_TEMP:  now.x=ppms_get_temp();  break ;
	}
	now.x=now.x*config.x_axis_factor+config.x_axis_offset;  
}

// get y coordiante
void get_y(void) 
{
	switch (config.y_axis_type) {
		case ACQ_NONE	:  now.y=0; break ;
		case ACQ_FAKE	:  now.y=(sweep_ch1.x)*(sweep_ch1.x)+(sweep_ch2.x)*(sweep_ch2.x); break;
		case ACQ_TIME	:  now.y=TIME ; break ;	
		case ACQ_ADC0	:  now.y = ADC0_read(); break ;
		case ACQ_ADC1	:  now.y = ADC1_read(); break ; 
		case ACQ_ADC2	:  now.y = ADC2_read(); break ; 
		case ACQ_ADC3	:  now.y = ADC3_read(); break ;
		case ACQ_CH1	:  now.y=sweep_ch1.x; break ;
		case ACQ_CH2	:  now.y=sweep_ch2.x; break ;
		case ACQ_HP34401A_1	:  now.y=hp34401A_1_Measure(); break ;
		case ACQ_HP34401A_2	:  now.y=hp34401A_2_Measure(); break ;   
		case ACQ_KEITHLEY	:  now.y=keithley_get_data(); break ; 
		case ACQ_XYMAG_THETA:  now.y=(360/(2*3.1415))*XYmagnet.theta;  break ; 
		case ACQ_XYMAG_X:  now.y=XYmagnet.x;  break ;      
		case ACQ_XYMAG_Y:  now.y=XYmagnet.y;  break ;     
		case ACQ_SR830_1:  now.y=sr830_readch1_1();  break ;
		case ACQ_SR830_2:  now.y=sr830_readch1_2();  break ; 
		case ACQ_SR830_3:  now.y=sr830_readch2_2();  break;
		case ACQ_LAKESHORE340:  now.y=lakeshore340_readtemp();  break ;
		case ACQ_E5062_CH1_Amp:  now.y=0;  break;
		case ACQ_E5062_CH1_Phase:  now.y=0;  break;
		//case ACQ_PPMS_TEMP:  now.y=ppms_get_temp();  break ;
		case ACQ_SIM970_CH1	:  now.y=SIM970_CH1_Measure(); break ;
		case ACQ_SIM970_CH2	:  now.y=SIM970_CH2_Measure(); break ; 
		case ACQ_SIM970_CH3	:  now.y=SIM970_CH3_Measure(); break ;
		case ACQ_SIM970_CH4	:  now.y=SIM970_CH4_Measure(); break ; 
		case ACQ_E4402B_Amp:  now.y=0;  break;
		
	}
	now.y=now.y*config.y_axis_factor+config.y_axis_offset;
}
// get second y coordiante 
void get_y1(void) 
{
	switch (config.y1_axis_type) {
		case ACQ_NONE	:  now.y1=0; break ;
		case ACQ_TIME	:  now.y1=TIME ; break ;	
		case ACQ_ADC0	:  now.y1 = ADC0_read(); break ;
		case ACQ_ADC1	:  now.y1 = ADC1_read(); break ; 
		case ACQ_ADC2	:  now.y1 = ADC2_read(); break ; 
		case ACQ_ADC3	:  now.y1 = ADC3_read(); break ;
		case ACQ_CH1	:  now.y1=sweep_ch1.x; break ;
		case ACQ_CH2	:  now.y1=sweep_ch2.x; break ;
		case ACQ_HP34401A_1	:  now.y1=hp34401A_1_Measure(); break ;
		case ACQ_HP34401A_2	:  now.y1=hp34401A_2_Measure(); break ;   
		case ACQ_KEITHLEY	:  now.y1=keithley_get_data(); break ;
		case ACQ_XYMAG_THETA:  now.y1=(360/(2*3.1415))*XYmagnet.theta;  break ; 
		case ACQ_XYMAG_X:  now.y1=XYmagnet.x;  break ;      
		case ACQ_XYMAG_Y:  now.y1=XYmagnet.y;  break ;      
		case ACQ_SR830_1:  now.y1=sr830_readch1_1();  break ;
		case ACQ_SR830_2:  now.y1=sr830_readch1_2();  break ;  
		case ACQ_SR830_3:  now.y1=sr830_readch2_2();  break; 
		case ACQ_LAKESHORE340:  now.y1=lakeshore340_readtemp();  break ; 
		case ACQ_E5062_CH1_Amp:  now.y1=0;  break;
		case ACQ_E5062_CH1_Phase:  now.y1=0;  break;
		//case ACQ_PPMS_TEMP:  now.y=ppms_get_temp();  break ; 
		case ACQ_SIM970_CH1	:  now.y1=SIM970_CH1_Measure(); break ;
		case ACQ_SIM970_CH2	:  now.y1=SIM970_CH2_Measure(); break ; 
		case ACQ_SIM970_CH3	:  now.y1=SIM970_CH3_Measure(); break ;
		case ACQ_SIM970_CH4	:  now.y1=SIM970_CH4_Measure(); break ;
		case ACQ_E4402B_Amp :  now.y1=0;  break;  
		  
		
	}
	now.y1=now.y1*config.y1_axis_factor+config.y1_axis_offset;
}

// get third y coordiante 
void get_y2(void) 
{
	switch (config.y2_axis_type) {
		case ACQ_NONE	:  now.y2=0; break ;
		case ACQ_TIME	:  now.y2=TIME ; break ;	
		case ACQ_ADC0	:  now.y2 = ADC0_read(); break ;
		case ACQ_ADC1	:  now.y2 = ADC1_read(); break ; 
		case ACQ_ADC2	:  now.y2 = ADC2_read(); break ; 
		case ACQ_ADC3	:  now.y2 = ADC3_read(); break ;
		case ACQ_CH1	:  now.y2=sweep_ch1.x; break ;
		case ACQ_CH2	:  now.y2=sweep_ch2.x; break ;
		case ACQ_HP34401A_1	:  now.y2=hp34401A_1_Measure(); break ;
		case ACQ_HP34401A_2	:  now.y2=hp34401A_2_Measure(); break ;   
		case ACQ_KEITHLEY	:  now.y2=keithley_get_data(); break ;
		case ACQ_XYMAG_THETA:  now.y2=(360/(2*3.1415))*XYmagnet.theta;  break ; 
		case ACQ_XYMAG_X:  now.y2=XYmagnet.x;  break ;      
		case ACQ_XYMAG_Y:  now.y2=XYmagnet.y;  break ;      
		case ACQ_SR830_1:  now.y2=sr830_readch1_1();  break ;
		case ACQ_SR830_2:  now.y2=sr830_readch1_2();  break ;  
		case ACQ_SR830_3:  now.y2=sr830_readch2_2();  break; 
		case ACQ_LAKESHORE340:  now.y2=lakeshore340_readtemp();  break ;
		case ACQ_E5062_CH1_Amp:  now.y2=0;  break;
		case ACQ_E5062_CH1_Phase:  now.y2=0;  break;
		//case ACQ_PPMS_TEMP:  now.y=ppms_get_temp();  break ;  
		case ACQ_SIM970_CH1	:  now.y2=SIM970_CH1_Measure(); break ;
		case ACQ_SIM970_CH2	:  now.y2=SIM970_CH2_Measure(); break ; 
		case ACQ_SIM970_CH3	:  now.y2=SIM970_CH3_Measure(); break ;
		case ACQ_SIM970_CH4	:  now.y2=SIM970_CH4_Measure(); break ; 
		case ACQ_E4402B_Amp :  now.y2=0;  break;  
		  
	}
	now.y2=now.y2*config.y2_axis_factor+config.y2_axis_offset;
}


// Here we count how many points per second we are taking and process interface
void Timing(void)
{
	timing.points_num++;
	if ((TIME-timing.start)>timing.length) // calculate how many points per second we take process the events 
			{
			   	timing.start=TIME;
			   	//update (0, 0, EVENT_TIMER_TICK, 0, 0, 0);
			  // 	GetUserEvent (0, 0, 0);
				ProcessDrawEvents();
				ProcessSystemEvents();  
				timing.points_per_sec=1000*(TIME-timing.start);
				//timing.points_per_sec=timing.points_num/(TIME-timing.start);
				timing.points_num=0;
				timing.start=TIME;
			}
}

/*			Operation of 2D magnet		*/
void Sweep_XYMagnet (void)
{
double ramp_rate_x,ramp_rate_y,Dx,Dy;
double theta,r;
// we get here if the sweep is running
	if ((TIME-XYmagnet.timing_start)>XYMAGNET_TIMING_LENGTH) { // Only speak to the magnet once every while
			   	XYmagnet.timing_start=TIME;
			   	XYmagnet_update();
			   	if (!XYmagnet.ramping) { // the magnet stopped ramping - we need to setup a ramp to a new point
			   		if (XYmagnet.step<XYmagnet.Nstep) { // not the end of sweep
			   			XYmagnet.step++;
			   			theta=XYmagnet.theta_start+XYmagnet.theta_step*XYmagnet.step;
			   			r=XYmagnet.r_start+XYmagnet.r_step*XYmagnet.step;
			   			Dx=fabs(r*cos(theta)-XYmagnet.x);
			   			Dy=fabs(r*sin(theta)-XYmagnet.y); 
			   			/* we want to sync. ramp rates so that both magnets finish ramping at the same time */
			   			if (Dx>Dy) { // higher rate x
			   			 ramp_rate_x=XYmagnet.maxrate;
			   			 ramp_rate_y=ramp_rate_x*Dy/Dx; } else { // higher rate y
			   			 ramp_rate_y=XYmagnet.maxrate;
			   			 ramp_rate_x=ramp_rate_y*Dx/Dy;}
			   			/* now ramp */ 
			   			XYmagnet_ramp(r*cos(theta),r*sin(theta),ramp_rate_x,ramp_rate_y); // start a ramp to a new point
			   		}
			   		else { // sweep is over
			   		XYmagnet.sweeping=0;
			   		}
			   			
			   	}
	}

}

void Autobreak_Checks (void) // breaking the wire using gradual electromigration
{
	const int OVERSAMPLING_TIMES=10;
	double resistance,y;
	int i;
	get_x();
	y=0; for (i=0;i<OVERSAMPLING_TIMES;i++) {get_y();y=y+now.y;}; now.y=y/OVERSAMPLING_TIMES;   // bad hack - need oversampling to decrease noise
	resistance=now.x/now.y;
	if ((sweep_ch1.x<autobreak.safe_voltage)&&(autobreak.first_time)) autobreak.critical_resistance=resistance*autobreak.critical_resistance_increase;
	if ((sweep_ch1.x>autobreak.safe_voltage)&&(resistance>autobreak.critical_resistance)) {
	// reset the sweep up, the wire broke a little
			autobreak.first_time=0;
			sweep_ch1.x=sweep_ch1.x*autobreak.withdraw_voltage;
			sweep_ch1.starting_time=TIME;
			sweep_ch1.starting_x=sweep_ch1.x;
			switch (sweep_ch1.type) {
				case SW_NONE	:	break;
		//		case SW_DAC0	:	AO_VWrite (1,	0,	sweep_ch1.x); break;
		//		case SW_DAC1	:	AO_VWrite (1,	1,	sweep_ch1.x); break;
			}
			//Delay(0.05);//bad - to settle after ramping voltage down
			/* Reset the ramping  */
			/*	y=0; for (i=0;i<OVERSAMPLING_TIMES;i++) {get_y();y=y+now.y;}; y=y/OVERSAMPLING_TIMES;
			autobreak.critical_resistance=autobreak.critical_resistance_increase*now.x/now.y; */
			autobreak.critical_resistance=autobreak.critical_resistance_increase*resistance;
			/* Resistance reached the goal - ramp down now */
			
	}
	if ((resistance>autobreak.target_resistance)&&(sweep_ch1.x>autobreak.safe_voltage)) {
				sweep_ch1.direction=-1;
				sweep_ch1.starting_time=TIME;
				sweep_ch1.starting_x=sweep_ch1.x;
				autobreak.on=0;
			}
}


// Recalculate the sweeping generator channel 1
void Update_ch1_Sweep(void) 
{		
	if (sweep_ch1.type==SW_IPS120) {sweep_ch1.on=ips120.ramping;}
	if (sweep_ch1.type==SW_CS4) {sweep_ch1.on=cs4.ramping;} 
	if ((sweep_ch1.type==SW_E5062) || (sweep_ch1.type==SW_E4402B))  {}
	if (sweep_ch1.type==SW_PPMS) {sweep_ch1.on=ppms.ramping;}  
	if ((sweep_ch1.type!=SW_IPS120)&&(sweep_ch1.type!=SW_CS4)&&(sweep_ch1.type!=SW_PPMS)&&(sweep_ch1.on)&&(sweep_ch1.type!=SW_E5062))
	{ // If ramping DACs or Keithly and such we manually set up the ramp
		if (sweep_ch1.direction==1) sweep_ch1.x=(TIME-sweep_ch1.starting_time)*sweep_ch1.rate_up+sweep_ch1.starting_x;   // updating ch1.x value
		if (sweep_ch1.direction==-1) sweep_ch1.x=-(TIME-sweep_ch1.starting_time)*sweep_ch1.rate_down+sweep_ch1.starting_x;
		switch (sweep_ch1.stop) {
			case STOP_AT_BOTH : if ((sweep_ch1.x>sweep_ch1.upper_limit)&&(sweep_ch1.direction==1)) { sweep_ch1.on=0; sweep_ch1.x=sweep_ch1.upper_limit;magnet.ramping=0;}
								if ((sweep_ch1.x<sweep_ch1.lower_limit)&&(sweep_ch1.direction==-1)) { sweep_ch1.on=0; sweep_ch1.x=sweep_ch1.lower_limit;magnet.ramping=0;}        
								break;
							
			case STOP_AT_MAX : 	if ((sweep_ch1.x>sweep_ch1.upper_limit)&&(sweep_ch1.direction==1)) { sweep_ch1.on=0; sweep_ch1.x=sweep_ch1.upper_limit;magnet.ramping=0;magnet.ramping=0;};
								if ((sweep_ch1.x<sweep_ch1.lower_limit)&&(sweep_ch1.direction==-1)) { sweep_ch1.direction=1; sweep_ch1.starting_time=TIME; sweep_ch1.starting_x=sweep_ch1.lower_limit;magnet.ramping=0;magnet.ramping=0;}
								break;
							
			case STOP_AT_MIN :  if ((sweep_ch1.x<sweep_ch1.lower_limit)&&(sweep_ch1.direction==-1)) { sweep_ch1.on=0; sweep_ch1.x=sweep_ch1.lower_limit;magnet.ramping=0;};        
								if ((sweep_ch1.x>sweep_ch1.upper_limit)&&(sweep_ch1.direction==1)) { sweep_ch1.direction=-1; sweep_ch1.starting_time=TIME; sweep_ch1.starting_x=sweep_ch1.upper_limit;magnet.ramping=0;}
								break;
			case DO_NOT_STOP : 	
								if ((sweep_ch1.x<sweep_ch1.lower_limit)&&(sweep_ch1.direction==-1)) { sweep_ch1.direction=1; sweep_ch1.starting_time=TIME; sweep_ch1.starting_x=sweep_ch1.lower_limit;magnet.ramping=0;}
								if ((sweep_ch1.x>sweep_ch1.upper_limit)&&(sweep_ch1.direction==1)) { sweep_ch1.direction=-1; sweep_ch1.starting_time=TIME; sweep_ch1.starting_x=sweep_ch1.upper_limit;magnet.ramping=0;}
		}
	}
	
		switch (sweep_ch1.type) {
			case SW_NONE	:	break;
			//case SW_DAC0	:	DAC0_set(sweep_ch1.x); break;
			//case SW_DAC1	:	DAC1_set(sweep_ch1.x); break;
			case SW_KE2400N1:	KE2400N1_set(sweep_ch1.x); break;
			case SW_KE2400N2:	KE2400N2_set(sweep_ch1.x); break;  
			case SW_KE2400s:	KE2400s_set(sweep_ch1.x); break;  			
			case SW_YOKO	:	YOKO_set(sweep_ch1.x); break;
			case SW_FAKE	:	break;      
			case SW_IPS120  :   sweep_ch1.x=ips120_get_field(); break;
			case SW_CS4 	:   sweep_ch1.x=cs4_get_field(); break; 
			case SW_PPMS	:   sweep_ch1.x=ppms_get_field(); break;
			case SW_FL6060	:   generic_set_freq(sweep_ch1.x); break;  
			case SW_SIM928N1  :   SIM928N1_set(sweep_ch1.x); break;
			case SW_Anritsu_68369: Anritsu_68369_set(sweep_ch1.x); break;
			case SW_SIM928N2  :   SIM928N2_set(sweep_ch1.x); break;
			case SW_SIM928N3  :   SIM928N3_set(sweep_ch1.x); break;
			case SW_SIM928N4  :   SIM928N4_set(sweep_ch1.x); break;
			case SW_SR850_Freq     :   sr850_set_freq(sweep_ch1.x); break;
			case SW_SR850_Amp      :   sr850_set_amp(sweep_ch1.x); break;
			case SW_SR850_AUX1:   sr850_set_aux1_volt(sweep_ch1.x);break;
			case SW_SR850_AUX2:   sr850_set_aux2_volt(sweep_ch1.x);break; 
			case SW_SR850_AUX3:   sr850_set_aux3_volt(sweep_ch1.x);break; 
			case SW_SR850_AUX4:   sr850_set_aux4_volt(sweep_ch1.x);break; 
			case SW_33220A_Freq:  ag33220a_set_freq(sweep_ch1.x);break;
			case SW_33220A_Amp:   ag33220a_set_amp(sweep_ch1.x);break;
			case SW_SIM965N1  :   SIM965N1_set(sweep_ch1.x); break;
			case SW_SIM965N2  :   SIM965N2_set(sweep_ch1.x); break;
		}
	}
	

void Update_ch2_Sweep(void) // update sweep channel 2
{											 
	// stop the magnet sweep if we are not ramping
	
	if ((sweep_ch1.type==SW_E5062) || (sweep_ch1.type==SW_E4402B))  {}
	if (sweep_ch2.type==SW_IPS120) {sweep_ch2.on=ips120.ramping;}
	if (sweep_ch2.type==SW_CS4) {sweep_ch2.on=cs4.ramping;}  
	if (sweep_ch2.type==SW_PPMS) {sweep_ch2.x=ppms_get_field();sweep_ch2.on=ppms.ramping;}  
	if (((sweep_ch2.type!=SW_IPS120)&&(sweep_ch2.type!=SW_CS4))&&(sweep_ch2.on)) 
	{ // If ramping DACs or Keithly and such we manually set up the ramp
		if (sweep_ch2.direction==1) sweep_ch2.x=(TIME-sweep_ch2.starting_time)*sweep_ch2.rate_up+sweep_ch2.starting_x;
		if (sweep_ch2.direction==-1) sweep_ch2.x=-(TIME-sweep_ch2.starting_time)*sweep_ch2.rate_down+sweep_ch2.starting_x;
		switch (sweep_ch2.stop) {
			case STOP_AT_BOTH : if ((sweep_ch2.x>sweep_ch2.upper_limit)&&(sweep_ch2.direction==1)) { sweep_ch2.on=0; sweep_ch2.x=sweep_ch2.upper_limit;magnet.ramping=0;}
								if ((sweep_ch2.x<sweep_ch2.lower_limit)&&(sweep_ch2.direction==-1)) { sweep_ch2.on=0; sweep_ch2.x=sweep_ch2.lower_limit;magnet.ramping=0;}        
								break;
							
			case STOP_AT_MAX : 	if ((sweep_ch2.x>sweep_ch2.upper_limit)&&(sweep_ch2.direction==1)) { sweep_ch2.on=0; sweep_ch2.x=sweep_ch2.upper_limit;magnet.ramping=0;magnet.ramping=0;};
								if ((sweep_ch2.x<sweep_ch2.lower_limit)&&(sweep_ch2.direction==-1)) { sweep_ch2.direction=1; sweep_ch2.starting_time=TIME; sweep_ch2.starting_x=sweep_ch2.lower_limit;magnet.ramping=0;magnet.ramping=0;}
								break;
							
			case STOP_AT_MIN :  if ((sweep_ch2.x<sweep_ch2.lower_limit)&&(sweep_ch2.direction==-1)) { sweep_ch2.on=0; sweep_ch2.x=sweep_ch2.lower_limit;magnet.ramping=0;};        
								if ((sweep_ch2.x>sweep_ch2.upper_limit)&&(sweep_ch2.direction==1)) { sweep_ch2.direction=-1; sweep_ch2.starting_time=TIME; sweep_ch2.starting_x=sweep_ch2.upper_limit;magnet.ramping=0;}
								break;
			case DO_NOT_STOP : 	
								if ((sweep_ch2.x<sweep_ch2.lower_limit)&&(sweep_ch2.direction==-1)) { sweep_ch2.direction=1; sweep_ch2.starting_time=TIME; sweep_ch2.starting_x=sweep_ch2.lower_limit;magnet.ramping=0;}
								if ((sweep_ch2.x>sweep_ch2.upper_limit)&&(sweep_ch2.direction==1)) { sweep_ch2.direction=-1; sweep_ch2.starting_time=TIME; sweep_ch2.starting_x=sweep_ch2.upper_limit;magnet.ramping=0;}
			}
		}
		switch (sweep_ch2.type) {
			case SW_NONE	:	break;
			//case SW_DAC0	:	DAC0_set(sweep_ch2.x); break;
			//case SW_DAC1	:	DAC1_set(sweep_ch2.x); break;
			case SW_YOKO	:	YOKO_set(sweep_ch2.x); break;
			case SW_KE2400N1:	KE2400N1_set(sweep_ch2.x); break;
			case SW_KE2400N2:	KE2400N2_set(sweep_ch2.x); break;  
			case SW_KE2400s:	KE2400s_set(sweep_ch2.x); break;  	
			case SW_IPS120  :   sweep_ch2.x=ips120_get_field(); break;
			case SW_CS4 	:   sweep_ch2.x=cs4_get_field(); break; 
			case SW_FL6060	:   generic_set_freq(sweep_ch2.x); break;
			case SW_PPMS	:   sweep_ch2.x=ppms_get_field(); break;
			case SW_SIM928N1  :   SIM928N1_set(sweep_ch2.x); break;  
			case SW_FAKE	:	break;
			case SW_Anritsu_68369: Anritsu_68369_set(sweep_ch2.x); break;
			case SW_SIM928N2  :   SIM928N2_set(sweep_ch2.x); break; 
			case SW_SIM928N3  :   SIM928N3_set(sweep_ch2.x); break; 
			case SW_SIM928N4  :   SIM928N4_set(sweep_ch2.x); break; 
			case SW_SR850_Freq    :   sr850_set_freq(sweep_ch2.x); break;
			case SW_SR850_Amp     :   sr850_set_amp(sweep_ch2.x); break; 
			case SW_SR850_AUX1:   sr850_set_aux1_volt(sweep_ch2.x);break;
			case SW_SR850_AUX2:   sr850_set_aux2_volt(sweep_ch2.x);break; 
			case SW_SR850_AUX3:   sr850_set_aux3_volt(sweep_ch2.x);break; 
			case SW_SR850_AUX4:   sr850_set_aux4_volt(sweep_ch2.x);break; 
			case SW_33220A_Freq:  ag33220a_set_freq(sweep_ch2.x);break;
			case SW_33220A_Amp:   ag33220a_set_amp(sweep_ch2.x);break;
			case SW_SIM965N1  :   SIM965N1_set(sweep_ch2.x); break;
			case SW_SIM965N2  :   SIM965N2_set(sweep_ch2.x); break;
		}
}

void Update_ch3_Sweep(void) // update sweep channel 3
{											 
	// stop the magnet sweep if we are not ramping
	
	//if ((sweep_ch1.type==SW_E5062) || (sweep_ch1.type==SW_E4402B))  {}
	if (sweep_ch3.type==SW_IPS120) {sweep_ch3.on=ips120.ramping;}
	if (sweep_ch3.type==SW_CS4) {sweep_ch3.on=cs4.ramping;}  
	if (sweep_ch3.type==SW_PPMS) {sweep_ch3.x=ppms_get_field();sweep_ch3.on=ppms.ramping;}  
	if (((sweep_ch3.type!=SW_IPS120)&&(sweep_ch3.type!=SW_CS4))&&(sweep_ch3.on)) 
	{ // If ramping DACs or Keithly and such we manually set up the ramp
		if (sweep_ch3.direction==1) sweep_ch3.x=(TIME-sweep_ch3.starting_time)*sweep_ch3.rate_up+sweep_ch3.starting_x;
		if (sweep_ch3.direction==-1) sweep_ch3.x=-(TIME-sweep_ch3.starting_time)*sweep_ch3.rate_down+sweep_ch3.starting_x;
		switch (sweep_ch3.stop) {
			case STOP_AT_BOTH : if ((sweep_ch3.x>sweep_ch3.upper_limit)&&(sweep_ch3.direction==1)) { sweep_ch3.on=0; sweep_ch3.x=sweep_ch3.upper_limit;magnet.ramping=0;}
								if ((sweep_ch3.x<sweep_ch3.lower_limit)&&(sweep_ch3.direction==-1)) { sweep_ch3.on=0; sweep_ch3.x=sweep_ch3.lower_limit;magnet.ramping=0;}        
								break;
							
			case STOP_AT_MAX : 	if ((sweep_ch3.x>sweep_ch3.upper_limit)&&(sweep_ch3.direction==1)) { sweep_ch3.on=0; sweep_ch3.x=sweep_ch3.upper_limit;magnet.ramping=0;magnet.ramping=0;};
								if ((sweep_ch3.x<sweep_ch3.lower_limit)&&(sweep_ch3.direction==-1)) { sweep_ch3.direction=1; sweep_ch3.starting_time=TIME; sweep_ch3.starting_x=sweep_ch3.lower_limit;magnet.ramping=0;magnet.ramping=0;}
								break;
							
			case STOP_AT_MIN :  if ((sweep_ch3.x<sweep_ch3.lower_limit)&&(sweep_ch3.direction==-1)) { sweep_ch3.on=0; sweep_ch3.x=sweep_ch3.lower_limit;magnet.ramping=0;};        
								if ((sweep_ch3.x>sweep_ch3.upper_limit)&&(sweep_ch3.direction==1)) { sweep_ch3.direction=-1; sweep_ch3.starting_time=TIME; sweep_ch3.starting_x=sweep_ch3.upper_limit;magnet.ramping=0;}
								break;
			case DO_NOT_STOP : 	
								if ((sweep_ch3.x<sweep_ch3.lower_limit)&&(sweep_ch3.direction==-1)) { sweep_ch3.direction=1; sweep_ch3.starting_time=TIME; sweep_ch3.starting_x=sweep_ch3.lower_limit;magnet.ramping=0;}
								if ((sweep_ch3.x>sweep_ch3.upper_limit)&&(sweep_ch3.direction==1)) { sweep_ch3.direction=-1; sweep_ch3.starting_time=TIME; sweep_ch3.starting_x=sweep_ch3.upper_limit;magnet.ramping=0;}
			}
		}
		switch (sweep_ch3.type) {
			case SW_NONE	:	break;
			//case SW_DAC0	:	DAC0_set(sweep_ch3.x); break;
			//case SW_DAC1	:	DAC1_set(sweep_ch3.x); break;
			case SW_YOKO	:	YOKO_set(sweep_ch3.x); break;
			case SW_KE2400N1:	KE2400N1_set(sweep_ch3.x); break;
			case SW_KE2400N2:	KE2400N2_set(sweep_ch3.x); break;  
			case SW_KE2400s:	KE2400s_set(sweep_ch3.x); break;  	
			case SW_IPS120  :   sweep_ch3.x=ips120_get_field(); break;
			case SW_CS4 	:   sweep_ch3.x=cs4_get_field(); break; 
			case SW_FL6060	:   generic_set_freq(sweep_ch3.x); break;
			case SW_PPMS	:   sweep_ch3.x=ppms_get_field(); break;
			case SW_SIM928N1  :   SIM928N1_set(sweep_ch3.x); break;  
			case SW_FAKE	:	break;
			case SW_Anritsu_68369: Anritsu_68369_set(sweep_ch3.x); break;
			case SW_SIM928N2  :   SIM928N2_set(sweep_ch3.x); break; 
			case SW_SIM928N3  :   SIM928N3_set(sweep_ch3.x); break; 
			case SW_SIM928N4  :   SIM928N4_set(sweep_ch3.x); break; 
			case SW_SR850_Freq     :   sr850_set_freq(sweep_ch3.x); break;
			case SW_SR850_Amp      :   sr850_set_amp(sweep_ch3.x); break; 
			case SW_SR850_AUX1:   sr850_set_aux1_volt(sweep_ch3.x);break;
			case SW_SR850_AUX2:   sr850_set_aux2_volt(sweep_ch3.x);break; 
			case SW_SR850_AUX3:   sr850_set_aux3_volt(sweep_ch3.x);break; 
			case SW_SR850_AUX4:   sr850_set_aux4_volt(sweep_ch2.x);break; 
			case SW_33220A_Freq:  ag33220a_set_freq(sweep_ch3.x);break;
			case SW_33220A_Amp:   ag33220a_set_amp(sweep_ch3.x);break;
			case SW_SIM965N1  :   SIM965N1_set(sweep_ch3.x); break;
			case SW_SIM965N2  :   SIM965N2_set(sweep_ch3.x); break;
		}
}


/* *********************** start UpdateMegaSweep ************************************ */
void UpdateMegaSweep(void) // Handles everything related to MegaSweep
{
	FILE* out;
	int i,temp, temp2;
	int ch3_direction;
	GetCtrlVal(EXTRAS,EXTRAS_CH3_DIRECTION,&ch3_direction);
	GetCtrlVal(EXTRAS,EXTRAS_megaButton,&sweep_ch3.mega);

	if (MegaSweep.on)
 	{
		switch (MegaSweep.state) {
		 case STARTING:
	 	// sweep both CH1 and CH2 down, when done switch to taking data
	 		 Message(" Starting Megasweep");
			 SetCtrlVal(MAIN,MAIN_CH2_DIRECTION,-1);  
			 SetCtrlVal(MAIN,MAIN_CH1_DIRECTION,-1);  
			 start_sweep_ch1(0,0,EVENT_COMMIT,0,0,0);
			 start_sweep_ch2(0,0,EVENT_COMMIT,0,0,0);			 
			 MegaSweep.state=WAITING_TO_RAMP_DOWN;
			 if (ch3_direction == 1) {MegaSweep.z3high = sweep_ch3.lower_limit;} 
			 else {MegaSweep.z3low = sweep_ch3.upper_limit;}
			 break;
		 case WAITING_TO_RAMP_DOWN:
		 // waiting until both ch1 and ch2 at low_limit.
			if ((!sweep_ch1.on)&&(!sweep_ch2.on)) { // start acq 
				cleargraph (0,0,EVENT_COMMIT,0,0,0); //clear graph  
			 	SetCtrlVal(MAIN,MAIN_CH1_DIRECTION,1);   
			 	start_sweep_ch1(0,0,EVENT_COMMIT,0,0,0);        
			 	data.acquiring=1; // start acq
			    MegaSweep.state=ACQ_DATA; 
			    Message(" Acquiring curve first curve");
			    cleargraph (0,0,EVENT_COMMIT,0,0,0); //clear graph
				}
			break;
		 case ACQ_DATA:
		 // check if acq is done, if done, save data, check if this is the last point, if not start ramping CH1 down
			GetCtrlVal(MAIN,MAIN_CH1_DIRECTION,&temp);
		 	if (sweep_ch1.on==!1) 
			{ // if the sweep is done
				Message("Curve acquired, sweeping CH1");
				// saving
					out=fopen(MegaSweep.filename,"a");   
					if (!config.y1_axis_active && !config.y2_axis_active)  {	// if only one channel is acqd.
						GetCtrlVal(EXTRAS,EXTRAS_megaButton,&sweep_ch3.mega);
						if ((sweep_ch3.mega ==1)&&(ch3_direction == 1)) // if channel 3 is selected and sweeping up
							{
							for(i=1;i<data.points_num;i++) fprintf( out , "%12.12e%s%12.12e%s%12.12e%s%12.12e%s", data.x[i], "\t",data.y[i], "\t",MegaSweep.z,"\t",MegaSweep.z3high,"\n");
							}
						else if ((sweep_ch3.mega ==1)&&(ch3_direction == -1)) // if channel 3 is selected and sweeping up
							{
							for(i=1;i<data.points_num;i++) fprintf( out , "%12.12e%s%12.12e%s%12.12e%s%12.12e%s", data.x[i], "\t",data.y[i], "\t",MegaSweep.z,"\t",MegaSweep.z3low,"\n");
							}
						else 
						{
							for(i=1;i<data.points_num;i++) fprintf( out , "%12.12e%s%12.12e%s%12.12e%s", data.x[i], "\t",data.y[i], "\t",MegaSweep.z,"\n");	//if channel 3 is not selected	   
						}
					}
					 
					else if (config.y1_axis_active && !config.y2_axis_active) {	// if two are acqd.
						GetCtrlVal(EXTRAS,EXTRAS_megaButton,&sweep_ch3.mega);
						if ((sweep_ch3.mega ==1)&&(ch3_direction == 1)) // if channel 3 is selected and sweeping up
							{
							for(i=1;i<data.points_num;i++) fprintf( out , "%12.12e%s%12.12e%s%12.12e%s%12.12e%s%12.12e%s", data.x[i], "\t",data.y[i], "\t",data.y1[i],"\t",MegaSweep.z,"\t",MegaSweep.z3high,"\n");
							}
						else if ((sweep_ch3.mega ==1)&&(ch3_direction == -1)) // if channel 3 is selected and sweeping up
							{
							for(i=1;i<data.points_num;i++) fprintf( out , "%12.12e%s%12.12e%s%12.12e%s%12.12e%s%12.12e%s", data.x[i], "\t",data.y[i], "\t",data.y1[i],"\t",MegaSweep.z,"\t",MegaSweep.z3low,"\n");
							}
						else 
						{
							for(i=1;i<data.points_num;i++) fprintf( out , "%12.12e%s%12.12e%s%12.12e%s%12.12e%s", data.x[i], "\t",data.y[i], "\t",data.y1[i],"\t",MegaSweep.z,"\n");	//if channel 3 is not selected	   
						}
					}
					else {		  // if all three channels are acqd.
						GetCtrlVal(EXTRAS,EXTRAS_megaButton,&sweep_ch3.mega);
						if ((sweep_ch3.mega ==1)&&(ch3_direction == 1)) // if channel 3 is selected and sweeping up
							{
							for(i=1;i<data.points_num;i++) fprintf( out , "%12.12e%s%12.12e%s%12.12e%s%12.12e%s%12.12e%s", data.x[i], "\t",data.y[i], "\t",data.y1[i],"\t",data.y2[i],"\t",MegaSweep.z,"\t",MegaSweep.z3high,"\n");
							}
						else if ((sweep_ch3.mega ==1)&&(ch3_direction == -1)) // if channel 3 is selected and sweeping up
							{
							for(i=1;i<data.points_num;i++) fprintf( out , "%12.12e%s%12.12e%s%12.12e%s%12.12e%s%12.12e%s", data.x[i], "\t",data.y[i], "\t",data.y1[i],"\t",data.y2[i],"\t",MegaSweep.z,"\t",MegaSweep.z3low,"\n");
							}
						else 
						{
							for(i=1;i<data.points_num;i++) fprintf( out , "%12.12e%s%12.12e%s%12.12e%s%12.12e%s%12.12e%s", data.x[i], "\t",data.y[i], "\t",data.y1[i],"\t",data.y2[i],"\t",MegaSweep.z,"\n");	//if channel 3 is not selected	   
						}
					}
					fclose(out);    
				// end saving
				
				
				if ((MegaSweep.updown==1) && (temp == 1)) {  // acquiring both up and down
			  		SetCtrlVal(MAIN,MAIN_CH1_DIRECTION,-temp);
					start_sweep_ch1(0,0,EVENT_COMMIT,0,0,0); break;
				}
				
				if (MegaSweep.z>=MegaSweep.upperlimit-0.0000001) { MegaSweep.on=0; break;} // MegaSweep done, hack to end on time    
				
				MegaSweep.z=MegaSweep.z+MegaSweep.step;
				/*************** start steppting channel 3 ****************/
				if (sweep_ch3.mega ==1) 
					{	 // if channel 3 is selected in megasweep
						//sweeping up
						if (ch3_direction == 1) {
							MegaSweep.z3high=MegaSweep.z3high+MegaSweep.step3;
							start_sweep_ch3(0,0,EVENT_COMMIT,0,0,0);
							// sweep ch2 
							SetCtrlVal(MAIN,MAIN_CH2_DIRECTION,1);   
			 				start_sweep_ch2(0,0,EVENT_COMMIT,0,0,0);     
							MegaSweep.state=STEPPING_CH2; 
							sweep_ch2.upper_limit=MegaSweep.z;
						}
						else { //sweeping down
							  MegaSweep.z3low=MegaSweep.z3low-MegaSweep.step3;
							  start_sweep_ch3(0,0,EVENT_COMMIT,0,0,0);
							  // sweep ch2
							  SetCtrlVal(MAIN,MAIN_CH2_DIRECTION,1);   
			 				  start_sweep_ch2(0,0,EVENT_COMMIT,0,0,0);     
							  MegaSweep.state=STEPPING_CH2; 
							  sweep_ch2.upper_limit=MegaSweep.z;
						}
					}
				else
				{
					SetCtrlVal(MAIN,MAIN_CH2_DIRECTION,1);   
			 		start_sweep_ch2(0,0,EVENT_COMMIT,0,0,0);     
					MegaSweep.state=STEPPING_CH2; 
					sweep_ch2.upper_limit=MegaSweep.z;
				}
				/*************** done stepping channel 3 ****************/
			}

		 	break;
		 
		case STEPPING_CH2: // we are changing "gate voltage".check if stepping is done, when done start ramping "field" down or acquire.
		 	if ((sweep_ch2.on==!1)&&(sweep_ch3.on==!1)) {
		 		if (MegaSweep.updown==0) { // we are only taking data on sweeps up
		 			SetCtrlVal(MAIN,MAIN_CH1_DIRECTION,-1);   
			 		start_sweep_ch1(0,0,EVENT_COMMIT,0,0,0); 
			    	MegaSweep.state=RAMPING_CH1_DOWN; 
				} 
				else { //taking data on  both sweeps up and down
			  	 	GetCtrlVal(MAIN,MAIN_CH1_DIRECTION,&temp);   
			  	 	SetCtrlVal(MAIN,MAIN_CH1_DIRECTION,-temp);
			  	 	cleargraph (0,0,EVENT_COMMIT,0,0,0); //clear graph   
			  	 	MegaSweep.state=ACQ_DATA;
			  	 	start_sweep_ch1(0,0,EVENT_COMMIT,0,0,0); 
			  	 }
		 	}
		 break;
		 case RAMPING_CH1_DOWN:
	 	// check if ramp is done, when done acquire data again
	  		if (sweep_ch1.on==!1) {
	  			cleargraph (0,0,EVENT_COMMIT,0,0,0); //clear graph   
				SetCtrlVal(MAIN,MAIN_CH1_DIRECTION,1);   
				Delay(MEGASWEEP_SETTLE_TIME);
			 	start_sweep_ch1(0,0,EVENT_COMMIT,0,0,0);         
			    MegaSweep.state=ACQ_DATA;
				 }
		 	break;

		}
	}
}
/* *********************** end UpdateMegaSweep ************************************ */

void Message (char* str)	// prints a text message wih a datestamp in iM interface
{
	InsertTextBoxLine(MAIN,MAIN_MESSAGES,-1,strcat(TimeStr(),str));  
}

void Init(void)
{
timing.length=0.2; // How often we update the interface in seconds
data.points_num=0;
data.acquiring=0;
data.bin_size=0.1;
config.y2_axis_active=0;
config.x_axis_type=ACQ_NONE;
config.y_axis_type=SW_NONE;
config.y1_axis_type=SW_NONE;
config.y2_axis_type=SW_NONE;    
config.x_axis_factor=1;
config.y_axis_factor=1;
config.y1_axis_factor=1;
config.y2_axis_factor=1;
config.x_axis_offset=0;
config.y_axis_offset=0;
config.y1_axis_offset=0;
config.y2_axis_offset=0;
now.x=0; now.y=0;
sweep_ch1.on=0;
sweep_ch1.x=0;
sweep_ch1.stop=STOP_AT_BOTH;
sweep_ch1.rate_up=0.2;
sweep_ch1.rate_down=0.1;
sweep_ch1.direction=1;
sweep_ch2.stop=STOP_AT_BOTH;
sweep_ch2.rate_up=0.01;
sweep_ch2.rate_down=0.1;
sweep_ch2.direction=1;
sweep_ch2.on=0;
sweep_ch2.x=0;
sweep_ch3.on=0;
sweep_ch3.x=0;
sweep_ch3.stop=STOP_AT_BOTH;
sweep_ch3.rate_up=0.1;
sweep_ch3.rate_down=0.1;
sweep_ch3.direction=1;
magnet.ramping=0;
magnet.initialized=0;
XYmagnet.initialized=0;
XYmagnet.sweeping=0;
XYmagnet.ramping=0;
MegaSweep.on=0;
sweep_ch3.mega=0;
}

void E5062_Loop(void) 
{  // to acquire data from E5062 VNA
	int i;
	double num;
	GetCtrlVal(MAIN,MAIN_VNA_points,&data.points_num); 
	GetCtrlVal(MAIN,MAIN_CH1_LOW,&sweep_ch1.lower_limit);
	GetCtrlVal(MAIN,MAIN_CH1_UP,&sweep_ch1.upper_limit);
	
	num = data.points_num; 
	Timing();
	while(data.acquiring) 
	{
		E5062_measure_ch1();  // do the one-shot measurement 
			switch (config.y_axis_type)
			{
				case ACQ_E5062_CH1_Amp:
					{
						for (i=0;i<data.points_num;i++)  
						{  
							GetCtrlVal(MAIN,MAIN_CH1_LOW,&sweep_ch1.lower_limit);
							GetCtrlVal(MAIN,MAIN_CH1_UP,&sweep_ch1.upper_limit);
							data.x[i] = sweep_ch1.lower_limit + i*(sweep_ch1.upper_limit-sweep_ch1.lower_limit)/(num-1); // assign x value
							data.y[i] = E5062_measure_ch1_single_amp(i); // assign the amp value
						}
						//to plot the graph
						PlotXY(MAIN,MAIN_GRAPH,data.x,data.y,data.points_num,VAL_DOUBLE,VAL_DOUBLE,VAL_THIN_LINE, VAL_X,VAL_SOLID, 1,config.y_color);
					break;
					}
					
				case ACQ_E5062_CH1_Phase:
					{
						for (i=0;i<data.points_num;i++)  
						{  
							data.x[i] = sweep_ch1.lower_limit + i*(sweep_ch1.upper_limit-sweep_ch1.lower_limit)/(num-1); // assign x value
							data.y[i] = E5062_measure_ch1_single_phase(i); // assign the phase value
						}
						//to plot the graph
						PlotXY(MAIN,MAIN_GRAPH,data.x,data.y,data.points_num,VAL_DOUBLE,VAL_DOUBLE,VAL_THIN_LINE, VAL_X,VAL_SOLID, 1,config.y_color);
					break;
					}	
			}
			
			if (config.y1_axis_active )  {
			switch (config.y1_axis_type)
			{
				case ACQ_E5062_CH1_Amp:
					{
						for (i=0;i<data.points_num;i++)  
						{  
							data.x[i] = sweep_ch1.lower_limit + i*(sweep_ch1.upper_limit-sweep_ch1.lower_limit)/(num-1); // assign x value
							data.y1[i] = E5062_measure_ch1_single_amp(i); // assign the amp value
						}
						//to plot the graph
						PlotXY(MAIN,MAIN_GRAPH,data.x,data.y1,data.points_num,VAL_DOUBLE,VAL_DOUBLE,VAL_THIN_LINE, VAL_X,VAL_SOLID, 1,config.y1_color);
					break;
					}
				case ACQ_E5062_CH1_Phase:
					{
						for (i=0;i<data.points_num;i++)  
						{  
							data.x[i] = sweep_ch1.lower_limit + i*(sweep_ch1.upper_limit-sweep_ch1.lower_limit)/(num-1); // assign x value
							data.y1[i] = E5062_measure_ch1_single_phase(i); // assign the amp value
						}
						//to plot the graph
						PlotXY(MAIN,MAIN_GRAPH,data.x,data.y1,data.points_num,VAL_DOUBLE,VAL_DOUBLE,VAL_THIN_LINE, VAL_X,VAL_SOLID, 1,config.y1_color);
					break;
					}		
			}
			}
			
			if (config.y2_axis_active )  {
			switch (config.y2_axis_type)
			{
				case ACQ_E5062_CH1_Amp:
					{
						for (i=0;i<data.points_num;i++)  
						{  
							data.x[i] = sweep_ch1.lower_limit + i*(sweep_ch1.upper_limit-sweep_ch1.lower_limit)/(num-1); // assign x value
							data.y2[i] = E5062_measure_ch1_single_amp(i); // assign the amp value
						}
						//to plot the graph
						PlotXY(MAIN,MAIN_GRAPH,data.x,data.y2,data.points_num,VAL_DOUBLE,VAL_DOUBLE,VAL_THIN_LINE, VAL_X,VAL_SOLID, 1,config.y2_color);
					break;
					}
				case ACQ_E5062_CH1_Phase:
					{
						for (i=0;i<data.points_num;i++)  
						{  
							data.x[i] = sweep_ch1.lower_limit + i*(sweep_ch1.upper_limit-sweep_ch1.lower_limit)/(num-1); // assign x value
							data.y2[i] = E5062_measure_ch1_single_phase(i); // assign the amp value
						}
						//to plot the graph
						PlotXY(MAIN,MAIN_GRAPH,data.x,data.y2,data.points_num,VAL_DOUBLE,VAL_DOUBLE,VAL_THIN_LINE, VAL_X,VAL_SOLID, 1,config.y2_color);
					break;
					}		
			}
			}


		break;
	} 

}

void E4402B_Loop(void) 
{  // to acquire data from E4402B spectrum analyzer
	int i;
	double num;
	GetCtrlVal(MAIN,MAIN_VNA_points,&data.points_num); 
	GetCtrlVal(MAIN,MAIN_CH1_LOW,&sweep_ch1.lower_limit);
	GetCtrlVal(MAIN,MAIN_CH1_UP,&sweep_ch1.upper_limit);
	num=data.points_num; 
	Timing();
	while(data.acquiring) 
	{
		E4402B_measure_ch1();  // do the one-shot measurement 
			switch (config.y_axis_type)
			{
				case ACQ_E4402B_Amp:
					{
						for (i=0;i<data.points_num;i++)  
						{  
							data.x[i] = sweep_ch1.lower_limit + i*(sweep_ch1.upper_limit-sweep_ch1.lower_limit)/(num-1); // assign x value
							data.y[i] = E4402B_measure_ch1_single_amp(i); // assign the amp value
						}
						//to plot the graph
						PlotXY(MAIN,MAIN_GRAPH,data.x,data.y,401,VAL_DOUBLE,VAL_DOUBLE,VAL_THIN_LINE, VAL_X,VAL_SOLID, 1,config.y_color);
					break;
					}
					
			}
			
			if (config.y1_axis_active )  
			{
			switch (config.y1_axis_type)
			{
				case ACQ_E4402B_Amp:
					{
						for (i=0;i<data.points_num;i++)  
						{  
							data.x[i] = sweep_ch1.lower_limit + i*(sweep_ch1.upper_limit-sweep_ch1.lower_limit)/(num-1); // assign x value
							data.y1[i] = E4402B_measure_ch1_single_amp(i); // assign the amp value
						}
					break;
					}
			}
			}
			
			if (config.y2_axis_active )  {
			switch (config.y2_axis_type)
			{
				case ACQ_E4402B_Amp:
					{
						for (i=0;i<data.points_num;i++)  
						{  
							data.x[i] = sweep_ch1.lower_limit + i*(sweep_ch1.upper_limit-sweep_ch1.lower_limit)/(num-1); // assign x value
							data.y2[i] = E4402B_measure_ch1_single_amp(i); // assign the amp value
						}
					break;
					}
						
			}
			}


		break;
	} 

}

void MainLoop(void) {  	// This is the main acquisition routine    

	double last_bin,current_bin,now_bin;
	double y_sum,y1_sum,y2_sum,y_number;
	//SuspendTimerCallbacks();
	//SetSleepPolicy (VAL_SLEEP_NONE);
	last_bin=0;
	current_bin=0;
	timing.points_num=0;
	y_sum=0; y1_sum=0; y2_sum=0;y_number=0;
	while(data.acquiring) {
		get_x();
		get_y();
		get_y1();
		get_y2(); 
		Update_ch1_Sweep();
		Update_ch2_Sweep();
		Update_ch3_Sweep(); 
		UpdateMegaSweep();
		if (XYmagnet.sweeping) { Sweep_XYMagnet();}
		Timing();
		now_bin=(floor(now.x/data.bin_size+0.5))*data.bin_size; //middle of the bin
		//assign the point to the right bin
		if (now_bin==current_bin) {
			y_sum=y_sum+now.y;
			y1_sum=y1_sum+now.y1;
			y2_sum=y2_sum+now.y2;
			y_number++;
		}
		if (now_bin==last_bin) {
			if (fabs(now.x-last_bin)<data.bin_size/4) {current_bin=now_bin;last_bin=0.12345678;} //its a hack to prevent last-bin current-bin cycle : deadly
		}
		if ((now_bin!=current_bin)&&(now_bin!=last_bin)){
				if (data.points_num<MAX_POINTS-1) {
					if (y_number>0) {
						data.x[data.points_num]=current_bin;
						data.y[data.points_num]=y_sum/y_number;
						data.y1[data.points_num]=y1_sum/y_number;
						data.y2[data.points_num]=y2_sum/y_number;
						data.points_num++;
						y_sum=now.y; y1_sum=now.y1;y2_sum=now.y2; y_number=1;
						}
				} else  //out of memory
				{
					data.acquiring=0;
				}
				// now new bin
				last_bin=current_bin;
				current_bin=now_bin;
			
		}
	}
}

void E5062_Mega(void)
{

	 FILE* out;
	 int i;
	 //Timing();
	 int ch3_direction;
	GetCtrlVal(EXTRAS,EXTRAS_CH3_DIRECTION,&ch3_direction);
	GetCtrlVal(EXTRAS,EXTRAS_megaButton,&sweep_ch3.mega);
	 if (MegaSweep.on)
	 {
		// Timing();
		 switch (MegaSweep.state)
		 {
			case STARTING:
			 	Message (" starting E5062 megasweep");
		 		SetCtrlVal(MAIN,MAIN_CH2_DIRECTION,-1);  
         		start_sweep_ch1(0,0,EVENT_COMMIT,0,0,0);   // set VNA condition
				start_sweep_ch2(0,0,EVENT_COMMIT,0,0,0);
				Update_ch2_Sweep();  
				MegaSweep.state = WAITING_TO_RAMP_DOWN;
				cleargraph (0,0,EVENT_COMMIT,0,0,0); // clear graph 
         		break;
				
			case WAITING_TO_RAMP_DOWN:
				//Timing();
				Update_ch2_Sweep(); 
				if ((!sweep_ch1.on)&&(!sweep_ch2.on)) 
				{ // start acq
                	data.acquiring=1; // start acq
               		MegaSweep.state = ACQ_DATA;
					sweep_ch1.on = 1;
               		Message(" Acquiring curve first curve");
				}
				break;
				
			case ACQ_DATA:
				if (sweep_ch1.on == 0) 
				{ // after the VNA condition is set
					E5062_Loop(); // do the one-shot measurement and dump curve into data array	
               		Message(" Curve acquired");
                  
				// saving
					out=fopen(MegaSweep.filename,"a");   
					if (!config.y1_axis_active )  {	// if only one channel is acqd.
						GetCtrlVal(EXTRAS,EXTRAS_megaButton,&sweep_ch3.mega);
						if ((sweep_ch3.mega ==1)&&(ch3_direction == 1)) // if channel 3 is selected and sweeping up
							{
							for(i=1;i<data.points_num;i++) fprintf( out , "%f%s%f%s%f%s%f%s", data.x[i], "\t",data.y[i], "\t",MegaSweep.z,"\t",MegaSweep.z3high,"\n");
							}
						else if ((sweep_ch3.mega ==1)&&(ch3_direction == -1)) // if channel 3 is selected and sweeping up
							{
							for(i=1;i<data.points_num;i++) fprintf( out , "%f%s%f%s%f%s%f%s", data.x[i], "\t",data.y[i], "\t",MegaSweep.z,"\t",MegaSweep.z3low,"\n");
							}
						else 
						{
							for(i=1;i<data.points_num;i++) fprintf( out , "%f%s%f%s%f%s", data.x[i], "\t",data.y[i], "\t",MegaSweep.z,"\n");	//if channel 3 is not selected	   
						}
					}
					 
					else {	// if two are acqd.
						GetCtrlVal(EXTRAS,EXTRAS_megaButton,&sweep_ch3.mega);
						if ((sweep_ch3.mega ==1)&&(ch3_direction == 1)) // if channel 3 is selected and sweeping up
							{
							for(i=1;i<data.points_num;i++) fprintf( out , "%f%s%f%s%f%s%f%s%f%s", data.x[i], "\t",data.y[i], "\t",data.y1[i],"\t",MegaSweep.z,"\t",MegaSweep.z3high,"\n");
							}
						else if ((sweep_ch3.mega ==1)&&(ch3_direction == -1)) // if channel 3 is selected and sweeping up
							{
							for(i=1;i<data.points_num;i++) fprintf( out , "%f%s%f%s%f%s%f%s%f%s", data.x[i], "\t",data.y[i], "\t",data.y1[i],"\t",MegaSweep.z,"\t",MegaSweep.z3low,"\n");
							}
						else 
						{
							for(i=1;i<data.points_num;i++) fprintf( out , "%f%s%f%s%f%s%f%s", data.x[i], "\t",data.y[i], "\t",data.y1[i],"\t",MegaSweep.z,"\n");	//if channel 3 is not selected	   
						}
					}
					fclose(out);    
				// end saving
				if (MegaSweep.z>=MegaSweep.upperlimit-0.0000001) { MegaSweep.on=0; break;} // MegaSweep done, hack to end on time  
				MegaSweep.z=MegaSweep.z+MegaSweep.step;
				/*************** start steppting channel 3 ****************/
				if (sweep_ch3.mega ==1) 
					{	 // if channel 3 is selected in megasweep
						//sweeping up
						if (ch3_direction == 1) {
							MegaSweep.z3high=MegaSweep.z3high+MegaSweep.step3;
							start_sweep_ch3(0,0,EVENT_COMMIT,0,0,0);
							// sweep ch2 
							SetCtrlVal(MAIN,MAIN_CH2_DIRECTION,1);   
			 				start_sweep_ch2(0,0,EVENT_COMMIT,0,0,0);     
							MegaSweep.state=STEPPING_CH2; 
							sweep_ch2.upper_limit=MegaSweep.z;
						}
						else { //sweeping down
							  MegaSweep.z3low=MegaSweep.z3low-MegaSweep.step3;
							  start_sweep_ch3(0,0,EVENT_COMMIT,0,0,0);
							  // sweep ch2
							  SetCtrlVal(MAIN,MAIN_CH2_DIRECTION,1);   
			 				  start_sweep_ch2(0,0,EVENT_COMMIT,0,0,0);     
							  MegaSweep.state=STEPPING_CH2; 
							  sweep_ch2.upper_limit=MegaSweep.z;
						}
					}
				else
				{
					SetCtrlVal(MAIN,MAIN_CH2_DIRECTION,1);   
			 		start_sweep_ch2(0,0,EVENT_COMMIT,0,0,0);     
					MegaSweep.state=STEPPING_CH2; 
					sweep_ch2.upper_limit=MegaSweep.z;
				}
				/*************** done stepping channel 3 ****************/
			}
		 	break;
				
			case STEPPING_CH2:
				Update_ch2_Sweep();
				if (!sweep_ch3.type==SW_NONE) {Update_ch3_Sweep();}
				if (sweep_ch2.on==0)
				{  // if stepping is done
					MegaSweep.state = ACQ_DATA;  // get ready to acquire next data set
					start_sweep_ch1(0,0,EVENT_COMMIT,0,0,0);  //   set VNA condition again
					cleargraph (0,0,EVENT_COMMIT,0,0,0); // clear graph 
				}
				break;
		 }
	 }
}
				

void E4402B_Mega(void)
{

	 FILE* out;
	 int i;
	 int CurrentStep = 0;
	 //Timing();
	int ch3_direction;
	GetCtrlVal(EXTRAS,EXTRAS_CH3_DIRECTION,&ch3_direction);
	GetCtrlVal(EXTRAS,EXTRAS_megaButton,&sweep_ch3.mega);
	 if (MegaSweep.on)
	 {
		// Timing();
		 switch (MegaSweep.state)
		 {
			case STARTING:
			 	Message (" starting E4402B megasweep");
		 		SetCtrlVal(MAIN,MAIN_CH2_DIRECTION,-1);  
         		start_sweep_ch1(0,0,EVENT_COMMIT,0,0,0);   // set E4402B condition
				start_sweep_ch2(0,0,EVENT_COMMIT,0,0,0);
				cleargraph (0,0,EVENT_COMMIT,0,0,0); // clear graph 
				Update_ch2_Sweep();  
				MegaSweep.state = WAITING_TO_RAMP_DOWN;
         		break;
				
			case WAITING_TO_RAMP_DOWN:
				//Timing();
				Update_ch2_Sweep(); 
				if ((!sweep_ch1.on)&&(!sweep_ch2.on)) 
				{ // start acq
                	data.acquiring=1; // start acq
               		MegaSweep.state = ACQ_DATA;
               		Message(" Acquiring curve first curve");
				}
				break;
				
            case ACQ_DATA:
				if (sweep_ch1.on == 0) 
				{ // after the VNA condition is set
					E4402B_Loop(); // do the one-shot measurement and dump curve into data array	
               		Message(" Curve acquired");
                  
				// saving
					out=fopen(MegaSweep.filename,"a");   
					if (!config.y1_axis_active )  {	// if only one channel is acqd.
						GetCtrlVal(EXTRAS,EXTRAS_megaButton,&sweep_ch3.mega);
						if ((sweep_ch3.mega ==1)&&(ch3_direction == 1)) // if channel 3 is selected and sweeping up
							{
							for(i=1;i<data.points_num;i++) fprintf( out , "%f%s%f%s%f%s%f%s", data.x[i], "\t",data.y[i], "\t",MegaSweep.z,"\t",MegaSweep.z3high,"\n");
							}
						else if ((sweep_ch3.mega ==1)&&(ch3_direction == -1)) // if channel 3 is selected and sweeping up
							{
							for(i=1;i<data.points_num;i++) fprintf( out , "%f%s%f%s%f%s%f%s", data.x[i], "\t",data.y[i], "\t",MegaSweep.z,"\t",MegaSweep.z3low,"\n");
							}
						else 
						{
							for(i=1;i<data.points_num;i++) fprintf( out , "%f%s%f%s%f%s", data.x[i], "\t",data.y[i], "\t",MegaSweep.z,"\n");	//if channel 3 is not selected	   
						}
					}
					 
					else {	// if two are acqd.
						GetCtrlVal(EXTRAS,EXTRAS_megaButton,&sweep_ch3.mega);
						if ((sweep_ch3.mega ==1)&&(ch3_direction == 1)) // if channel 3 is selected and sweeping up
							{
							for(i=1;i<data.points_num;i++) fprintf( out , "%f%s%f%s%f%s%f%s%f%s", data.x[i], "\t",data.y[i], "\t",data.y1[i],"\t",MegaSweep.z,"\t",MegaSweep.z3high,"\n");
							}
						else if ((sweep_ch3.mega ==1)&&(ch3_direction == -1)) // if channel 3 is selected and sweeping up
							{
							for(i=1;i<data.points_num;i++) fprintf( out , "%f%s%f%s%f%s%f%s%f%s", data.x[i], "\t",data.y[i], "\t",data.y1[i],"\t",MegaSweep.z,"\t",MegaSweep.z3low,"\n");
							}
						else 
						{
							for(i=1;i<data.points_num;i++) fprintf( out , "%f%s%f%s%f%s%f%s", data.x[i], "\t",data.y[i], "\t",data.y1[i],"\t",MegaSweep.z,"\n");	//if channel 3 is not selected	   
						}
					}
					fclose(out);    
				// end saving
				if (MegaSweep.z>=MegaSweep.upperlimit-0.0000001) { MegaSweep.on=0; break;} // MegaSweep done, hack to end on time  
				//if (CurrentStep > MegaSweep.nstep)  { MegaSweep.on=0; break;} 
				MegaSweep.z=MegaSweep.z+MegaSweep.step;
				/*************** start steppting channel 3 ****************/
				if (sweep_ch3.mega ==1) 
					{	 // if channel 3 is selected in megasweep
						//sweeping up
						if (ch3_direction == 1) {
							MegaSweep.z3high=MegaSweep.z3high+MegaSweep.step3;
							start_sweep_ch3(0,0,EVENT_COMMIT,0,0,0);
							// sweep ch2 
							SetCtrlVal(MAIN,MAIN_CH2_DIRECTION,1);   
			 				start_sweep_ch2(0,0,EVENT_COMMIT,0,0,0);     
							MegaSweep.state=STEPPING_CH2; 
							sweep_ch2.upper_limit=MegaSweep.z;
						}
						else { //sweeping down
							  MegaSweep.z3low=MegaSweep.z3low-MegaSweep.step3;
							  start_sweep_ch3(0,0,EVENT_COMMIT,0,0,0);
							  // sweep ch2
							  SetCtrlVal(MAIN,MAIN_CH2_DIRECTION,1);   
			 				  start_sweep_ch2(0,0,EVENT_COMMIT,0,0,0);     
							  MegaSweep.state=STEPPING_CH2; 
							  sweep_ch2.upper_limit=MegaSweep.z;
						}
					}
				else
				{
					SetCtrlVal(MAIN,MAIN_CH2_DIRECTION,1);   
			 		start_sweep_ch2(0,0,EVENT_COMMIT,0,0,0);     
					MegaSweep.state=STEPPING_CH2; 
					sweep_ch2.upper_limit=MegaSweep.z;
				}
				/*************** done stepping channel 3 ****************/
				CurrentStep ++;
				
				}
			
			
		 	break;
				
				
			case STEPPING_CH2:
				Update_ch2_Sweep();
				if (sweep_ch2.on==0)
				{  // if stepping is done
					MegaSweep.state = ACQ_DATA;  // get ready to acquire next data set
					cleargraph (0,0,EVENT_COMMIT,0,0,0); // clear graph
					start_sweep_ch1(0,0,EVENT_COMMIT,0,0,0);  //   set VNA condition again
				}
				break;
		 }
	 }
}
				



