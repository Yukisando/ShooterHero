#include "ofApp.h"
#include <cstdlib>
#include <string>
using namespace std;

ofApp::ofApp() {}


void ofApp::setup() {
	cout << "Game running..." << endl;

	setThings = Settings::getInstance();
	setThings->easy = false;
	setThings->medium = false;
	setThings->hard = false;

	shipSprite1.load(ofToDataPath("Images\\ship.png"));//loads all the sprites for the ship
	shipSprite2.load(ofToDataPath("Images\\ship2.png"));
	shipSprite3.load(ofToDataPath("Images\\ship3.png"));
	shipSprite4.load(ofToDataPath("Images\\ship4.png"));
	shipSprite5.load(ofToDataPath("Images\\ship5.png"));

	shipSprite1.resize(50, 50);//resizes all the sprites for the ship
	shipSprite2.resize(50, 50);
	shipSprite3.resize(50, 50);
	shipSprite4.resize(50, 50);
	shipSprite5.resize(50, 50);

	shipSprite1.rotate90(1);//rotates all the sprites for the ship
	shipSprite2.rotate90(1);
	shipSprite3.rotate90(1);
	shipSprite4.rotate90(1);
	shipSprite5.rotate90(1);

	enemySprite.load(ofToDataPath("Images\\enemy.png")); //loads the enemy sprite that may be used later on. For now I like the simple version
	enemySprite.resize(10, 10); //resize the enemy sprite
	enemySprite.rotate90(1); //rotates the enmy sprite

	//loads all the sounds and fonts for the game.
	theme.loadSound(ofToDataPath("Sounds\\theme.mp3"));//Main theme
	windows.loadSound(ofToDataPath("Sounds\\windows.mp3"));//Main theme
	hard.loadSound(ofToDataPath("Sounds\\hard.mp3"));//Main theme
	win.loadSound(ofToDataPath("Sounds\\yay.mp3"));//winning theme
	winEndless.loadSound(ofToDataPath("Sounds\\omgmlg.mp3"));//Win in endless theme (Easter egg)
	gameover.loadSound(ofToDataPath("Sounds\\gameover.mp3")); //Shame shame (sample I took form game of thrones)
	death1.loadSound(ofToDataPath("Sounds\\death1.wav")); //when an enemy dies
	shoot1.loadSound(ofToDataPath("Sounds\\shoot1.wav")); //when you shoot
	shoot2.loadSound(ofToDataPath("Sounds\\shoot2.wav")); //when you shoot with power ups
	shoot3.loadSound(ofToDataPath("Sounds\\shoot3.wav"));
	powerUp.loadSound(ofToDataPath("Sounds\\powerUp.wav"));//when you grab a power up

	myFont.loadFont("Fonts\\TETRIS.TTF", 60); //loads all the fonts
	myFont4.loadFont("Fonts\\TETRIS.TTF", 80);
	myFont5.loadFont("Fonts\\TITLE.TTF", 20);
	myFont2.loadFont("Fonts\\TITLE.TTF", 30);
	myFont3.loadFont("Fonts\\TITLE.TTF", 20);

	theme.setLoop(true);//loops the main soundtrack
	theme.setVolume(0.2);
	easy.setLoop(true);//loops the main soundtrack
	easy.setVolume(0.2);
	windows.setLoop(true);//loops the main soundtrack
	windows.setVolume(0.2);
	hard.setLoop(true);//loops the main soundtrack
	hard.setVolume(0.2);

	death1.setVolume(0.5);//sets volume for death sounds
	powerUp.setVolume(0.7);
	win.setVolume(0.5);
	winEndless.setVolume(0.5);
	gameover.setVolume(0.2);//reduces the volume to "barely not way too loud..."
	shoot1.setVolume(0.02);
	shoot2.setVolume(0.1);
	shoot3.setVolume(0.2);

	theme.play();// starts it right from the the begining.

	setThings->loadedLevel = 1;
	firstShot = true;
	canFire = false;

	ofEnableSmoothing(); //A little bit of AA I think ?
	ofSetFrameRate(59);// fixed framerate

	setThings->state = 1; //starts menu state

	//Clears all vectors at start.
	powers.clear();
	bullets.clear();
	enemies.clear();
}


