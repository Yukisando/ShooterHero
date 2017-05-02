#pragma once
#include "ofMain.h"

class Button
{
public:

	void draw();
	void setup(int xPos, int yPos, int w, int h, string t, ofColor c, ofColor tC, ofTrueTypeFont * f);
	bool mouseHover();

	Button();
	int height;
	int width;
	int x;
	int y;
	int dark;

	string text;
	ofColor color, textColor, colorDark, textColorDark;
	ofTrueTypeFont * font;
};

