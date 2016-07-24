#pragma once

#include "ofMain.h"
#include "GuiApp.h"
#include "WobblingCircles.hpp"
#include "Trons.hpp"
#include "Grid.hpp"
#include "ofxJSON.h"
#include "PdSampler.h"
#include <ctime>
// for osc input
#define IN_PORT 12345

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
    void printJSON();
    void printJSONForAttribute(string attributeName, int value);
    void loadFile();
    // float getValue(ofxJSONElement timeVals, float currentTime);
    float getValue(string param, string sceneName, float currentTime);
		void receiveOSC();
		ofxOscReceiver receiver;

    Grid* grid;

//    GuiApp* gui;
    std::shared_ptr<GuiApp> gui;
    
    // SCENE FILE
    ofxJSONElement scenes;
    float sceneTime;
    string currentScene;
    
    // FADE
    int fadeAmnt;
    ofFbo fbo; // with alpha

    // SERIAL
    ofSerial	serial;
    float speed;
    float rotation;
    ofVec2f* center;

    std::vector<WobblingCircles*> wanderingCircles;
    std::vector<Trons*> trons;

    // PD osc sampler thingy
    PdSampler sampler;

};
