/***************************************************************************/
/*  Copyright 1993 National Instruments Corporation. All Rights Reserved   */
/***************************************************************************/
#include <ansi_c.h>
#include <utility.h>
#include <gpib.h>
#include <formatio.h>
#include <stdio.h>
#include "fl6060.h"
			
/*= Fluke 6060 RF Signal Generator ========================================*/
/* LabWindows 2.0 Instrument Driver                                        */
/* Original Release: March 1992                                            */
/* By: DS, National Instruments, Germany                                   */
/* Originally written in C                                                 */
/* Modification History:      Based on the original FL6060 driver.         */
/*                            Modified to allow the multiinstance use of   */
/*                            the driver. Modified to follow the VPP 1.0   */
/*                            specifications.                              */
/*                                                                         */
/* Modification Date: August 1994                                          */
/*                            Modified for multi-instance use. Added       */
/*                            functions for error checking and handling    */
/*                            and the other utility operations. Re-        */
/*                            arranged function tree, rewrote function     */
/*                            and control help panels, and modified error  */
/*                            reporting and checking. Generated new Doc    */
/*                            file.                                        */
/*                                                                         */
/* Modified by: PK                                                         */
/*              Technical University Ostrava, Czech Republic               */
/*                                                                         */
/* Modifications were done in C                                            */
/*                                                                         */
/*=========================================================================*/
/*          10/22/94:   Modifications are done to create DLL.              */
/*                      In function panel the additional controls, namely  */
/*                      the term_m, valid_m and unbuf_m have been added    */
/*                      to the function 'int fl6060_interface_mode()' to   */
/*                      match with the .c file.                            */     
/*       Modified by:   SA,  LWILDP                                        */
/*                                                                         */    
/*                                                                         */
/*         June 1996:   Modified for MDLL compatibility.                   */
/*                      Modified by:  TKN, National Instruments            */
/*                      Phone (800) 433-3488  Fax (512) 794-5678           */    
/*                                                                         */
/*=========================================================================*/

/*= INSTRUMENT TABLE ======================================================*/
/* address array: contains the GPIB addresses of opened instruments.       */
/* bd array: contains the device descriptors returned by OpenDev.          */
/* instr_cnt: contains the number of instruments open of this model type.  */
/* uncal_switch: contains the switches controling reporting of             */
/*               uncalibrated error code                                   */
/*=========================================================================*/
static int address[fl6060_MAX_INSTR + 1];
static int bd[fl6060_MAX_INSTR + 1];
static int uncal_switch[fl6060_MAX_INSTR + 1];
static int instr_cnt;

/*= DEFINITION & STATIC DATA ==============================================*/
/* VXIPP_REVISION: Define number of VPP revision                           */
/* DRIVER_REVISION: Define number of driver revision                       */
/* MINFW_REVISION: Define firmvare version, which driver supports          */
/* CMD_LENGTH: Length of the command buffer                                */
/* fl6060_MAX_ERR_MESSAGES: Define maximum number of error messages        */
/* fl6060_err_msg_cnt:  Count of error messages                            */
/* fl6060_err_idx_tbl[fl6060_MAX_ERR_MESSAGES]: Table of error codes       */
/* fl6060_err_msg_tbl[fl6060_MAX_ERR_MESSAGES]: Table of error messages    */
/* cmd[CMD_LENGTH]: A command buffer for GPIB I/O strings                  */
/* fl6060_err: Error variable                                              */
/* ibcnt: contains the number of bytes transferred by GPIB reads and       */
/*        writes.  See the GPIB library I/O Class for more information     */
/*=========================================================================*/

#define VXIPP_REVISION         "1.0"
#define DRIVER_REVISION        "Rev 2.1, 2/96, CVI 3.1"
#define MINFW_REVISION         "V2.1"
#define CMD_LENGTH                50
#define fl6060_MAX_ERR_MESSAGES  100

static int  fl6060_err_msg_cnt;
static int fl6060_err_idx_tbl[fl6060_MAX_ERR_MESSAGES];
static char *fl6060_err_msg_tbl[fl6060_MAX_ERR_MESSAGES];
static char cmd[CMD_LENGTH];
static int fl6060_err;

/*= INSTRUMENT-DEPENDENT COMMAND ARRAYS ===================================*/
char *freq_units[4];
char *ampl_units[4];
char *step_table[8];
char *reject_table[21];
char *uncal_table[15];
char *reset_comm[3];
char *displ_comm[7];

/*= UTILITY ROUTINES ======================================================*/
int fl6060_open_instr (int, int *);
int fl6060_close_instr (int);
int fl6060_invalid_integer_range (int, int, int, int);
int fl6060_invalid_longint_range (long, long, long, int);
int fl6060_invalid_real_range (double, double, double, int);
int fl6060_device_closed (int);
int fl6060_read_data (int, char *, int);
int fl6060_write_data (int, char *, int);
int fl6060_read_data_file (int, char *);
int fl6060_write_data_file (int, char *);
int fl6060_set_timeout (int, int, int *);
int fl6060_status(int);
void fl6060_setup_arrays (void);
void fl6060_setup_err_messages (void);
int fl6060_err_query (int instrID, int *error, int uncal);

