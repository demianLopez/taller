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
	bool isDead();
	int getType(){ return type;};
	double getx(){ return posx; };
	double gety(){ return posy; };
	void colocar(int type,double posx, double posy);

	virtual ~Enemigo();
private:
	Move_pattern * movePattern;
	int type;
	double posx;
	double posy;
	bool dead;
};

#endif /* ENEMIGO_H_ */
