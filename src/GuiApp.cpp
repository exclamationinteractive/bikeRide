//
//  guiApp.cpp
//  09_gaussianBlurFilter
//
//  Created by Guy on 2016-07-10.
//
//

#include "GuiApp.h"

GuiApp::GuiApp()
{

}

//--------------------------------------------------------------
void GuiApp::setup(){
    gui.setup();

    gui.add(rotation.setup("rotation",0,-1,1));
    gui.add(speed.setup("speed",1,0,15));

    gui.add(wandCircFade.setup("circFade",1,0,1));
    gui.add(wandCircRadius.setup("radius",1,0,100));
    gui.add(wandCircCount.setup("count",100,0,10000));
    gui.add(wandCircAddFreq.setup("add freq",100,0,100));
    gui.add(wandCircMaxSpeed.setup("maxSpeed",10,1,100));
    gui.add(wandCircMaxAccel.setup("maxAccel",10,1,100));
    gui.add(wandCircAccelFreq.setup("accelFreq",10,1,100));
    gui.add(wandCircGravityStrength.setup("gravStrenth",10,1,3000));
    gui.add(wandCircGravityAttractiveScale.setup("GravScale",1,-1,1));
    gui.add(wandCircGravityAttractivePower.setup("GravPow",1,0,5));
    gui.add(wandRotationDistance.setup("wand rot dist",0,0,300));

    gui.add(fade.setup("tron fade",0.5,0,1));
    gui.add(tronCount.setup("tron count",100,0,100));
    gui.add(tronLineThickness.setup("tron width",1,0,300));
    gui.add(tronMaxSpeed.setup("tron max speed",10,1,30));
    gui.add(tronLowerT.setup("tron lower t",0,0,1));
    gui.add(tronRotationDistance.setup("tron rot dist",0,0,300));

    gui.add(gridOn.setup("grid on", false));
    gui.add(gridFade.setup("grid fade", 1,0,1));
    gui.add(gridSpeed.setup("grid speed",10,1,30));
    gui.add(gridIterations.setup("grid iteration",10,1,30));
    gui.add(gridLowerT.setup("grid lower T",0,0,1));
    gui.add(gridRotationDistance.setup("grid rot distance",0,0,300));
}

//--------------------------------------------------------------
void GuiApp::update(){
}

//--------------------------------------------------------------
void GuiApp::draw(){
    ofSetColor(128);
    ofSetBackgroundColor(0,0,0);
    gui.draw();
}

