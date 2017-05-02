#include "gameObject.h"

 gameObject::gameObject(int xPos, int yPos, ofColor setColor) {
 
	 ofSetColor(color);
	 color = setColor;
	 x = xPos;
	 y = yPos;
 };

 void gameObject::setup() {

 }
 void gameObject::draw() {

 }
 void gameObject::update() {}