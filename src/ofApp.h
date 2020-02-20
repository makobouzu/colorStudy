#pragma once

#include "ofMain.h"
#include "calculation.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
private:
    
    glm::vec3 emphasisPosition;
    ofColor emphasisColor;
};