//--------------------------------------------------------------
void ofApp::update() {

	errorCatching();

	//Sets up all the buttons
	howToPlayButton.setup(50, edgeY - 50, 183, 25, "How to play?", ofColor(0, 50, 150, 200), ofColor(0, 30, 200), &myFont3);
	quitButton.setup(edgeX - 114, edgeY - 50, 62, 25, "Quit", ofColor(0, 50, 150, 200), ofColor(0, 30, 200), &myFont3);
	trackSelectionButton.setup(edgeX - 209, edgeY - 100, 157, 25, "Next track", ofColor(0, 50, 150, 200), ofColor(0, 30, 200), &myFont3);

	easyButton.setup(edgeX / 2 - 150, edgeY / 2, 66, 25, "Easy", ofColor(0, 50, 150, 200), ofColor(0, 30, 200), &myFont3);
	mediumButton.setup(edgeX / 2 - 53, edgeY / 2, 106, 25, "Medium", ofColor(0, 50, 150, 200), ofColor(0, 30, 200), &myFont3);
	hardButton.setup(edgeX / 2 + 100, edgeY / 2, 70, 25, "Hard", ofColor(0, 50, 150, 200), ofColor(0, 30, 200), &myFont3);
	endlessButton.setup(edgeX / 2 - 53, edgeY / 2 + 100, 110, 25, "Endless", ofColor(0, 50, 150, 200), ofColor(0, 30, 200), &myFont3);

	//Window Related settings:
	//if (edgeY <= 900) { ofSetWindowShape(1200, 900); } //Makes sure the window does not resize to unfair proportions. 

	edgeX = ofGetWindowWidth();
	edgeY = ofGetWindowHeight();

	//Animation settings:
	incrementSin++;
	animation += sin(((2 * PI)*incrementSin) / 100); //handles the left and right animations for power ups titles.
	levelGlowAnimation += sin(((2 * PI)*incrementSin) / 200) * 220; //handles the glowing animation for power ups titles.
	titleGlowAnimation += sin(((2 * PI)*incrementSin) / 80) * 200; //handles the glowing animation for power ups titles.
	powerUps(); //

	//Menu state:
	if (setThings->state == 1) {

		//sets the number of levels to be played depending on the difficulty

		if (setThings->easy) {
			setThings->levelNum = 15;
			cout << "Easy" << " selected" << endl; // tells you how many levels are about to be played before wining.
			level.Generate(setThings->levelNum, setThings); // generates the levels in the bin/levels
			setThings->state = 2;//starts game state
		}
		if (setThings->medium) {
			setThings->levelNum = 30;
			level.Generate(setThings->levelNum, setThings);
			setThings->state = 2;
			cout << "Medium" << " selected" << endl;
		}
		if (setThings->hard) {
			setThings->levelNum = 50;
			level.Generate(setThings->levelNum, setThings);
			setThings->state = 2;
			cout << "Hard" << " selected" << endl;
		}
		if (setThings->endless) {
			setThings->levelNum = 1000;
			level.endlessGeneration(setThings->levelNum, setThings);
			thread t1(&Level::threadedEndlessGeneration, &level, setThings->levelNum, setThings); //The first 30 levels are created normaly and the rest is created while you play on a detached thread (In that case, the other 970 levels).
			if (setThings->generatingLevels) {
				t1.detach(); //Allows for the generation to keep on going while playing.
			}
			else {
				t1.join();//hitting the "quit" button instead of pressing Escape makes waits for the thread to be finished before exiting the game. Safe!
			}

			setThings->state = 2;
			cout << "Endless" << " selected" << endl;
		}
		if (setThings->howToPlay) {
			setThings->state = 4;
			setThings->backButton = false;
			cout << "How to play?" << " selected" << endl;
		}

		//draws the particules
		particules.push_back(Particle(theShip));
		particules.erase(remove_if(particules.begin(), particules.end(), [this](Particle p) {return p.x < 20; }), particules.end());
	}

	if (setThings->state == 2) {
		if (timerSS.isStarted() || timerSM.isStarted() || timerSB.isStarted() || timerAS.isStarted()) {
			cout << "SB: " << timerSB.elapsedTime() << " SM: " << timerSM.elapsedTime() << " AS: " << timerAS.elapsedTime() << " SpB: " << timerSpB.elapsedTime() << endl;
		}
		if (setThings->autoShoot && setThings->mouseIsPressed) {
			bulletFired = true;
			bullets.push_back(Bullet(theShip));//adds a bullet to the vector everytime you shoot
			if (!setThings->slowMo) {
				shoot2.play(); // plays the shot sound
			}
		}
		else {
			bulletFired = false;
		}

		for (auto& bullet : bullets) { // scans through all the bullets in vector

			if (!setThings->slowMo && !setThings->spreadBullet) {
				bullet.fire();//makes sure the bullets move as soon as they appear.
			}
			else if (setThings->slowMo) {//puts down the speed of the bullets (this makes the bullets stay on screen longer which gives a massive advantage
				bullet.slowMo();
				if (setThings->mouseIsPressed && canFire) { //play the sound
					shoot3.play();
				}
			}
			else if (setThings->spreadBullet) { //greatly increases the spread of the bullets making them less precise but also makes shooting clusters easier
				bullet.spreadBullet();
			}
		}
		for (int e = 0; e < enemies.size(); e++) {// makes the enemies move as soon as they are created
			(enemies[e])->move(); //makes all the enemies move
		}
		for (int b = 0; b < barriers.size(); b++) {// makes the barriers move as soon as they are created
			barriers[b].move(); //makes all the barriers move

			if (theShip->x + 50 >= barriers[b].x && theShip->x <= barriers[b].x + 15 && theShip->y >= barriers[b].y && theShip->y <= barriers[b].y + barriers[b].barrierYSize) {//You lose if you hit a barrier
				setThings->gameOver = true;
			}
		}

		for (int e(0); e < enemies.size(); e++) {

			if (ofDist((enemies[e])->x, enemies[e]->y, theShip->x, theShip->y) < 55) { //checks if the ship hit the ship (I chose a pretty big hit box)

				powerUp.play();
				powers.push_back(Power(ofRandom(edgeY), theShip, setThings));//spawns a new power up when your ship scavenges the enemies
				enemies.erase(enemies.begin() + e);//erases the touched
			}
		}

		for (int e(0); e < powers.size(); e++) {
			if (ofDist(powers[e].x, powers[e].y, theShip->x, theShip->y) < 55) { //detects if your ship has grabed a power UP
				randomPower = ofRandom(0, 4);//this number will be used to make any power up random

				// Enables each different power and start a different counter for each of them.
				if (randomPower <= 1 && !setThings->superBullet) {
					setThings->superBullet = true;
					timerSB.start();
					//thePower->startTimers();
					cout << "Super Bullet On " << endl;
				}
				else if (randomPower > 1 && randomPower <= 2 && !setThings->autoShoot) {
					setThings->autoShoot = true;
					timerAS.start();
					//thePower->startTimers();
					cout << "Auto Shoot On " << endl;
				}
				else if (randomPower > 2 && randomPower <= 3 && !setThings->slowMo) {
					setThings->slowMo = true;
					timerSM.start();
					//thePower->startTimers();
					cout << "Time Stoped On " << endl;
				}
				else if (randomPower > 3 && randomPower <= 4 && !setThings->spreadBullet) {
					setThings->spreadBullet = true;
					timerSpB.start();
					//thePower->startTimers();
					cout << "Spread bullet On " << endl;
				}

				powers.erase(powers.begin() + e); // erases the powers when grabed
			}
		}

		for (int b(0); b < bullets.size(); b++) {
			for (int e(0); e < enemies.size(); e++) {
				bool bulletTouchEnemy = ofDist((enemies[e])->x, (enemies[e])->y, bullets[b].x, bullets[b].y) < (enemies[e])->getSize(); //checks if a bullet has touched an enemy

				if (bulletTouchEnemy) { //checks if the bullets hit the ship (I chose a pretty big hit box
					(enemies[e])->isHit(100);
					if (setThings->superBullet) {
						(enemies[e])->isHit(100);
					}
					if ((enemies[e])->isDead() || true) {
						enemies.erase(enemies.begin() + e);
					}
				}
			}
		}


		for (int e = 0; e < enemies.size(); e++) {
			if ((enemies[e])->x < 10) {//if any of the enemy touches the edge of the screen, you lose ! Get them all !
				setThings->gameOver = true;
			}
		}
		if (enemies.size() <= 0) {
			if (setThings->loadedLevel != 1) {
				cout << "Finished" << endl; //when you finish a level and head to the next one.
			}
			nextLevel();//runs the next level straight away !
		}

		if (setThings->gameOver || setThings->win) { // sets state to 3 whether you win or lose.
			ofSoundUpdate();
			cout << "End game" << endl;
			setThings->state = 3;
		}

		//Pushing particules and random barriers:

		randomEvent++;
		if (setThings->easy) {
			if (randomEvent == 60) {
				barriers.push_back(Barrier(ofRandom(ofGetWindowHeight()), 150, theShip, setThings));
				randomEvent = 0;
			}
		}
		if (setThings->medium) {
			if (randomEvent == 50) {
				barriers.push_back(Barrier(ofRandom(ofGetWindowHeight()), 150, theShip, setThings));
				randomEvent = 0;
			}
		}
		if (setThings->hard) {
			if (randomEvent == 45) {
				barriers.push_back(Barrier(ofRandom(ofGetWindowHeight()), 150, theShip, setThings));
				randomEvent = 0;
			}
		}
		if (setThings->endless) {
			if (randomEvent == 40) {
				barriers.push_back(Barrier(ofRandom(ofGetWindowHeight()), 150, theShip, setThings));
				randomEvent = 0;
			}
		}
		if (setThings->state == 3) {
			int points = timer.elapsedTime() / 10;
			timer.stop();
			timer.reset();
			score = "Your score is:  " + to_string(points);
		}

		particules.push_back(Particle(theShip));

		// deletes off-screen elements.
		bullets.erase(remove_if(bullets.begin(), bullets.end(), [this](Bullet b) {return b.x > edgeX - 20; }), bullets.end());
		barriers.erase(remove_if(barriers.begin(), barriers.end(), [this](Barrier b) {return b.x < 5; }), barriers.end());
		powers.erase(remove_if(powers.begin(), powers.end(), [this](Power p) {return p.x < 10; }), powers.end());
		particules.erase(remove_if(particules.begin(), particules.end(), [this](Particle p) {return p.x < 20; }), particules.end());
	}

	if (restartPressed) {
		cout << "Restarting Game !" << endl;//if you press restart.
		restart();
	}

	if (setThings->state == 4) {
		if (setThings->backButton) {
			setThings->state = 1;
			setThings->howToPlay = false;
			cout << "Back" << " selected" << endl;
		}
	}

	ofHideCursor(); //Hides the cursor!
	musicUpdate();	//Updates soundtracks
}


