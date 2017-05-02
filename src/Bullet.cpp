#include "bullet.h"

Bullet::Bullet(Ship *_theShip) :theShip(_theShip) {//constructor
	colour.set(ofRandom(255), ofRandom(255), ofRandom(255), 200);//random color everytime.

	// Initial x position of the ball
	x = theShip->x + 10;
	// Initial y position of the ball
	y = theShip->y + 25;
}

Bullet::Bullet() {}//Empty constructor

void Bullet::draw() {//draws he bullets
	ofSetColor(colour);
	ofDrawRectangle(x, y, 13, 7);
}

void Bullet::fire() {//just makes the bullet go faster
	x += 12;
	y += (int)ofRandom(-5, 5);
}

void Bullet::slowMo() {//just makes the bullet go faster
	x += 6;
	y += (int)ofRandom(-5, 5);
}

void Bullet::spreadBullet() {//just makes the bullet go faster
	x += 12;
	y += (int)ofRandom(-20, 20);
}

void Bullet::superBullet() {
	ofSetColor(colour);
	ofDrawRectangle(x, y, 20, 25);
}