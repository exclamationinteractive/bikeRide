#pragma once

#include "ofMain.h"

class Grid : public ofBaseApp{
public:
    Grid(int ms, int lt);
    
    void update();
    void draw(float f, float lowerT, int perspPow, float opacity);
    void setSpeed(float s);
    void setCenter(ofVec2f* c, int incX, int incY);
    float fRand(float fMin, float fMax);
    void windowResized(int w, int h);


    ofFbo fbo; // with alpha

    ofVec2f center;
    
    float incrementX;
    float incrementY;

    float speed;
    float t;

    std::vector<std::array<ofVec2f*, 4>> lines;

    
};
