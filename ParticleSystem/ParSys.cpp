#include "ParSys.h"


ParSys::ParSys(Vector2f emitter, float rate, int alpha, Vector2f size, float minvel,int b, int tt)
{
	this->emitter = emitter;
	this->rate = rate;
	this->minvel = minvel;
	this->size = size;
	this->tt= tt;
	this->max = 10;
	this->alpha = alpha;
	this->behavior = b;
	this->keyTimer = 0;
}

void ParSys::draw(RenderWindow& window) {
	for (Particle* p : particles)
	{
		p->draw(window);
	}
}

void ParSys::update() {

	if (Keyboard::isKeyPressed(Keyboard::S) && keyTimer > 0.05f) {
		max++;
		rate *= 0.8f;
		keyTimer = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::A) && keyTimer > 0.05f) {
		max--;
		rate *= 1.2f;
		keyTimer = 0;
	}

	float dt = clock.restart().asSeconds();
	keyTimer += dt;
	timePassed += dt;
	
	for (Particle* p : particles)
	{
		p->update();
	}

	if (timePassed >= rate && particles.size() < max)
	{
		particles.push_back(createParticles());
		timePassed = 0;
	}
	kill();
}

void ParSys::kill() {
	for (auto it = particles.begin(); it != particles.end(); ++it)
	{
		if (!(*it)->alive)
		{
			Particle* p = *it;
			it = particles.erase(it);
			delete p;
			continue;
		}
	}
}
Particle* ParSys::createParticles() {
	float speed = rand() % 3 * 0.005f + minvel;
	float life = rand() % 100 * 0.005f + 2.0f;
	float agl = ((rand() % 90) + alpha) * 3.14f / 180.f;
	float rot = rand() % 360;
	return new Particle(emitter, size, speed, agl, rot, life, behavior, tt);
}
