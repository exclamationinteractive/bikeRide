#pragma once

#include "ofMain.h"
#include "guiApp.h"
#include "WobblingCircles.hpp"
#include "Trons.hpp"
#include "Grid.hpp"

class ofApp : public ofBaseApp{
	public:
    ofApp(std::shared_ptr<GuiApp> g);

    void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    void drawLines(int lineCount);
    void drawCircles(int circleCount);
    
    Grid* grid;

//    GuiApp* gui;
    std::shared_ptr<GuiApp> gui;
    
    // FADE
    int fadeAmnt;
    ofFbo fbo; // with alpha

    // SERIAL
    ofSerial	serial;
    float speed;

    std::vector<WobblingCircles*> wanderingCircles;
    std::vector<Trons*> trons;

};
