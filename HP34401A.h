/* This code controls HP34401A voltmeter */

#include <gpib.h>
#include <ansi_c.h>

#define HP34401A_1_ADDRESS 6
#define HP34401A_2_ADDRESS 4
#define HP34401A_Measure	"READ?"


struct {
	int handle;
} hp34401A_1;
	   
struct {
	int handle;
} hp34401A_2;


void hp34401A_1_initialize(void);
void hp34401A_2_initialize(void);
long double hp34401A_1_Measure(void);
double hp34401A_2_Measure(void);
