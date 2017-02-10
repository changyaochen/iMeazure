#define TIME (double)clock()/CLOCKS_PER_SEC
#define MEGASWEEP_SETTLE_TIME 1 // 1s to waiting before starting data acq to settle the signal
#define TIMING_LENGTH 0.1 // The length of bin for calculating POINTS_PER_SEC
#define XYMAGNET_TIMING_LENGTH 0.1 // How often we speak to the magnet in seconds
#define MAX_POINTS 3000000 // Maximum number of datapoints stored
//****************************

enum ACQ_TYPE {ACQ_NONE,ACQ_FAKE,ACQ_TIME,ACQ_ADC0,ACQ_ADC1,ACQ_ADC2,ACQ_ADC3,ACQ_CH1,ACQ_CH2,ACQ_CH3,ACQ_HP34401A_1,ACQ_HP34401A_2,ACQ_KEITHLEY,ACQ_SR830_1,ACQ_SR830_2,ACQ_SR830_3,ACQ_LAKESHORE340,ACQ_XYMAG_THETA,ACQ_XYMAG_X,ACQ_XYMAG_Y,ACQ_XYMAG_R,ACQ_E5062_CH1_Amp,ACQ_E5062_CH1_Phase,ACQ_SIM970_CH1,ACQ_SIM970_CH2,ACQ_SIM970_CH3,ACQ_SIM970_CH4,ACQ_E4402B_Amp};
enum CH_TYPE {SW_NONE,SW_DAC0,SW_DAC1,SW_MAGNET,SW_MAGNET_THETA,SW_YOKO,SW_KE2400N1,SW_KE2400N2,SW_KE2400s,SW_IPS120,SW_CS4,SW_PPMS,SW_FL6060,SW_FAKE,SW_SIM928N1,SW_Anritsu_68369,SW_E5062,SW_SIM928N2,SW_SIM928N3,SW_SIM928N4,SW_E4402B,SW_SR850_Freq,SW_SR850_Amp,SW_SR850_AUX1,SW_SR850_AUX2,SW_SR850_AUX3,SW_SR850_AUX4,SW_33220A_Freq,SW_33220A_Amp,SW_SIM965N1,SW_SIM965N2};
enum DISPLAY_TYPE {NONE,DRAFT,LINES,LINESANDPOINTS};
enum SWEEP_TYPE {DO_NOT_STOP,STOP_AT_MIN,STOP_AT_MAX,STOP_AT_BOTH};
enum MEGASWEEP_STATE {STARTING,WAITING_TO_RAMP_DOWN,ACQ_DATA,RAMPING_CH1_DOWN, STEPPING_CH2};
struct {
	int on;
	int first_time;
	double target_resistance;
	double critical_resistance_increase;
	double safe_voltage;
	double withdraw_voltage;
	double critical_resistance;
	double slow_rate_up;
} autobreak;
 struct {
	double x;
	double y; 
	double y1;
	double y2;
} now;
 struct {
	int x_axis_type;
	double x_axis_offset;
	double x_axis_factor;
	int y_axis_type;
	double y_axis_offset;
	double y_axis_factor;
	int y1_axis_type;
	int y2_axis_type;
	double y1_axis_offset;
	double y1_axis_factor;
	double y2_axis_offset;
	double y2_axis_factor;
	int y1_axis_active;
	int y2_axis_active;  
	int y_color;
	int y1_color;
	int y2_color;
	int sweep_type;
	int display_type;
	int draging_cursor; // 1 when the cursor is being dragged, so that Update does not update x and y
} config;

 struct {
	int on;
	int type;
	int  stop;
	double x;
	int direction;
	double rate_up;
	double rate_down;
	double starting_time; 
	double starting_x;
	double upper_limit;
	double lower_limit;
	int mega; // when included in mega, =1, otherwise 0
} sweep_ch3 ;
 
 struct {
	int on;
	int type;
	int  stop;
	double x;
	int direction;
	double rate_up;
	double rate_down;
	double starting_time; 
	double starting_x;
	double upper_limit;
	double lower_limit;
} sweep_ch2 ;

 struct {
	int on;
	int type;
	int  stop;
	double x;
	int direction;
	double rate_up;
	double rate_down;
	double starting_time; 
	double starting_x;
	double upper_limit;
	double lower_limit;
} sweep_ch1 ;
 struct {
	long double x[MAX_POINTS];
	long double y[MAX_POINTS];
	long double y1[MAX_POINTS];
	long double y2[MAX_POINTS];
	int points_num;  // points acquired so far
	int acquiring; // whether or not acuisition active
	double bin_size;

} data;
 struct {
	double start;
	double length;
	int points_num;
	int points_per_sec;
	double VNA;  // sweep time for E5062 VNA
	int VNA_average;  // average cycles for E5062 VNA
} timing;

 struct {
 	int on;
 	int state;
 	int updown; //if 1 sweep takes data on both up and down sweeps and changes z each time the direction changes
 	double z;
	double z3low;
	double z3high;
 	double step;
	double step3; 
	double upperlimit;
 	char filename[260];
 	char filename_2[260]; 
	int    nstep;
} MegaSweep;
 
 
static char one_shot[900000];	 // string for stripping row data to individual one
char * token;  // pointer string for the stripping purpose 


void E5062_Loop(void);
void get_x(void);
void get_y(void);
void get_y1(void);
void get_y2(void);  
void Timing(void);
void Message (char* str);
void Autobreak_Checks(void);
void Update_ch1_Sweep(void);
void Update_ch2_Sweep(void);
void Update_ch3_Sweep(void);
void UpdateMegaSweep(void);
void Sweep_XYMagnet(void);
void MainLoop(void);
void Init(void);
void E5062_Mega(void);
void E4402B_Loop(void) ;
void E4402B_Mega(void); 

