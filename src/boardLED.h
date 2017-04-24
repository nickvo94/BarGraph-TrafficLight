/*
 * boardLED.h
 *
 *  Created on: Jan 2, 2017
 *      Author: Nick
 */

#ifndef BOARDLED_H_
#define BOARDLED_H_

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif
#include "DigitalIOPin.h"

static uint8_t lightport[] = { 0, 1, 0, 0, 0 };
static uint8_t lightpins[] = { 24, 0, 27, 28, 12 };

class BoardLED {
public:
	BoardLED();
	virtual ~BoardLED();
	void setLED(int, bool);
};

#endif /* BOARDLED_H_ */
