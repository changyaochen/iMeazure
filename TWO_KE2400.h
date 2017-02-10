/* Controls two Keithly2400 sourcemeter */																		 /* This code controls AMI bipolar power supply */
#include <gpib.h>
#include <ansi_c.h>

#define KE2400N1_OFFSET  0
#define KE2400N2_OFFSET  0
#define KE2400N1_FACTOR  1
#define KE2400N2_FACTOR  1

void KE2400s_initialize(void); 
void KE2400s_set(double voltage);  // set output voltage to ...KE2400s_init

