/* This code controls AMI bipolar power supply */
#include <gpib.h>
#include <ansi_c.h>

#define MAG_PAUSE			"PAUSE\n"
#define MAG_GET_STATE			"STATE?\n"  
#define MAG_COM_ID				"*IDN?\n"
#define MAG_SET_FIELD			"CONF:FIELD:PROG"
#define MAG_SET_RATE			"CONF:RAMP:RATE:FIELD"
#define MAG_GET_FIELD			"FIELD:MAG?\n"	  
#define MAG_RAMP				"RAMP\n"
#define MAG_ZERO				"ZERO\n"
#define MAG_GET_LAST_ERROR			"SYST:ERR?\n"

struct {
	int handle;
	double field;
	double rate;
	double taget_field;
	int ramping;
	int initialized;
}	magnet;
	   

void magnet_initialize(void) ;
double magnet_get_field(void);
void magnet_stop_sweep(void);
void magnet_ramp(double target,double rate);
