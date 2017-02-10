/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2015. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  EXTRAS                           1
#define  EXTRAS_HIDE                      2       /* control type: command, callback function: hide_extras */
#define  EXTRAS_TARGET_RESISTANCE         3       /* control type: numeric, callback function: (none) */
#define  EXTRAS_SWEEP_CH3                 4       /* control type: command, callback function: start_sweep_ch3 */
#define  EXTRAS_SAFE_VOLTAGE              5       /* control type: numeric, callback function: (none) */
#define  EXTRAS_WITHDRAW_VOLTAGE          6       /* control type: numeric, callback function: (none) */
#define  EXTRAS_CRIT_RESISTANCE           7       /* control type: numeric, callback function: (none) */
#define  EXTRAS_CRIT_RESISTANCE_INC       8       /* control type: numeric, callback function: (none) */
#define  EXTRAS_AUTOBREAK                 9       /* control type: command, callback function: do_autobreak */
#define  EXTRAS_CH3_UP                    10      /* control type: numeric, callback function: (none) */
#define  EXTRAS_CH3_LOW                   11      /* control type: numeric, callback function: (none) */
#define  EXTRAS_CH3_RATE_DOWN             12      /* control type: numeric, callback function: ch3_rate_down_change */
#define  EXTRAS_CH3_RATE_UP               13      /* control type: numeric, callback function: ch3_rate_up_change */
#define  EXTRAS_Y                         14      /* control type: numeric, callback function: (none) */
#define  EXTRAS_X                         15      /* control type: numeric, callback function: (none) */
#define  EXTRAS_THETA                     16      /* control type: numeric, callback function: (none) */
#define  EXTRAS_R                         17      /* control type: numeric, callback function: (none) */
#define  EXTRAS_SWEEP2DMAG                18      /* control type: command, callback function: Sweep_2DMAG */
#define  EXTRAS_THETA_TO                  19      /* control type: numeric, callback function: (none) */
#define  EXTRAS_R_TO                      20      /* control type: numeric, callback function: (none) */
#define  EXTRAS_MAXRATE                   21      /* control type: numeric, callback function: (none) */
#define  EXTRAS_STEPS                     22      /* control type: numeric, callback function: (none) */
#define  EXTRAS_CH3_SWEEP_NOW             23      /* control type: numeric, callback function: (none) */
#define  EXTRAS_DECORATION_2              24      /* control type: deco, callback function: (none) */
#define  EXTRAS_AUTOBR_TEXT               25      /* control type: textMsg, callback function: (none) */
#define  EXTRAS_2DMagINIT                 26      /* control type: radioButton, callback function: Magnet2D_Init */
#define  EXTRAS_2DMAG_FRAME               27      /* control type: deco, callback function: (none) */
#define  EXTRAS_CH3_DIRECTION             28      /* control type: binary, callback function: ch3_direction_change */
#define  EXTRAS_CH3_TYPE                  29      /* control type: ring, callback function: ch3_type_change */
#define  EXTRAS_sweep_ch_3                30      /* control type: textMsg, callback function: (none) */
#define  EXTRAS_MFIELD                    31      /* control type: textMsg, callback function: (none) */
#define  EXTRAS_CH3_SWEEP_TYPE            32      /* control type: ring, callback function: change_ch3_sweep_type */
#define  EXTRAS_SWEEPLIMITSCH3            33      /* control type: textMsg, callback function: (none) */
#define  EXTRAS_SWEEP_CH3_FRAME           34      /* control type: deco, callback function: (none) */
#define  EXTRAS_megaButton                35      /* control type: radioButton, callback function: ch3_mega */

