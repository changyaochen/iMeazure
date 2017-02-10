/*********************************************************************
*
* CVI Example program:
*    Acq-IntClk.c
*
* Example Category:
*    AI
*
* Description:
*    This example demonstrates how to acquire a finite amount of data
*    using the DAQ device's internal clock.
*
* Instructions for Running:
*    1. Select the physical channel to correspond to where your
*       signal is input on the DAQ device.
*    2. Enter the minimum and maximum voltages.
*    Note: For better accuracy try to match the input range to the
*          expected voltage level of the measured signal.
*    3. Select the number of samples to acquire.
*    4. Set the rate of the acquisition.
*    Note: The rate should be AT LEAST twice as fast as the maximum
*          frequency component of the signal being acquired.
*
* Steps:
*    1. Create a task.
*    2. Create an analog input voltage channel.
*    3. Set the rate for the sample clock. Additionally, define the
*       sample mode to be finite and set the number of samples to be
*       acquired per channel.
*    4. Call the Start function to start the acquisition.
*    5. Read all of the waveform data.
*    6. Call the Clear Task function to clear the task.
*    7. Display an error if any.
*
* I/O Connections Overview:
*    Make sure your signal input terminal matches the Physical
*    Channel I/O Control. For further connection information, refer
*    to your hardware reference manual.
*
*********************************************************************/

#include <stdlib.h>
#include <cvirte.h>
#include <userint.h>
#include <math.h>
#include <NIDAQmx.h>
//#include <DAQmxIOctrl.h>
//#include "Acq-IntClk.h"
#include "iMeazure_logic.h" 



TaskHandle  taskHandle0=0;
TaskHandle  taskHandle1=0;
TaskHandle  taskHandle2=0;
TaskHandle  taskHandle3=0;
TaskHandle  taskHandleA=0; 
TaskHandle  taskHandleB=0; 
char        chan[256];
float64     min = -10;
float64     max = 10;
float64		rate = 100000;
uInt32      sampsPerChan = 1;
int32       numRead = 1;
uInt32      numChannels = 1;
float64     DAQdata0[2],  DAQdata1[2],  DAQdata2[2],  DAQdata3[2];

double		final0, final1, final2, final3;


double ADC0_read(void)
{
		/*********************************************/
		// DAQmx Configure Code
		/*********************************************/

		DAQmxCreateTask("",&taskHandle0);
		DAQmxCreateAIVoltageChan(taskHandle0,"Dev1/ai0","",DAQmx_Val_Cfg_Default,min,max,DAQmx_Val_Volts,NULL);
		DAQmxCfgSampClkTiming(taskHandle0,"",rate,DAQmx_Val_Rising,DAQmx_Val_ContSamps,sampsPerChan);
				
		/*********************************************/
		// DAQmx Start Code
		/*********************************************/
		DAQmxStartTask(taskHandle0);
		
	
		/*********************************************/
		// DAQmx Read Code
		/*********************************************/
		DAQmxReadAnalogF64(taskHandle0,sampsPerChan,10.0,DAQmx_Val_GroupByChannel,DAQdata0,sampsPerChan*numChannels,&numRead,NULL);

		final0 = DAQdata0[0];

		
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(taskHandle0);
		DAQmxClearTask(taskHandle0);
		
		return final0;
}


double ADC1_read(void)
{
		/*********************************************/
		// DAQmx Configure Code
		/*********************************************/

		DAQmxCreateTask("",&taskHandle1);
		DAQmxCreateAIVoltageChan(taskHandle1,"Dev1/ai1","",DAQmx_Val_Cfg_Default,min,max,DAQmx_Val_Volts,NULL);
		DAQmxCfgSampClkTiming(taskHandle1,"",rate,DAQmx_Val_Rising,DAQmx_Val_ContSamps,sampsPerChan);
				
		/*********************************************/
		// DAQmx Start Code
		/*********************************************/
		DAQmxStartTask(taskHandle1);
		
	
		/*********************************************/
		// DAQmx Read Code
		/*********************************************/
		DAQmxReadAnalogF64(taskHandle1,sampsPerChan,10.0,DAQmx_Val_GroupByChannel,DAQdata1,sampsPerChan*numChannels,&numRead,NULL);

		final1 = DAQdata1[0];

		
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(taskHandle1);
		DAQmxClearTask(taskHandle1);
		
		return final1;
}


