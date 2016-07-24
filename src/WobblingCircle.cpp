//
//  WobblingCircle.cpp
//  09_gaussianBlurFilter
//
//  Created by Guy on 2016-07-14.
//
//

#include "WobblingCircle.hpp"

WobblingCircle::WobblingCircle(int r, float ms, float ma, float accelFreq)
{
    int buffer = 100;

    maxSpeed = ms/10.0;
    maxAccel = ma/10.0;
    accelChangeFreq = accelFreq;

    radius = r;

    (rand() % (ofGetWindowWidth() + 2*buffer) - buffer);

    pos.set(rand() % (ofGetWindowWidth()  + 2 * buffer) - buffer, rand() % (ofGetWindowHeight() + 2 * buffer) - buffer);
    vel.set(fRand(-maxSpeed, maxSpeed), fRand(-maxSpeed, maxSpeed));
    accel.set(fRand(-maxAccel, maxAccel), fRand(-maxAccel, maxAccel));

    GravityCenter gravCent;
    gravCent.center = *new ofVec2f(ofGetMouseX(), ofGetMouseY());
    gravCent.strength = 1000;
    gravCent.power = 0;

    gravCent.attractiveScale = 1;

    gravityCenters.push_back(gravCent);

}

//--------------------------------------------------------------
void WobblingCircle::update(){

    pos = pos + vel * ofGetLastFrameTime() * 100;
    vel = vel + accel * ofGetLastFrameTime() * 100;
    
    for (std::vector<GravityCenter>::iterator it = gravityCenters.begin() ; it != gravityCenters.end(); ++it)
    {
        float gravDist = it->center.distance(pos);

            vel = vel + it->attractiveScale * ((pos-it->center).normalize() * it->strength / pow(gravDist,it->power)) * ofGetLastFrameTime() * 100;
    }
    
    if (vel.length() > maxSpeed)
    {
        vel = vel.normalize()*maxSpeed;
    }
    
    if (vel.length() < -maxSpeed)
    {
        vel = - vel.normalize()*maxSpeed;
    }
    
    if (ofRandom(1) < accelChangeFreq)
    {
        accel.set(fRand(-maxAccel, maxAccel), fRand(-maxAccel, maxAccel));
    }

}

void WobblingCircle::setMaxSpeed(float ms, float ma, float acf)
{
    maxSpeed = ms/10.0;
    maxAccel = ma/10.0;
    accelChangeFreq = acf;
}

void WobblingCircle::setGravityStrength(int strength, int attractiveScale, int power)
{
    for (std::vector<GravityCenter>::iterator it = gravityCenters.begin() ; it != gravityCenters.end(); ++it)
    {
        it->strength = strength;
        it->attractiveScale = attractiveScale;
        it->power = power;
    }
}

void WobblingCircle::setGravityCenter(ofVec2f* c)
{
    for (std::vector<GravityCenter>::iterator it = gravityCenters.begin() ; it != gravityCenters.end(); ++it)
    {
        it->center = *c;
    }
}


//--------------------------------------------------------------
void WobblingCircle::draw(){
    ofDrawCircle(pos.x,pos.y,radius);
}

bool WobblingCircle::shouldDelete(int windowWidth, int windowHeight)
{
    if (pos.x < -500 || pos.y < -500 || pos.x > windowWidth + 500 || pos.y > windowHeight + 500)
    {
        return true;
    }

    return false;
    
}

float WobblingCircle::fRand(float fMin, float fMax)
{
    float f = (float)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