//--------------------------------------------------------------
void ofApp::draw() {

	if (setThings->state == 1) {

		ofSoundUpdate();//makes sure the sound is playing correctly
		ofBackgroundGradient(ofColor(0, 0, 0), ofColor(40, 0, (sin(((2 * PI)*incrementSin) / 800) * 100 + 100)), OF_GRADIENT_BAR);//just a nice spacy background, try to give a small speed effect to the game.
		ofSetColor(220, 220, 220, 200);
		myFont4.drawString("Shooter Hero", edgeX / 2 - 265, edgeY / 7);//Title of the game

		easyButton.draw();//draws the buttons
		mediumButton.draw();
		hardButton.draw();
		endlessButton.draw();
		howToPlayButton.draw();
		quitButton.draw();

		//draws the menu ship
		theShip->menu();
		shipSprite3.draw(theShip->x, theShip->y);

		for (auto& particule : particules) {
			particule.draw(theShip, setThings);
			particule.move(theShip, setThings);
		}
	}

	if (setThings->state == 2) {

		ofSoundUpdate();
		ofBackgroundGradient(ofColor(0, 0, 0), levelColor, OF_GRADIENT_BAR);// draws the ingame background

		if (setThings->endless) { //the speed of the enemies increases as the levels go up in endless mode.
			setThings->endlessSpeedFrac = 320;
			if (setThings->loadedLevel >= 141) {
				setThings->endlessSpeedFrac -= 120;
			}
			else if (setThings->loadedLevel >= 101) {
				setThings->endlessSpeedFrac -= 90;
			}
			else if (setThings->loadedLevel >= 51) {
				setThings->endlessSpeedFrac -= 60;
			}
			else if (setThings->loadedLevel >= 31) {
				setThings->endlessSpeedFrac -= 30;
			}
		}

		// makes the background change according to the level
		if (setThings->loadedLevel >= 50) {
			levelColor.set(sin(((2 * PI)*incrementSin) / 200) + 20, 0, sin(((2 * PI)*incrementSin) / 200) + 20);
		}
		else if (setThings->loadedLevel >= 50) {
			levelColor.set(0, 0, sin(((2 * PI)*incrementSin) / 200) + 40);
		}
		else if (setThings->loadedLevel >= 20) {
			levelColor.set(30, 0, sin(((2 * PI)*incrementSin) / 100) + 40);
		}
		else if (setThings->loadedLevel >= 10) {
			levelColor.set(0, 0, sin(((2 * PI)*incrementSin) / 100) + 40);
		}
		else if (setThings->loadedLevel >= 5) {
			levelColor.set(0, 30, 30);
		}
		else {
			levelColor.set(0, 0, 50);
		}

		powerUpString();//Draws on the screen the power ups you pick up

		actualLevel = to_string(setThings->loadedLevel - 1); //returns the level -1 since loadedLevel starts at 1.
		ofSetColor(255, levelGlowAnimation);
		myFont5.drawString(actualLevel, 50, 50);//draws the level your playing on the top left corner.

		for (auto& Power : powers) { // draws and makes the powers move
			Power.draw();
			Power.move();
		}
		for (auto& enemy : enemies) {// draws the new enemies
			enemy->draw(); //Draws all the enemies in the array
		}
		for (auto& barrier : barriers) {
			barrier.draw();
		}

		for (auto& particule : particules) {
			particule.draw(theShip, setThings);
			particule.move(theShip, setThings);
		}

		for (auto& bullet : bullets) {
			if (setThings->superBullet) {
				bullet.superBullet();//draws bigger bullets
			}
			else {
				bullet.draw();
			}
			if (bulletFired) {
				bullet.fire(); //makes the bullet go forward
			}
			else {
				bulletFired = false;
			}
		}
		theShip->drawHitboxSmooth(setThings); // draws the ships
		if (setThings->loadedLevel >= 100) {
			shipSprite5.draw(theShip->x, theShip->y);
		}
		else if (setThings->loadedLevel >= 20) {
			shipSprite4.draw(theShip->x, theShip->y);
		}
		else if (setThings->loadedLevel >= 10) {
			shipSprite3.draw(theShip->x, theShip->y);
		}
		else if (setThings->loadedLevel >= 5) {
			shipSprite2.draw(theShip->x, theShip->y);
		}
		else if (setThings->loadedLevel > 0) {
			shipSprite1.draw(theShip->x, theShip->y);
		}
		if (!timerStarted) {
			timer.start();
		}
		myFont3.drawString("points: " + to_string(timer.elapsedTime() / 10), edgeX - 200, 100); // draws your current score
	}


	if (setThings->state == 3) {
		restartButton.setup(edgeX / 2 - 60, edgeY / 2 + 200, 115, 25, "RESTART", ofColor(0, 50, 150, 200), ofColor(0, 30, 200), &myFont3); // draws the restart button

		if (setThings->gameOver && setThings->win == false) {
			if (setThings->endless) {
				ofBackgroundGradient(ofColor(sin(((2 * PI)*incrementSin) / 200) * 100 + 100, 0, 0), ofColor(0, 0, 0), OF_GRADIENT_CIRCULAR);
				string levelReached = "You reached level " + actualLevel + " !";
				myFont2.drawString(score, edgeX / 2 - 198, edgeY / 2 + 160);

				ofSetColor(255); // draws the Game Over title.

				myFont.drawString("GAME OVER", edgeX / 2 - 166, edgeY / 2);
				myFont2.drawString(levelReached, edgeX / 2 - 198, edgeY / 2 + 130);

				restartButton.draw();// draws the restart button.
				quitButton.draw();
			}
			else {
				ofBackgroundGradient(ofColor(sin(((2 * PI)*incrementSin) / 200) * 100 + 100, 0, 0), ofColor(0, 0, 0), OF_GRADIENT_CIRCULAR);
				string levelReached = "You reached level " + actualLevel + " !";

				ofSetColor(255); // draws the Game Over title.

				myFont.drawString("GAME OVER", edgeX / 2 - 166, edgeY / 2);
				myFont2.drawString(levelReached, edgeX / 2 - 198, edgeY / 2 + 130);
				myFont2.drawString(score, edgeX / 2 - 198, edgeY / 2 + 160);

				restartButton.draw();// draws the restart button.
				quitButton.draw();
			}
		}

		if (setThings->win && setThings->gameOver == false) {

			if (setThings->endless) {
				string levelReached = "You reached level " + actualLevel + " !";
				string youWin = "Well Done!";
				ofBackgroundGradient(ofColor(0, 0, sin(((2 * PI)*incrementSin) / 200) * 100 + 100), ofColor(0, 0, 0), OF_GRADIENT_CIRCULAR);    //makes the wining background flicker slightly :)
				ofSetColor(255); // draws the Win title.

				myFont.drawString(youWin, edgeX / 2 - 154, edgeY / 2);
				restartButton.draw();

				myFont2.drawString(levelReached, edgeX / 2 - 198, edgeY / 2 + 130);
				myFont2.drawString(score, edgeX / 2 - 198, edgeY / 2 + 160);

				restartButton.draw();// draws the restart button.
				quitButton.draw();
			}
			else {
				string youWin = "Well Done!";
				ofBackgroundGradient(ofColor(0, 0, sin(((2 * PI)*incrementSin) / 200) * 100 + 100), ofColor(0, 0, 0), OF_GRADIENT_CIRCULAR);    //makes the wining background flicker slightly :)
				ofSetColor(255); // draws the Win title.

				myFont.drawString(youWin, edgeX / 2 - 154, edgeY / 2);
				myFont2.drawString(score, edgeX / 2 - 198, edgeY / 2 + 160);
				restartButton.draw();
				quitButton.draw();
			}
		}
	}
	if (setThings->state == 4) {
		backButton.setup(50, edgeY - 100, 70, 25, "BACK", ofColor(0, 50, 150, 200), ofColor(0, 30, 200), &myFont3);
		ofBackgroundGradient(ofColor(0, 0, 0), ofColor(0, 0, sin(((2 * PI)*incrementSin) / 200) * 100 + 100), OF_GRADIENT_BAR);//just a nice spacy background, try to give a small speed effect to the game.
		ofSetColor(255, 255, 255, 200);
		myFont4.drawString("How to Play?", edgeX / 2 - 245, edgeY / 7);//Title of the game


		myFont3.drawString(" You lose if the enemies touch the edge of the screen \n \n \n You Lose if your ship hits a barrier \n \n \n Use the mouse to move the ship \n \n \n Use left mouse button to fire bullets \n \n \n Capture enemies with your ship to spawn power Ups \n \n \n Grab the power Ups to gain ship upgrades \n \n \n [ A Mouse is highly recommended for higher difficulties ]", edgeX / 6, edgeY / 4 + 50);//Title of the game

		backButton.draw();
		trackSelectionButton.draw();
	}
	ofSetColor(200, 0, 80);
	cursorSX = sin(((2 * PI)*incrementSin) / 60 + 10) * 5;//make them lively
	cursorSY = sin(((2 * PI)*incrementSin) / 60 + 10) * 5;
	ofDrawEllipse(ofGetMouseX(), ofGetMouseY(), cursorSX + 15, cursorSY + 15);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	setThings->mouseIsReleased = false;
	setThings->mouseIsPressed = true;
	// checks if you mouse is on each buttons

	if (easyButton.mouseHover() && setThings->state == 1) {
		setThings->easy = true;
	}
	if (mediumButton.mouseHover() && setThings->state == 1) {
		setThings->medium = true;
	}

	if (hardButton.mouseHover() && setThings->state == 1) {
		setThings->hard = true;
	}
	if (endlessButton.mouseHover() && setThings->state == 1) {
		setThings->endless = true;
	}
	if (quitButton.mouseHover() && (setThings->state == 1 || setThings->state == 3)) {
		setThings->generatingLevels = false;
		std::exit(0);
		cout << "Exiting game..." << endl;
	}
	if (restartButton.mouseHover() && setThings->state == 3) {
		restartPressed = true;
	}
	if (howToPlayButton.mouseHover() && setThings->state == 1) {
		setThings->howToPlay = true;
	}
	if (backButton.mouseHover() && setThings->state == 4) {
		setThings->backButton = true;
	}
	if (trackSelectionButton.mouseHover() && setThings->state == 4) {
		trackSelectionPressed = true;
	}

	if (canFire = true) {//allows a bullet from being fired after you pressed a difficulty

		if (setThings->state == 2 && firstShot == false) {
			bulletFired = true;
			bullets.push_back(Bullet(theShip));//adds a bullet to the vector everytime you shoot
			if (!setThings->slowMo || !setThings->autoShoot) {
				shoot2.play();
			}
		}

		else {
			bulletFired = false;
		}
	}

	if (firstShot) {
		firstShot = false; //Prevents a bullet from shooting, at the menu when an option is chosen.
		canFire = true;
	}
}

