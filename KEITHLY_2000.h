#include <gpib.h>
#include <ansi_c.h>

#define KEITHLEY_FETCH			"FETC?"


struct {
	int handle;
	int initialized;
} keithley;
	   

void keithley_initialize(void) ;
double keithley_get_data(void);
