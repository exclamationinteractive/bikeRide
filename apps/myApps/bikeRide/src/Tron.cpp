//
//  WobblingCircle.cpp
//  09_gaussianBlurFilter
//
//  Created by Guy on 2016-07-14.
//
//

#include "Tron.hpp"

Tron::Tron(int ms, int lt)
{
    int buffer = 100;

    maxSpeed = ms/1000.0;
    t = 0;
    
    lineThickness = lt;
    
    center.set(ofGetMouseX(), ofGetMouseY());
//    center.set(ofGetWindowWidth()/2.0, ofGetWindowHeight()/2.0);
    l1Rate.set(0 - center.x, 0 - center.y);
    l2Rate.set(0 - center.x, ofGetWindowHeight() - center.y);
    l3Rate.set(ofGetWindowWidth() - center.x, ofGetWindowHeight() - center.y);
    l4Rate.set(ofGetWindowWidth() - center.x, 0 - center.y);
    
    
}

//--------------------------------------------------------------
void Tron::update(){
    t = t + maxSpeed * ofGetLastFrameTime()*100;
}

void Tron::drawThickLine(ofVec2f rate1, ofVec2f rate2)
{
    ofFill();

    ofPolyline line;
    
    ofVec2f p1;
    p1.set(center + t * rate1);
    ofVec2f p2;
    p2.set(center + (t+lineThickness/1000.0) * rate1);
    ofVec2f p3;
    p3.set(center + (t+lineThickness/1000.0) * rate2);
    ofVec2f p4;
    p4.set(center + t * rate2);

    ofBeginShape();
    ofVertex(p1.x, p1.y);
    ofVertex(p2.x, p2.y);
    ofVertex(p3.x, p3.y);
    ofVertex(p4.x, p4.y);
    ofEndShape();
//
//    line.addVertex(p1);
//    line.addVertex(p2);
//    line.addVertex(p3);
//    line.addVertex(p4);
//    line.close(); // close the shape
//    line.draw();
}
//--------------------------------------------------------------
void Tron::draw(){
    float x = 0;
    float y = 0;
    float z = 0;
    
    float xRate = 1;
    float yRate = 1;

//    ofSetLinethickness(lineThickness);
    ofVec2f p1;
    p1.set(center + t * l1Rate);
    ofVec2f p2;
    p2.set(center + t * l2Rate);
    ofVec2f p3;
    p3.set(center + t * l3Rate);
    ofVec2f p4;
    p4.set(center + t * l4Rate);

//    ofSetLineWidth(lineThickness);
    
    // left
    if (rand() % (100) > 50)
    {
        drawThickLine(l1Rate, l2Rate);
    }
    // bottom
    if (rand() % (100) > 0)
    {
        drawThickLine(l2Rate, l3Rate);
    }
    // right
    if (rand() % (100) > 50)
    {
        drawThickLine(l3Rate, l4Rate);
    }
    // top
    if (rand() % (100) > 90)
    {
        drawThickLine(l4Rate, l1Rate);
    }
//    ofDrawLine(p1, p2);
//    ofDrawLine(p2, p3);
//    ofDrawLine(p3, p4);
//    ofDrawLine(p4, p1);
}

bool Tron::shouldDelete()
{
    if (t > ofGetWindowWidth())
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