void ofApp::mouseReleased(int x, int y, int button) {
	setThings->mouseIsPressed = false;//prevents multiple clicks on one click
	setThings->mouseIsReleased = true;
}

void ofApp::nextLevel() { //Called everytime you end a level

	level.nextLevel(setThings, enemies, &barriers);
	if (setThings->loadedLevel == setThings->levelNum + 1) { //You win if you finish the last level.
		setThings->win = true;
	}
}

void ofApp::restart() { //Sets all the values back to setup state, removes all remaining objects, clears al vectors and starts state 1 (menu)

	powerReset();
	setThings->gameOver = false;
	setThings->win = false;
	firstShot = true;
	canFire = false;
	setThings->easy = false;
	setThings->medium = false;
	setThings->hard = false;
	setThings->endless = false;
	setThings->howToPlay = false;
	restartPressed = false;
	setThings->loadedLevel = 1;
	setThings->state = 1;
	endingSoundsPlayed = false;
	trackSelectionPressed = false;
	timerStarted = false;

	bullets.erase(remove_if(bullets.begin(), bullets.end(), [this](Bullet b) {return restartPressed; }), bullets.end());
	barriers.erase(remove_if(barriers.begin(), barriers.end(), [this](Barrier b) {return restartPressed; }), barriers.end());
	powers.erase(remove_if(powers.begin(), powers.end(), [this](Power p) {return restartPressed; }), powers.end());
	particules.erase(remove_if(particules.begin(), particules.end(), [this](Particle p) {return restartPressed; }), particules.end());

	powers.clear();
	bullets.clear();
	enemies.clear();
	barriers.clear();
	particules.clear();

	if (!pickedASong) {
		easy.stop();
		windows.stop();
		hard.stop();
		theme.play();
	}
}

