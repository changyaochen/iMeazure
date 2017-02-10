/* Readin out SR 830 lock-ins */
#include <gpib.h>
#include <ansi_c.h>

#define SR830_1_ADDR			7 // First lock-in GPIB address
#define SR830_2_ADDR			8 // Second lock-in GPIB address, dubbed as SR850  

#define SR830_OUTPUTX			"OUTR ?1\n"
#define SR830_OUTPUTY			"OUTR ?2\n" 
#define FREQ                    "FREQ "
#define AMP                     "SLVL "
#define AUXV1					"AUXV 1, "
#define AUXV2					"AUXV 2, " 
#define AUXV3					"AUXV 3, " 
#define AUXV4					"AUXV 4, " 

struct {
	int handle_1;
	int handle_2;
} sr830;

void sr830_initialize_1(void);
void sr830_initialize_2(void);
void sr850_initialize(void); 
double sr830_readch1_1(void) ; // take one reading, lockin #1
double sr830_readch1_2(void) ; // take one reading, lockin #2, channel 2
double sr830_readch2_2(void) ; // take one reading, lockin #2, channel 2
void sr850_set_freq(double); // set frequency on sr850
void sr850_set_amp(double); // set the output amplitude of sr850
void sr850_set_aux1_volt(double); // set voltage for AUX1 output, the machine range is from -10V to 10V
void sr850_set_aux2_volt(double);
void sr850_set_aux3_volt(double);
void sr850_set_aux4_volt(double);
