/* 
 *  28x specific Idle example.
 *  
 *  This example:
 * 
 *  1) prints "Hello world" in main()
 *  
 *  2) prints the current value of a counter from
 *     within an Idle function each time an
 *     a timer interrupt goes off.
 * 
 *  All output is routed to a log buffer which can be viewed
 *  using the RTA "Raw Logs" viewer. After loading and running
 *  the application, launch the Tools->RTA->Raw Logs tool to
 *  view the logs.
 */

#define xdc__strict //gets rid of #303-D typedef warning re Uint16, Uint32

#define getTempSlope (*(int (*)(void))0x3d7e80)  //LS
#define getTempOffset (*(int (*)(void))0x3d7e83) //LS



#include "Peripheral_Headers/F2802x_Device.h"
#include <xdc/std.h>
//#include <xdc/runtime/Log.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>



/* Flag used by idle function to check if interrupt occurred */
volatile Bool isrFlag = FALSE;

/* Counter incremented by timer interrupt */
volatile UInt tickCount = 0;

// Global Variable:
int16 pbcount = 0; //counts pushbutton pushes


//function prototypes:

extern void DeviceInit(void);

/*
 *  ======== main ========
 */

//declare global variables:
int16 JOYSTICK_X; //J1 - 2
int16 JOYSTICK_Y; //J2 - 10
int16 DATA;


Int main()
{
    /*
     * Print "Hello world" to a log buffer. 
     */
    System_printf("Hello world\n");

    /* 
     * Start BIOS
     * Perform a few final initializations and then
     * fall into a loop that continually calls the
     * installed Idle functions.
     */
    DeviceInit(); //initialize peripherals

    BIOS_start();    /* does not return */
    return(0);
}

/*
 *  ======== myTickFxn ========
 *  Timer Tick function that increments a counter, and sets the isrFlag.
 */
Void myTickFxn(UArg arg) 
{
    AdcRegs.ADCSOCFRC1.all = 0x1; //start conversion via software
    while(AdcRegs.ADCINTFLG.bit.ADCINT1 == 0)
        {
        ; //wait for interrupt flag to be set
        }
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear interrupt flag


    JOYSTICK_X = AdcResult.ADCRESULT0; //get reading
    JOYSTICK_Y = AdcResult.ADCRESULT1;
    //LS (Everything above)

    DATA = GpioDataRegs.GPADAT.bit.GPIO0;
    if(DATA >= 1)
    {
        tickCount += 1;    /* increment the counter */
    }

    isrFlag = TRUE;    /* tell background that new data is available */
}

/*
 *  ======== myIdleFxn ========
 *  Background idle function that is called repeatedly 
 *  from within BIOS_start() thread.
 */
Void myIdleFxn(Void) 
{
    if (isrFlag == TRUE) {
        isrFlag = FALSE;
        /*
         * Print the current value of tickCount to a log buffer. 
         */
        GpioDataRegs.GPATOGGLE.bit.GPIO0 = 1;
        System_printf("Tick Count = %d\n", tickCount);
    }
}


Void ButtonDetect(Void)

{

    pbcount++;

}