void ofApp::powerUps() {

	//Allows the power ups to stay on for a small period of time
	if (timerSB.elapsedTime() >= 4000 && timerSB.isStarted()) {
		setThings->superBullet = false;
		cout << "Super Bullet Off " << timerSB.elapsedTime() << endl;
		timerSB.stop();
		timerSB.reset(); //Resets the timer for next power up

	}
	if (timerSM.elapsedTime() >= 4000 && timerSM.isStarted()) {
		setThings->slowMo = false;
		cout << "Time Stopped Off " << timerSM.elapsedTime() << endl;
		timerSM.stop();
		timerSM.reset();
	}
	if (timerAS.elapsedTime() >= 4000 && timerAS.isStarted()) {
		setThings->autoShoot = false;
		cout << "Auto Shoot Off " << timerAS.elapsedTime() << endl;
		timerAS.stop();
		timerAS.reset();
	}
	if (timerSpB.elapsedTime() >= 4000 && timerSpB.isStarted()) {
		setThings->spreadBullet = false;
		cout << "Spread Bullet Off " << timerSpB.elapsedTime() << endl;
		timerSpB.stop();
		timerSpB.reset();
	}
}

void ofApp::powerUpString() {
	ofSetColor(255, titleGlowAnimation);
	float offSet1 = 0, offSet2 = 20, offSet3 = 40, offSet4 = 60;

	if (setThings->superBullet) {
		myFont5.drawString(superBulletString, edgeX / 2 - 100 + animation, edgeY / 8 + offSet1);
	}
	if (setThings->autoShoot) {
		myFont5.drawString(autoShootString, edgeX / 2 - 100 - animation, edgeY / 8 + offSet2);
	}
	if (setThings->slowMo) {
		myFont5.drawString(slowMoString, edgeX / 2 - 150 - animation, edgeY / 8 + offSet3);
	}
	if (setThings->spreadBullet) {
		myFont5.drawString(spreadBulletString, edgeX / 2 - 150 + animation, edgeY / 8 + offSet4);
	}
}


