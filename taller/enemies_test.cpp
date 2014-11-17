#include "server/moving_objects/enemy_factory.h"
#include "server/moving_objects/player_character.h"

int main() {
	Player_character* player = new Player_character();
	Enemy* basic = Enemy_factory::get_standar_enemy();
	delete basic;
	return 0;
}
