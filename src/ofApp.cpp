#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetWindowTitle("NeuroRoboto - 2022");
  ofSetFrameRate(60);
  ofSetVerticalSync(true);

  headModel.loadModel("head.obj");
  headModel.setScale(0.75, 0.75, 0.75);

  muse.setup();

  neuroFont.setup("RobotoMono-Regular.ttf", 200);

  initialPath = neuroFont.getInitialPath('B');
}

//--------------------------------------------------------------
void ofApp::update() {
  muse.update();

  neuroFont.update(muse);

  headModel.setPosition(ofGetWidth() * 0.5, ofGetHeight() * 0.5 , -10);
  headModel.setRotation(0, muse.rotation.x, 1, 0, 0);
  headModel.setRotation(1, muse.rotation.y, 0, 1, 0);
  
//  path = neuroFont.updatePath(initialPath, 200);
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofBackground(120, 120, 120, 0);

  ofSetLineWidth(1.75f);

  ofEnableDepthTest();
  ofSetColor(10, 10, 10, 200);
  headModel.draw(OF_MESH_FILL);
  ofSetColor(200, 200, 200, 255);
  headModel.draw(OF_MESH_WIREFRAME);
  ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
  if (key == F_KEY) {
    ofToggleFullscreen();
  }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
