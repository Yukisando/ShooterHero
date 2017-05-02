#include "Ship.h"

Ship::Ship() {
	// Set the initial colour
	colour.set(ofRandom(255), ofRandom(255), ofRandom(255), 0);
	shipColour.set(255, 255, 255);

	y = ofGetWindowHeight() / 4;
	x = ofGetWindowWidth() / 8;

}

void Ship::drawHitBox() {//draws the hit box
	y = ofGetMouseY();
	ofSetColor(colour);
	ofRect(x, y, 50, 50);
	ofSetColor(shipColour);
}

void Ship::menu() {//draws the hit box
	y += ofRandom(-1, 2);
	x += ofRandom(-1, 3);
}

void Ship::drawHitboxSmooth(Settings *setThings) {//draws the hit box

	if (y < ofGetMouseY() - 25 && (y + setThings->shipSpeed < ofGetMouseY() - 25)) {
		y += setThings->shipSpeed;
		setThings->movingDown = false;
		setThings->movingUp = true;
	}
	else if (y > ofGetMouseY() - 25 && (y + setThings->shipSpeed > ofGetMouseY() - 25)) {
		y -= setThings->shipSpeed;
		setThings->movingDown = true;
		setThings->movingUp = false;
	}
	else {
		y = ofGetMouseY() - 25;
		setThings->movingDown = false;
		setThings->movingUp = false;
	}

	ofSetColor(colour);
	ofRect(x, y, 50, 50);
	ofSetColor(shipColour);
}


