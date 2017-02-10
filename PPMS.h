/* This code controls OXFORD IPS120-10 bipolar power supply */
#include <gpib.h>
#include <ansi_c.h>
#define PPMS_ADDR					15
#define PPMS_SET_FIELD				"FIELD"
#define PPMS_GET_FIELD				"GETDAT? 4"
#define PPMS_GET_TEMP				"GETDAT? 2"
struct {
	int handle;
	double field;
	double rate;
	double target_field;
	int ramping;
	int initialized;
}	ppms;
	   

void ppms_initialize(void) ;
double ppms_get_field(void);
double ppms_get_temp(void);
void ppms_stop_sweep(void);
void ppms_ramp(double target,double rate);
