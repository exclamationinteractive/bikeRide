#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Tron.hpp"

class Trons : public ofBaseApp{
public:
    
    ofFbo fbo; // with alpha

    Trons();

    void update(float tronCount, int lineThickness, float tronMaxSpeed, ofVec2f* center);
    void draw(float f, float lowerT, int persPower, float opacity);
    void windowResized(int w, int h);
    std::vector<Tron*> trons;
};
