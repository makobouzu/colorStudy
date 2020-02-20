#include "ofApp.h"

const std::vector<VertexColorPair> meshToVertexColorPair(const ofMesh& mesh){
    std::vector<VertexColorPair> ret;
    for(auto i = 0; i < mesh.getVertices().size(); ++i){
        ret.push_back(std::make_pair(mesh.getVertex(i), mesh.getColor(i)));
    }
    return ret;
}

//width 400, height 500
std::vector<VertexColorPair> vertex{
    { glm::vec3{100, 550, 1.0}, ofColor{255,   0,   0} },
    { glm::vec3{500, 550, 1.0}, ofColor{  0,   0, 255} },
    { glm::vec3{100, 50, 1.0}, ofColor{  0, 255,   0} },
    { glm::vec3{500, 50, 1.0}, ofColor{255, 255,   0} }
};

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    emphasisPosition = calculation::emphasisPos(vertex);
    emphasisColor = {255, 255, 255};
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(auto i = 0; i < vertex.size(); ++i){
        ofSetColor(vertex.at(i).second);
        ofDrawSphere(vertex.at(i).first, 10);
    }
    
    ofSetColor(emphasisColor);
    ofDrawSphere(emphasisPosition, 10);
    
    glm::vec3 target = {mouseX, mouseY, 1.0};
    std::vector<glm::vec3> neighbor = calculation::neighborVertex(target, vertex, 3);
    ofSetColor(255);
    ofDrawLine(neighbor.at(1), neighbor.at(2));
    ofDrawLine(neighbor.at(2), neighbor.at(0));
    ofSetColor(255, 0, 0);
    ofDrawLine(neighbor.at(0), neighbor.at(1));
    
    glm::vec3 interPos = calculation::polygonIntersection(target, neighbor, emphasisPosition);
    ofColor  interCol1 = calculation::intersectionColor(interPos, vertex, neighbor);
    ofSetColor(interCol1);
    ofDrawSphere(interPos, 10);
//    cout << interPos << endl;

    ofColor targetCol = calculation::targetColor(target, interPos, interCol1, emphasisPosition, emphasisColor);
    ofSetColor(targetCol);
    ofDrawSphere(target, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    glm::vec3 target = {x, y, 1.0};
    std::vector<glm::vec3> neighbor = calculation::neighborVertex(target, vertex, 3);
    for(auto i = neighbor.begin(); i != neighbor.end(); ++i){
        cout << *i << endl;
    }
}
