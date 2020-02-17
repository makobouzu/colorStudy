#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3,2);
    settings.setSize(600, 600);
    ofCreateWindow(settings);
    ofRunApp(std::make_shared<ofApp>());
}
