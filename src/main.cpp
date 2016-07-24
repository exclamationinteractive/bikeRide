#include "ofMain.h"
#include "ofApp.h"
#include "GuiApp.h"


//========================================================================
int main( ){

//	ofGLWindowSettings settings;
//	settings.setGLVersion(3,2);
//	ofCreateWindow(settings);
    
//   ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
//	ofRunApp(new ofApp());

    
    
    ofGLFWWindowSettings settings;
    settings.width = 1440;
    settings.height = 1000;
    // settings.setPosition(ofVec2f(2720,-500));
    settings.setPosition(ofVec2f(0,-500));

    auto mainWindow = ofCreateWindow(settings);
    //shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

    
    settings.width = 300;
    settings.height = 800;
    settings.setPosition(ofVec2f(0,0));
    auto guiWindow = ofCreateWindow(settings);

    auto guiApp = make_shared<GuiApp>();

    //    int* countGui = &guiApp->countGuiInt;
//    int* fadeGui = &guiApp->fadeGuiInt;
    auto mainApp = make_shared<ofApp>(guiApp);


    ofRunApp(guiWindow, guiApp);
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
//	ofRunApp( new ofApp(guiApp));
}


