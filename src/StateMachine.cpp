/*
 * StateMachine.cpp
 *
 *  Created on: Dec 30, 2016
 *      Author: Nick
 */

#include "StateMachine.h"

StateMachine::StateMachine() {
	currentState = CarShowGreen;
}

StateMachine::~StateMachine() {
	// TODO Auto-generated destructor stub
}

void StateMachine::HandleState(bool pedestrian, bool car, uint32_t ticks_){

	cartime = carCount.hasWaited();
	pedtime = pedCount.hasWaited();
	//sprintf(count, "car: %d, ped:%d\n", cartime, pedtime);
	//ITM_write(count);

	switch(currentState){

		case None:
			lightState = AllRed;
			if (car) {
				currentState = CarEnter;
			}
			if (pedestrian) {
				pedCount.startWait(0);
				currentState = PedestrianEnter;
			}
			break;

		case CarEnter:
			carCount.startWait(0);
			tPedestrianInQueue.disable();
			tNoCarsWhileGreen.disable();
			currentState = CarShowGreen;
		break;

		case CarShowGreen:
			if (carCount.hasWaited() < 5000) {
				lightState = CartoGreen;
			}
			if (carCount.hasWaited() > 5000){
				lightState = CarGreen;
				if (tPedestrianInQueue.enabled) {
					// Pedestrian has waited 60s or No cars are present:
					if (tPedestrianInQueue.isDone() || (tPedestrianInQueue.enabled && !car)) {
						currentState = PedestrianEnter;
						pedCount.startWait(0);
						sprintf(count, "Pedestrian queue complete.\n");
						ITM_write(count);
					}
				} else {
					// No cars present for 60 seconds:
					if (!car) {
						if (!tNoCarsWhileGreen.enabled) {
							tNoCarsWhileGreen.startWait(60000);
						} else {
							if (tNoCarsWhileGreen.isDone()) { currentState = CarExit; }
						}
					} else {
					 tNoCarsWhileGreen.disable();
					}

					// Pedestrian button pressed:
					if(pedestrian && !tPedestrianInQueue.enabled) {
						Board_LED_Set(1, true);
						tPedestrianInQueue.startWait(60000);
						sprintf(count, "Pedestrian queued.\n");
						ITM_write(count);
					}
				}
			}
			break;

		case CarExit:
			currentState = None;
			break;

		case PedestrianEnter:
			if(lightState == AllRed){
				if(pedCount.hasWaited() > 1000){
					lightState = PedGreen;
					if(pedCount.hasWaited() > 16000){currentState = PedestrianExit;}
				}
			}
			if(lightState == CarGreen){
				if(pedCount.hasWaited() < 5000){
					lightState = CartoRed;
				}
			}
			if(pedCount.hasWaited() > 5000){
				lightState = PedGreen;
				if(pedCount.hasWaited() > 25000){currentState = PedestrianExit;}
				Board_LED_Set(1, false);
			}
			break;

		case PedestrianExit:
			currentState = CarEnter;
			break;
	}


	switch(lightState) {
	case AllRed:
		LEDS.setLED(0, true);
		LEDS.setLED(1, false);
		LEDS.setLED(2, true);
		LEDS.setLED(3, false);
		LEDS.setLED(4, false);
		break;
	case CartoGreen:
		LEDS.setLED(0, true);
		LEDS.setLED(1, false);
		LEDS.setLED(2, true);
		LEDS.setLED(3, true);
		LEDS.setLED(4, false);
		break;
	case CarGreen:
		LEDS.setLED(0, true);
		LEDS.setLED(1, false);
		LEDS.setLED(2, false);
		LEDS.setLED(3, false);
		LEDS.setLED(4, true);
		break;
	case CartoRed:
		LEDS.setLED(0, true);
		LEDS.setLED(1, false);
		LEDS.setLED(2, false);
		LEDS.setLED(3, true);
		LEDS.setLED(4, false);
		break;
	case PedGreen:
		LEDS.setLED(0, false);
		LEDS.setLED(1, true);
		LEDS.setLED(2, true);
		LEDS.setLED(3, false);
		LEDS.setLED(4, false);
		break;
	}
}

/*
	switch(currentState){

		case None:

			lightState = AllRed;

			if (car) {
				carCount.startWait(0);
				currentState = CarEnter;
			}
			//if (car == false) { currentState = CarExit; }
			if (pedestrian) {
				pedCount.startWait(0);
				currentState = PedestrianEnter;
			}
			//if (pedestrian == false) { currentState = PedestrianExit; }

			break;

		case CarEnter:

			if (carCount.hasWaited() < 5000) {
				lightState = CartoGreen;
			}
			if (carCount.hasWaited() > 5000){
				lightState = CarGreen;

				if (carCount.hasWaited() > 60000) { currentState = CarExit; }

				if(pedestrian && car){
					carPresent = true;
				}

				if(carPresent == true && car){
					carTracking = carTracking++;
					if(carTracking == 60){
						pedCount.startWait(0);
						currentState = PedestrianEnter;
						carPresent = false,
						carTracking = 0;
					}
				}else if (carPresent == true && car == false){
					pedCount.startWait(0);
					currentState = PedestrianEnter;
					carPresent = false, carTracking = 0;
				}

			}
			break;

		case CarExit:
			currentState = None;
			break;

		case PedestrianEnter:

			if(lightState == AllRed){
				if(pedCount.hasWaited() > 1000){
					lightState = PedGreen;
					if(pedCount.hasWaited() > 16000){currentState = PedestrianExit;}
				}
			}
			if(lightState == CarGreen){
				if(pedCount.hasWaited() < 5000){
					lightState = CartoRed;
				}
			}
			if(pedCount.hasWaited() > 5000){
				lightState = PedGreen;
				if(pedCount.hasWaited() > 25000){currentState = PedestrianExit;}
			}
			break;


		case PedestrianExit:
			currentState = None;
			if(carCount.hasWaited() < 60000){
				carCount.startWait(0);
				currentState = CarEnter;
			}else{currentState = None;}
			break;
	}

*/
