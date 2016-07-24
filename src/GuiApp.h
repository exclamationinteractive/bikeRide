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

    ofxToggle manualMode;
    
    ofxToggle bikeControlled;

    ofxFloatSlider rotation;
    ofxFloatSlider speed;

    ofxIntSlider centerX;
    ofxIntSlider centerY;
    ofxIntSlider bikeCenteringCenter;
    ofxIntSlider bikeCenteringScale;

    ofxIntSlider perspective;


    ofxFloatSlider wandCircAlpha;
    ofxFloatSlider wandCircFade;
    ofxFloatSlider wandCircSpeedScale;
    ofxFloatSlider wandCircMaxAccel;
    ofxFloatSlider wandCircAccelFreq;
    ofxIntSlider wandCircRadius;
    ofxIntSlider wandCircCount;
    ofxIntSlider wandCircAddFreq;
    ofxIntSlider wandCircGravityStrength;
    ofxIntSlider wandCircGravityScale;
    ofxIntSlider wandCircGravityPower;
    ofxIntSlider wandRotationDistance;

    ofxFloatSlider tronAlpha;
    ofxFloatSlider tronFade;
    ofxFloatSlider tronSpeedScale;
    ofxFloatSlider tronCount;
    ofxIntSlider tronLineThickness;
    ofxFloatSlider tronLowerT;
    ofxFloatSlider tronRotationDistanceX;
    ofxFloatSlider tronRotationDistanceY;

    ofxFloatSlider gridAlpha;
    ofxFloatSlider gridFade;
    ofxFloatSlider gridSpeedScale;
    ofxIntSlider gridIterationsX;
    ofxIntSlider gridIterationsY;
    ofxFloatSlider gridLowerT;
    ofxFloatSlider gridRotationDistanceX;
    ofxFloatSlider gridRotationDistanceY;

};
