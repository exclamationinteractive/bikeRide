//
//  WobblingCircle.cpp
//  09_gaussianBlurFilter
//
//  Created by Guy on 2016-07-14.
//
//

#include "WobblingCircle.hpp"

WobblingCircle::WobblingCircle(int r, int ms, int ma, int accelFreq)
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

//    for (int i=1; i<=50; i++)f
//    {

//    sub.push_back ({"Math", 70, 0});
    GravityCenter gravCent;
//    gravCent.center = new ofVec2f(400.0,400.0);
    gravCent.center = *new ofVec2f(ofGetMouseX(), ofGetMouseY());
    gravCent.strength = 1000;
    gravCent.power = 0;

    gravCent.attractiveScale = 1;

    //    gravityCenters.push_back({, 10, -1});
    gravityCenters.push_back(gravCent);

}

//--------------------------------------------------------------
void WobblingCircle::update(){

    pos = pos + vel * ofGetLastFrameTime() * 100;
    vel = vel + accel * ofGetLastFrameTime() * 100;
    

    for (std::vector<GravityCenter>::iterator it = gravityCenters.begin() ; it != gravityCenters.end(); ++it)
    {
        it->center = *new ofVec2f(ofGetMouseX(), ofGetMouseY());
        float gravDist = it->center.distance(pos);

//        if (gravDist > 200){
            vel = vel + it->attractiveScale * ((pos-it->center).normalize() * it->strength / pow(gravDist,it->power)) * ofGetLastFrameTime() * 100;
//        }
//        if (gravDist < 300)
//        {
//            vel = vel + 0.01*((pos-it->center).normalize() * it->strength / (gravDist));
//        }
//        else{
//            vel = vel - 2*((pos-it->center).normalize() * it->strength / (gravDist));
//        }
//        vel = vel + 2*((pos-grav2D).normalize() * ((*it)->z / (gravDist * gravDist)));
    }
    
    if (vel.length() > maxSpeed)
    {
        vel = vel.normalize()*maxSpeed;
    }
    
    if (vel.length() < -maxSpeed)
    {
        vel = - vel.normalize()*maxSpeed;
    }
    

    if (rand() % (100) > accelChangeFreq)
    {
        accel.set(fRand(-maxAccel, maxAccel), fRand(-maxAccel, maxAccel));
    }


}

void WobblingCircle::setMaxSpeed(float ms, float ma, int acf)
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


//--------------------------------------------------------------
void WobblingCircle::draw(){
    ofDrawCircle(pos.x,pos.y,radius);
}

bool WobblingCircle::shouldDelete()
{
    if (pos.x < -500 || pos.y < -500 || pos.x > ofGetWindowWidth() + 500 || pos.y > ofGetWindowHeight() + 500)
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
