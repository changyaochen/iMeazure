#include "KE2400#1.h"
#include "KE2400#2.h"
#include "TWO_KE2400s.h"

void KE2400s_initialize(void)  
{
	double NSTEPS=100.0;
	double x;
	KE2400N1_initialize();
	KE2400N2_initialize();
	for(x=0;x<1;x=x+1/NSTEPS) {
			KE2400N1_set(KE2400N1_OFFSET*x);
			KE2400N2_set(KE2400N2_OFFSET*x);
		}
}

void KE2400s_set(double voltage)
{
	KE2400N1_set(voltage*KE2400N1_FACTOR+KE2400N1_OFFSET);
	KE2400N2_set(voltage*KE2400N2_FACTOR+KE2400N2_OFFSET);

}
