#include "ofApp.h"


ofApp::ofApp(std::shared_ptr<GuiApp> g){
    this->gui = g;
}

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0,0,0);
    ofSetFrameRate(60);

    loadFile();
    
    // GRID
    grid = new Grid(1,5);


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

    // Scene
    currentScene = "scene00";

    // SERIAL
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    int baud = 115200;
    //    int baud = 9600;
    //serial.setup(1, baud); //open the first device
    //serial.setup("COM4", baud); // windows example
    //serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example
    serial.setup(0, baud); //linux example

    sampler = PdSampler();
    receiver.setup(IN_PORT);

}

//--------------------------------------------------------------
void ofApp::update(){

    // SOUND OSC
    sampler.setBikeSpeed(gui->speed);
    receiveOSC();

    if (!gui->manualMode)
    {
        gui->manualMode = !gui->manualMode;
        // ofxJSONElement a = scenes.get(currentScene,0);
        sceneTime=10;
        // sceneTime += ofGetLastFrameTime();

        // // GLOBAL
        // gui->perspective = getValue("perspective", "default", sceneTime);
        gui->centerX = getValue("centerX", "default", sceneTime);
        gui->centerY = getValue("centerY", "default", sceneTime);
        gui->bikeCenteringCenter = getValue("bikecalab-cent", "default", sceneTime);
        gui->bikeCenteringScale = getValue("bikecalab-scale", "default", sceneTime);
 
        // // GRID
        gui->gridAlpha = getValue("grid-alpha", currentScene, sceneTime);
        gui->gridFade = getValue("grid-fade", currentScene,sceneTime);
        gui->gridIterationsX = getValue("grid-iterationsX", currentScene, sceneTime);
        gui->gridIterationsY = getValue("grid-iterationsY", currentScene, sceneTime);
        gui->gridSpeedScale = getValue("grid-speed-scale", currentScene, sceneTime);
        gui->gridLowerT = getValue("grid-lower-t", currentScene, sceneTime);
        gui->gridRotationDistanceX = getValue("grid-rot-dist-x", currentScene, sceneTime);
        gui->gridRotationDistanceY = getValue("grid-rot-dist-y", currentScene, sceneTime);

        // // WANDERING CIRCLES
        gui->wandCircAlpha = getValue("wob-alpha", currentScene, sceneTime);
        gui->wandCircFade = getValue("wob-fade", currentScene,sceneTime);
        gui->wandCircCount = getValue("wob-count", currentScene,sceneTime);
        gui->wandCircAddFreq = getValue("wob-add-freq", currentScene,sceneTime);
        gui->wandCircRadius = getValue("wob-radius", currentScene,sceneTime);
        gui->wandCircSpeedScale = getValue("wob-max-speed", currentScene,sceneTime);
        gui->wandCircMaxAccel = getValue("wob-max-accel", currentScene, sceneTime);
        gui->wandCircAccelFreq = getValue("wob-accel-freq", currentScene, sceneTime);
        gui->wandCircGravityStrength = getValue("wob-grav-strength", currentScene, sceneTime);
        gui->wandCircGravityScale = getValue("wob-grav-scale", currentScene, sceneTime);
        gui->wandCircGravityPower = getValue("wob-grav-power", currentScene, sceneTime);

        // // TRON
        gui->tronAlpha = getValue("tron-alpha", currentScene, sceneTime);
        gui->tronFade = getValue("tron-fade", currentScene, sceneTime);
        gui->tronCount = getValue("tron-count", currentScene, sceneTime);
        gui->tronLineThickness = getValue("tron-width", currentScene, sceneTime);
        gui->tronSpeedScale = getValue("tron-speed-scale", currentScene, sceneTime);
        gui->tronLowerT = getValue("tron-lower-t", currentScene, sceneTime);
        gui->tronRotationDistanceX = getValue("tron-rot-dist-x", currentScene, sceneTime);
        gui->tronRotationDistanceY = getValue("tron-rot-dist-y", currentScene, sceneTime);
    }

    // SERIAL
    serial.writeByte('a');

    int nTimesRead  = 0;  // a temp variable to keep count per read
    int nRead  = 0;  // a temp variable to keep count per read
    unsigned char bytesReturned[15];

    memset(bytesReturned, 0, 15);

//serial.readBytes(
    if (serial.available() > 0)
    {
        while( (nRead = serial.readBytes( bytesReturned, 15)) > 0){

            int a = 0;
            int b = 0;
            a = bytesReturned[0];
            b = bytesReturned[1];

            // cout << "data:";
            // cout << a;
            // cout << ":";
            // cout << b;
            // cout << ":\n";
     
            speed = a;
            float bikeScale = gui->bikeCenteringScale;
            float new_rotation = 1-(b - gui->bikeCenteringCenter)/bikeScale;
            rotation = rotation + (new_rotation - rotation )/2.0;
            if (gui->bikeControlled)
            {
                gui->rotation = rotation;
                gui->speed = speed;
            }
        };
    }

    if (!gui->bikeControlled)
    {
        speed = gui->speed;
        rotation = gui->rotation;
    }

    // WANDERING CIRCLES
    for (std::vector<WobblingCircles*>::iterator it = wanderingCircles.begin() ; it != wanderingCircles.end(); ++it)
    {
        (*it)->update(gui->wandCircCount, gui->wandCircAddFreq, speed*gui->wandCircSpeedScale, gui->wandCircRadius, gui->wandCircMaxAccel, 1-gui->wandCircAccelFreq, gui->wandCircGravityStrength, gui->wandCircGravityScale, gui->wandCircGravityPower, new ofVec2f(ofGetWindowWidth()/2.0+gui->rotation*gui->wandRotationDistance, ofGetMouseY()));
    }
    // TRON
    for (std::vector<Trons*>::iterator it = trons.begin() ; it != trons.end(); ++it)
    {
        (*it)->update(1-gui->tronCount, gui->tronLineThickness, speed * gui->tronSpeedScale / 10.0, new ofVec2f(gui->centerX+rotation*gui->tronRotationDistanceX, gui->centerY - cos(rotation)*gui->tronRotationDistanceY));
    }

    // GRID
    grid->setSpeed(speed*gui->gridSpeedScale);
    grid->setCenter(new ofVec2f(gui->centerX+rotation*gui->gridRotationDistanceX, gui->centerY - cos(rotation)*gui->gridRotationDistanceY), gui->gridIterationsX, gui->gridIterationsY);
    grid->update();

}

