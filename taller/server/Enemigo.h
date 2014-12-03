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
#include "B2DAfterChange.h"

#include <vector>
using std::vector;

class Enemigo: public Personaje, public B2DAfterChange {
public:
	Enemigo();
	void hit();
	void evaluateMovement(Jugador * nearPlayer);
	void evaluateAnimation();
	bool isDead();
	int getType(){ return type;};
	double getx(){ return posx; };
	double gety(){ return posy; };
	void colocar(int type,double posx, double posy);
	void movimientoLoco();


	void checkStatus();
	bool isInmovil();
	bool kicked();
	void tryKick(Jugador * kickerPlayer);

	void change();
	void deadEvent();

	float getRotation();
	virtual ~Enemigo();

	void addEnemyToList(Enemigo * e);
	void destroyMiSnowBall();

	void golpeadoPorBola(Enemigo * e);
	void shoot();
	void endShoot();

	void seLlevoAJugador(Jugador* j);
	void salioDeBola(Jugador * j);

private:
	int patron;
	Move_pattern * movePattern;
	int type;
	double posx;
	double posy;
	bool dead;

	bool inmovil;
	int timeInmovil;
	int nivelNieve;

	int snowBallTime;

	bool pateado;

	vector<Enemigo*> enemyContainer;
	vector<Jugador*> playerContainer;

	Jugador * kickedBy;

	bool shooted;

};

#endif /* ENEMIGO_H_ */