void ofApp::powerReset() { //Resets all the settings for power ups
	setThings->superBullet = false;
	setThings->autoShoot = false;
	setThings->slowMo = false;
	setThings->spreadBullet = false;
}

void ofApp::keyPressed(int key) { //Cheat and troubleshooting functions
	if (key == 32) {
		setThings->autoShoot = !setThings->autoShoot;
		setThings->spreadBullet = !setThings->spreadBullet;
	}
}

void ofApp::musicUpdate() {
	ofSoundUpdate();

	if (setThings->state == 4) {
		if (trackSelectionPressed) {
			pickedASong = true;
			track++;
			track = track % 4;
			if (track == 0) {
				hard.stop();
				windows.stop();
				theme.play();
				cout << "First track playing..." << endl;
			}
			if (track == 1) {
				theme.stop();
				windows.stop();
				hard.play();
				cout << "Second track playing..." << endl;
			}
			if (track == 2) {
				theme.stop();
				hard.stop();
				windows.play();
				cout << "Third track playing..." << endl;
			}
			if (track == 3) {
				theme.stop();
				hard.stop();
				windows.stop();
			}
		}
		trackSelectionPressed = false;
	}

	if (setThings->state == 3) {
		if (!endingSoundsPlayed) {

			//Skips if already played to avoid loops.
			if (setThings->win && setThings->endless) {
				winEndless.play();
			}
			if (setThings->win && !setThings->endless) {
				win.play();
			}
			else if (setThings->gameOver) {
				gameover.play();
			}
			endingSoundsPlayed = true;
		}
	}
}

void ofApp::errorCatching() {

}