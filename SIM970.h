/* This code controls SIM970 4 channel voltmeter */

#include <gpib.h>
#include <ansi_c.h>

#define SIM970_ADDR 2
#define SIM970_Measure	"VOLT?"


struct {
	int handle;
	
} SIM970;

void SIM970_CH1_initialize(void);
void SIM970_CH2_initialize(void);   
void SIM970_CH3_initialize(void);   
void SIM970_CH4_initialize(void);   
double SIM970_CH1_Measure(void);
double SIM970_CH2_Measure(void);  
long double SIM970_CH3_Measure(void);  
long double SIM970_CH4_Measure(void);  

