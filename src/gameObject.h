#pragma once
#include "ofMain.h"
#include "settings.h"


class gameObject {
public:
	gameObject(int xPos, int yPos, ofColor setColor);

	virtual void setup() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	int x, y;
	ofColor color;


	virtual ~gameObject() = 0;
};