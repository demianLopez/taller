#include <iostream>

#include "server/moving_objects/enemy.h"
#include "server/moving_objects/enemy_factory.h"
#include "server/moving_objects/player_character.h"
#include "server/weapons/projectile/projectile.h"
#include "server/World.h"

using std::cout;
using std::endl;

void test_a() {
	World* world = new World(new b2Vec2(1, 1));
	Player_character* shiningFlareWingman = new Player_character(world);
	Enemy* shiningPhoenixEnforcer = Enemy_factory::get_standar_enemy(world);

	int energy = shiningPhoenixEnforcer->get_energy();

	cout << "Mismo disparo" << endl;

	Projectile* p = shiningFlareWingman->fire();
	p->collide(*shiningPhoenixEnforcer);
	cout << "Shining Phoenix Enforcer tiene ahora: "
			<< shiningPhoenixEnforcer->get_energy() << " de " << energy << endl;

	p->collide(*shiningPhoenixEnforcer);
	cout << "Shining Phoenix Enforcer tiene ahora: "
			<< shiningPhoenixEnforcer->get_energy() << " de " << energy << endl;

	p->collide(*shiningPhoenixEnforcer);
	cout << "Shining Phoenix Enforcer tiene ahora: "
			<< shiningPhoenixEnforcer->get_energy() << " de " << energy << endl;

	p->collide(*shiningPhoenixEnforcer);
	cout << "Shining Phoenix Enforcer tiene ahora: "
			<< shiningPhoenixEnforcer->get_energy() << " de " << energy << endl;

	p->collide(*shiningPhoenixEnforcer);
	cout << "Shining Phoenix Enforcer tiene ahora: "
			<< shiningPhoenixEnforcer->get_energy() << " de " << energy << endl;

	delete shiningPhoenixEnforcer;
	delete shiningFlareWingman;
}

void test_b() {
	World* world = new World(new b2Vec2(1, 1));
	Player_character* shiningFlareWingman = new Player_character(world);
	Enemy* shiningPhoenixEnforcer = Enemy_factory::get_standar_enemy(world);

	int energy = shiningPhoenixEnforcer->get_energy();

	cout << "Varios disparos distintos" << endl;

	Projectile* p = shiningFlareWingman->fire();
	p->collide(*shiningPhoenixEnforcer);
	cout << "Shining Phoenix Enforcer tiene ahora: "
			<< shiningPhoenixEnforcer->get_energy() << " de " << energy << endl;

	p = shiningFlareWingman->fire();
	p->collide(*shiningPhoenixEnforcer);
	cout << "Shining Phoenix Enforcer tiene ahora: "
			<< shiningPhoenixEnforcer->get_energy() << " de " << energy << endl;

	p = shiningFlareWingman->fire();
	p->collide(*shiningPhoenixEnforcer);
	cout << "Shining Phoenix Enforcer tiene ahora: "
			<< shiningPhoenixEnforcer->get_energy() << " de " << energy << endl;

	p = shiningFlareWingman->fire();
	p->collide(*shiningPhoenixEnforcer);
	cout << "Shining Phoenix Enforcer tiene ahora: "
			<< shiningPhoenixEnforcer->get_energy() << " de " << energy << endl;

	p = shiningFlareWingman->fire();
	p->collide(*shiningPhoenixEnforcer);
	cout << "Shining Phoenix Enforcer tiene ahora: "
			<< shiningPhoenixEnforcer->get_energy() << " de " << energy << endl;

	delete shiningPhoenixEnforcer;
	delete shiningFlareWingman;
}

/**/
int main() {
	test_a();
	test_b();
	return 0;
}
