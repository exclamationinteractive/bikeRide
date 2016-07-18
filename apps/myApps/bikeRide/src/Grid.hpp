#pragma once

#include "ofMain.h"

class Grid : public ofBaseApp{
public:
    Grid(int ms, int lt);
    
    void update();
    void draw();
    void drawThickLine(ofVec2f rate1, ofVec2f rate2);
    void setSpeed(float s);
    void setCenter(ofVec2f* c);
    float fRand(float fMin, float fMax);
    
    ofVec2f center;
    
    float increment;
    float speed;
    float t;

    std::vector<std::array<ofVec2f*, 4>> lines;

};
