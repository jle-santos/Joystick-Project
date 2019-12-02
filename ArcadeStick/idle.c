//Author: Lemuel Santos & Ryan Wong
//Date: December 1, 2019
//Arcade Stick Project - ELEX 7820
//Sends out commands to computer via SCI communication
//
//Code Sections --------------------------------------
//LS - For code written by Lemuel Santos
//RW - For code written by Ryan Wong

#define xdc__strict //gets rid of #303-D typedef warning re Uint16, Uint32

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

// Global Variables:
int16 pbcount = 0; // help trouble shoot

// Face Buttons
int16 X_button = 0; // Corresponds to the 'X' button on a controller -RW
int16 T_button = 0; // Corresponds to the Triangle button on a controller -RW
int16 O_button = 0; // Corresponds to the 'O' button on a controller -RW
int16 S_button = 0; // Corresponds to the Square button on a controller -RW
int16 L1_button = 0; // Corresponds to the 'L1' button on a controller -RW
int16 R1_button = 0; // Corresponds to the 'R1' button on a controller -RW

int16 start_button = 0; // Corresponds to the 'start' button on a controller -RW
int16 select_button = 0; // Corresponds to the 'select' button on a controller -RW

// Directional buttons
int16 up_button = 0; // Corresponds to the 'up' button on the D-pad -RW
int16 down_button = 0; // Corresponds to the 'down' button on the D-pad -RW
int16 left_button = 0; // Corresponds to the 'left' button on the D-pad -RW
int16 right_button = 0; // Corresponds to the 'right' button on the D-pad -RW

unsigned int JOYSTICK_X; //J1 - 2 Corresponds to analog thumb stick in X direction -LS
unsigned int JOYSTICK_Y; //J2 - 10 Corresponds to analog thumb stick in Y direction -LS

int16 frame1_dec = 0; //Variable to store decimal value of frame1 -RW
int16 frame2_dec = 0; //Variable to store decimal value of frame2 -Rw

Uint16 LP_count = 0; // Low power counter -RW
Uint32 load; // CPU Load variable -Rw

// Constant Definitions
#define INACTIVE -16192 //The value of a frame if it is inactive -LS
#define ONE_MINUTE 6000 //Number of ticks before entering low power mode -LS

//function prototypes:
extern void DeviceInit(void);
unsigned int ScaleADC(unsigned int raw); //Scales the ADC readings to 8-bit -LS

/*
 *  ======== main ========
 */
