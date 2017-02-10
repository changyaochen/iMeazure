/* Reading out temperature using LakeShore controller */
#include <gpib.h>
#include <ansi_c.h>

#define LAKESHORE340_ADDR			12 
#define LAKESHORE340_READT			"KRDG? 0\n" // 0 - channel number. either 0 or 1 (A or B channels)

struct {
	int handle;
} lakeshore340;

void lakeshore340_init(void);
double lakeshore340_readtemp(void);

