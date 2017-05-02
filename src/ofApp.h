#pragma once

#include "ofMain.h"
#include "Ship.h"
#include "enemy.h"
#include "bullet.h"
#include "power.h"
#include "button.h"
#include "settings.h"
#include "Level.h"
#include "particle.h"

class ofApp : public ofBaseApp {

public:
	ofApp();
	void setup();
	void update();
	void draw();
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void keyPressed(int key);
	void nextLevel();
	void restart();
	void powerReset();
	void powerUps();
	void powerUpString();
	void musicUpdate();
	void errorCatching();

	float edgeX;
	float edgeY;
	float randomPower;
	float incrementSin = 0;
	float animation = 0;
	float randomEvent = 0;
	float titleGlowAnimation = 0;
	float levelGlowAnimation = 0;
	float cursorSX = 0;
	float cursorSY = 0;

	int track = 0;

	bool restartPressed = false;
	bool bulletFired = false;
	bool firstShot = true;
	bool canFire = false;
	bool enemyTouched = false;
	bool endingSoundsPlayed = false;
	bool timerStarted = false;
	bool trackSelectionPressed = false;
	bool pickedASong = false;

	Timer timerSB, timerSS, timerAS, timerSM, timerSpB, timer;
	Settings *setThings;
	Level level;
	Ship *theShip = new Ship();
	vector<Bullet> bullets;
	vector<Enemy*> enemies;
	vector<Power> powers;
	vector<Barrier> barriers;
	vector<Particle> particules;
	ofColor levelColor;
	ofTrueTypeFont myFont, myFont2, myFont3, myFont4, myFont5;
	ofSoundPlayer theme, gameover, win, winEndless, death1, powerUp, shoot1, shoot2, shoot3, easy, windows, hard;
	Button easyButton, mediumButton, hardButton, endlessButton, restartButton, howToPlayButton, backButton, quitButton, trackSelectionButton;
	ofImage shipSprite1, enemySprite, shipSprite2, shipSprite3, shipSprite4, shipSprite5;

	string actualLevel;
	string score;
	string superBulletString = "Bigger bullets";
	string slowMoString = "Slow Mo";
	string spreadBulletString = "Shotgun";
	string autoShootString = "Automatic Fire";
};
