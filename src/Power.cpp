#include "power.h"


Power::Power(float _y, Ship *theShip, Settings *setThings) :setThings(setThings) {

	colour.set(ofRandom(200, 255), ofRandom(0, 255), ofRandom(200, 255));
	// Initial x position of the ball
	x = ofGetWindowWidth();

	// Initial y position of the ball
	y = _y;
};

void Power::move() {

	if (setThings->easy) {
		setThings->powerSpeed = ofGetWindowWidth() / 180;
		incrementSin++;
		enemySize = sin(((2 * PI)*incrementSin) / 60) * 10 + 20;
	}
	else if (setThings->medium) {
		setThings->powerSpeed = ofGetWindowWidth() / 170;
		incrementSin++;
		enemySize = sin(((2 * PI)*incrementSin) / 60) * 10 + 10;
	}
	else if (setThings->hard) {
		setThings->powerSpeed = ofGetWindowWidth() / 150;
		incrementSin++;
		enemySize = sin(((2 * PI)*incrementSin) / 60) * 10 + 5;
	}
	else if (setThings->endless) {
		setThings->powerSpeed = ofGetWindowWidth() / 150;
		incrementSin++;
		enemySize = sin(((2 * PI)*incrementSin) / 60) * 10 + 5;
	}


	x -= setThings->powerSpeed;//makes them move
}

void Power::draw() {//draws the enemies
	ofSetColor(colour);
	ofDrawRectangle(x, y, enemySize, enemySize);
}

void Power::title() {
	string superBullet = "Bigger bullets";
	string slowMo = "Slow Mo";
	string spreadBullet = "Shotgun";
	string autoShoot = "Automatic Fire";

	//sets the title for the powerUps

	if (setThings->superBullet) {
		powerUp.drawString(superBullet, ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 8);
		if (timerSB.elapsedTime() >= 1.5) {
			timerSB.stop();
			timerSB.reset();
		}
	}
	if (setThings->spreadBullet) {
		powerUp.drawString(spreadBullet, ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 8);
		if (timerSpB.elapsedTime() >= 1.5) {
			timerSpB.stop();
			timerSpB.reset();
		}
	}
	if (setThings->autoShoot) {
		powerUp.drawString(autoShoot, ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 8);
		if (timerAS.elapsedTime() >= 1.5) {
			timerAS.stop();
			timerAS.reset();
		}
	}
	if (setThings->slowMo) {
		powerUp.drawString(slowMo, ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 8);
		if (timerSM.elapsedTime() >= 1.5) {
			timerSM.stop();
			timerSM.reset();
		}
	}
}

void Power::startTimers() {
	if (setThings->superBullet) {
		timerSB.start();
	}
	if (setThings->autoShoot) {
		timerAS.start();
	}
	if (setThings->spreadBullet) {
		timerSpB.start();
	}
	if (setThings->slowMo) {
		timerSM.start();
	}
}