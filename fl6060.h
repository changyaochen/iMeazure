/*= Fluke 6060A Include File ==============================================*/
/*= Created from .fp file =================================================*/
#ifndef __Fl6060_HEADER
#define __Fl6060_HEADER

/*== GLOBAL CONSTANT DECLARATIONS =========================================*/
#define PUBLIC __stdcall

#if defined (__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

#define fl6060_MAX_INSTR    10

#define FL6060_ADDR 9 // GPIB addresss
#define FL6060_ADDR_2 5// GPIB addresss
#define FL6060_DELTA 0.00033 // delta freq in MHz


struct {
	int handle;
	int handle_2;
} fl6060;

void PUBLIC fl6060_initialize(void); 
void PUBLIC fl6060_set_freq(double freq);  // set output voltage to ...
void PUBLIC generic_set_freq(double freq); // set frequency to , in unit of Hz

int PUBLIC fl6060_init (int GPIBAddress, int IDQuery, int resetDevice, int *instrumentID);
int PUBLIC fl6060_frequency (int instrumentID, double frequency, int frequencyUnits);
int PUBLIC fl6060_amplitude (int instrumentID, double amplitude, int amplitudeUnits);
int PUBLIC fl6060_step_size_config (int instrumentID, double frequencyStep,
                             int frequencyUnits, double amlitudeStep,
                             int amplitudeUnits, double deviationStep,
                             int deviationUnits, int stepAMDepth);   
                             
int PUBLIC fl6060_interface_mode (int instrumentID, int clearErrorMode, int recordMode,
                                  int term_mode, int valid_mode, int unbuf_mode);
int PUBLIC fl6060_am_mod (int instrumentID, int externalAM, int internalAM, int AMDepth,
                   int internalModFreq);
int PUBLIC fl6060_fr_mod (int instrumentID, int externalFM, int internalFM,
                   double FMDeviationkHz, int internalModFreq);
int PUBLIC fl6060_read_attenuation (int instrumentID, int *attenuation);
int PUBLIC fl6060_write_attenuation (int instrumentID, int attenuationdB);
int PUBLIC fl6060_level_correction (int instrumentID, int levelCorrection);
int PUBLIC fl6060_rf_out (int instrumentID, int RFOutput);
int PUBLIC fl6060_step_ex (int instrumentID, int stepParameter, int direction);
int PUBLIC fl6060_store_panel (int instrumentID, int memoryLocation);
int PUBLIC fl6060_recall_panel (int instrumentID, int settingSelect, int memoryLocation);
int PUBLIC fl6060_save_setup (int instrumentID, int settingSelect, int memoryLocation,
                       char filename[]);
int PUBLIC fl6060_load_setup (int instrumentID, int memoryLocation, char filename[]);
int PUBLIC fl6060_reset (int instrumentID, int resetType);
int PUBLIC fl6060_self_test (int instrumentID, int *AMFMTest, int *synthesizerTest,
                      int *digitalTest, int *outputFilterTest);
int PUBLIC fl6060_revision (int instrumentID, char VPPRevision[], char instrDriverRev[],
                     char firmwareRevision[], char supportedFirmware[]);
int PUBLIC fl6060_report_uncal (int instrumentID, int uncalibratedOutput);
int PUBLIC fl6060_error_query (int instrumentID, int *error, int uncalibratedOutput);
int PUBLIC fl6060_error_message (int errorCode, char errorMessage[]);
int PUBLIC fl6060_instr_disp (int instrumentID, int displayAction);
int PUBLIC fl6060_send_message (int instrumentID, char writeBuffer[]);
int PUBLIC fl6060_receive_message (int instrumentID, int numberBytesToRead,
                            char readBuffer[], int *numBytesRead);
int PUBLIC fl6060_close (int instrumentID);

#if defined (__cplusplus) || defined(__cplusplus__)
}
#endif
/*==== END INCLUDE FILE ====================================================*/

#endif

