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
    int buffer = 100;
    
    speed = ms/1000.0;
    t = 0;

    increment = inc;

    center.set(ofGetMouseX(), ofGetMouseY());
//    center.set(ofGetWindowWidth()/2.0, ofGetWindowHeight()/2.0);

    float xRes = ofGetWindowWidth() / increment;
    float yRes = ofGetWindowHeight() / increment;

    for (int i = 0; i <= increment + 1; i ++)
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
void Grid::draw(){
    float x = 0;
    float y = 0;
    float z = 0;
    
    float xRate = 1;
    float yRate = 1;

    for(int i = 0; i < increment-1; i ++)
    {
        for(int ii = 0; ii < increment; ii ++)
        {
            for(int j = 0; j < 4; j ++)
            {
                ofVec2f p1;
                p1.set(center + ofWrap(t + 1.0/increment * i, 0, 1) * *lines.at(ii).at(j));
                ofVec2f p2;
                p2.set(center + ofWrap(t + 1.0/increment * i, 0, 1) * *lines.at(ii+1).at(j));
                ofVec2f p3;
                p3.set(center + ofWrap(t + 1.0/increment * i + 1.0/increment, 0, 1) * *lines.at(ii).at(j));
                ofVec2f p4;
                p4.set(center + ofWrap(t + 1.0/increment * i + 1.0/increment, 0, 1) * *lines.at(ii+1).at(j));
                
                ofDrawLine(p1,p2);
                ofDrawLine(p2,p4);
                ofDrawLine(p4,p3);
                ofDrawLine(p3,p1);
            }
        }
    }
    
    //    ofSetLinethickness(lineThickness);
//    for(int i = 0; i < increment; i ++)
//    {
//        for (std::vector<std::array<ofVec2f*, 4>>::iterator it = lines.begin() ; it != lines.end(); ++it)
//        {
////            // HORIZONTAL
//            ofVec2f p1;
//            p1.set(center + ofWrap(t + 1.0/increment * i, 0, 1) * *it->at(0));
//            ofVec2f p2;
//            p2.set(center + ofWrap(t + 1.0/increment * i, 0, 1) * *it->at(1));
//            ofVec2f p3;
//            p3.set(center + ofWrap(t + 1.0/increment * i, 0, 1) * *it->at(2));
//            ofVec2f p4;
//            p4.set(center + ofWrap(t + 1.0/increment * i, 0, 1) * *it->at(3));
//            
//            ofDrawCircle(p1,3);
//            ofDrawCircle(p2,3);
//            ofDrawCircle(p3,3);
//            ofDrawCircle(p4,3);
//
////            ofDrawLine(p1, p2);
////            ofDrawLine(p2, p3);
//            ofDrawLine(p3, p4);
////            ofDrawLine(p4, p1);
////            
////            // VERTICAL
//            ofVec2f v1;
//            v1.set(center + ofClamp(t + 1.0/increment * (i - 1), 0, 1) * *it->at(0));
//            ofVec2f v2;
//            v2.set(center + ofClamp(t + 1.0/increment * (i - 1), 0, 1) * *it->at(1));
//            ofDrawLine(v1, v2);
//            ofVec2f v3;
//            v3.set(center + ofClamp(t + 1.0/increment * (i - 1), 0, 1) * *it->at(2));
//            ofVec2f v4;
//            v4.set(center + ofClamp(t + 1.0/increment *(i - 1), 0, 1) * *it->at(3));
////
////            ofDrawLine(p1, v1);
////            ofDrawLine(p2, v2);
////            ofDrawLine(p3, v3);
////            ofDrawLine(p4, v4);
//
//        }
//    }
}

void Grid::setSpeed(float s)
{
    speed = s/1000.0;
}

void Grid::setCenter(ofVec2f* c, int inc)
{
    increment = inc;

    center = *c;
    
    lines.clear();

    float xRes = ofGetWindowWidth() / increment;
    float yRes = ofGetWindowHeight() / increment;

    for (int i = 0; i <= increment + 1; i ++)
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
