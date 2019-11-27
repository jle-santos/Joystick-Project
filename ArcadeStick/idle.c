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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/utils/Load.h>

/* Swi handle defined in swi.cfg */
extern const Swi_Handle swiscan;
extern const Swi_Handle swisend;

/* Semaphore handle defined in task.cfg */
extern const Semaphore_Handle lpsem;


/* Counter incremented by timer interrupt */
volatile UInt tickCount = 0;

// Global Variable:
int16 pbcount = 0; // help trouble shoot


int16 X_button = 0; // Corresponds to the 'X' button on a controller
int16 T_button = 0; // Corresponds to the Triangle button on a controller
int16 O_button = 0; // Corresponds to the 'O' button on a controller
int16 S_button = 0; // Corresponds to the Square button on a controller
int16 L1_button = 0; // Corresponds to the 'L1' button on a controller
int16 R1_button = 0; // Corresponds to the 'R1' button on a controller

int16 start_button = 0; // Corresponds to the 'start' button on a controller
int16 select_button = 0; // Corresponds to the 'select' button on a controller


int16 up_button = 0; // Corresponds to the 'up' button on the D-pad
int16 down_button = 0; // Corresponds to the 'down' button on the D-pad
int16 left_button = 0; // Corresponds to the 'left' button on the D-pad
int16 right_button = 0; // Corresponds to the 'right' button on the D-pad

unsigned int JOYSTICK_X; //J1 - 2 Corresponds to analog thumb stick in x direction
unsigned int JOYSTICK_Y; //J2 - 10 Corresponds to analog thumb stick in x direction

int16 LP_count = 0; // low power counter



//function prototypes:
extern void DeviceInit(void);
unsigned int ScaleADC(unsigned int raw);

/*
 *  ======== main ========
 */
