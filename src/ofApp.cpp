#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofBackground(200, 200, 200);

  ofSetWindowTitle("NeuroRoboto - 2022");
  ofSetFrameRate(60);
  ofSetVerticalSync(true);

  muse.setup();

  neuroFont.setup("RobotoMono-Regular.ttf", 200);

  initialPath = neuroFont.getInitialPath('B');
}

//--------------------------------------------------------------
void ofApp::update() {
  muse.update();

  neuroFont.update(muse);
//  path = neuroFont.updatePath(initialPath, 200);
}

//--------------------------------------------------------------
void ofApp::draw() {
  
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
