/* Controls Keithly2400 sourcemeter */																		 /* This code controls AMI bipolar power supply */
#include <gpib.h>
#include <ansi_c.h>

#define KE2400N1_SET			":SOUR:VOLT:LEV:IMM:AMPL"
#define KE2400N1_OUTPUT		":OUTP:STAT"
#define KE2400N1_ADDR 24
#define KE2400N1_RANGE ":SOUR:VOLT:RANG 20" // -20V to +20V


struct {
	int handle;
} KE2400N1;

void KE2400N1_initialize(void); 
void KE2400N1_set(double voltage);  // set output voltage to ...
