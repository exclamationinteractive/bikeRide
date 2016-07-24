//
//  WobblingCircles.cpp
//  bikeRide
//
//  Created by Guy on 2016-07-18.
//
//

#include "Trons.hpp"

Trons::Trons()
{
    fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA32F_ARB); // with alpha, 8 bits red, 8 bits green, 8 bits blue, 8 bits alpha, from 0 to 255 in 256 steps
    
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
}

//--------------------------------------------------------------
void Trons::update(float tronCount, int lineThickness, float tronMaxSpeed, ofVec2f* center){
    for (std::vector<Tron*>::iterator it = trons.begin() ; it != trons.end(); ++it)
    {
        (*it)->update();
    }

    if (ofRandom(1000) < (1-tronCount) * 100) 
    {
        cout << tronMaxSpeed;
        if (tronMaxSpeed > 1)
        {
            trons.push_back(new Tron(tronMaxSpeed, lineThickness, (*center).x, (*center).y));
        }
    }
    
    
    std::vector<Tron*>::iterator it2 = trons.begin();
    while (it2 != trons.end()) {
//        (*it2)->setMaxSpeed(wandCircMaxSpeed, wandCircMaxAccel, wandCircAccelFreq);

        if ((*it2)->shouldDelete())
        {
            delete((*it2));
            it2 = trons.erase(it2);
        }
        else
        {
            ++it2;
        }
    }
}

//--------------------------------------------------------------
void Trons::draw(float f, float lowerT, int persPower, float opacity){
    
    // FADE
    fbo.begin();
    float fade = 1.0-f;
    ofSetColor(0,0,0,255*(pow(fade,3)));
    ofDrawRectangle(0,0,fbo.getWidth(), fbo.getHeight());
    
    ofSetColor(255,255,255,255);
    
    int windWidth = ofGetWindowWidth();
    int windHeight = ofGetWindowHeight();
    for (std::vector<Tron*>::reverse_iterator it = trons.rbegin() ; it != trons.rend(); ++it)
    {
        (*it)->draw(lowerT, windWidth, windHeight, persPower);
    }

    // OPACITY
    ofSetColor(0,0,0,255*(1.0-opacity));
    ofDrawRectangle(0,0,fbo.getWidth(), fbo.getHeight());

    fbo.end();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    fbo.draw(0,0);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
}

//--------------------------------------------------------------
void Trons::windowResized(int w, int h){
    fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA32F_ARB); // with alpha, 8 bits red, 8 bits green, 8 bits blue, 8 bits alpha, from 0 to 255 in 256 steps
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
}
