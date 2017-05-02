#ifndef bullet_h
#define bullet_h

#include "ofMain.h"
#include "ship.h"
#include "settings.h"

class Bullet {
public:
	// Properties
	float x;
	float y;

	// Constructor
	Bullet(Ship *theShip);
	Bullet();

	// Methods
	void fire();
	void draw();
	void superBullet();
	void slowMo();
	void spreadBullet();

	// Properties
	ofColor colour;
	Ship *theShip;
	Settings *setThings;
};
#endif