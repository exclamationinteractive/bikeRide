#pragma once

#include "ofMain.h"

class Grid : public ofBaseApp{
public:
    Grid(int ms, int lt);
    
    void update();
    void draw(float f, float lowerT);
    void setSpeed(float s);
    void setCenter(ofVec2f* c, int inc);
    float fRand(float fMin, float fMax);
    void windowResized(int w, int h);


    ofFbo fbo; // with alpha

    ofVec2f center;
    
    float increment;
    float speed;
    float t;

    std::vector<std::array<ofVec2f*, 4>> lines;

    
};
