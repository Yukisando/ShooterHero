#include "button.h"



Button::Button()//Super button class
{

}

void Button::setup(int xPos, int yPos, int w, int h, string t, ofColor c, ofColor tC, ofTrueTypeFont * f) { //quite a big constructor, I need all these parameters, not very user friendly, I'll work on that.
	x = xPos;
	y = yPos;
	width = w;
	height = h;
	text = t;
	color = c;
	colorDark = c;
	font = f;

	//makes the color the user chose slightly brighter when the mouse hovers it. 
	colorDark[1] = color[1] + 50;
	colorDark[2] = color[2] + 50;
	colorDark[3] = color[3] + 50;


}

bool Button::mouseHover() {

	if ((ofGetMouseX() >= x) && (ofGetMouseX() <= (x + width)) //checks if the mouse is over the button
		&& (ofGetMouseY() >= y) && (ofGetMouseY() <= (y + height))) {
		return true;
	}
	else {
		return false;
	}
}

void Button::draw() {//draws the button
	ofColor buttonColor;//adjust the color depending on the hover.
	if (mouseHover()) {
		buttonColor.set(colorDark);
	}
	else {
		buttonColor.set(color);
	}
	ofSetColor(buttonColor);
	ofDrawRectangle(x, y, width, height);

	ofSetColor(textColor);
	(*font).drawString(text, x+3, y + height - 5);
}


