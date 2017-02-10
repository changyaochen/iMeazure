/* setting for Agilent 33220A arbitrary function generator */
#include <gpib.h>
#include <ansi_c.h>

#define ag33220a_1_ADDR			10	 // GPIB address


#define FREQ                    "FREQ "
#define AMP						"VOLT "


struct {
	int handle_1;
	int handle_2;
} ag33220a;

void ag33220a_1_initialize(void);

void ag33220a_set_freq(double); // set frequency on ag33220a
void ag33220a_set_amp(double); // set RMS amplitude of ag33220a  
