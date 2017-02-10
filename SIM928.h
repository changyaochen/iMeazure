/* Controls SIM928 voltage source */																		 
#include <gpib.h>
#include <ansi_c.h>
#include <time.h> 

#define SIM928_SET			" volt"	/* set volt*/
#define SIM928_OUTPUT			"opon"   /* output on*/
#define SIM928_ADDR 2


struct {
	int handle;
} SIM928;

void SIM928_initializeN1(void); 
void SIM928_initializeN2(void); 
void SIM928_initializeN3(void); 
void SIM928_initializeN4(void); 
void SIM928N1_set(double voltage);  // set output voltage to ...
void SIM928N2_set(double voltage);
void SIM928N3_set(double voltage);
void SIM928N4_set(double voltage);
int reset_time(void);