/*=========================================================================*/
/* Function: Initialize                                                    */
/* Purpose:  This function opens the instrument, queries the instrument    */
/*           for its ID, and initializes the instrument to a known state.  */
/*=========================================================================*/
void PUBLIC fl6060_initialize(void)
{
	fl6060.handle= ibdev (0, FL6060_ADDR, NO_SAD, T1s, 1, 0); // eneric initialization
	//fl6060_init(FL6060_ADDR,0,0,&fl6060.handle);   // Skip query, do not reset
	//fl6060_init(FL6060_ADDR_2,0,0,&fl6060.handle_2);   // Skip query, do not reset
}

void PUBLIC fl6060_set_freq(double freq) // In MHz
{
	int f;
	//Addr4882_t a;
	//Addr4882_t b[]={2,5,NOADDR};
	//Fmt (cmd, "%s<FR%f%s", freq, freq_units[2]);
    //fl6060_write_data (fl6060.handle, cmd, NumFmtdBytes());
    //ibwrt(bd[fl6060.handle],cmd,NumFmtdBytes());
    //Delay(0.1);
    //Send(0,2,cmd,NumFmtdBytes(),2);
    //Fmt (cmd, "%s<FR%f%s", freq+0.0003, freq_units[2]); 
 	//Send(0,5,cmd,NumFmtdBytes(),2);   
 	//a={2,5};
 	//SendList(0,b,cmd,NumFmtdBytes(),2);
 	//Delay(0.1);
	f=fl6060_frequency(fl6060.handle,freq,2); // Freq in MHz
	//f=fl6060_frequency(fl6060.handle_2,freq+FL6060_DELTA,2); // Freq in MHz
	//Delay(0.1);
	
	//f=fl6060_amplitude(fl6060.handle,freq,2); // Amplitude in volts

}

void PUBLIC generic_set_freq(double freq) // in kHz
{
	char buf[20];
	sprintf(buf,"%s%f%s", "FREQ", freq, "\n");  //set frequency in Hz 
	ibwrt(fl6060.handle, buf, strlen(buf));
}

