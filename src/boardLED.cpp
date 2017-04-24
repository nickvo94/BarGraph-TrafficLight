/*
 * boardLED.cpp
 *
 *  Created on: Jan 2, 2017
 *      Author: Nick
 */

#include "boardLED.h"

BoardLED::BoardLED() {
	// TODO Auto-generated constructor stub

}

BoardLED::~BoardLED() {
	// TODO Auto-generated destructor stub
}

void BoardLED::setLED(int idx, bool state) {
	Chip_IOCON_PinMuxSet(LPC_IOCON, lightport[idx], lightpins[idx], IOCON_MODE_INACT | IOCON_DIGMODE_EN);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, lightport[idx], lightpins[idx]);
	Chip_GPIO_SetPinState(LPC_GPIO, lightport[idx], lightpins[idx], state);
}
