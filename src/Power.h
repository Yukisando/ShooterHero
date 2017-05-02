#ifndef power_h
#define power_h

#include "Ship.h"
#include "ofMain.h"
#include "settings.h"


class Power {
public:

	//Properties
	float incrementSin = 0;
	float enemySize = 0;
	int x = 0;
	int y = 0;
	Ship *theShip;
	Settings *setThings;
	Timer timerSB, timerSpB, timerAS, timerSM;

	// Constructor
	Power(float enemySize, Ship *theShip, Settings *setThings);

	// Methods
	void move();
	void draw();
	void title();
	void startTimers();

	// Properties
	ofColor colour;
	ofTrueTypeFont powerUp;
};
#endif