#pragma once
#ifndef Barrier_h
#define Barrier_h

#include "Ship.h"
#include "ofMain.h"
#include "bullet.h"
#include "settings.h"


class Barrier {
public:
	// Properties
	float barrierYSize = 0;
	float bSX = 0;
	float bSY = 0;
	float x = 0;
	float y = 0;
	float barrierYPos = 0;
	Ship *theShip;
	Bullet *bullets;
	Settings *setThings;

	// Constructor
	Barrier(float barrierSize, float u, Ship *theShip, Settings *setThings);

	// Methods
	void move();
	void draw();

	// Properties
	ofColor colour;
};
#endif