#ifndef COSACONMOVIMIENTO_H_
#define COSACONMOVIMIENTO_H_

#include "VectorXY.h"
#include <Box2D/Box2D.h>
#include "engine/Animation.h"
#include "Resources.h"

class CosaConMovimiento {	// No puedo pensar un nombre mejor.
private:
	const float MOVEMENT_SPEED_X_DEFAULT = 4;
	const float MOVEMENT_SPEED_Y_DEFAULT = 6;

	b2Vec2 lastVelocity;

protected:
	bool mirandoParaLaDerecha;

	// Define si se esta moviendo.
	bool movingLeft;
	bool movingRight;
	bool wasMovingLeftFirst;

	// Modulo de la velocidad.
	float movementSpeedX;
	float movementSpeedY;

	// Cosa en box2d
	b2Body * body;

public:
	// Inicializa cosa.
	CosaConMovimiento(b2World * gameWorld);
	~CosaConMovimiento();

	// Frena la cosa en X y/o Y
	void frenar(bool frenarEnX, bool frenarEnY);

	bool isGoingUp();
	bool isGoingDown();

	// Devuelve true si esta mirando para la derecha.
	bool estaMirandoParaLaDerecha();

	virtual void update();

	void setFreezeRotation(bool freezeRotation);
	virtual Animation * getAnimation(Resources * resources);

	void setMovingLeft(bool movingLeft);
	void setMovingRight(bool movingRight);
	bool isMovingLeft();
	bool isMovingRight();

	void stop(bool stopX = true, bool stopY = true);

	b2Body * getBody();

	bool stopAtHit;

	bool goingUp;
	bool goingDown;
	bool onTopJump;

	bool isOnAir();

};

#endif /* COSACONMOVIMIENTO_H_ */
