/* Controls Yokogawa voltage source */																		 /* This code controls AMI bipolar power supply */
#include <gpib.h>
#include <ansi_c.h>

#define YOKO_SET			":SOURce:LEVel"
#define YOKO_OUTPUT			":OUTP"
#define YOKO_TRIGGER		"E"
#define YOKO_ADDR 20


struct {
	int handle;
} YOKO;

void YOKO_initialize(void); 
void YOKO_set(double voltage);  // set output voltage to ...
