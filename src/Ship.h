#pragma once
#ifndef Ship_h
#define Ship_h
#include "ofMain.h"
#include "settings.h"

class Ship {
public:
	// Properties
	int x;
	int y;

	// Constructor
	//Ship(Settings *setThings);
	Ship();

	// Methods

	void drawHitBox();
	void drawHitboxSmooth(Settings *setThings);
	void menu();

	// Properties
	ofColor colour, shipColour;
};
#endif