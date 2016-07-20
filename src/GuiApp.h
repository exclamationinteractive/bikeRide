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

    ofxFloatSlider rotation;
    ofxFloatSlider speed;

    ofxFloatSlider wandCircFade;
    ofxIntSlider wandCircMaxSpeed;
    ofxIntSlider wandCircMaxAccel;
    ofxIntSlider wandCircAccelFreq;
    ofxIntSlider wandCircRadius;
    ofxIntSlider wandCircCount;
    ofxIntSlider wandCircGravityStrength;
    ofxIntSlider wandCircGravityAttractiveScale;
    ofxIntSlider wandCircGravityAttractivePower;

    ofxFloatSlider fade;
    ofxIntSlider tronMaxSpeed;
    ofxIntSlider tronCount;
    ofxIntSlider tronLineThickness;
    ofxFloatSlider tronLowerT;
    ofxFloatSlider tronRotationDistance;
    
    ofxToggle gridOn;
    ofxFloatSlider gridFade;
    ofxIntSlider gridSpeed;
    ofxIntSlider gridIterations;
    ofxFloatSlider gridLowerT;
    ofxFloatSlider gridRotationDistance;


};
