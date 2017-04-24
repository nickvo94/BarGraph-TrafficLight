/*
 * NewBarGraph.h
 *
 *  Created on: Dec 14, 2016
 *      Author: Nick
 */

#ifndef NEWBARGRAPH_H_
#define NEWBARGRAPH_H_

#include "BarGraph.h"
#include "LiquidCrystal.h"

class NewBarGraph : public BarGraph {
public:
	NewBarGraph (int x_, int y_, LiquidCrystal& lcd_, int length_ = 5, bool vertical_ = false);
	void SetPosition(int, int);
	void SetGraph(int, int);
	virtual ~NewBarGraph();
private:
	int x;
	int y;
};

#endif /* NEWBARGRAPH_H_ */
