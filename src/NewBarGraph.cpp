/*
 * NewBarGraph.cpp
 *
 *  Created on: Dec 14, 2016
 *      Author: Nick
 */

#include "NewBarGraph.h"

NewBarGraph::NewBarGraph(int x_, int y_, LiquidCrystal& lcd_, int length_, bool vertical_) : BarGraph(lcd_, length_, vertical_) {
	SetPosition(x_, y_);
}

NewBarGraph::~NewBarGraph() {
	// TODO Auto-generated destructor stub
}

void NewBarGraph::SetPosition (int x_, int y_) {
	x = x_;
	y = y_;
}

void NewBarGraph::SetGraph (int d0, int d10) {
	lcd.setCursor(x, y);
	draw(d0);
	lcd.setCursor(x, y+1);
	draw(d10);
}
