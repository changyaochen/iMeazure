/* Controls Anritsu_68369 */																	
#include <gpib.h>
#include <ansi_c.h>

#define Anritsu_68369_SET			" F1"	/* set frequency F1*/
#define Anritsu_68369_OUTPUT			"opon"   /* output on*/
#define Anritsu_68369_ADDR 4


struct {
	int handle;
} Anritsu_68369;

void Anritsu_68369_initialize(void); 
void Anritsu_68369_set(double frequency);  // set output frequency to ...
