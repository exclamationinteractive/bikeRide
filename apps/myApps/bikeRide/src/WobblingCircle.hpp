#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class WobblingCircle : public ofBaseApp{
public:
    WobblingCircle(int r, int ms, int ma, int af);

    void update();
    void draw();
    bool shouldDelete();
    void setGravityStrength(int strength, int attractiveScale, int power);
    void setMaxSpeed(float ms, float ma, int acf);
    float fRand(float fMin, float fMax);
 
    ofxPanel gui;
    ofxIntSlider countGui;
    ofxIntSlider fadeGui;

    int countGuiInt;
    int fadeGuiInt;
    
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f accel;
    
    float maxSpeed;
    float maxAccel;
    float accelChangeFreq;
    int radius;
    
    struct GravityCenter {
        ofVec2f center;
        float strength;
        float power;
        int attractiveScale; // 1 or -1 depending on if you want to be repelling or attracting
    } ;

    std::vector<GravityCenter> gravityCenters;

    
};
