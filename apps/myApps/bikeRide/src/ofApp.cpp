#include "ofApp.h"

ofApp::ofApp(std::shared_ptr<GuiApp> g){
    this->gui = g;
}

//--------------------------------------------------------------
void ofApp::setup(){
    fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA32F_ARB); // with alpha, 8 bits red, 8 bits green, 8 bits blue, 8 bits alpha, from 0 to 255 in 256 steps

    ofBackground(0,0,0);

    // FADE
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    
    // WANDERING CIRCLES
    for (int i=1; i<=1; i++)
    {
        wanderingCircles.push_back(new WobblingCircle(5,1, 1,1));
    }
    
    // TRON
    for (int i=1; i<=1; i++)
    {
        trons.push_back(new Tron(5, 5));
    }
    
    // GRID
    grid = new Grid(1,5);


}

//--------------------------------------------------------------
void ofApp::update(){
    
    // WANDERING CIRCLES
    for (std::vector<WobblingCircle*>::iterator it = wanderingCircles.begin() ; it != wanderingCircles.end(); ++it)
    {
        (*it)->update();
    }
    
    if (rand() % (100) > gui->wandCircCount)
    {
        wanderingCircles.push_back(new WobblingCircle(gui->wandCircRadius,gui->wandCircMaxSpeed, gui->wandCircMaxAccel, gui->wandCircAccelFreq));
        wanderingCircles.push_back(new WobblingCircle(gui->wandCircRadius,gui->wandCircMaxSpeed, gui->wandCircMaxAccel, gui->wandCircAccelFreq));
        wanderingCircles.push_back(new WobblingCircle(gui->wandCircRadius,gui->wandCircMaxSpeed, gui->wandCircMaxAccel, gui->wandCircAccelFreq));
        wanderingCircles.push_back(new WobblingCircle(gui->wandCircRadius,gui->wandCircMaxSpeed, gui->wandCircMaxAccel, gui->wandCircAccelFreq));
        wanderingCircles.push_back(new WobblingCircle(gui->wandCircRadius,gui->wandCircMaxSpeed, gui->wandCircMaxAccel, gui->wandCircAccelFreq));
        wanderingCircles.push_back(new WobblingCircle(gui->wandCircRadius,gui->wandCircMaxSpeed, gui->wandCircMaxAccel, gui->wandCircAccelFreq));
        wanderingCircles.push_back(new WobblingCircle(gui->wandCircRadius,gui->wandCircMaxSpeed, gui->wandCircMaxAccel, gui->wandCircAccelFreq));
        wanderingCircles.push_back(new WobblingCircle(gui->wandCircRadius,gui->wandCircMaxSpeed, gui->wandCircMaxAccel, gui->wandCircAccelFreq));
        wanderingCircles.push_back(new WobblingCircle(gui->wandCircRadius,gui->wandCircMaxSpeed, gui->wandCircMaxAccel, gui->wandCircAccelFreq));
    }
    
    std::vector<WobblingCircle*>::iterator it2 = wanderingCircles.begin();
    while (it2 != wanderingCircles.end()) {
        
        void setGravityStrength(int strength, int attractiveScale, int power);
        (*it2)->setGravityStrength(gui->wandCircGravityStrength, gui->wandCircGravityAttractiveScale, gui->wandCircGravityAttractivePower);

        (*it2)->setMaxSpeed(gui->wandCircMaxSpeed, gui->wandCircMaxAccel, gui->wandCircAccelFreq);

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

    // TRON
    for (std::vector<Tron*>::iterator it = trons.begin() ; it != trons.end(); ++it)
    {
        (*it)->update();
    }

    if (rand() % (100) > gui->tronCount)
    {
        trons.push_back(new Tron(gui->tronMaxSpeed, gui->tronLineThickness));
    }

    std::vector<Tron*>::iterator itTrons = trons.begin();
    while (itTrons != trons.end()) {
        if ((*itTrons)->shouldDelete())
        {
            delete((*itTrons));
            itTrons = trons.erase(itTrons);
        }
        else
        {
            ++itTrons;
        }
    }
    
    
    // GRID
    grid->setSpeed(gui->gridSpeed);
    grid->setCenter(new ofVec2f(ofGetMouseX(), ofGetMouseY()), gui->gridIterations);
    grid->update();

}

void ofApp::drawLines(int lineCount)
{
        // DRAW LINES
        int buffer = 300;
        for( int a = 0; a < lineCount; a = a + 1 )
        {
            ofPath line;
    
            line.setFilled(false);
            line.setStrokeWidth(15);
            line.setCurveResolution(200);
    
    
            int brightness = ofRandom( 0, 255 );
            line.setStrokeColor( ofColor(brightness, brightness, brightness));
    
            line.curveTo( ofPoint(rand() % (ofGetWindowWidth() + 2*buffer) - buffer, rand() % (ofGetWindowHeight() + 2*buffer)-buffer));
            line.curveTo( ofPoint(rand() % (ofGetWindowWidth() + 2*buffer) - buffer, rand() % (ofGetWindowHeight() + 2*buffer)-buffer));
            line.curveTo( ofPoint(rand() % (ofGetWindowWidth() + 2*buffer) - buffer, rand() % (ofGetWindowHeight() + 2*buffer)-buffer));
            line.curveTo( ofPoint(rand() % (ofGetWindowWidth() + 2*buffer) - buffer, rand() % (ofGetWindowHeight() + 2*buffer)-buffer));
            
            line.draw();
        }

}

void ofApp::drawCircles(int circleCount)
{
    // DRAW CIRCLES
    int buffer = 300;

    ofSetColor(ofColor(255, 255, 255));

    for( int a = 0; a < circleCount; a = a + 1 )
    {
        ofSetColor(ofColor(255, 255, 255));
        ofDrawCircle(ofRandom(0,ofGetWindowWidth()),ofRandom(0,ofGetWindowHeight()),ofRandom(2,2));
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    fbo.begin();

    // FADE
    float fade = gui->fade;
    ofSetColor(0,0,0,255*(pow(fade,3)));
    ofDrawRectangle(0,0,fbo.getWidth(), fbo.getHeight());

//    drawLines(*countGuiIntPointer);
//    drawCircles(*countGuiIntPointer);

    
    // DRAW WANDERING CIRCLES
    ofSetColor(255,255,255);
    for (std::vector<WobblingCircle*>::iterator it = wanderingCircles.begin() ; it != wanderingCircles.end(); ++it)
    {
        (*it)->draw();
    }
    
    // DRAW TRONS
    ofSetColor(255,255,255);
    for (std::vector<Tron*>::iterator it = trons.begin() ; it != trons.end(); ++it)
    {
        (*it)->draw();
    }
    
    // GRID
    if (gui->gridOn)
    {
        grid->draw();
    }

    fbo.end();
    
    fbo.draw(0,0);
    
    ofSetColor(255,0,0);
    ofDrawBitmapString(ofGetFrameRate(), 100, 100);
    ofSetColor(255,255,255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key)
    {
        case 'f':
            ofToggleFullscreen();
        break;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA32F_ARB); // with alpha, 8 bits red, 8 bits green, 8 bits blue, 8 bits alpha, from 0 to 255 in 256 steps
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}