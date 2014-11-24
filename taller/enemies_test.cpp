#include <iostream>

#include "server/moving_objects/enemy.h"
#include "server/moving_objects/enemy_factory.h"
#include "server/moving_objects/player_character.h"
#include "server/weapons/projectile/projectile.h"

using std::cout;
using std::endl;

int main() {
	Player_character* shiningFlareWingman = new Player_character();
	Enemy* shiningPhoenixEnforcer = Enemy_factory::get_standar_enemy();

	int energy = shiningPhoenixEnforcer->get_energy();

	Projectile* p = shiningFlareWingman->fire();
	p->collide(*shiningPhoenixEnforcer);

	cout << "Shining Phoenix Enforcer tiene ahora: "
			<< shiningPhoenixEnforcer->get_energy() << " de " << energy << endl;

	delete shiningPhoenixEnforcer;
	delete shiningFlareWingman;
	return 0;
}
