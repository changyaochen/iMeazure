/* This code controls OXFORD IPS120-10 bipolar power supply */
#include <gpib.h>
#include <ansi_c.h>

#define IPS120_PAUSE			"A0\n"
#define IPS120_GET_STATE			"X\n"  
#define IPS120_SET_FIELD			"J"
#define IPS120_SET_RATE			"T"
#define IPS120_GET_FIELD			"FIELD:MAG?\n"	  
#define IPS120_RAMP				"A1\n"
#define IPS120_ZERO				"A2\n"

struct {
	int handle;
	double field;
	double rate;
	double taget_field;
	int ramping;
	int initialized;
}	ips120;
	   

void ips120_initialize(void) ;
double ips120_get_field(void);
void ips120_stop_sweep(void);
void ips120_ramp(double target,double rate);
