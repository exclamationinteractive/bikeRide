#pragma once

#include "ofMain.h"

class Tron : public ofBaseApp{
public:
    Tron(int ms, int lt);
    
    void update();
    void draw();
    void drawThickLine(ofVec2f rate1, ofVec2f rate2);
    bool shouldDelete();
    float fRand(float fMin, float fMax);
    
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
