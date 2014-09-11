/*
 /*
 * pruebaEngine.cpp
 *
 *  Created on: 21/8/2014
 *      Author: EscDemi
 */

#include "pruebaEngine.h"
#include "engine/Graphics.h"


pruebaEngine::pruebaEngine(const char *title) : Game(title) {
	this->testImage = NULL;
	this->spriteSheet = NULL;
	this->subSprite = NULL;
	this->animationTest = NULL;
	this->animation = NULL;

	rotation = 0;
}

void pruebaEngine::init(){

	this->testImage = new Image("Resources/a.png");
	this->spriteSheet = new SpriteSheet("Resources/tilea3.png", 64 ,64);
	this->subSprite = spriteSheet->getSubImage(0, 1);

	this->animationTest = new SpriteSheet("Resources/anim.png", 21, 40);
	this->animation = new Animation();

	for(int x = 0; x < 8; x++){
		this->animation->addFrame(this->animationTest->getSubImage(x, 0), 75);
	}

	b2Vec2 gravity(0,9.8);

	this->world = new b2World(gravity);




		// Define the dynamic body. We set its position and call the body factory.
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(10.0f, 30.0f);
		bodyDef.angularVelocity = 3.14;
		bodyDef.linearVelocity = b2Vec2(50, -100);
		this->body = world->CreateBody(&bodyDef);

		// Define another box shape for our dynamic body.
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(1.0f, 1.0f);

		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;

		// Set the box density to be non-zero, so it will be dynamic.
		fixtureDef.density = 100.0f;

		// Override the default friction.
		fixtureDef.friction = 0.3f;



		// Add the shape to the body.
		body->CreateFixture(&fixtureDef);




}

void pruebaEngine::exit(){
	delete testImage;
	delete spriteSheet;
	delete subSprite;
	delete animationTest;
	delete animation;
}

void pruebaEngine::render(Graphics *g){

	g->drawImage(this->subSprite, body->GetPosition().x * 10, body->GetPosition().y * 10, body->GetAngle() * 10);
	g->drawAnimation(this->animation, 100, 100);

	/*
	g->drawImage(testImage, 0, 50);

	g->drawRect(60, 20, 20, 20);



	g->setColor(255, 0, 0);

	g->drawLine(20, 60, 80, 60);
	g->drawPoint(90, 60);

	fpsText.str("");
	fpsText<<this->getFPS()<< " FPS";

	g->drawText(10, 10, fpsText.str().c_str());
	rotation+=0.05f;
	g->drawFillRect(400, 20, 30, 20);

	g->drawAnimation(this->animation, 100, 100);
	*/
}

void pruebaEngine::keyEvent(SDL_Event e){


}


void pruebaEngine::update(unsigned int delta){
	float time = ((float) delta) / 1000;
	world->Step(time, 6, 2);

}

pruebaEngine::~pruebaEngine() {
	// TODO Auto-generated destructor stub
}
