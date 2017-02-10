/* Controls Anritsu_68369 */																	
#include <gpib.h>
#include <ansi_c.h>

#define E5062_SET			"FREQ"	// setting frequency
#define E5062_out			"opon"   /* output on*/
#define E5062_ADDR 17
#define E5062_READ1    "CALC1:DATA:FDAT?\n"		  // reading data from channel 1
#define E5062_READ2    "CALC2:DATA:FDAT?\n" 	  // reading data from channel 2


struct {
	int handle;
} E5062;

void E5062_initialize(void); 
void E5062_autoscale(void); // autosacle the graph
void E5062_average(int average);  // set cycles and restart the average
void E5062_set_low(double frequency);  // set lower frequency to ...
void E5062_set_high(double frequency);  // set higher frequency to ...
void E5062_measure_ch1(void);  // one shot measurement
double E5062_measure_ch1_single_amp(int point);  // "pick" each amp point from the one-shot-measured data
double E5062_measure_ch1_single_phase(int point);  // "pick" each phase point from the one-shot-measured data
void E5062_points(int points);  //set measurement points
void E5062_time(double time);  //set measurement time
//double E5062_measure_ch2(void);  // fetch data from VNA E5062 channel 2 and write into "strut data"    
