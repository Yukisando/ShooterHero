#include "particle.h"


Particle::Particle(Ship *theShip) {

	colour.set(ofRandom(150, 255), 0, ofRandom(150, 255));
	thrusterColor.set(210, 160, 0, 130);
	// Initial x position of the ball
	x = ofGetWindowWidth() + ofRandom(100);
	thrustersX = theShip->x + ofRandom(0, 15);
	y = ofRandom(ofGetWindowHeight());

};

void Particle::move(Ship *theShip, Settings *setThings) {
	incrementSin++;
	particleSpeedIncrease++;
	if (setThings->state == 1) {
		x -= setThings->particleSpeed + 30;//makes them move
	}
	if (setThings->easy) {
		x -= setThings->particleSpeed;//makes them move
	}
	if (setThings->medium) {
		x -= setThings->particleSpeed + 10;//makes them move
	}
	if (setThings->hard) {
		x -= setThings->particleSpeed + 20;//makes them move
	}
	if (setThings->endless) {
		x -= setThings->particleSpeed + particleSpeedIncrease;//makes them move
	}

	thrustersX -= setThings->particleSpeed;
	y += sin(((2 * PI)*incrementSin) / 20) + ofRandom(-5, 5);
}

void Particle::draw(Ship *theShip, Settings *setThings) {
	//draws the particles
	ofSetColor(colour);
	ofDrawCircle(x, y, ofRandom(2, 3));

	//draws the thrusters
	ofSetColor(thrusterColor);
	ofDrawRectangle(thrustersX, theShip->y + 25 + ofRandom(-15, -5), ofRandom(15, 25), 2);
	ofDrawRectangle(thrustersX, theShip->y + 25 + ofRandom(5, 15), ofRandom(15, 25), 2);
}