#define  MAIN                             2
#define  MAIN_QUIT                        2       /* control type: command, callback function: Quit */
#define  MAIN_MEGASWEEP                   3       /* control type: command, callback function: Start_Megasweep */
#define  MAIN_SWEEP_CH2                   4       /* control type: command, callback function: start_sweep_ch2 */
#define  MAIN_SWEEP_CH1                   5       /* control type: command, callback function: start_sweep_ch1 */
#define  MAIN_Y2                          6       /* control type: numeric, callback function: (none) */
#define  MAIN_Y1                          7       /* control type: numeric, callback function: (none) */
#define  MAIN_X                           8       /* control type: numeric, callback function: (none) */
#define  MAIN_CH2_UP                      9       /* control type: numeric, callback function: (none) */
#define  MAIN_CH2_LOW                     10      /* control type: numeric, callback function: (none) */
#define  MAIN_CH2_RATE_DOWN               11      /* control type: numeric, callback function: ch2_rate_down_change */
#define  MAIN_CH2_RATE_UP                 12      /* control type: numeric, callback function: ch2_rate_up_change */
#define  MAIN_CH1_RATE_DOWN               13      /* control type: numeric, callback function: ch1_rate_down_change */
#define  MAIN_CH1_RATE_UP                 14      /* control type: numeric, callback function: ch1_rate_up_change */
#define  MAIN_CH1_UP                      15      /* control type: numeric, callback function: (none) */
#define  MAIN_CH1_LOW                     16      /* control type: numeric, callback function: (none) */
#define  MAIN_TIMER                       17      /* control type: timer, callback function: update */
#define  MAIN_Y                           18      /* control type: numeric, callback function: (none) */
#define  MAIN_GRAPH                       19      /* control type: graph, callback function: graph */
#define  MAIN_CLEAR                       20      /* control type: command, callback function: cleargraph */
#define  MAIN_SAVE                        21      /* control type: command, callback function: save */
#define  MAIN_CH2_SWEEP_NOW               22      /* control type: numeric, callback function: (none) */
#define  MAIN_CH1_SWEEP_NOW               23      /* control type: numeric, callback function: (none) */
#define  MAIN_SWEEPLIMITSCH2              24      /* control type: textMsg, callback function: (none) */
#define  MAIN_SWEEPLIMITSCH1              25      /* control type: textMsg, callback function: (none) */
#define  MAIN_TEXTMSG_6                   26      /* control type: textMsg, callback function: (none) */
#define  MAIN_DATA                        27      /* control type: scale, callback function: (none) */
#define  MAIN_BIN_SIZE                    28      /* control type: numeric, callback function: (none) */
#define  MAIN_TEXTMSG_3                   29      /* control type: textMsg, callback function: (none) */
#define  MAIN_LOADSETTINGS                30      /* control type: command, callback function: load_settings */
#define  MAIN_SAVESETTINGS                31      /* control type: command, callback function: save_settings */
#define  MAIN_ACQUIRE                     32      /* control type: command, callback function: Acquire */
#define  MAIN_ACQUIRE_FRAME               33      /* control type: deco, callback function: (none) */
#define  MAIN_Acquisition                 34      /* control type: textMsg, callback function: (none) */
#define  MAIN_SWEEP_CH1_FRAME             35      /* control type: deco, callback function: (none) */
#define  MAIN_SWEEP_CH2_FRAME             36      /* control type: deco, callback function: (none) */
#define  MAIN_DECORATION_6                37      /* control type: deco, callback function: (none) */
#define  MAIN_CH2_DIRECTION               38      /* control type: binary, callback function: ch2_direction_change */
#define  MAIN_CH1_DIRECTION               39      /* control type: binary, callback function: ch1_direction_change */
#define  MAIN_TEXTMSG_8                   40      /* control type: textMsg, callback function: (none) */
#define  MAIN_Y2_TYPE                     41      /* control type: ring, callback function: y2_axis_type_change */
#define  MAIN_TEXTMSG_2                   42      /* control type: textMsg, callback function: (none) */
#define  MAIN_Y1_TYPE                     43      /* control type: ring, callback function: y1_axis_type_change */
#define  MAIN_Y_TYPE                      44      /* control type: ring, callback function: y_axis_type_change */
#define  MAIN_Y_AXIS_OFFSET               45      /* control type: numeric, callback function: y_axis_offset_change */
#define  MAIN_CH2_TYPE                    46      /* control type: ring, callback function: ch2_type_change */
#define  MAIN_CH1_TYPE                    47      /* control type: ring, callback function: ch1_type_change */
#define  MAIN_Y2_AXIS_OFFSET              48      /* control type: numeric, callback function: y2_axis_offset_change */
#define  MAIN_X_TYPE                      49      /* control type: ring, callback function: x_axis_type_change */
#define  MAIN_Y2_AXIS_FACTOR              50      /* control type: numeric, callback function: y2_axis_factor_change */
#define  MAIN_Y_AXIS_FACTOR               51      /* control type: numeric, callback function: y_axis_factor_change */
#define  MAIN_Y1_AXIS_OFFSET              52      /* control type: numeric, callback function: y1_axis_offset_change */
#define  MAIN_X_AXIS_OFFSET               53      /* control type: numeric, callback function: x_axis_offset_change */
#define  MAIN_Y1_AXIS_FACTOR              54      /* control type: numeric, callback function: y1_axis_factor_change */
#define  MAIN_X_AXIS_FACTOR               55      /* control type: numeric, callback function: x_axis_factor_change */
#define  MAIN_DECORATION_5                56      /* control type: deco, callback function: (none) */
#define  MAIN_YMIN                        57      /* control type: numeric, callback function: axis_scale_changed */
#define  MAIN_YMAX                        58      /* control type: numeric, callback function: axis_scale_changed */
#define  MAIN_XMIN                        59      /* control type: numeric, callback function: axis_scale_changed */
#define  MAIN_XMAX                        60      /* control type: numeric, callback function: axis_scale_changed */
#define  MAIN_CH2_SWEEP_TYPE              61      /* control type: ring, callback function: change_ch2_sweep_type */
#define  MAIN_Y1_COLOR_2                  62      /* control type: color, callback function: y1_color_change */
#define  MAIN_CH1_SWEEP_TYPE              63      /* control type: ring, callback function: change_ch1_sweep_type */
#define  MAIN_MESSAGES                    64      /* control type: textBox, callback function: (none) */
#define  MAIN_EXTENSIONS                  65      /* control type: command, callback function: extensions */
#define  MAIN_MEGA_STEP_NUMBER            66      /* control type: numeric, callback function: mega_time */
#define  MAIN_Y1_COLOR                    67      /* control type: color, callback function: y1_color_change */
#define  MAIN_Y_COLOR                     68      /* control type: color, callback function: y_color_change */
#define  MAIN_MEGASWEEP_FRAME             69      /* control type: deco, callback function: (none) */
#define  MAIN_UPDOWN                      70      /* control type: binary, callback function: (none) */
#define  MAIN_Factor                      71      /* control type: textMsg, callback function: (none) */
#define  MAIN_Offset                      72      /* control type: textMsg, callback function: (none) */
#define  MAIN_Type                        73      /* control type: textMsg, callback function: (none) */
#define  MAIN_MEGA_TIME_FRAME             74      /* control type: deco, callback function: (none) */
#define  MAIN_MEGA_TIME                   75      /* control type: numeric, callback function: (none) */
#define  MAIN_TEXTMSG_5                   76      /* control type: textMsg, callback function: (none) */
#define  MAIN_VNA_points                  77      /* control type: numeric, callback function: VNA_points */
#define  MAIN_VNA_time                    78      /* control type: numeric, callback function: VNA_time */
#define  MAIN_TEXTMSG                     79      /* control type: textMsg, callback function: (none) */
#define  MAIN_DECORATION_7                80      /* control type: deco, callback function: (none) */
#define  MAIN_VNA_average                 81      /* control type: numeric, callback function: (none) */
#define  MAIN_TEXTMSG_4                   82      /* control type: textMsg, callback function: (none) */
#define  MAIN_TEXTMSG_7                   83      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Acquire(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK axis_scale_changed(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ch1_direction_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ch1_rate_down_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ch1_rate_up_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ch1_type_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ch2_direction_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ch2_rate_down_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ch2_rate_up_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ch2_type_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ch3_direction_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ch3_mega(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ch3_rate_down_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ch3_rate_up_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ch3_type_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK change_ch1_sweep_type(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK change_ch2_sweep_type(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK change_ch3_sweep_type(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK cleargraph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK do_autobreak(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK extensions(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK graph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK hide_extras(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK load_settings(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Magnet2D_Init(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK mega_time(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Quit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK save_settings(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Start_Megasweep(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK start_sweep_ch1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK start_sweep_ch2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK start_sweep_ch3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Sweep_2DMAG(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK update(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VNA_points(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VNA_time(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK x_axis_factor_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK x_axis_offset_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK x_axis_type_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK y1_axis_factor_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK y1_axis_offset_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK y1_axis_type_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK y1_color_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK y2_axis_factor_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK y2_axis_offset_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK y2_axis_type_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK y_axis_factor_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK y_axis_offset_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK y_axis_type_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK y_color_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