double ADC2_read(void)
{
		/*********************************************/
		// DAQmx Configure Code
		/*********************************************/

		DAQmxCreateTask("",&taskHandle2);
		DAQmxCreateAIVoltageChan(taskHandle2,"Dev1/ai2","",DAQmx_Val_Cfg_Default,min,max,DAQmx_Val_Volts,NULL);
		DAQmxCfgSampClkTiming(taskHandle2,"",rate,DAQmx_Val_Rising,DAQmx_Val_ContSamps,sampsPerChan);
				
		/*********************************************/
		// DAQmx Start Code
		/*********************************************/
		DAQmxStartTask(taskHandle2);
		
	
		/*********************************************/
		// DAQmx Read Code
		/*********************************************/
		DAQmxReadAnalogF64(taskHandle2,sampsPerChan,10.0,DAQmx_Val_GroupByChannel,DAQdata2,sampsPerChan*numChannels,&numRead,NULL);

		final2 = DAQdata2[0];

		
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(taskHandle2);
		DAQmxClearTask(taskHandle2);
		
		return final2;
}


double ADC3_read(void)
{
		/*********************************************/
		// DAQmx Configure Code
		/*********************************************/

		DAQmxCreateTask("",&taskHandle3);
		DAQmxCreateAIVoltageChan(taskHandle3,"Dev1/ai3","",DAQmx_Val_Cfg_Default,min,max,DAQmx_Val_Volts,NULL);
		DAQmxCfgSampClkTiming(taskHandle3,"",rate,DAQmx_Val_Rising,DAQmx_Val_ContSamps,sampsPerChan);
				
		/*********************************************/
		// DAQmx Start Code
		/*********************************************/
		DAQmxStartTask(taskHandle3);
		
	
		/*********************************************/
		// DAQmx Read Code
		/*********************************************/
		DAQmxReadAnalogF64(taskHandle3,sampsPerChan,10.0,DAQmx_Val_GroupByChannel,DAQdata3,sampsPerChan*numChannels,&numRead,NULL);

		final3 = DAQdata3[0];

		
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(taskHandle3);
		DAQmxClearTask(taskHandle3);
		
		return final3;
}

void DAC0_set(double voltage)
{

	float64 setV1[20] = {0};
	setV1[0] = (float)voltage;
	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	DAQmxCreateTask("",&taskHandleA);
	DAQmxCreateAOVoltageChan(taskHandleA,"Dev1/ao0","",-10.0,10.0,DAQmx_Val_Volts,"");

	/*********************************************/
	// DAQmx Start Code
	/*********************************************/
	DAQmxStartTask(taskHandleA);

	/*********************************************/
	// DAQmx Write Code
	/*********************************************/
	DAQmxWriteAnalogF64(taskHandleA,1,1,10.0,DAQmx_Val_GroupByChannel,setV1,NULL,NULL);
	
	/*********************************************/
	// DAQmx Stop Code
	/*********************************************/
	DAQmxStopTask(taskHandleA);
	DAQmxClearTask(taskHandleA);

}

void DAC1_set(double voltage)
{

	float64 setV2[20] = {0};
	setV2[0] = (float)voltage;
	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	DAQmxCreateTask("",&taskHandleB);
	DAQmxCreateAOVoltageChan(taskHandleB,"Dev1/ao1","",-10.0,10.0,DAQmx_Val_Volts,"");

	/*********************************************/
	// DAQmx Start Code
	/*********************************************/
	DAQmxStartTask(taskHandleB);

	/*********************************************/
	// DAQmx Write Code
	/*********************************************/
	DAQmxWriteAnalogF64(taskHandleB,1,1,10.0,DAQmx_Val_GroupByChannel,setV2,NULL,NULL);
	
	/*********************************************/
	// DAQmx Stop Code
	/*********************************************/
	DAQmxStopTask(taskHandleB);
	DAQmxClearTask(taskHandleB);

}
