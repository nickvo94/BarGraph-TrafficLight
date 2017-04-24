/*
 * DeltaTime.cpp
 *
 *  Created on: Jan 2, 2017
 *      Author: Nick
 */

#include "DeltaTime.h"

DeltaTime::DeltaTime() {
	start = ticks;
	until = ticks;
	enabled = false;
}

void DeltaTime::startWait(uint32_t waitTime) {
		enabled = true;
		start = ticks;
		until = ticks + waitTime;
}

void DeltaTime::disable() {
	enabled = false;
}

bool DeltaTime::isDone() {
	if (enabled && ticks >= until) {
		enabled = false;
		return true;
	}
	return false;
}

uint32_t DeltaTime::hasWaited() {
	return ticks - start;
}
