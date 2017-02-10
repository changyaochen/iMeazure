/* Controls DAQ board PCI 6221 */																		 /* This code controls AMI bipolar power supply */
#include <gpib.h>
#include <ansi_c.h>
#include <NIDAQmx.h> 



struct {
	int handle;
} DAC;

double ADC0_read(void); 
double ADC1_read(void); 
double ADC2_read(void); 
double ADC3_read(void);
void DAC0_set(double voltage);
void DAC1_set(double voltage);
