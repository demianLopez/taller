/*
 * Enemigo.h
 *
 *  Created on: 29/11/2014
 *      Author: demian
 */

#ifndef ENEMIGO_H_
#define ENEMIGO_H_

#include "Personaje.h"
#include "moving_objects/move_patterns/move_pattern.h"
#include "Jugador.h"

class Enemigo: public Personaje {
public:
	Enemigo(Move_pattern * movePattern);
	void hit();
	void evaluateMovement(Jugador * nearPlayer);
	void evaluateAnimation();
	virtual ~Enemigo();
private:
	Move_pattern * movePattern;
};

#endif /* ENEMIGO_H_ */
