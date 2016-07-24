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

    gui.add(manualMode.setup("manual",false));

    gui.add(bikeControlled.setup("bike control",true));
    
    gui.add(rotation.setup("rotation",0,-1,1));
    gui.add(speed.setup("speed",1,0,15));

    gui.add(centerX.setup("centerX",600,0,800));
    gui.add(centerY.setup("centerY",400,0,800));

    gui.add(bikeCenteringCenter.setup("bike calib center",100,1,200));
    gui.add(bikeCenteringScale.setup("bike calib scale",150,1,200));
    
    gui.add(perspective.setup("perspective",3,-5,5));

    gui.add(wandCircAlpha.setup("circAlpha",1,0,1));
    gui.add(wandCircFade.setup("circFade",1,0,1));
    gui.add(wandCircRadius.setup("radius",1,1,10));
    gui.add(wandCircCount.setup("count",100,0,10000));
    gui.add(wandCircAddFreq.setup("add freq",100,0,100));
    gui.add(wandCircSpeedScale.setup("wand speed scale",1,0,10));
    gui.add(wandCircMaxAccel.setup("maxAccel",10,1,100));
    gui.add(wandCircAccelFreq.setup("accelFreq",0,0,1));
    gui.add(wandCircGravityStrength.setup("gravStrenth",10,1,3000));
    gui.add(wandCircGravityScale.setup("GravScale",1,-1,1));
    gui.add(wandCircGravityPower.setup("GravPow",1,0,1));
    gui.add(wandRotationDistance.setup("wand rot dist",0,0,300));

    gui.add(tronAlpha.setup("tron alpha",1,0,1));
    gui.add(tronFade.setup("tron fade",0.5,0,1));
    gui.add(tronCount.setup("tron count",0,0,1));
    gui.add(tronLineThickness.setup("tron width",1,0,300));
    gui.add(tronSpeedScale.setup("tron speed scale",10,1,30));
    gui.add(tronLowerT.setup("tron lower t",0,0,1));
    gui.add(tronRotationDistanceX.setup("tron rot dist x",0,0,500));
    gui.add(tronRotationDistanceY.setup("tron rot dist y",0,0,500));

    gui.add(gridAlpha.setup("grid alpha", 1,0,1));
    gui.add(gridFade.setup("grid fade", 0,0,1));
    gui.add(gridSpeedScale.setup("grid speed scale",0,0,2));
    gui.add(gridIterationsX.setup("grid iterationX",5,0,30));
    gui.add(gridIterationsY.setup("grid iterationY",2,0,30));
    gui.add(gridLowerT.setup("grid lower T",0.5,0,1));
    gui.add(gridRotationDistanceX.setup("grid rot dist X",0,0,500));
    gui.add(gridRotationDistanceY.setup("grid rot dist Y",0,0,500));
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

