#include "server/moving_objects/enemy_factory.h"
#include "server/moving_objects/player_character.h"

int main() {
	Player_character* shiningFlareWingman = new Player_character();
	Enemy* shiningPhoenixEnforcer = Enemy_factory::get_standar_enemy();

	Projectile* p = shiningFlareWingman->fire();

	delete shiningPhoenixEnforcer;
	delete shiningFlareWingman;
	return 0;
}
