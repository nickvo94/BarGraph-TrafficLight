/*
 * DeltaTime.h
 *
 *  Created on: Jan 2, 2017
 *      Author: Nick
 */

#ifndef DELTATIME_H_
#define DELTATIME_H_

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

extern uint32_t ticks;
extern uint32_t counter;

class DeltaTime {
public:
	DeltaTime();
	void startWait(uint32_t);
	void disable();
	bool isDone();
	uint32_t hasWaited();
	bool enabled;
private:
	uint32_t start;
	uint32_t until;
};

#endif /* DELTATIME_H_ */
