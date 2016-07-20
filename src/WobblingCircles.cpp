//
//  WobblingCircles.cpp
//  bikeRide
//
//  Created by Guy on 2016-07-18.
//
//

#include "WobblingCircles.hpp"

WobblingCircles::WobblingCircles()
{
    fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA32F_ARB); // with alpha, 8 bits red, 8 bits green, 8 bits blue, 8 bits alpha, from 0 to 255 in 256 steps
    
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
}

//--------------------------------------------------------------
void WobblingCircles::update(int wandCircCount, int wandCircMaxSpeed, int wandCircRadius, int wandCircMaxAccel, int wandCircAccelFreq, int wandCircGravityStrength, int wandCircGravityAttractiveScale, int wandCircGravityAttractivePower){
    // WANDERING CIRCLES
    for (std::vector<WobblingCircle*>::iterator it = wanderingCircles.begin() ; it != wanderingCircles.end(); ++it)
    {
        (*it)->update();
    }
    
    if (rand() % (100) > wandCircCount)
    {
        wanderingCircles.push_back(new WobblingCircle(wandCircRadius,wandCircMaxSpeed, wandCircMaxAccel, wandCircAccelFreq));
        wanderingCircles.push_back(new WobblingCircle(wandCircRadius,wandCircMaxSpeed, wandCircMaxAccel, wandCircAccelFreq));
        wanderingCircles.push_back(new WobblingCircle(wandCircRadius,wandCircMaxSpeed, wandCircMaxAccel, wandCircAccelFreq));
        wanderingCircles.push_back(new WobblingCircle(wandCircRadius,wandCircMaxSpeed, wandCircMaxAccel, wandCircAccelFreq));
        wanderingCircles.push_back(new WobblingCircle(wandCircRadius,wandCircMaxSpeed, wandCircMaxAccel, wandCircAccelFreq));
        wanderingCircles.push_back(new WobblingCircle(wandCircRadius,wandCircMaxSpeed, wandCircMaxAccel, wandCircAccelFreq));
        wanderingCircles.push_back(new WobblingCircle(wandCircRadius,wandCircMaxSpeed, wandCircMaxAccel, wandCircAccelFreq));
        wanderingCircles.push_back(new WobblingCircle(wandCircRadius,wandCircMaxSpeed, wandCircMaxAccel, wandCircAccelFreq));
    }
    
    std::vector<WobblingCircle*>::iterator it2 = wanderingCircles.begin();
    while (it2 != wanderingCircles.end()) {

        void setGravityStrength(int strength, int attractiveScale, int power);
        (*it2)->setGravityStrength(wandCircGravityStrength, wandCircGravityAttractiveScale, wandCircGravityAttractivePower);
        
        (*it2)->setMaxSpeed(wandCircMaxSpeed, wandCircMaxAccel, wandCircAccelFreq);
        
        if ((*it2)->shouldDelete())
        {
            delete((*it2));
            it2 = wanderingCircles.erase(it2);
        }
        else
        {
            ++it2;
        }
    }
}

//--------------------------------------------------------------
void WobblingCircles::draw(float f){
    
    // FADE
    fbo.begin();
    float fade = f;
    ofSetColor(0,0,0,255*(pow(fade,3)));
    ofDrawRectangle(0,0,fbo.getWidth(), fbo.getHeight());

    ofSetColor(255,255,255,255);

    for (std::vector<WobblingCircle*>::iterator it = wanderingCircles.begin() ; it != wanderingCircles.end(); ++it)
    {
        (*it)->draw();
    }
    fbo.end();

    ofEnableBlendMode(OF_BLENDMODE_ADD);
    fbo.draw(0,0);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
}

//--------------------------------------------------------------
void WobblingCircles::windowResized(int w, int h){
    fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA32F_ARB); // with alpha, 8 bits red, 8 bits green, 8 bits blue, 8 bits alpha, from 0 to 255 in 256 steps
}
