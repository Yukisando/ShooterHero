#ifndef enemy_h
#define enemy_h

#include "Ship.h"
#include "ofMain.h"
#include "bullet.h"
#include "settings.h"


class Enemy {
public:
	// Properties
	float enemySize = 0;
	float eSX = 0;
	float eSY = 0;
	float incrementSin = 0;
	float x = 0;
	float y = 0;
	float enemyYPos = 0;
	float health = 100;
	bool dead = false;
	bool touched = false;
	bool enemyTouched = false;
	Ship *theShip;
	Bullet *bullets;
	Settings *setThings;

	// Constructor
	Enemy(float enemySize, float u, Ship *theShip, Bullet *theBullet, Settings *setThings);

	// Methods
	void move();
	void draw();
	float getSize();
	float getHealth();
	void isHit(float damage);

	bool isDead();

	// Properties
	ofColor colour;
};
#endif