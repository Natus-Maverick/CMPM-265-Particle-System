#include "Particle.h"

float circ_easeIn(float t, float b, float c, float d)
{
	return -c * (sqrt(1 - (t /= d)*t) - 1) + b;
}

float circ_easeOut(float t, float b, float c, float d) {
	return c * sqrt(1 - (t = t / d - 1)*t) + b;
}

float circ_easeInOut(float t, float b, float c, float d) {
	if ((t /= d / 2) < 1) return -c / 2 * (sqrt(1 - t*t) - 1) + b;
	return c / 2 * (sqrt(1 - t*(t -= 2)) + 1) + b;
}

float bounce_easeOut(float t, float b, float c, float d) {
	if ((t /= d) < (1 / 2.75f)) {
		return c*(7.5625f*t*t) + b;
	}
	else if (t < (2 / 2.75f)) {
		float postFix = t -= (1.5f / 2.75f);
		return c*(7.5625f*(postFix)*t + .75f) + b;
	}
	else if (t < (2.5 / 2.75)) {
		float postFix = t -= (2.25f / 2.75f);
		return c*(7.5625f*(postFix)*t + .9375f) + b;
	}
	else {
		float postFix = t -= (2.625f / 2.75f);
		return c*(7.5625f*(postFix)*t + .984375f) + b;
	}
}

float bounce_easeIn(float t, float b, float c, float d) {
	return c - bounce_easeOut(d - t, 0, c, d) + b;
}

float bounce_easeInOut(float t, float b, float c, float d) {
	if (t < d / 2) return bounce_easeIn(t * 2, 0, c, d) * .5f + b;
	else return bounce_easeOut(t * 2 - d, 0, c, d) * .5f + c*.5f + b;
}

Particle::Particle(Vector2f pos, Vector2f size, float speed, float alpha, float rot, float lifetime, int b, int tt)
{
	this->pos = pos;
	this->startPos = pos;
	this->vel = Vector2f (speed * cos(alpha), speed * sin(alpha));
	this->startVel = vel;	
	this->size = size;
	this->startSize = size;		
	this->lifetime = lifetime;
	this->behavior = b;
	this->alive = true;
	this->rot = rot;
	rect.setOrigin(size.x /2, size.y /2);
	rect.setPosition(pos);
	rect.setTexture(&tts[tt]);
	timePassed = 0;
	switch (behavior){
	case 0:
		this->endVel = vel * 8.0f;
		this->endSize = size * 0.1f;
		break;
	case 1:
		this->endVel = vel * 6.0f;
		this->endSize = size * 3.0f;
		break;
	case 2:
		this->endVel = vel * 0.9f;
		this->endSize = size * 3.0f;
		break;
	}
}

void Particle::update() {
	float dt = clock.restart().asSeconds();
	timePassed += dt;
	if (timePassed >= lifetime)
	{
		alive = false;
	}
	pos += vel;
	vel = startVel + (timePassed / lifetime) * (endVel - startVel);
	rect.setPosition(pos);
	//size = startSize + (timePassed / lifetime) * (endSize - startSize);
	switch (behavior) {
	case 0:
		size.x = bounce_easeIn(timePassed, startSize.x, endSize.x - startSize.x, lifetime);
		size.y = bounce_easeIn(timePassed, startSize.y, endSize.y - startSize.y, lifetime);
		break;
	case 1:
		size.x = bounce_easeOut(timePassed, startSize.x, endSize.x - startSize.x, lifetime);
		size.y = bounce_easeOut(timePassed, startSize.y, endSize.y - startSize.y, lifetime);
		break;
	case 2:
		size.x = circ_easeIn(timePassed, startSize.x, endSize.x - startSize.x, lifetime);
		size.y = circ_easeIn(timePassed, startSize.y, endSize.y - startSize.y, lifetime);
		break;
	}
	rect.setSize(size);
	rect.setOrigin(size.x / 2, size.y / 2);
	float degree = bounce_easeOut(timePassed, 0, rot, lifetime);
	rect.setRotation(degree);
}

void Particle::draw(RenderWindow& window) {
	window.draw(rect);
}