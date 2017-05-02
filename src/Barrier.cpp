#include "Barrier.h"


Barrier::Barrier(float _y, float _s, Ship *theShip, Settings *setThings) :setThings(setThings) {

	colour.set(ofRandom(10), ofRandom(0 - 100), ofRandom(100 - 255));
	// Initial x position of the ball
	x = ofGetWindowWidth() + ofRandom(50);

	// Initial y position of the ball
	barrierYPos = _y;

	barrierYSize = _s;
};

void Barrier::move() {

	if (setThings->easy) {
		setThings->barrierSpeed = ofGetWindowWidth() / 220;
	}
	else if (setThings->medium) {
		setThings->barrierSpeed = ofGetWindowWidth() / 200;
	}
	else if (setThings->hard) {
		setThings->barrierSpeed = ofGetWindowWidth() / 150;
	}
	else if (setThings->endless) {
		setThings->barrierSpeed = ofGetWindowWidth() / setThings->endlessSpeedFrac;
	}

	bSX = 15;
	bSY = barrierYSize;
	x -= setThings->barrierSpeed;//makes them move
	y = barrierYPos;
}

void Barrier::draw() {//draws the enemies
	ofSetColor(colour);
	ofDrawRectangle(x, y, bSX, bSY);
}