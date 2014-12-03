#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "Personaje.h"
#include "../game/BolaDeNieve.h"
#include "../common/client_handler.h"
#include <vector>
#include "../common/CommandCode.h"
#include <mutex>
#include "B2DAfterChange.h"

class Enemigo;

using std::vector;
using std::mutex;

// Jugador principal
class Jugador: public Personaje, public B2DAfterChange {
private:

	char * name;
	vector<KeyCode> keyCode;
	Client_handler * client;

	vector<Jugador *> mySpector;

	bool offline;

	void evaluateAnimation();
	void deadEvent();



	bool invulnerable;
	char secondsInvulLeft;

	void shoot();

	Enemigo * enemy;

	/*
	 const float VELOCIDAD_MAXIMA_BUFF_X = VELOCIDAD_MAXIMA_DEFAULT_X * 1.5;
	 */

	int superSpeedTime;

public:
	void enableSuperSpeed();
	void touchingEnemy(Enemigo * enemigo);
	void updateOnClientUserStats();
	Jugador * clonePlayer();

	bool isInvulnerable();
	bool isDead();

	void change();
	void decreaseShoot();

	int lives;
	int score;

	int shootRealized;

	mutex playerBusy;

	int keyRequestSend;
	bool isReady;

	int getPlayerLives();
	int getPlayerScore();

	void setOffline(bool isOffline);
	bool isOffline();

	void hit();
	void checkStatus();


	Jugador(Client_handler * client, char * name);
	void addSpectingMe(Jugador * j);

	void setClient(Client_handler * client);

	char * getName();

	void addKeyCode(KeyCode keyCode);
	void apllyCodes();

	char * getPlayerName();

	Client_handler * getClient();

	char tipoDeObjeto; // Para contact listener.
	int afterB2DEvent;

};

#endif /* JUGADOR_H_ */
