#include "ofApp.h"

void ofApp::setup() {
  ofSetWindowTitle("NeuroRoboto - 2022");
  ofSetVerticalSync(true);

  updateDimensions();

  muse.setup();

  neuroFont.setup("RobotoMono-Regular.ttf", 200);

  initialPath = neuroFont.getInitialPath('B');
}

void ofApp::update() {
  muse.update();

  neuroFont.update(muse);

//  headModel.setPosition(ofGetWidth() * 0.5, ofGetHeight() * 0.5 , -10);
//  headModel.setRotation(0, muse.rotation.x, 1, 0, 0);
//  headModel.setRotation(1, muse.rotation.y, 0, 1, 0);
  
//  path = neuroFont.updatePath(initialPath, 200);
}

void ofApp::draw() {
  ofBackgroundGradient(ofColor(30), ofColor(10));
}

void ofApp::updateDimensions() {
  float wScreen = ofGetWidth();
  float hScreen = ofGetHeight();

  sidebarDimensions.width = wScreen * 0.3;
  sidebarDimensions.height = hScreen * (1.0 - 0.02);
}

void ofApp::drawSidebar() {
  
}

void ofApp::keyReleased(int key) {
  if (key == F_KEY) {
    ofToggleFullscreen();
  }
}

void ofApp::windowResized(int w, int h) {
  updateDimensions();
}

void ofApp::keyPressed(int key) {}
void ofApp::mouseMoved(int x, int y) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
