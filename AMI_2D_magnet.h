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
#define MAG_GET_LAST_ERROR		"SYST:ERR?\n"
#define X_MAGNET_ADDR 23
#define Y_MAGNET_ADDR 24
struct {
	int handle_X;
	int handle_Y;
	double maxrate;
	double taget_field;
	int initialized;
	int ramping;
	int sweeping;
	double x, y, r, theta, theta_start, theta_step, r_step, r_start;
	int Nstep,step; // total number of steps in angle, current step number
	double timing_start, timing_length;
	// all that follows is for testing purposes
	int test_xramping;
	int test_yramping;
	double test_timetorampx;
	double test_timetorampy;
	double test_rampstart_x;
	double test_rampstart_y;
	double test_rate_x;
	double test_rate_y;
	double test_rampstarttime_x;
	double test_rampstarttime_y;
	
}	XYmagnet;
	   

void XYmagnet_initialize(void) ;
double XYmagnet_update(void);
void XYmagnet_stop_sweep(void);
void XYmagnet_ramp(double X_target,double Y_taget, double ramp_rate_x,double ramp_rate_y);
