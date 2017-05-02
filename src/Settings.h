#pragma once
#include "timer.h"
#include <iostream>

class Settings
{

	static Settings* _pInstance;
public:

	Settings();

	float enemySpeed = 10;
	float barrierSpeed = 10;
	float powerSpeed = 10;
	float bulletSpeed = 15;
	float particleSpeed = 30;
	float shipSpeed = 10;
	int state = 1;
	int endlessSpeedFrac = 320;
	int endlessEnemyNum = 5;
	int levelNum = 5;
	int loadedLevel = 0;
	bool easy = false;
	bool medium = false;
	bool hard = false;
	bool endless = false;
	bool howToPlay = false;
	bool backButton = false;
	bool mouseIsPressed = false;
	bool mouseIsReleased = false;
	bool generatingLevels = true;
	bool gameOver = false;
	bool win = false;
	bool movingUp = false;
	bool movingDown = false;

	bool superBullet = false;
	bool slowMo = false;
	bool spreadBullet = false;
	bool autoShoot = false;

	Timer timer;
	static Settings* getInstance();

	~Settings() { std::cout << "Settings Deleted" << std::endl; }


};