#include "settings.h"
#include "Ship.h"
#include "enemy.h"
#include "bullet.h"
#include "ofMain.h"
#include "Barrier.h"

class Level {


public:
	
	Level();
	int eS, eY, bS, bY;

	Bullet theBullet;
	Ship *theShip;

	int levelNumber;
	float ePos = 0, eSize = 0, bPos = -50, bSize = 0;
	int enemyNumber, barrierNumber;
	ofstream myfile;

	void nextLevel(Settings *setThings, vector<Enemy*> enemies, vector<Barrier> *barriers);
	void levelRead(string level, Settings *setThings, vector<Enemy*> enemies, vector<Barrier> *barriers);
	void Generate(int levelNum, Settings *setThings);
	void endlessGeneration(int levelNum, Settings *setThings);
	void threadedEndlessGeneration(int levelNum, Settings *setThings);
};

