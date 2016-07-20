#include "ofApp.h"

ofApp::ofApp(std::shared_ptr<GuiApp> g){
    this->gui = g;
}

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0,0,0);
    ofSetFrameRate(120);

    // FADE
    fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA32F_ARB); // with alpha, 8 bits red, 8 bits green, 8 bits blue, 8 bits alpha, from 0 to 255 in 256 steps

    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    
    // WANDERING CIRCLES
    for (int i=1; i<=1; i++)
    {
        wanderingCircles.push_back(new WobblingCircles());
    }
    
    // TRON
    for (int i=1; i<=1; i++)
    {
        trons.push_back(new Trons());
    }
    
    // GRID
    grid = new Grid(1,5);

    // SERIAL
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    int baud = 115200;
    //    int baud = 9600;
    serial.setup(1, baud); //open the first device
    //serial.setup("COM4", baud); // windows example
    //serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example
    //	serial.setup("/dev/ttyUSB0", baud); //linux example


}

//--------------------------------------------------------------
void ofApp::update(){
    
    // SERIAL
    int nTimesRead  = 0;  // a temp variable to keep count per read
    int nRead  = 0;  // a temp variable to keep count per read
    unsigned char bytesReturned[3];
    while( (nRead = serial.readBytes( bytesReturned, 3)) > 0){
        nTimesRead++;
    };

    speed = nTimesRead;

    // WANDERING CIRCLES
    for (std::vector<WobblingCircles*>::iterator it = wanderingCircles.begin() ; it != wanderingCircles.end(); ++it)
    {
        (*it)->update(gui->wandCircCount, gui->wandCircMaxSpeed, gui->wandCircRadius, gui->wandCircMaxAccel, gui->wandCircAccelFreq, gui->wandCircGravityStrength, gui->wandCircGravityAttractiveScale, gui->wandCircGravityAttractivePower);
    }
    
    // TRON
    for (std::vector<Trons*>::iterator it = trons.begin() ; it != trons.end(); ++it)
    {
        (*it)->update(gui->tronCount, gui->tronLineThickness, gui->tronMaxSpeed, gui->rotation*gui->tronRotationDistance);
    }


    // GRID
    grid->setSpeed(gui->gridSpeed);
//    grid->setSpeed(speed);
//    grid->setCenter(new ofVec2f(ofGetMouseX()+gui->rotation*gui->gridRotationDistance, ofGetMouseY()), gui->gridIterations);
    grid->setCenter(new ofVec2f(ofGetWindowWidth()/2.0+gui->rotation*gui->gridRotationDistance, ofGetWindowHeight()/2.0 - cos(gui->rotation)*gui->gridRotationDistance/3.0), gui->gridIterations);
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

    
    fbo.end();
    
    fbo.draw(0,0);

    
    // DRAW TRONS
    ofSetColor(255,255,255);
    for (std::vector<Trons*>::iterator it = trons.begin() ; it != trons.end(); ++it)
    {
        (*it)->draw(gui->fade, gui->tronLowerT);
    }

    // DRAW WANDERING CIRCLES
    for (std::vector<WobblingCircles*>::iterator it = wanderingCircles.begin() ; it != wanderingCircles.end(); ++it)
    {
        (*it)->draw(gui->wandCircFade);
    }
    
    // GRID
    if (gui->gridOn)
    {
        grid->draw(gui->gridFade, gui->gridLowerT);
    }



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

    // WANDERING CIRCLES
    for (std::vector<WobblingCircles*>::iterator it = wanderingCircles.begin() ; it != wanderingCircles.end(); ++it)
    {
        (*it)->windowResized(w, h);
    }

    // TRONs
    for (std::vector<Trons*>::iterator it = trons.begin() ; it != trons.end(); ++it)
    {
        (*it)->windowResized(w, h);
    }

    grid->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}