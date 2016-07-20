//
//  WobblingCircle.cpp
//  09_gaussianBlurFilter
//
//  Created by Guy on 2016-07-14.
//
//

#include "Tron.hpp"

Tron::Tron(int ms, int lt, float centerOffset)
{
    int buffer = 100;

    // FADE
    fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA32F_ARB); // with alpha, 8 bits red, 8 bits green, 8 bits blue, 8 bits alpha, from 0 to 255 in 256 steps
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();


    maxSpeed = ms/1000.0;
    t = 0;

    lineThickness = lt;

//    center.set(ofGetMouseX(), ofGetMouseY());
//    center.set(ofGetWindowWidth()/2.0, ofGetWindowHeight()/2.0);
    center.set(ofGetWindowWidth()/2.0 + centerOffset, ofGetWindowHeight()/2.0 );
    l1Rate.set(0 - center.x, 0 - center.y);
    l2Rate.set(0 - center.x, ofGetWindowHeight() - center.y);
    l3Rate.set(ofGetWindowWidth() - center.x, ofGetWindowHeight() - center.y);
    l4Rate.set(ofGetWindowWidth() - center.x, 0 - center.y);
    
    
}

//--------------------------------------------------------------
void Tron::update(){
    t = t + maxSpeed * ofGetLastFrameTime()*100;
}

void Tron::drawThickLine(ofVec2f rate1, ofVec2f rate2, float lowerT)
{
    ofFill();

    ofPolyline line;

    ofVec2f p1;
    p1.set(center + (t + lowerT) * rate1);
    ofVec2f p2;
    p2.set(center + (t+lowerT+lineThickness/1000.0) * rate1);
    ofVec2f p3;
    p3.set(center + (t+lowerT+lineThickness/1000.0) * rate2);
    ofVec2f p4;
    p4.set(center + (t + lowerT) * rate2);

    ofBeginShape();
    ofVertex(p1.x, p1.y);
    ofVertex(p2.x, p2.y);
    ofVertex(p3.x, p3.y);
    ofVertex(p4.x, p4.y);
    ofEndShape();

//    line.addVertex(p1);
//    line.addVertex(p2);
//    line.addVertex(p3);
//    line.addVertex(p4);
//    line.close(); // close the shape
//    line.draw();

}
//--------------------------------------------------------------
void Tron::draw(float lowerT){
    float x = 0;
    float y = 0;
    float z = 0;
    
    float xRate = 1;
    float yRate = 1;

//    ofSetLinethickness(lineThickness);
    ofVec2f p1;
    p1.set(center + (t + lowerT) * l1Rate);
    ofVec2f p2;
    p2.set(center + (t + lowerT) * l2Rate);
    ofVec2f p3;
    p3.set(center + (t + lowerT) * l3Rate);
    ofVec2f p4;
    p4.set(center + (t + lowerT) * l4Rate);
    
    ofSetColor(0,0,0);
    ofDrawRectangle(0,0,ofGetWindowWidth(),p1.y);
    ofDrawRectangle(0,0,p1.x,ofGetWindowHeight());
    ofDrawRectangle(0,p3.y,ofGetWindowWidth(),ofGetWindowHeight());
    ofDrawRectangle(p3.x,0,ofGetWindowWidth(),ofGetWindowHeight());

    ofSetColor(255,255,255);


//    ofSetLineWidth(lineThickness);

    // left
    if (rand() % (100) > 30)
    {
        drawThickLine(l1Rate, l2Rate, lowerT);
    }
    // bottom
    if (rand() % (100) > 0)
    {
        drawThickLine(l2Rate, l3Rate, lowerT);
    }
    // right
    if (rand() % (100) > 30)
    {
        drawThickLine(l3Rate, l4Rate,lowerT);
    }
    // top
    if (rand() % (100) > 50)
    {
        drawThickLine(l4Rate, l1Rate,lowerT);
    }
//    ofDrawLine(p1, p2);
//    ofDrawLine(p2, p3);
//    ofDrawLine(p3, p4);
//    ofDrawLine(p4, p1);
}

bool Tron::shouldDelete()
{
    if (t > 1.5)
    {
        return true;
    }
    
    return false;
    
}

float Tron::fRand(float fMin, float fMax)
{
    float f = (float)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
