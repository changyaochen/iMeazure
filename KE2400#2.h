/* Controls Keithly2400 sourcemeter */																		 /* This code controls AMI bipolar power supply */
#include <gpib.h>
#include <ansi_c.h>

#define KE2400N2_SET			":SOUR:VOLT:LEV:IMM:AMPL"
#define KE2400N2_OUTPUT		":OUTP:STAT"
#define KE2400N2_ADDR 23
#define KE2400N2_RANGE ":SOUR:VOLT:RANG MAX" // -200V to +200V


struct {
	int handle;
} KE2400N2;

void KE2400N2_initialize(void); 
void KE2400N2_set(double voltage);  // set output voltage to ...
