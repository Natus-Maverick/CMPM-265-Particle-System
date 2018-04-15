#pragma once

#include "Global.h"
#include "Particle.h"

using namespace sf;

class ParSys
{
public:

	ParSys(Vector2f emmiter, float rate, int alpha, Vector2f size, float minvel, int b, int tt);
	void update();
	void kill();
	void draw(RenderWindow& window);
	Particle* createParticles();
	Vector2f emitter;
	vector<Particle*> particles;
	Vector2f size;
	int tt;
	int max;
	float rate;
	int alpha;
	int behavior;
	float minvel;
	float timePassed;
	float keyTimer;
	Clock clock;
};
