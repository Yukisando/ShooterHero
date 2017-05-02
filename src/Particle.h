#pragma once
#include "ofMain.h"
#include "settings.h"
#include "Ship.h"

class Particle
{
public:
	Particle(Ship *theShip);

	// Properties
	float x = 0;
	float y = 0;
	float thrustersX = 0;
	float incrementSin = 0;
	float particleSpeedIncrease = 0;

	// Methods
	void move(Ship *theShip, Settings *setThings);
	void draw(Ship *theShip, Settings *setThings);

	// Properties
	ofColor colour, thrusterColor;
	Settings *setThings;
};