Int main()
{

    SysCtrlRegs.LPMCR0.bit.LPM = 0x0000; // LPM mode = Idle
    //SysCtrlRegs.LPMCR0.bit.LPM = 0x0001; // LPM mode = Standby
    //SysCtrlRegs.LPMCR0.bit.LPM = 0x2; // LPM mode = Halt
    /*D
     * Print "Gamer's Rise Up" to a log buffer.
     */
    System_printf("Gamer's Rise Up\n");

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
Void swiSCAN(UArg arg)
{
    GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;//determine runtime of thread

    AdcRegs.ADCSOCFRC1.all = 0x1; //start conversion via software
    while(AdcRegs.ADCINTFLG.bit.ADCINT1 == 0)
        {
        ; //wait for interrupt flag to be set
        }
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear interrupt flag

    JOYSTICK_X = ScaleADC(AdcResult.ADCRESULT0); //get X Reading
    JOYSTICK_Y = ScaleADC(AdcResult.ADCRESULT1); //Get Y Reading
    //LS (Everything above)

    int16 test1; // test input value
    int16 test2; // test input value
    int16 test3; // test input value
    int16 test4; // test input value
    int16 test5; // test input value
    int16 test6; // test input value
    int16 test7; // test input value
    int16 test8; // test input value
    int16 test9; // test input value
    int16 test10; // test input value
    int16 test11; // test input value
    int16 test12; // test input value


    test1 = GpioDataRegs.GPADAT.bit.GPIO19; // test for X button press on GPIO19
    if(test1 == 0) // active low
    {
        X_button = 1;
    } else {
        X_button = 0;
    }

    test2 = GpioDataRegs.GPADAT.bit.GPIO18; // test for Square button press on GPIO12
    if(test2 == 0)
    {
        S_button = 1;
    } else {
        S_button = 0;
    }

    test3 = GpioDataRegs.GPADAT.bit.GPIO16; // test for Triangle button press on GPIO0
    if(test3 == 0) //active high
    {
        T_button = 1;
    } else {
        T_button = 0;
    }

    test4 = GpioDataRegs.GPADAT.bit.GPIO1; // test for circle button press on GPIO1
    if(test4 == 0)
    {
        O_button = 1;
    } else {
        O_button = 0;
    }

    test5 = GpioDataRegs.GPADAT.bit.GPIO2; // test for R1 button press on GPIO2
    if(test5 == 0)
    {
        R1_button = 1;
    } else {
        R1_button = 0;
    }

    test6 = GpioDataRegs.GPADAT.bit.GPIO3; // test for L1 button press on GPIO3
    if(test6 == 0)
    {
        L1_button = 1;
    } else {
        L1_button = 0;
    }

    test7 = GpioDataRegs.GPADAT.bit.GPIO4; // test for start button press on GPIO4
    if(test7 == 0)
    {
        start_button = 1;
    } else {
        start_button = 0;
    }

    test8 = GpioDataRegs.GPADAT.bit.GPIO5; // test for select button press on GPIO5
    if(test8 == 0)
    {
        select_button = 1;
    } else {
        select_button = 0;
    }

    test9 = GpioDataRegs.GPADAT.bit.GPIO6; // test for up button press on GPIO6
    if(test9 == 0)
    {
        up_button = 1;
    } else {
        up_button = 0;
    }

    test10 = GpioDataRegs.GPADAT.bit.GPIO7; // test for down button press on GPIO7
    if(test10 == 0)
    {
        down_button = 1;
    } else {
        down_button = 0;
    }

    test11 = GpioDataRegs.GPADAT.bit.GPIO28; // test for left button press on GPIO28
    if(test11 == 0)
    {
        left_button = 1;
    } else {
        left_button = 0;
    }


    test12 = GpioDataRegs.GPADAT.bit.GPIO17; // test for right button press on GPIO12
    if(test12 == 0)
    {
        right_button = 1;
    } else {
        right_button = 0;
    }


    //if ((pain % 10) == 0) {
    //    Semaphore_post(lpsem);
    //}


    Swi_post(swisend);
}

unsigned int ScaleADC(unsigned int raw)
{
    unsigned int ScaledOutput = 0;

    ScaledOutput = raw/16;

    return ScaledOutput;
}


Void swiUART(UArg arg)
{
    GpioDataRegs.GPACLEAR.bit.GPIO0 = 1; //determine run time of thread
    int16 frame1[8] = {X_button, T_button, O_button, S_button, R1_button, L1_button, start_button, select_button};
    int16 frame1_dec = 0;
    int16 frame2_dec = 0;
    int16 i;
    // calculates decimal value for frame 1
    for (i = 0; i < 8; ++i) {
        frame1_dec <<= 1;
        frame1_dec += frame1[i];
    }

    int16 frame2[8] = {up_button, down_button, left_button, right_button, 0, 0, 0, 0};
    // calculates decimal value for frame 2
    for (i = 0; i < 8; ++i) {
        frame2_dec <<= 1;
        frame2_dec += frame2[i];
    }



    SciaRegs.SCITXBUF = JOYSTICK_X; //Frame 2
    SciaRegs.SCITXBUF = JOYSTICK_Y; //Frame 2

    // if frame1 and frame2 are empty incement counter
    if (frame1_dec == 0 && frame2_dec == 0)
    {
        LP_count += 1;
    }
    else // set counter back to zero
    {
      LP_count = 0;
    }

    // if no buttons have been pressed for 1 min (tick 0.5sec) enter lp mode
    if (LP_count >= 120)
    {
        Semaphore_post(lpsem);
    }
}



/*
 *  ======== myIdleFxn ========
 *  Background idle function that is called repeatedly 
 *  from within BIOS_start() thread.
 */
Void myIdleFxn(Void) 
{
    GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;//determine run time of thread
  //load = Load_getCPULoad();

}

// fires every 0.5 seconds
// sets tick rate
Void Tickrate(Void)
{
    /* post a Swi to perform the "heavy lifting" */
    GpioDataRegs.GPASET.bit.GPIO1 = 1;
    Swi_post(swiscan);

}


/*
 *  ======== myTaskFxn ========
 *  Task function that pends on a semaphore until 10 ticks have
 *  expired.
 */
Void LPtsk(Void)
{
    /*
     * Do this forever
     */
    while (TRUE) {
        /*
         * Pend on "lpsem" until the timer ISR says
         * its time to do something.
         */
        Semaphore_pend(lpsem, BIOS_WAIT_FOREVER);
        CpuTimer0Regs.TCR.bit.TIE = 0;//disable timer
        asm(" IDLE");
    }
}

Void awaken(Void)
{
    System_printf("Awaken\n");
    CpuTimer0Regs.TCR.bit.TIE = 1;//re-enable timer
    LP_count = 0;

}
