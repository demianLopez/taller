/*
 * SnowBross.h
 *
 *  Created on: 13/9/2014
 *      Author: EscDemi
 */

#ifndef SNOWBROSS_H_
#define SNOWBROSS_H_

#include "engine/Game.h"

class SnowBross: public Game {
public:
	SnowBross( const char *pTitle);
	bool isClosing();
	virtual ~SnowBross();
protected:
	void initializeGameStates();
	void initGame();
	void exitGame();

private:
	bool closingGame;

};

#endif /* SNOWBROSS_H_ */