int PUBLIC fl6060_init (int addr, int id_query, int rest, int *instrID)
{
    int  ID;

    if (fl6060_invalid_integer_range (addr, 0, 30, -1) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (id_query, 0, 1, -2) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (rest, 0, 1, -3) != 0)
        return fl6060_err;

    if (fl6060_open_instr (addr, &ID) != 0)
        return fl6060_err;

    if (id_query) {
        if (fl6060_write_data (ID, "ID", 2) != 0) {
            fl6060_close_instr (ID);
            return fl6060_err;
        }
        if (fl6060_read_data (ID, cmd, CMD_LENGTH) != 0) {
            fl6060_close_instr (ID);
            return fl6060_err;
        }

        Scan (cmd, "6060");
        if (NumFmtdBytes () != 4) {
            fl6060_err = 223;
            fl6060_close_instr (ID);
            return fl6060_err;
        }
    }

    if (fl6060_write_data (ID, "TM0,VM1,UM0", 11) != 0) {
        fl6060_close_instr (ID);
        return fl6060_err;
    }

    if (rest) {
        if (fl6060_write_data (ID, "CL,RO0", 6) != 0) {
            fl6060_close_instr (ID);
            return fl6060_err;
        }
    }

    fl6060_setup_arrays ();
    fl6060_setup_err_messages ();

    *instrID = ID;

    fl6060_status (ID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Read Attenuation                                              */
/* Purpose:  This function reads the Attenuator Level Control              */
/*=========================================================================*/
int PUBLIC fl6060_read_attenuation (int instrID, int *attenuation)
{
 /*   int    n;  */
    char   buf[10];

    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    Fmt (cmd, "%s<CB,XA");
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;
    if (fl6060_read_data (instrID, buf, 10) != 0)
        return fl6060_err;
    if (Scan (buf, "%s>%i[b4]", attenuation) != 1) {
        fl6060_err = 236;
        return fl6060_err;
    }
    if (fl6060_invalid_integer_range (*attenuation, 0, 23, 236) != 0)
        return fl6060_err;
    *attenuation *= 6;

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Write Attenuation                                             */
/* Purpose:  This function sets the Attenuator Level Control               */
/*=========================================================================*/
int PUBLIC fl6060_write_attenuation (int instrID, int attenuation)
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (attenuation, 0, 138, -2) != 0)
        return fl6060_err;

    Fmt (cmd, "%s<XB%d[b4]", (attenuation+3)/6);
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Self-Test                                                     */
/* Purpose:  This function initiates a self test and transfers the results */
/*           of the self tests to a string containing the self-test code.  */
/*=========================================================================*/
int PUBLIC fl6060_self_test (int instrID, int *AM_FM, int *synthesizer, int *digital,
                      int *filter)
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    Fmt (cmd, "%s<CB,SP02,IT");
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;
    if (fl6060_read_data (instrID, cmd, CMD_LENGTH) != 0)
        return fl6060_err;
    if (Scan (cmd, "%s>%d[b4],%d[b4],%d[b4],%d[b4]", AM_FM, synthesizer, digital, filter) != 4) {
        fl6060_err = 236;
        return fl6060_err;
    }
    if (*AM_FM || *synthesizer || *digital || *filter) {
        fl6060_err = 500;
        return fl6060_err;
    }

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Save Setup to File                                            */
/* Purpose:  This function transfers the front panel setup stored at the   */
/*           memory location specified by location to a file specified by  */
/*           filename.                                                     */
/*=========================================================================*/
int PUBLIC fl6060_save_setup (int instrID, int source_loc, int location,
                       char filename[])
{
    int w, x, y, z;
    w = x = y = z = 0;

    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (source_loc, 0, 3, -2) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (location, 1, 50, -3) == 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    /* Find Length of Filename & Extension and return Error if Invalid */
    w = strlen (filename);
    if (w < 1) {
        fl6060_err = -4;
        return fl6060_err;
    }
    x = FindPattern (filename, 0, (unsigned int)-1, ".", 0, 1);
    if (x == -1)
        x = 0;
    else {
        x = w - x;
        if (x > 4) {
            fl6060_err = -4;
            return fl6060_err;
        }
    }
    y = FindPattern (filename, 0, (unsigned int)-1, "\\", 0, 1);
    if (y == -1)
        y = 0;
    else
        y +=1;

    z = w - x - y;
    if (z > 8) {
        fl6060_err = -4;
        return fl6060_err;
    }

    switch (source_loc) {
        case 0: location = 0;    /* Last setting */
                break;
        case 2: location = 98;   /* Preset state */
                break;
        case 3: location = 99;   /* Present state */
                break;
    }


    Fmt (cmd, "%s<TM1,CB,LM%d[b4]", location);
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;
    if (fl6060_read_data_file (instrID, filename) != 0)
        return fl6060_err;

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Load Setup From File                                          */
/* Purpose:  This function loads the front panel setup stored at a file    */
/*           specified by filename and stores it into an instrument memory */
/*           location specified by location.                               */
/*=========================================================================*/
int PUBLIC fl6060_load_setup (int instrID, int location, char filename[])
{
    int handle,bytes_read, err, w, x, y, z;
    char setup_string[100];
    w = x = y = z = 0;

    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (location, 1, 50, -2) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    /* Find Length of Filename & Extension and return Error if Invalid */
    w = strlen (filename);
    if (w < 1) {
        fl6060_err = -3;
        return fl6060_err;
    }
    x = FindPattern (filename, 0, (unsigned int)-1, ".", 0, 1);
    if (x == -1)
        x = 0;
    else {
        x = w - x;
        if (x > 4) {
            fl6060_err = -3;
            return fl6060_err;
        }
    }
    y = FindPattern (filename, 0, (unsigned int)-1, "\\", 0, 1);
    if (y == -1)
        y = 0;
    else
        y +=1;

    z = w - x - y;
    if (z > 8) {
        fl6060_err = -3;
        return fl6060_err;
    }

    handle = OpenFile (filename, 1, 2, 1);
    if (handle == -1) { /* open file error, handle invalid */
        fl6060_err = -3;
        return fl6060_err;
    }
    bytes_read = ReadFile (handle, setup_string, 99);
    if (bytes_read == -1) { /* read file error */
        fl6060_err = 504;
        return fl6060_err;
    }
    if (bytes_read == 0) {  /* file was empty */
        fl6060_err = 505;
        return fl6060_err;
    }
    if (bytes_read > 65) {  /* file too big or incorrect */
        fl6060_err = 506;
        return fl6060_err;
    }
    err = CloseFile (handle);
    if (err == -1) {  /* close file error */
        fl6060_err = 507;
        return fl6060_err;
    }
    Fmt (cmd, "%s<LI%d[b4]%s", location, setup_string);
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Store Front Panel                                             */
/* Purpose:  This function stores the current front panel setup at the     */
/*           memory location specified by location.                        */
/*=========================================================================*/
int PUBLIC fl6060_store_panel (int instrID, int location)
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (location, 1, 50, -2) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    Fmt (cmd, "%s<ST%d[b4]", location);
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Recall Front Panel                                            */
/* Purpose:  This function recalls the front panel setup stored at the     */
/*           memory location specified by location.                        */
/*=========================================================================*/
int PUBLIC fl6060_recall_panel (int instrID, int source_loc, int location)
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (source_loc, 0, 3, -2) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (location, 1, 50, -3) == 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    switch (source_loc) {
        case 0: location = 0;    /* Last setting */
                break;
        case 2: location = 98;   /* Preset state */
                break;
        case 3: location = 99;   /* Present state */
                break;
    }
    Fmt (cmd, "%s<RC%d[b4]", location);
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Step Size Configuration                                       */
/* Purpose:  Step Entry function for frequency step size setting           */
/*           Step Entry Function for amplitude step size setting           */
/*           Step Entry Function for FM step size setting                  */
/*           Step Entry Function for AM step size setting                  */
/*=========================================================================*/
int PUBLIC fl6060_step_size_config (int instrID, double freq, int f_units,
                             double ampl, int a_units, double d_freq,
                             int df_units, int depth)
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (f_units, 0, 3, -3) != 0)
        return fl6060_err;
    if (fl6060_invalid_real_range (freq * pow(10.0, (3.0 * f_units)), 0.0, 1.05E9, -2) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (a_units, 0, 3, -5) != 0)
        return fl6060_err;
    if (a_units == 3)               /* Amplitude input in dBm */
        if (fl6060_invalid_real_range (ampl, 0.0, 166.0, -4) != 0)
             return fl6060_err;
    else                            /* Amplitude input in V, mV or æV */
        if (fl6060_invalid_real_range (ampl * pow(10.0, (3.0 * a_units)), 0.0, 1999.0, -4) != 0)
            return fl6060_err;
    if (fl6060_invalid_integer_range (df_units, 0, 3, -7) != 0)
        return fl6060_err;
    if (fl6060_invalid_real_range (d_freq * pow(10.0, (3.0 * df_units)), 0.0, 99900.0, -6) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (depth, 0, 99, -8) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    Fmt (cmd, "%s<FS%f%s,LS%f%s,DS%f%s,PS%d[b4]PC", freq, freq_units[f_units],
         ampl, ampl_units[a_units], d_freq, freq_units[df_units], depth);
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Execute Step                                                  */
/* Purpose:  Step Execution of the specified Parameter in the specified    */
/*           direction.                                                    */
/*=========================================================================*/
int PUBLIC fl6060_step_ex (int instrID, int step_parameter, int step_mode)
{
    int  key;

    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (step_parameter, 0, 3, -2) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (step_mode, 0, 1, -3) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    key = (step_parameter << 1) + step_mode;
    Fmt (cmd, "%s<%s", step_table[key]);
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Instrument Display                                            */
/* Purpose:  This function performs the selected action on the Generator   */
/*           display.                                                      */
/*=========================================================================*/
int PUBLIC fl6060_instr_disp (int instrID, int control)
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (control, 0, 6, -2) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    Fmt (cmd, "%s<%s", displ_comm[control]);
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: RF Output                                                     */
/* Purpose:  This function enables or disables the output of the Generator.*/
/*=========================================================================*/
int PUBLIC fl6060_rf_out (int instrID, int control)
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (control, 0, 1, -2) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    Fmt (cmd, "%s<RO%d[b4]", control);
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Interface Mode Configuration                                  */
/* Purpose:  This function sets some of the interface parameters.          */
/*=========================================================================*/
int PUBLIC fl6060_interface_mode (int instrID, int error_m, int record_m, int term_m,
                           int valid_m, int unbuf_m)
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (error_m, 0, 1, -2) != 0)                                
        return fl6060_err;
    if (fl6060_invalid_integer_range (record_m, 0, 1, -3) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (term_m, 0, 1, -4) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (valid_m, 0, 1, -5) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (unbuf_m, 0, 1, -6) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    Fmt (cmd, "%s<EM%d[b4],RM%d[b4],TM%d[b4],VM%d[b4],UM%d[b4]", error_m, record_m, term_m,
        valid_m, unbuf_m);
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Frequency Modulation                                          */
/* Purpose:  This function enables or disables Frequency Modulation and    */
/*           sets the appropriate Parameters.                              */
/*=========================================================================*/
int PUBLIC fl6060_fr_mod (int instrID, int ext_control, int int_control,
                   double deviation, int internfreq)
{
    int n;

    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (ext_control, 0, 1, -2) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (int_control, 0, 1, -3) != 0)
        return fl6060_err;
    if (fl6060_invalid_real_range (deviation, 0.0, 99.9, -4) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (internfreq, 0, 1, -5) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    Fmt (cmd, "%s<FM%fKZ,FE%d[b4],", deviation, ext_control);
    n = NumFmtdBytes();
    if (int_control)
        Fmt (cmd, "%s[a]<MR%d[b4],FI1", internfreq);
    else
        Fmt (cmd, "%s[a]<FI0");
    n += NumFmtdBytes();

    if (fl6060_write_data (instrID, cmd, n) != 0)
        return fl6060_err;

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Amplitude Modulation                                          */
/* Purpose:  This function enables or disables Amplitude Modulation and    */
/*           sets the appropriate Parameters.                              */
/*=========================================================================*/
int PUBLIC fl6060_am_mod (int instrID, int ext_control, int int_control, int depth,
                   int internfreq)
{
    int n;

    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (ext_control, 0, 1, -2) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (int_control, 0, 1, -3) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (depth, 0, 99, -4) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (internfreq, 0, 1, -5) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    Fmt (cmd, "%s<AM%d[b4]PC,AE%d[b4],", depth, ext_control);
    n = NumFmtdBytes();
    if (int_control)
        Fmt (cmd, "%s[a]<MR%d[b4],AI1", internfreq);
    else
        Fmt (cmd, "%s[a]<AI0");
    n += NumFmtdBytes();

    if (fl6060_write_data (instrID, cmd, n) != 0)
        return fl6060_err;

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Frequency                                                     */
/* Purpose:  This function sets the frequency of the generated Sinewave    */
/*=========================================================================*/
int PUBLIC fl6060_frequency (int instrID, double freq, int f_units)
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (f_units, 0, 3, -3) != 0)
        return fl6060_err;
    if (fl6060_invalid_real_range (freq * pow(10.0, (3.0 * f_units)), 1.0E4, 1.05E9, -2) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    Fmt (cmd, "%s<FR%f%s", freq, freq_units[f_units]);
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Amplitude                                                     */
/* Purpose:  This function sets the amplitude of the generated Sinewave    */
/*=========================================================================*/
int PUBLIC fl6060_amplitude (int instrID, double ampl, int a_units)
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (a_units, 0, 3, -3) != 0)
        return fl6060_err;
    if (a_units == 3) {                  /* Amplitude input in dBm */
        if (fl6060_invalid_real_range (ampl, -147.0, 19.0, -2) != 0)
            return fl6060_err;
    }
    else {                               /* Amplitude input in V, mV or æV */
        if (fl6060_invalid_real_range (ampl * pow(10.0, (3.0 * a_units)),
            0.01, 2000000.0, -2) != 0)
            return fl6060_err;
    }
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    Fmt (cmd, "%s<AP%f%s", ampl, ampl_units[a_units]);
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Level Correction                                              */
/* Purpose:  This function sets the level correction                       */
/*=========================================================================*/
int PUBLIC fl6060_level_correction (int instrID, int corr_select)
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (corr_select, 0, 2, -2) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    Fmt (cmd, "%s<SP%d[b4]", 80+corr_select);
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Reset                                                         */
/* Purpose:  This function cleares of selected part of the instrument      */
/*=========================================================================*/
int PUBLIC fl6060_reset (int instrID, int reset_select)
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (reset_select, 0, 2, -2) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    Fmt (cmd, "%s<%s", reset_comm[reset_select]);
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Error Query                                                   */
/* Purpose:  This function queries the instrument error queue.             */
/*=========================================================================*/
int PUBLIC fl6060_error_query (int instrID, int *error, int uncal)
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    fl6060_err_query(instrID, error, uncal);

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Revision                                                      */
/* Purpose:  This function returns the driver and instrument revisions.    */
/*=========================================================================*/
int PUBLIC fl6060_revision (int instrID, char vxipp_rev[], char driver_rev[],
                      char instr_rev[], char minfw_rev[])
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    if (fl6060_write_data (instrID, "IV", 2) != 0)
        return fl6060_err;
    if (fl6060_read_data (instrID, cmd, CMD_LENGTH) != 0)
        return fl6060_err;

    Fmt (instr_rev,  "%s<%s[w*]", ibcnt, cmd);
    Fmt (vxipp_rev,  "%s<%s", VXIPP_REVISION);
    Fmt (driver_rev, "%s<%s", DRIVER_REVISION);
    Fmt (minfw_rev,  "%s<%s", MINFW_REVISION);

    fl6060_status (instrID);
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Error Message                                                 */
/* Purpose:  This function returns a text message for a corresponding      */
/*           instrument driver error code.                                 */
/*=========================================================================*/
int PUBLIC fl6060_error_message (int err, char message[])
{
    int i;

    fl6060_err = 0;

    /* Initialize Error Message arrays if they are still uninitialized. */
    if (fl6060_err_msg_cnt == 0)
        fl6060_setup_err_messages ();

    if (err < 0)  {
        Fmt (message, "%s<Parameter %d[b4] of last function call is out of range.", -err);
        return fl6060_err;
    }

    for (i=0; i<fl6060_err_msg_cnt; i++)  {
        if (fl6060_err_idx_tbl[i] == err)  {
           Fmt (message, "%s<%s.", fl6060_err_msg_tbl[i]);
           return fl6060_err;
        }
    }

    if (i == fl6060_err_msg_cnt)  {
        Fmt (message, "%s<%s %d[b4].", fl6060_err_msg_tbl[fl6060_err_msg_cnt], err);
        fl6060_err = 290; /* Wrong Error Code */
    }
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Report Uncalibrated Output Error                              */
/* Purpose:  This function sets the switch enabling/disabling uncalibrated */
/*           output error report in every instrument function Error Code   */
/*           control.                                                      */
/*=========================================================================*/
int PUBLIC fl6060_report_uncal (int instrID, int report_select)
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_invalid_integer_range (report_select, 0, 1, -2) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    uncal_switch[instrID] = report_select;
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Send Message                                                  */
/* Purpose:  This function writes a command string to the instrument.      */
/*=========================================================================*/
int PUBLIC fl6060_send_message (int instrID, char cmd_string[])
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    Fmt (cmd, "%s<%s", cmd_string);
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;

    return fl6060_err;
}

/*=========================================================================*/
/* Function: Receive Message                                               */
/* Purpose:  This function reads the output buffer of the instrument.      */
/*=========================================================================*/
int PUBLIC fl6060_receive_message (int instrID, int numbytes, char in_buff[],
                            int *bytes_read)
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    *bytes_read = 0;
    if (fl6060_read_data (instrID, in_buff, numbytes) != 0)
        return fl6060_err;

    *bytes_read = ibcnt;

    return fl6060_err;
}

/*=========================================================================*/
/* Function: Close                                                         */
/* Purpose:  This function closes the instrument.                          */
/*=========================================================================*/
int PUBLIC fl6060_close (int instrID)
{
    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_device_closed (instrID))
        return fl6060_err;

    fl6060_close_instr (instrID);

    return fl6060_err;
}

/*= UTILITY ROUTINES ======================================================*/

/*=========================================================================*/
/* Function: Open Instrument                                               */
/* Purpose:  This function locates and initializes an entry in the         */
/*           Instrument Table and the GPIB device table for the            */
/*           instrument.  The size of the Instrument Table can be changed  */
/*           in the include file by altering the constant                  */
/*           fl6060_MAX_INSTR.  The return value of this function is equal */
/*           to the global error variable.                                 */
/*=========================================================================*/
int fl6060_open_instr (int addr, int *ID)
{
    int i, instrID;

    instrID = 0;
    fl6060_err = 0;

/* Check to see if the instrument is already in the Instrument Table. */

    for (i = 1; i <= fl6060_MAX_INSTR; i++)
        if (address[i] == addr) {
            instrID = i;
            i = fl6060_MAX_INSTR;
         }

/* If it is not in the instrument table, open an entry for the instrument. */

    if (instrID <= 0)
        for (i = 1; i <= fl6060_MAX_INSTR; i++)
            if (address[i] == 0) {
                instrID = i;
                i = fl6060_MAX_INSTR;
             }

/* If an entry could not be opened in the Instrument Table, return an error.*/

    if (instrID <= 0) {
        fl6060_err = 220;
        return fl6060_err;
    }

/* If the device has not been opened in the GPIB device table (bd[ID] = 0),*/
/*  then open it.                                                          */

    if (bd[instrID] <= 0) {
        if (instr_cnt <= 0)
            CloseInstrDevs("fl6060");
        bd[instrID] = OpenDev ("", "fl6060");
        if (bd[instrID] <= 0) {
            fl6060_err = 220;
            return fl6060_err;
        }
        instr_cnt += 1;
        address[instrID] = addr;
     }

/*  Change the primary address of the device    */

    if (ibpad (bd[instrID], addr) & 0x8000) {
        fl6060_err = 233;
        return fl6060_err;
    }

    *ID = instrID;
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Close Instrument                                              */
/* Purpose:  This function closes the instrument by removing it from the   */
/*           GPIB device table and setting the address and bd[instrID] to  */
/*           zero in the Instrument Table.  The return value is equal to   */
/*           the global error variable.                                    */
/*=========================================================================*/
int fl6060_close_instr (int instrID)
{
    if (bd[instrID] != 0) {
        CloseDev (bd[instrID]);
        bd[instrID] = 0;
        address[instrID] = 0;
        instr_cnt -= 1;
    }
    else
        fl6060_err = 221;

    return fl6060_err;
}

/*=========================================================================*/
/* Function: Status                                                        */
/* Purpose:  This function checks the instrument dependent errors          */
/*=========================================================================*/
int fl6060_status (int instrID)
{
    char response;
    int error;

    if (fl6060_invalid_integer_range (instrID, 1, fl6060_MAX_INSTR, -1) != 0)
        return fl6060_err;
    if (fl6060_device_closed(instrID) != 0)
        return fl6060_err;

    response = 0;                    /* Wait for OPC or an error */
    while (!(response & 0x07))
        if (ibrsp (bd[instrID], &response) & 0x8000)
            fl6060_err = 226;

    Delay (0.1);           /* Delay needed for correct error bits set */

    if (ibrsp (bd[instrID], &response) & 0x8000)   /* Read status */
        fl6060_err = 226;
    else
        fl6060_err = 0;
    if (response & 0x02) {                 /* Reject entry ? */
        fl6060_err_query(instrID, &error, 0);
        fl6060_err = error;
        return fl6060_err;
    }
    if ((response & 0x04) && uncal_switch[instrID]) {    /* Uncal. entry ? */
        fl6060_err_query(instrID, &error, 1);
        fl6060_err = error;
        return fl6060_err;
    }

    return fl6060_err;
}

/*=========================================================================*/
/* Function: Err Query                                                     */
/* Purpose:  This function queries the instrument error queue.             */
/*=========================================================================*/
int fl6060_err_query (int instrID, int *error, int uncal)
{
    int match1, match2, match3, i, err_code;

    Fmt (cmd, "%s<CB,IR");
    if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
        return fl6060_err;
    if (fl6060_read_data (instrID, cmd, CMD_LENGTH) != 0)
        return fl6060_err;

    /* compare the cmd to the reject_table */
    err_code = 300;
    for (i = 0; i < 21; i++) {
        match1 = CompareBytes (cmd, 3, reject_table[i], 0, 3, 0);
        match2 = CompareBytes (cmd, 10, reject_table[i], 3, 3, 0);
        match3 = CompareBytes (cmd, 17, reject_table[i], 6, 3, 0);
        if ((match1 == 0) && (match2 == 0) && (match3 == 0)) {
            err_code = i;
            i = 21;
        }
    }

    if (err_code) {
        if (err_code > 20)
            *error = 300;
        else
            *error = 300+err_code;
        return fl6060_err;
    }

    if (uncal) {
        Fmt (cmd, "%s<IU");
        if (fl6060_write_data (instrID, cmd, NumFmtdBytes()) != 0)
            return fl6060_err;
        if (fl6060_read_data (instrID, cmd, CMD_LENGTH) != 0)
            return fl6060_err;
        /* compare the cmd to the uncal_table */
        err_code = 400;
        for (i = 0; i < 15; i++) {
            match1 = CompareBytes (cmd, 3, uncal_table[i], 0, 3, 0);
            match2 = CompareBytes (cmd, 10, uncal_table[i], 3, 3, 0);
            match3 = CompareBytes (cmd, 17, uncal_table[i], 6, 3, 0);
            if ((match1 == 0) && (match2 == 0) && (match3 == 0)) {
                err_code = i;
                i = 15;
            }
        }

        if (err_code) {
            if (err_code > 14)
                *error = 400;
            else
                *error = 400+err_code;
        }
        else
            *error = 0;
        return fl6060_err;
    }
    *error = 0;
    return fl6060_err;

}

/*=========================================================================*/
/* Function: Invalid Integer Range                                         */
/* Purpose:  This function checks an integer to see if it lies between a   */
/*           minimum and maximum value.  If the value is out of range, set */
/*           the global error variable to the value err_code.  If the      */
/*           value is OK, error = 0.  The return value is equal to the     */
/*           global error value.                                           */
/*=========================================================================*/
int fl6060_invalid_integer_range (int val, int min, int max, int err_code)
{
    if (val < min || val > max)
        fl6060_err = err_code;
    else
        fl6060_err = 0;

    return fl6060_err;
}

/*=========================================================================*/
/* Function: Invalid Long Integer Range                                    */
/* Purpose:  This function checks a long integer to see if it lies between */
/*           a minimum and maximum value.  If the value is out of range,   */
/*           set the global error variable to the value err_code.  If the  */
/*           value is OK, error = 0.  The return value is equal to the     */
/*           global error value.                                           */
/*=========================================================================*/
int fl6060_invalid_longint_range (long val, long min, long max, int err_code)
{
    if (val < min || val > max)
        fl6060_err = err_code;
    else
        fl6060_err = 0;

    return fl6060_err;
}

/*=========================================================================*/
/* Function: Invalid Real Range                                            */
/* Purpose:  This function checks a real number to see if it lies between  */
/*           a minimum and maximum value.  If the value is out of range,   */
/*           set the global error variable to the value err_code.  If the  */
/*           value is OK, error = 0.  The return value is equal to the     */
/*           global error value.                                           */
/*=========================================================================*/
int fl6060_invalid_real_range (double val, double min, double max,
                               int err_code)
{
    if (val < min || val > max)
        fl6060_err = err_code;
    else
        fl6060_err = 0;

    return fl6060_err;
}

/*=========================================================================*/
/* Function: Device Closed                                                 */
/* Purpose:  This function checks to see if the module has been            */
/*           initialized.  If the device has not been opened, set the      */
/*           global error variable to 232, 0 otherwise. The return value   */
/*           is equal to the global error value.                           */
/*=========================================================================*/
int fl6060_device_closed (int instrID)
{
    if (bd[instrID] <= 0)
        fl6060_err = 232;
    else
        fl6060_err = 0;

    return fl6060_err;
}

/*=========================================================================*/
/* Function: Read Data                                                     */
/* Purpose:  This function reads a buffer of data from the instrument. The */
/*           return value is equal to the global error variable.           */
/*=========================================================================*/
int fl6060_read_data (int instrID, char *buf, int cnt)
{
    if (ibrd(bd[instrID], buf, (long)cnt) & 0x8000)
        fl6060_err = 231;
    else
        fl6060_err = 0;

    return fl6060_err;
}

/*=========================================================================*/
/* Function: Write Data                                                    */
/* Purpose:  This function writes a buffer of data to the instrument. The  */
/*           return value is equal to the global error variable.           */
/*=========================================================================*/
int fl6060_write_data (int instrID, char *buf, int cnt)
{
    if (ibwrt(bd[instrID], buf, (long)cnt) & 0x8000)
        fl6060_err = 230;
    else
        fl6060_err = 0;

    return fl6060_err;
}

/*=========================================================================*/
/* Function: Read Data File                                                */
/* Purpose:  This function reads a buffer of data from the instrument and  */
/*           stores it to the file specified by "filename".  Filename must */
/*           either be a string, such as "C:\\lw\\instr\\file" or a pointer*/
/*           to such a string.  The return value is equal to the global    */
/*           error variable.                                               */
/*=========================================================================*/
int fl6060_read_data_file (int instrID, char *filename)
{
    if (ibrdf (bd[instrID], filename) & 0x8000)
        fl6060_err = 229;
    else
        fl6060_err = 0;

    return fl6060_err;
}

/*=========================================================================*/
/* Function: Write Data File                                               */
/* Purpose:  This function writes a buffer of data from the file specified */
/*           by "filename" to the instrument. Filename must either be a    */
/*           string, such as "C:\\lw\\instr\\file" or a pointer to such a  */
/*           string.  The return value is equal to the global error        */
/*           variable.                                                     */
/*=========================================================================*/
int fl6060_write_data_file (int instrID, char *filename)
{
    if (ibwrtf (bd[instrID], filename) & 0x8000)
        fl6060_err = 228;
    else
        fl6060_err = 0;

    return fl6060_err;
}

/*=========================================================================*/
/* Function: Set Timeout                                                   */
/* Purpose:  This function changes or disables the timeout of the device.  */
/*           Refer to the LabWindows Standard Libraries Reference Manual   */
/*           for timeout codes. The return value is equal to the global    */
/*           error variable.                                               */
/*=========================================================================*/
int fl6060_set_timeout (int instrID, int tmo_code, int *old_timeout)
{
    if (ibtmo (bd[instrID], tmo_code) & 0x8000)
        fl6060_err = 239;
    else {
        *old_timeout = iberr;
        fl6060_err = 0;
    }
    return fl6060_err;
}

/*=========================================================================*/
/* Function: Setup Error Messages                                          */
/* Purpose:  This function performs the error messages setup.              */
/*=========================================================================*/
void fl6060_setup_err_messages (void)
{
 /*  int i;    */

/* The following code initializes Error Message Table and Error Index Table
   with all posible errors that can occure during execution of the driver
   functions. This array does not contain "Parameter Out of Range" errors.
*/

    fl6060_err_msg_cnt = 0;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] = 0;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "No Error";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] = 220;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Unable to open instrument";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] = 221;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Unable to close instrument";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] = 223;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Instrument identification query failed";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] = 224;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Error clearing instrument";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  226;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Error polling instrument";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  228;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Error writing to instrument from file";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  229;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Error reading from instrument to file";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  230;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Error writing to instrument";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  231;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Error reading from instrument";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  232;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Instrument not initialized";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  233;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Error configuring GPIB address";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  236;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Error interpreting instrument response";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  239;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Error configuring time out";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  240;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Instrument timed out";
    fl6060_err_msg_cnt++;

/* Fluke 6060A dependent error messages: */

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  300;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Execution error";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  301;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "FM deviation not between 0 and 99.9 kHz (9.99 kHz with Option -651)";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  302;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "FM deviation step not between 0 and 99.9 kHz (9.99 kHz with Option -651)";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  303;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "AM depth not between 0 and 99%";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  304;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "AM depth step no between o and 99%";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  305;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "IEEE-488 command syntax error";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  306;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "IEEE-488 input value out of range";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  307;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Special function requires IEEE option";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  308;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "IEEE edit or step operation beyond allowed range";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  309;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Frequency not between 0.1 and 1050 MHz";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  310;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Frequency step not between 0.1 and 1050 MHz";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  311;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Invalid memory location";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  312;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Invalid data in memory";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  313;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Special function not allowed";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  314;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Output amplitude not between 10n V and 2 V";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  315;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Insufficient resolution for units conversion";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  316;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Units conversion to volts not allowed with reference in dB";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  317;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Units conversion to dB not allowed with reference in volts";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  318;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Amplitude step not between 0 and 166 dB or 0 and 1.999 V";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  319;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Units conversion on amplitude step not allowed";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  320;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Amplitude step and current amplitude display not in same units";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  400;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Uncalibrated output";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  401;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "FM deviation < 100 Hz (< 10 Hz with Option -651)";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  402;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "FM deviation > (freq -100 kHz)/3";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  403;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Excess FM deviation, main or reference PLL unlocked";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  404;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "AM depth > 90%";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  405;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Main or reference PLL unlocked";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  406;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Level vernier below calibrated range or level < -137 dBm";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  407;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Peak (AM) amplitude > +13 dBm";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  408;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Amplitude unleveled";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  409;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Fixed-range level vernier at 0";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  410;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Fixed-range level vernier at full scale";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  411;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "RPP tripped";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  412;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Level below -137 dBm";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  413;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Level correction disabled";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  414;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "RF output off";
    fl6060_err_msg_cnt++;

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  500;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Self-test failed";
    fl6060_err_msg_cnt++;

/*-End of instrument-dependent error list----------------------------------*/

    fl6060_err_idx_tbl[fl6060_err_msg_cnt] =  290L;
    fl6060_err_msg_tbl[fl6060_err_msg_cnt] = "Unknown error code";
}

/*=========================================================================*/
/* Function: Setup Arrays                                                  */
/* Purpose:  This function is called by the init routine to initialize     */
/*           static arrays.                                                */
/*=========================================================================*/
void fl6060_setup_arrays ()
{
    freq_units[0] = "HZ";
    freq_units[1] = "KZ";
    freq_units[2] = "MZ";
    freq_units[3] = "GZ";

    ampl_units[0] = "UV";
    ampl_units[1] = "MV";
    ampl_units[2] = "V";
    ampl_units[3] = "DB";

    step_table[0] = "FD";
    step_table[1] = "FU";
    step_table[2] = "LD";
    step_table[3] = "LU";
    step_table[4] = "DD";
    step_table[5] = "DU";
    step_table[6] = "PD";
    step_table[7] = "PU";

    reject_table[0]   = "000000000";
    reject_table[1]   = "001000000";
    reject_table[2]   = "002000000";
    reject_table[3]   = "004000000";
    reject_table[4]   = "010000000";
    reject_table[5]   = "020000000";
    reject_table[6]   = "040000000";
    reject_table[7]   = "100000000";
    reject_table[8]   = "200000000";
    reject_table[9]   = "000001000";
    reject_table[10]  = "000004000";
    reject_table[11]  = "000040000";
    reject_table[12]  = "000100000";
    reject_table[13]  = "000200000";
    reject_table[14]  = "000000001";
    reject_table[15]  = "000000002";
    reject_table[16]  = "000000004";
    reject_table[17]  = "000000010";
    reject_table[18]  = "000000020";
    reject_table[19]  = "000000040";
    reject_table[20]  = "000000100";


    uncal_table[0]  = "000000000";
    uncal_table[1]  = "001000000";
    uncal_table[2]  = "002000000";
    uncal_table[3]  = "004000000";
    uncal_table[4]  = "020000000";
    uncal_table[5]  = "000010000";
    uncal_table[6]  = "000000001";
    uncal_table[7]  = "000000002";
    uncal_table[8]  = "000000004";
    uncal_table[9]  = "000000010";
    uncal_table[10] = "000000020";
    uncal_table[11] = "000000040";
    uncal_table[12] = "000000100";
    uncal_table[13] = "000000200";
    uncal_table[14] = "000000400";

    reset_comm[0] = "CB";
    reset_comm[1] = "CE";
    reset_comm[2] = "CL";

    displ_comm[0] = "SP13";
    displ_comm[1] = "SP12";
    displ_comm[2] = "SP03";
    displ_comm[3] = "SP09";
    displ_comm[4] = "SP10";
    displ_comm[5] = "APDB";
    displ_comm[6] = "APV";
}

/*=== THE END =============================================================*/
