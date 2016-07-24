//
//  WobblingCircle.cpp
//  09_gaussianBlurFilter
//
//  Created by Guy on 2016-07-14.
//
//

#include "Grid.hpp"

Grid::Grid(int ms, int inc)
{

    // FADE
    fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA32F_ARB); // with alpha, 8 bits red, 8 bits green, 8 bits blue, 8 bits alpha, from 0 to 255 in 256 steps
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();

    int buffer = 100;
    
    speed = ms/1000.0;
    t = 0;

    incrementX = 2;
    incrementY = 5;

    center.set(ofGetMouseX(), ofGetMouseY());
//    center.set(ofGetWindowWidth()/2.0, ofGetWindowHeight()/2.0);

    
    float xRes = ofGetWindowWidth() / incrementX;
    float yRes = ofGetWindowHeight() / incrementX;
    
    for (int i = 0; i <= incrementX + 1; i ++)
    {
        std::array<ofVec2f*, 4> l = {new ofVec2f(xRes * i - center.x, 0 - center.y), new ofVec2f(xRes * i - center.x, ofGetWindowHeight() - center.y), new ofVec2f(0 - center.x, xRes * i - center.y), new ofVec2f(ofGetWindowWidth() - center.x, xRes * i - center.y)};

        lines.push_back(l);
    }
}

//--------------------------------------------------------------
void Grid::update(){
    t = t + speed * ofGetLastFrameTime()*100;
}

//--------------------------------------------------------------
void Grid::draw(float f, float lowerT, int perspPow, float opacity){
    // FADE
    fbo.begin();
    float fade = 1.0-f;
    ofSetColor(0,0,0,255*(pow(fade,3)));
    ofDrawRectangle(0,0,fbo.getWidth(), fbo.getHeight());
    
    ofSetColor(255,255,255,255*opacity);

    float x = 0;
    float y = 0;
    float z = 0;
    
    float xRate = 1;
    float yRate = 1;

    // DRAW CENTER OF GRID
    for(int ii = 0; ii < incrementX; ii ++)
    {
        for(int j = 0; j < 4; j ++)
        {
            ofVec2f p1;
            p1.set(center + pow(lowerT,perspPow) * *lines.at(ii).at(j));
            ofVec2f p2;
            p2.set(center + pow(lowerT,perspPow) * *lines.at(ii+1).at(j));
            ofVec2f p3;
            p3.set(center + (pow(lowerT + 1.0/incrementY,perspPow)) * *lines.at(ii).at(j));
            ofVec2f p4;
            p4.set(center + (pow(lowerT + 1.0/incrementY,perspPow)) * *lines.at(ii+1).at(j));

            ofDrawLine(p1,p2);
            ofDrawLine(p2,p4);
            ofDrawLine(p1,p3);
        }
    }


    // DRAW GRID
    for(int i = 0; i < incrementY-1; i ++)
    {
        for(int ii = 0; ii < incrementX; ii ++)
        {
            for(int j = 0; j < 4; j ++)
            {
                ofVec2f p1;
                p1.set(center + (pow(lowerT + ofWrap(t + 1.0/incrementY * i, 0, 1),perspPow)) * *lines.at(ii).at(j));
                ofVec2f p2;
                p2.set(center + (pow(lowerT + ofWrap(t + 1.0/incrementY * i, 0, 1),perspPow)) * *lines.at(ii+1).at(j));
                ofVec2f p3;
                p3.set(center + (pow(lowerT + ofWrap(t + 1.0/incrementY * i + 1.0/incrementY, 0, 1),perspPow)) * *lines.at(ii).at(j));
                ofVec2f p4;
                p4.set(center + (pow(lowerT + ofWrap(t + 1.0/incrementY * i + 1.0/incrementY, 0, 1),perspPow)) * *lines.at(ii+1).at(j));

                ofDrawLine(p1,p2);
                ofDrawLine(p2,p4);
                ofDrawLine(p4,p3);
                ofDrawLine(p3,p1);
            }
        }
    }
    
    // ofSetColor(0,0,0,255*(1.0-opacity));
    // ofDrawRectangle(0,0,fbo.getWidth(), fbo.getHeight());

    fbo.end();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    fbo.draw(0,0);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);


}

void Grid::setSpeed(float s)
{
    speed = s/1000.0;
}

void Grid::setCenter(ofVec2f* c, int incX, int incY)
{
    incrementX = incX;
    incrementY = incY;

    center = *c;
    
    lines.clear();

    float xRes = ofGetWindowWidth() / incrementX;
    float yRes = ofGetWindowHeight() / incrementX;

    for (int i = 0; i <= incrementX + 1; i ++)
    {
        std::array<ofVec2f*, 4> l = {new ofVec2f(xRes * i - center.x, 0 - center.y), new ofVec2f(xRes * i - center.x, ofGetWindowHeight() - center.y), new ofVec2f(0 - center.x, yRes * i - center.y), new ofVec2f(ofGetWindowWidth() - center.x, yRes * i - center.y)};

        lines.push_back(l);
    }

}

float Grid::fRand(float fMin, float fMax)
{
    float f = (float)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


//--------------------------------------------------------------
void Grid::windowResized(int w, int h){
    fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA32F_ARB); // with alpha, 8 bits red, 8 bits green, 8 bits blue, 8 bits alpha, from 0 to 255 in 256 steps
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
}
