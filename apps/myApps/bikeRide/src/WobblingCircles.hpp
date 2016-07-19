#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "WobblingCircle.hpp"

class WobblingCircles : public ofBaseApp{
public:

    ofFbo fbo; // with alpha

    WobblingCircles();

    void update(int wandCircCount, int wandCircMaxSpeed, int wandCircRadius, int wandCircMaxAccel, int wandCircAccelFreq);
    void update(int wandCircCount, int wandCircMaxSpeed, int wandCircRadius, int wandCircMaxAccel, int wandCircAccelFreq, int wandCircGravityStrength, int wandCircGravityAttractiveScale, int wandCircGravityAttractivePower);
    void draw(float f);
    void windowResized(int w, int h);
    std::vector<WobblingCircle*> wanderingCircles;
};
