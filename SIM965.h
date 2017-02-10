/* Controls SIM965 analog filter */	
/* I will pretend there are 4 SIM964s*/
#include <gpib.h>
#include <ansi_c.h>
#include <time.h> 

#define SIM965_SET			"FREQ "	/* set volt*/
#define SIM965_ADDR 2
#define slot1 3   // slot number for the SIM965 N1
#define slot2 6   // slot number for the SIM965 N2


struct {
	int handle;
} SIM965;


void SIM965_initializeN1(void); 
void SIM965_initializeN2(void); 
void SIM965_initializeN3(void); 
void SIM965_initializeN4(void); 
void SIM965N1_set(double frequency);  // set corner frequency to ...
void SIM965N2_set(double frequency);
void SIM965N3_set(double frequency);
void SIM965N4_set(double frequency);
int reset_time_1min(void);
																