Int main()
{
    //Specify the low power mode to be IDLE
    SysCtrlRegs.LPMCR0.bit.LPM = 0x0000; // LPM mode = Idle -RW
    //SysCtrlRegs.LPMCR0.bit.LPM = 0x0001; // LPM mode = Standby
    //SysCtrlRegs.LPMCR0.bit.LPM = 0x2; // LPM mode = Halt
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
 *  ======== swiSCAN ========
 *  Polls button presses and samples the joystick
 */
Void swiSCAN(UArg arg)
{
    //GpioDataRegs.GPATOGGLE.bit.GPIO0 = 1;//flash intime with the tickrate

    AdcRegs.ADCSOCFRC1.all = 0x1; //Start conversion via software -LS
    while(AdcRegs.ADCINTFLG.bit.ADCINT1 == 0) //Poll for the ADC flag -LS
        {
        ; //wait for interrupt flag to be set -LS
        }
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear interrupt flag -LS

    JOYSTICK_X = ScaleADC(AdcResult.ADCRESULT0); //Get X Reading and scale -LS
    JOYSTICK_Y = ScaleADC(AdcResult.ADCRESULT1); //Get Y Reading and scale -LS
    //LS (Everything above)

    int16 test1; // test input value -RW
    int16 test2; // test input value -RW
    int16 test3; // test input value -RW
    int16 test4; // test input value -RW
    int16 test5; // test input value -RW
    int16 test6; // test input value -RW
    int16 test7; // test input value -RW
    int16 test8; // test input value -RW
    int16 test9; // test input value -RW
    int16 test10; // test input value -RW
    int16 test11; // test input value -RW
    int16 test12; // test input value -RW

    /* Start - Section below written by RW */
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
    /* End -End of section by RW */

    Swi_post(swisend);//start UART thread for synchrnoization -RW
    }

//Function written by LS
unsigned int ScaleADC(unsigned int raw)
{
    unsigned int ScaledOutput = 0;

    ScaledOutput = raw/16; //Example: 4096/16 = 256 (8-bit maximum) -LS

    return ScaledOutput;
}

/*
 *  ======== swiUART ========
 *  Sends the data frames via SCI
 */
Void swiUART(UArg arg)
{
    int16 frame1[8] = { 1, 1, O_button, S_button, R1_button, L1_button, start_button, select_button}; //Compile data into one array (Face Buttons) -RW
    int16 frame2[8] = { 1, 1,up_button, down_button, left_button, right_button, X_button, T_button};  //Compile data into one aray (Directional Buttons) -RW
    int16 i; // index for for-loop -RW

    // calculates decimal value for frame 1 -RW
    for (i = 0; i < 8; ++i) {
        frame1_dec <<= 1;
        frame1_dec += frame1[i];
    }
    // calculates decimal value for frame 2 -Rw
    for (i = 0; i < 8; ++i) {
        frame2_dec <<= 1;
        frame2_dec += frame2[i];
    }

    //Buttons
    SciaRegs.SCITXBUF = frame1_dec; //Face buttons -LS
    SciaRegs.SCITXBUF = frame2_dec; //Directional buttons -LS

    SciaRegs.SCITXBUF = JOYSTICK_X; //Joystick X Axes -LS
    SciaRegs.SCITXBUF = JOYSTICK_Y; //Joystick Y Axes -LS

    SciaRegs.SCITXBUF = 0x0A; //EOL Check -LS

    // if frame1 and frame2 are empty increment counter -RW
    if (frame1_dec == INACTIVE && frame2_dec == INACTIVE)
    {
        LP_count += 1;
    }
    else // set counter back to zero
    {
      LP_count = 0;
    }

    // if no buttons have been pressed for 1 minute (tick 0.01sec) enter LPM -RW
    if (LP_count >= ONE_MINUTE)
    {
        Semaphore_post(lpsem); //Post semaphore allowing entry into LPM -RW
    }
}



/*
 *  ======== myIdleFxn ========
 *  Background idle function that is called repeatedly 
 *  from within BIOS_start() thread.
 */
Void myIdleFxn(Void) 
{
    //Calculate the CPU load on the system -RW
    load = Load_getCPULoad();
    GpioDataRegs.GPATOGGLE.bit.GPIO0 = 1;
}

/*
 *  ======== Tickrate ========
 *  Timer that raises an interrupt every 0.01 seconds (100Hz)
 */
Void Tickrate(Void)
{
    /* post a Swi to perform the "heavy lifting" -RW*/
    Swi_post(swiscan);
}


/*
 *  ======== LPtsk ========
 *  Task function that pends on a semaphore until 6000 ticks have
 *  expired.
 */
Void LPtsk(Void)
{
    /*
     * Do this forever during IDLE -RW
     */
    while (TRUE) {
        /*
         * Pend on "lpsem" until the 1min of no button presses has passed
         * then enter low power mode -RW
         */
        Semaphore_pend(lpsem, BIOS_WAIT_FOREVER);
        CpuTimer0Regs.TCR.bit.TIE = 0;//disable timer -RW
        asm(" IDLE");// enter low power mode -RW
    }
}

/*
 *  ======== awaken ========
 *  Hardware interrupt that turns on CPU timers resuming the device
 */
Void awaken(Void)
{
    System_printf("Awaken\n");
    CpuTimer0Regs.TCR.bit.TIE = 1;//re-enable timer -RW
    LP_count = 0;//reset low power mode counter -RW
}
