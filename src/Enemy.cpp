#include "enemy.h"


Enemy::Enemy(float _y, float _s, Ship *theShip, Bullet *theBullet, Settings *setThings) :setThings(setThings) {

	colour.set(ofRandom(10), ofRandom(0 - 100), ofRandom(100 - 255));
	// Initial x position of the ball
	x = ofGetWindowWidth() + ofRandom(100);

	// Initial y position of the ball
	enemyYPos = _y;

	enemySize = _s;
};

void Enemy::move() {


	if (setThings->easy) {
		setThings->enemySpeed = ofGetWindowWidth() / 400;
	}
	else if (setThings->medium) {
		setThings->enemySpeed = ofGetWindowWidth() / 320;
	}
	else if (setThings->hard) {
		setThings->enemySpeed = ofGetWindowWidth() / 290;
	}
	else if (setThings->endless) {
		setThings->enemySpeed = ofGetWindowWidth() / setThings->endlessSpeedFrac;
	}

	incrementSin++;
	eSX = enemySize + sin(((2 * PI)*incrementSin) / 60 + 10) * 2;//make them lively
	eSY = enemySize + sin(((2 * PI)*incrementSin) / 60 + 10) * 5;
	x -= setThings->enemySpeed;//makes them move
	y = enemyYPos;

	if (setThings->easy) {
		health = 100;
	}
	if (setThings->medium) {
		health = 200;
	}
	if (setThings->hard) {
		health = 300;
	}
	if (setThings->endless) {
		health = 100;
	}
}

void Enemy::draw() {//draws the enemies
	ofSetColor(colour);
	ofDrawEllipse(x, y, eSX, eSY);
}

float Enemy::getSize() {
	return enemySize;
}
float Enemy::getHealth() {
	return health;
}

void Enemy::isHit(float damage) {

	health -= damage;

	if (health <= 0) {
		dead = true;
	}
}

bool Enemy::isDead() {
	return dead;
}