#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class GuiApp : public ofBaseApp{
public:
    GuiApp();

    void setup();
    void update();
    void draw();

    ofxPanel gui;

    ofxFloatSlider fade;

    ofxFloatSlider wandCircFade;
    ofxIntSlider wandCircMaxSpeed;
    ofxIntSlider wandCircMaxAccel;
    ofxIntSlider wandCircAccelFreq;
    ofxIntSlider wandCircRadius;
    ofxIntSlider wandCircCount;
    ofxIntSlider wandCircGravityStrength;
    ofxIntSlider wandCircGravityAttractiveScale;
    ofxIntSlider wandCircGravityAttractivePower;

    ofxIntSlider tronMaxSpeed;
    ofxIntSlider tronCount;
    ofxIntSlider tronLineThickness;
    
    ofxToggle gridOn;
    ofxFloatSlider gridFade;
    ofxIntSlider gridSpeed;
    ofxFloatSlider gridIterations;
    
    

};