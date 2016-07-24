#pragma once

#include "ofMain.h"

class Tron : public ofBaseApp{
public:
    Tron(float ms, int lt, float x, float y);
    
    void update();
    void draw(float lowerT, int windWidth, int windHeight, int perspPower);
    void drawThickLine(ofVec2f rate1, ofVec2f rate2, float lowerT, int perspPower);
    bool shouldDelete();
    float fRand(float fMin, float fMax);

    //FADE
    ofFbo fbo;

    ofVec2f center;
    ofVec2f l1Rate;
    ofVec2f l2Rate;
    ofVec2f l3Rate;
    ofVec2f l4Rate;

    float x1Rate;
    float x2Rate;
    float y1Rate;
    float y2Rate;
    
    int lineThickness;

    float maxSpeed;
    float t;

    std::vector<ofVec3f*> gravityCenters;
};
