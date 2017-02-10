/* This code controls CRYOMAGNETICS CS4 bipolar supply */
#include <gpib.h>
#include <ansi_c.h>
								
#define CS4_PAUSE				"SWEEP PAUSE\n"
#define CS4_GET_STATE			"SWEEP?\n"  
#define CS4_SET_ULIMIT		"ULIM"
#define CS4_SET_LLIMIT		"LLIM"
#define CS4_SET_RATE			"RATE" // usage RATE 0 0.250 (range 0(0-3) current 0.250A
#define CS4_GET_FIELD			"IOUT?\n"	  
#define CS4_SWEEP_UP				"SWEEP UP\n"
#define CS4_SWEEP_DOWN			"SWEEP DOWN\n"
#define CS4_ZERO				"SWEEP ZERO\n"

#define CS4_ADDRESS				1	// GPIB address
#define CS4_TOLERANCE 0.0001 //Field tolerance so that we know when to stop the sweep

struct {
	int handle;
	double field;
	double rate;
	double target_field;
	int ramping;
	int initialized;
}	cs4;
	   

void cs4_initialize(void) ;
double cs4_get_field(void);
void cs4_stop_sweep(void);
void cs4_ramp(double llimit,double ulimit, double rate, int direction);
