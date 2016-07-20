#pragma once

#include "ofMain.h"

class Tron : public ofBaseApp{
public:
    Tron(int ms, int lt, float centerOffset);
    
    void update();
    void draw(float lowerT);
    void drawThickLine(ofVec2f rate1, ofVec2f rate2, float lowerT);
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