// OSC parsing
void ofApp::receiveOSC(){
  // check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);
    float val = 0;
		// print incomming addr
    cout << m.getAddress() << endl;

    if(m.getAddress() == "/grid/gridAlpha"){
        val = m.getArgAsFloat(0);
        cout << val;
        gui->gridAlpha = m.getArgAsFloat(0);
    }
    else if(m.getAddress() == "/grid/gridFade"){
        val = m.getArgAsFloat(0);
        gui->gridFade = m.getArgAsFloat(0);
    }
    else if(m.getAddress() == "/grid/gridSpeedScale"){
        val = m.getArgAsFloat(0);
        gui->gridSpeedScale = m.getArgAsFloat(0);
    }
    else if(m.getAddress() == "/grid/gridIterationsX"){
        val = m.getArgAsFloat(0);
        gui->gridIterationsX = (int)(m.getArgAsFloat(0)*gui->gridIterationsX.getMax());
    }
    else if(m.getAddress() == "/grid/gridIterationsY"){
        val = m.getArgAsFloat(0);
        gui->gridIterationsY = (int)(m.getArgAsFloat(0)*gui->gridIterationsY.getMax());
    }
    else if(m.getAddress() == "/grid/gridLowerT"){
        val = m.getArgAsFloat(0);
        gui->gridLowerT = m.getArgAsFloat(0);
    }
    else if(m.getAddress() == "/grid/gridRotationDistanceX"){
        val = m.getArgAsFloat(0);
        gui->gridRotationDistanceX = (int)(m.getArgAsFloat(0)*gui->gridRotationDistanceX.getMax());
    }
    else if(m.getAddress() == "/grid/gridRotationDistanceY"){
        val = m.getArgAsFloat(0);
        gui->gridRotationDistanceY = (int)(m.getArgAsFloat(0)*gui->gridRotationDistanceY.getMax());
    }
    else if(m.getAddress() == "/wand/wandCircAlpha"){
        val = m.getArgAsFloat(0);
        gui->wandCircAlpha = m.getArgAsFloat(0);
    }
    else if(m.getAddress() == "/wand/wandCircFade"){
        val = m.getArgAsFloat(0);
        gui->wandCircFade = m.getArgAsFloat(0);
    }
    else if(m.getAddress() == "/wand/wandCircSpeedScale"){
        val = m.getArgAsFloat(0);
        gui->wandCircSpeedScale = m.getArgAsFloat(0) * gui->wandCircSpeedScale.getMax();
    }
    else if(m.getAddress() == "/wand/wandCircMaxAccel"){
        val = m.getArgAsFloat(0);
        gui->wandCircMaxAccel = m.getArgAsFloat(0) * gui->wandCircMaxAccel.getMax();
    }
    else if(m.getAddress() == "/wand/wandCircAccelFreq"){
        val = m.getArgAsFloat(0);
        gui->wandCircAccelFreq = m.getArgAsFloat(0) * gui->wandCircAccelFreq.getMax();
    }
    else if(m.getAddress() == "/wand/wandCircRadius"){
        val = m.getArgAsFloat(0);
        gui->wandCircRadius = (int)(m.getArgAsFloat(0)*gui->wandCircRadius.getMax()+1);
    }
    else if(m.getAddress() == "/wand/wandCircCount"){
        val = m.getArgAsFloat(0);
        gui->wandCircCount = (int)(m.getArgAsFloat(0)*gui->wandCircCount.getMax());
    }
    else if(m.getAddress() == "/wand/wandCircAddFreq"){
        val = m.getArgAsFloat(0);
        gui->wandCircAddFreq = (int)(m.getArgAsFloat(0)*gui->wandCircAddFreq.getMax());
    }
    else if(m.getAddress() == "/wand/wandCircGravityStrength"){
        val = m.getArgAsFloat(0);
        gui->wandCircGravityStrength = (int)(m.getArgAsFloat(0)*gui->wandCircGravityStrength.getMax());
    }
    else if(m.getAddress() == "/wand/wandCircGravityScale"){
        val = m.getArgAsFloat(0);
        gui->wandCircGravityScale = (int)(m.getArgAsFloat(0)*2-1;
    }
    else if(m.getAddress() == "/wand/wandCircGravityPower"){
        val = m.getArgAsFloat(0);
        gui->wandCircGravityPower = (int)(m.getArgAsFloat(0)*gui->wandCircGravityPower.getMax());
    }
    else if(m.getAddress() == "/wand/wandRotationDistance"){
        val = m.getArgAsFloat(0);
        gui->wandRotationDistance = (int)(m.getArgAsFloat(0)*gui->wandRotationDistance.getMax());
    }
    else if(m.getAddress() == "/tron/tronAlpha"){
        val = m.getArgAsFloat(0);
        gui->tronAlpha = m.getArgAsFloat(0);
    }
    else if(m.getAddress() == "/tron/tronFade"){
        val = m.getArgAsFloat(0);
        gui->tronFade = m.getArgAsFloat(0);
    }
    else if(m.getAddress() == "/tron/tronSpeedScale"){
        val = m.getArgAsFloat(0);
        gui->tronSpeedScale = m.getArgAsFloat(0)*gui->tronSpeedScale.getMax();
    }
    else if(m.getAddress() == "/tron/tronCount"){
        val = m.getArgAsFloat(0);
        gui->tronCount = m.getArgAsFloat(0);
    }
    else if(m.getAddress() == "/tron/tronLineThickness"){
        val = m.getArgAsFloat(0);
        gui->tronLineThickness = (int)(m.getArgAsFloat(0)*gui->tronLineThickness.getMax());
    }
    else if(m.getAddress() == "/tron/tronLowerT"){
        val = m.getArgAsFloat(0);
        gui->tronLowerT = m.getArgAsFloat(0);
    }
    else if(m.getAddress() == "/tron/tronRotationDistanceX"){
        val = m.getArgAsFloat(0);
        gui->tronRotationDistanceX = m.getArgAsFloat(0);
    }
    else if(m.getAddress() == "/tron/tronRotationDistanceY"){
        val = m.getArgAsFloat(0);
        gui->tronRotationDistanceY = m.getArgAsFloat(0);
    }
  }
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

	ofSetHexColor(0x0cb0b6);
	for (int j = 0; j < 10000; j++){
		//	ofDrawCircle(ofRandom(0,850), ofRandom(0,600),20);

	}    

    // DRAW TRONS
    ofSetColor(255,255,255);
    for (std::vector<Trons*>::iterator it = trons.begin() ; it != trons.end(); ++it)
    {
        (*it)->draw(gui->tronFade, gui->tronLowerT, gui->perspective, gui->tronAlpha);
    }

    // DRAW WANDERING CIRCLES
    for (std::vector<WobblingCircles*>::iterator it = wanderingCircles.begin() ; it != wanderingCircles.end(); ++it)
    {
        (*it)->draw(gui->wandCircFade, gui->wandCircAlpha);
    }
    
    // GRID
    if (gui->gridAlpha > 0)
    {
        grid->draw(gui->gridFade, gui->gridLowerT, gui->perspective, gui->gridAlpha);
    }



    ofSetColor(255,0,0);
    ofDrawBitmapString(ofGetFrameRate(), 100, 100);
    ofSetColor(255,255,255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  // sampler.setSong(1, 2);
  // sampler.cueTrack(1, 0.5);
  // sampler.setGain(1, 0.5, 1000);

    switch(key)
    {
        case 'q':
            gui->centerY = gui->centerY - 1;
            break;
        case 'a':
            gui->centerY = gui->centerY + 1;
            break;
        case 'w':
            gui->centerY = gui->centerY - 10;
            break;
        case 's':
            gui->centerY = gui->centerY + 10;
            break;
            
        case'p':
            printJSON();
        break;
        case 'f':
            ofToggleFullscreen();
        break;
        case 'm':
            gui->manualMode = !gui->manualMode;
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


void ofApp::printJSONForAttribute(string attributeName, int value)
{
    string output = "";
    output += "\""+attributeName+"\":[[0,";
    output += to_string(value);
    output += "]],\n";
    cout << output;
}


void ofApp::printJSON()
{

    cout <<"----\n";
    cout << "PRINT JSON\n";
    time_t now = time(0);
    cout << ctime(&now);
    cout <<"----\n";
    printJSONForAttribute("wandCircCount",gui->wandCircCount);
    printJSONForAttribute("wandCircFade",gui->wandCircFade);
}


float ofApp::getValue(string param, string sceneName, float currentTime){

    ofxJSONElement scene = scenes.get(sceneName,0);
    ofxJSONElement timeVals = scene.get(param,0);
    
    if (timeVals == 0)
    {
        return getValue(param, "default", currentTime);
    }
    
    // // Check if last time
    int lastTime = timeVals[timeVals.size()-1][0].asInt();
    if (currentTime > lastTime)
    {
        return timeVals[timeVals.size()-1][1].asFloat();
    }
        
    // // If not last time, get the interpolated value    
    if (timeVals.size() > 1)
    {

        for (Json::ArrayIndex i = 1; i < timeVals.size(); ++i)
        {
            int time = timeVals[i][0].asInt();
            if (time >= currentTime)
            {
                float value = timeVals[i][1].asFloat();
                float prevValue = timeVals[i-1][1].asFloat();
                int prevTime = timeVals[i-1][1].asInt();
                float timeIter = (currentTime-prevTime)/(float)(time-prevTime);
                return ofLerp(prevValue, value, timeIter );
            }
        }
    }
        
   for (Json::ArrayIndex i = 0; i < timeVals.size(); ++i)
   {
       ofxJSONElement timeVal = timeVals[i];
       for (Json::ArrayIndex j = 0; j < timeVal.size(); ++j)
       {
           std::string message = timeVal[j].asString();
       }
   }
    return 0;
}



void ofApp::loadFile()
{

    std::string file = "scenes.json";
    ofxJSONElement result;
    
    // Now parse the JSON
    bool parsingSuccessful = result.open(file);
    
    
    if (parsingSuccessful)
    {
//        result.
//        ofxJSONElement a = result.get("scene0",0);
        scenes = result;

//        getValue(a.get("wob-speed", 0),10);
        
//        b.get
//        Json::ArrayIndex i = 0;
//        int c = b.get(i,1);
//        int ddd = 2;
//        ofLogNotice("ofApp::setup") << result.getRawString();
//        
//        // now write pretty print
//        if (!result.save("example_output_pretty.json", true))
//        {
//            ofLogNotice("ofApp::setup") << "example_output_pretty.json written unsuccessfully.";
//        }
//        else
//        {
//            ofLogNotice("ofApp::setup") << "example_output_pretty.json written successfully.";
//        }
//        
//        // now write without pretty print
//        if (!result.save("example_output_fast.json", false))
//        {
//            ofLogNotice("ofApp::setup") << "example_output_pretty.json written unsuccessfully.";
//        }
//        else
//        {
//            ofLogNotice("ofApp::setup") << "example_output_pretty.json written successfully.";
//        }
        
    }
    else
    {
        ofLogError("ofApp::setup")  << "Failed to parse JSON" << endl;
    }
}

