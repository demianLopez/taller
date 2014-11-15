#include "server/enemies/enemy_factory.h"

int main(){
	Enemy* basic = Enemy_factory::get_standar_enemy();
	delete basic;
	return 0;
}
