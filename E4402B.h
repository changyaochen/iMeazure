										
#include <gpib.h>
#include <ansi_c.h>

#define E4402B_SET			"FREQ"	// setting frequency
#define E4402B_out			"opon"   /* output on*/
#define E4402B_ADDR 18
#define E4402B_READ1    ":TRAC? TRACE1\n"		  // reading data from channel 1
//#define E4402B_READ2    "CALC2:DATA:FDAT?\n" 	  // reading data from channel 2


struct {
	int handle;
} E4402B;

void E4402B_initialize(void); 
void E4402B_average(int average);  // set cycles and restart the average
void E4402B_set_low(double frequency);  // set lower frequency to ...
void E4402B_set_high(double frequency);  // set higher frequency to ...
void E4402B_measure_ch1(void);  // one shot measurement
double E4402B_measure_ch1_single_amp(int point);  // "pick" each amp point from the one-shot-measured data
//double E4402B_measure_ch1_single_phase(int point);  // "pick" each phase point from the one-shot-measured data
void E4402B_points(int points);  //set measurement points, for E4402B, it must be set to 401 points
void E4402B_time(double time);  //set measurement time
 
