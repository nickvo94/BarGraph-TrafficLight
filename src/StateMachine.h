/*
 * StateMachine.h
 *
 *  Created on: Dec 30, 2016
 *      Author: Nick
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "DigitalIOPin.h"
#include "DeltaTime.h"
#include "BoardLED.h"
#include "ITM_write.h"

class StateMachine {
	public:
		StateMachine();
		virtual ~StateMachine();
		enum state_t {None, CarEnter, CarShowGreen, CarExit, PedestrianEnter, PedestrianExit};
		enum lightState_t {AllRed, CartoGreen, CarGreen, CartoRed, PedGreen};
		void HandleState(bool, bool, uint32_t);
	private:
		state_t currentState;
		lightState_t lightState;
		DeltaTime carCount;
		DeltaTime pedCount;
		DeltaTime tNoCarsWhileGreen;
		DeltaTime tPedestrianInQueue;

		BoardLED LEDS;
		char count[40];
		uint32_t cartime;
		uint32_t pedtime;
		bool carPresent = false;
		int carTracking = 0;

};

#endif /* STATEMACHINE_H_ */
