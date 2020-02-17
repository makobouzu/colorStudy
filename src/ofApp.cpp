#include "ofApp.h"

const std::vector<VertexColorPair> meshToVertexColorPair(const ofMesh& mesh){
    std::vector<VertexColorPair> ret;
    for(auto i = 0; i < mesh.getVertices().size(); ++i){
        ret.push_back(std::make_pair(mesh.getVertex(i), mesh.getColor(i)));
    }
    return ret;
}

std::vector<VertexColorPair> vertex{
    { glm::vec3{100, 500, 1.0}, ofColor{255,   0,   0} },
    { glm::vec3{500, 500, 1.0}, ofColor{  0,   0, 255} },
    { glm::vec3{100, 100, 1.0}, ofColor{  0, 255,   0} },
    { glm::vec3{500, 100, 1.0}, ofColor{255, 255,   0} }
};

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(auto i = 0; i < vertex.size(); ++i){
        ofSetColor(vertex.at(i).second);
        ofDrawCircle(vertex.at(i).first, 10);
    }
    
    glm::vec3 emphasisPosition = calculation::emphasisPos(vertex);
    ofColor emphasisColor = {255};
    ofSetColor(emphasisColor);
    ofDrawCircle(emphasisPosition, 10);
    
    glm::vec3 target = {mouseX, mouseY, 1.0};
    std::vector<glm::vec3> neighbor = calculation::neighborVertex(target, vertex);
    
    glm::vec3 interPos = calculation::polygonIntersection(target, neighbor, emphasisPosition);
    ofColor  interCol1 = calculation::intersectionColor(interPos, vertex, neighbor);
    ofSetColor(interCol1);
    ofDrawCircle(interPos, 10);

    ofColor targetCol = calculation::targetColor(target, interPos, interCol1, emphasisPosition, emphasisColor);
    ofSetColor(targetCol);
    ofDrawCircle(target, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    glm::vec3 target = {x, y, 1.0};
    std::vector<glm::vec3> neighbor = calculation::neighborVertex(target, vertex);
    for(auto i = neighbor.begin(); i != neighbor.end(); ++i){
        cout << *i << endl;
    }
}
