#pragma once
#include "Global.h"

using namespace sf;

class Particle
{
public:
	
	Particle(Vector2f pos, Vector2f size, float speed, float alpha, float rot, float lifetime, int b, int tt);

	void update();
	void draw(RenderWindow& window);

	RectangleShape rect;
	Vector2f startPos;
	Vector2f pos;
	Vector2f vel;
	Vector2f dir;
	Vector2f size;
	Vector2f startVel, startSize;
	Vector2f endVel, endSize;
	float lifetime;
	float timePassed;
	float rot;
	int behavior;
	bool alive;
	Clock clock;
};