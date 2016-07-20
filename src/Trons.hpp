#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Tron.hpp"

class Trons : public ofBaseApp{
public:
    
    ofFbo fbo; // with alpha

    Trons();

    void update(int tronCount, int lineThickness, float tronMaxSpeed, float rotation);
    void draw(float f, float lowerT);
    void windowResized(int w, int h);
    std::vector<Tron*> trons;
};
