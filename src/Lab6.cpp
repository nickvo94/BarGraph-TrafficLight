/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif
#include "DigitalIOPin.h"
#include "BarGraph.h"
#include "NewBarGraph.h"
#include "DeltaTime.h"
#include "StateMachine.h"
#include "ITM_write.h"

#include <cr_section_macros.h>

#define TICKRATE_HZ (4000)

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

//static volatile uint32_t count1;
//static volatile uint32_t count2;

/*
 * Ask teacher about changing timer variables from
 *  static volatile uint32_t
 *           to
 *  uint32_t
 *  with
 *  extern uint32_t (in DeltaTime.h)
 *
 */
uint32_t ticks = 0;
uint32_t counter = 0;

extern "C" {

void SysTick_Handler(void){

	/* Every 1/2 second */
	static bool blink;

	//count1++;
	//count2++;

	ticks++;

	if(counter > 0) counter--;
}

} // extern "C"


// returns the interrupt enable state before entering critical section
bool enter_critical(void)
{
	uint32_t pm = __get_PRIMASK();
	__disable_irq();
	return (pm & 1) == 0;
}



void Sleep(uint32_t time)
{
	counter = time;
	while(counter > 0) {
		__WFI();
	}
}

int main(void) {
	#if defined (__USE_LPCOPEN)
	#if !defined(NO_BOARD_LIB)
		Board_Init();
		Chip_RIT_Init(LPC_RITIMER); // initialize RIT (enable clocking etc.)
	#endif
	#endif
	uint32_t sysTickRate;
	SystemCoreClockUpdate();
	Chip_Clock_SetSysTickClockDiv(1);
	sysTickRate = Chip_Clock_GetSysTickClockRate();
	SysTick_Config(sysTickRate / TICKRATE_HZ);

	ITM_init();

    DigitalIoPin button2 (0, 0, true, true, false);
    DigitalIoPin button1 (3, 1, true, true, false);

    // TODO: insert code here
    bool button1press;
    bool button2press;
    bool button1state;
    bool button2state;
    int counting = 0;


    StateMachine tLights;
	char debugStr[20];

	Sleep(25);
	sprintf(debugStr, "Start\n");
	ITM_write(debugStr);

	while(1) {
		button1press = button1.read();
		button2press = button2.read();
		tLights.HandleState(button1press, button2press, ticks);
		//sprintf(debugStr, "t:%d\n", ticks);
		//ITM_write(debugStr);
	}
    return 0;
}
