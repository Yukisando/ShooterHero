#include "ofMain.h"
#include "ofApp.h"

//========================================================================

int main() {
	int resolutionX = 1200, resolutionY = 900;
	ofSetupOpenGL(resolutionX, resolutionY, OF_WINDOW);		// <-------- setup the GL context
	//ofSetWindowPosition(665, 40);
	ofSetWindowTitle("Shooter Hero 1.0");
	

	ofRunApp(new ofApp());
}
