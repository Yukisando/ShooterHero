#include "Level.h"
#include <cstdlib>


Level::Level() {
	//constructor
	cout << "Levels Initialized" << endl;
}

void Level::levelRead(string level, Settings *setThings, vector<Enemy*> enemies, vector<Barrier> *barriers) {//pushs all the enemies in the vector at each level
	std::ifstream levels(ofToDataPath(level).c_str()); // looks for a file in the data folder. 
	if (levels.is_open()) {
		cout << "Loading : " << level << endl;//checks that it loads properly
		while (levels >> eY >> eS && eY != 10000) {//grabs the values from the list to push
			enemies.push_back(&Enemy(eY, eS, theShip, &theBullet, setThings)); // assigns the locations of all the enemies as well as how many of them
		}
		while (levels >> bY >> bS) {
			barriers->push_back(Barrier(bY, bS, theShip, setThings)); // assigns the locations of all the enemies as well as how many of them
		}
		levels.close();//closes the file
		cout << enemies.size() << " enemies created." << endl;//tells how many enemies will be in the level
		cout << barriers->size() << " barriers created." << endl;//tells how many barriers will be in the level
	}
	else {
		cout << "Could not load file" << endl; // prevents any crashs if it cannot read the file
	}
}

void Level::nextLevel(Settings *setThings, vector<Enemy*> enemies, vector<Barrier> *barriers) {
	string j = to_string(setThings->loadedLevel); //Loads the next level
	levelRead("levels\\level(" + j + ").txt", setThings, enemies, barriers);
	setThings->loadedLevel++;
}

void Level::Generate(int levelNum, Settings *setThings) {

	string path = std::string("rm ") + ofToDataPath("levels\\*.txt"); //Deletes the values inside each level. Prevents the values from stacking at each program starts
	levelNumber = levelNum;
	ePos = 0;
	eSize = 0;
	bPos = 0;
	bSize = 0;
	for (int lvl = 1; lvl <= levelNumber; lvl++) {

		myfile.open(ofToDataPath("levels\\level(" + to_string(lvl) + ").txt")); //Goes through all the generated levels and writes into them the values.

		if (setThings->easy) { //The harder the difficutly, the more enemies you will encounter and the smaller they will be.
			enemyNumber = 5 + (int)ofRandom(2);
			barrierNumber = 1;
		}
		else if (setThings->medium) {
			enemyNumber = 8 + (int)ofRandom(2);
			barrierNumber = 2;
		}
		else if (setThings->hard) {
			enemyNumber = 10 + (int)ofRandom(3);
			barrierNumber = 3;
		}

		for (int j = 0; j <= enemyNumber - 1; j++) { //Writes the different values and add them to a list for each level. 
			if (setThings->easy) { //Adjusts the size of the number of enemies according to the difficulty
				ePos = (int)ofRandom(ofGetWindowHeight());
				eSize = (int)ofRandom(10) + 30;
			}
			else if (setThings->medium) {
				ePos = (int)ofRandom(ofGetWindowHeight());
				eSize = (int)ofRandom(10) + 20;
			}
			else if (setThings->hard) {
				ePos = (int)ofRandom(ofGetWindowHeight());
				eSize = (int)ofRandom(10) + 15;
			}
			myfile << ePos << " " << eSize << endl;
		}
		myfile << 10000 << " " << 10000 << endl;

		for (int i = 0; i <= barrierNumber - 1; i++) {
			if (setThings->easy) {
				bPos = (int)ofRandom(ofGetWindowHeight() - 100);
				bSize = 150;
			}
			if (setThings->medium) {
				bPos = (int)ofRandom(ofGetWindowHeight() - 100);
				bSize = 200;
			}
			if (setThings->hard) {
				bPos = (int)ofRandom(ofGetWindowHeight() - 100);
				bSize = 250;
			}
			myfile << bPos << " " << bSize << endl;
		}
		myfile.close();
	}
}

void Level::endlessGeneration(int levelNum, Settings *setThings) {

	string path = std::string("rm ") + ofToDataPath("levels\\*.txt"); //Deletes the values inside each level. Prevents the values from stacking at each program starts
	levelNumber = levelNum;
	ePos = 0;
	eSize = 0;
	bPos = 0;
	bSize = 0;

	for (int lvl = 1; lvl < 30; lvl++) {

		myfile.open(ofToDataPath("levels\\level(" + to_string(lvl) + ").txt")); //Goes through all the generated levels and writes into them the values.

		enemyNumber = 10 + (int)ofRandom(3);
		barrierNumber = 1 + (int)ofRandom(3);


		for (int j = 0; j <= enemyNumber - 1; j++) { //Writes the different values and add them to a list for each level. 

			ePos = (int)ofRandom(ofGetWindowHeight());
			eSize = (int)ofRandom(15) + 15;

			myfile << ePos << " " << eSize << endl;
		}

		myfile << 10000 << " " << 10000 << endl;

		for (int i = 0; i <= barrierNumber - 1; i++) {

			bPos = (int)ofRandom(ofGetWindowHeight() - 100);
			bSize = 150;

			myfile << bPos << " " << bSize << endl;
		}
		myfile.close();
	}
}

void Level::threadedEndlessGeneration(int levelNum, Settings *setThings) {
	try {
		levelNumber = levelNum;
		ePos = 0;
		eSize = 0;
		bPos = 0;
		bSize = 0;

		for (int lvl = 30; lvl <= levelNum; lvl++) {
			string path = std::string("rm ") + ofToDataPath("levels\\level(" + to_string(lvl) + ").txt"); //Deletes the values inside each level. Prevents the values from stacking at each program starts
			myfile.open(ofToDataPath("levels\\level(" + to_string(lvl) + ").txt")); //Goes through all the generated levels and writes into them the values.

			enemyNumber = 10 + (int)ofRandom(3);
			barrierNumber = 1 + (int)ofRandom(3);


			for (int j = 0; j <= enemyNumber - 1; j++) { //Writes the different values and add them to a list for each level. 

				ePos = (int)ofRandom(ofGetWindowHeight());
				eSize = (int)ofRandom(15) + 15;

				myfile << ePos << " " << eSize << endl;
			}

			myfile << 10000 << " " << 10000 << endl;

			for (int i = 0; i <= barrierNumber - 1; i++) {

				bPos = (int)ofRandom(ofGetWindowHeight() - 100);
				bSize = 150;

				myfile << bPos << " " << bSize << endl;
			}
			myfile.close();

		}
	}
	catch (...)
	{
		cout << "Program exited before file creation was completed" << endl; //Attempts to ignore the break if you stop the program before the endlessGeneration thread is done.
	}
}
