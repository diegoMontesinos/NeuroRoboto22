#include "ofApp.h"

const vector<string> ofApp::SPECIMEN_ROWS = {
  "A  B  C  D  E  F  G  H  I  J",
  "K  L  M  N  O  P  Q  R  S  T",
  "U  V  W  X  Y  Z",
  "a  b  c  d  e  f  g  h  i  j",
  "k  l  m  n  o  p  q  r  s  t",
  "u  v  w  x  y  z",
  "0  1  2  3  4  5  6  7  8  9",
  "@  #  *  +  -  ?  !"
};

void ofApp::setup() {
  ofSetWindowTitle("NeuroRoboto - 2022");
  ofSetVerticalSync(true);

  muse.setup();
  neuroFont.setup("RobotoMono-Regular.ttf", 100);

  updateDimensions();

  // Title
  initialTitlePaths = neuroFont.getStrPaths("Neuro\nRoboto");
  titlePaths = initialTitlePaths;

  // Info
  infoFont.load("RobotoMono-Regular.ttf", 22, true, true, true);

  // Specimen
  for (string specimenRow : SPECIMEN_ROWS) {
    vector<ofPath> rowPaths = neuroFont.getStrPaths(specimenRow);
    initialSpecimenPaths.push_back(rowPaths);
    specimenPaths.push_back(rowPaths);
  }

  // Head
  headModel.loadModel("head.obj");
  headModel.setScale(0.68, 0.68, 0.68);
  headModel.setPosition(0, 0, 10);

  headModel.setRotation(1, -20, 0, 1, 0);
}

void ofApp::update() {
  muse.update();

  if (muse.status.hasBadConnection()) {
    return;
  }

  neuroFont.update(muse);

  headModel.setRotation(0, muse.rotation.x, 1, 0, 0);
  headModel.setRotation(1, muse.rotation.y, 0, 1, 0);

  titlePaths = neuroFont.updatePaths(initialTitlePaths, 100);

  specimenPaths.clear();
  for (vector<ofPath> specimenRow : initialSpecimenPaths) {
    vector<ofPath> rowPaths = neuroFont.updatePaths(specimenRow, 36);
    specimenPaths.push_back(rowPaths);
  }
}

void ofApp::draw() {
  ofBackgroundGradient(ofColor(18), ofColor(8));

  drawHead();
  drawTitle();
  drawInfo();

  drawSpecimen();

  if (muse.status.hasBadConnection()) {
    drawBadConnection();
  }
}

void ofApp::drawTitle() {
  ofSetColor(250);

  ofPushMatrix();
  ofTranslate(titlePos.x, titlePos.y);

  for (ofPath & path : titlePaths) {
    path.draw();
  }

  ofPopMatrix();
}

void ofApp::drawInfo() {
  ofSetColor(250);

  stringstream info;
  info << "Intervención experimental" << endl;
  info << "de la tipografía Roboto.";

  infoFont.drawStringAsShapes(info.str(), infoPos.x, infoPos.y);
}

void ofApp::drawHead() {
  ofPushStyle();
  ofSetLineWidth(2.5f);

  ofPushMatrix();
  ofTranslate(ofGetWidth() * 0.32, ofGetHeight() * 0.5, 0);

  ofEnableDepthTest();
  ofSetColor(12, 190);
  headModel.draw(OF_MESH_FILL);
  ofSetColor(170);
  headModel.draw(OF_MESH_WIREFRAME);
  ofDisableDepthTest();

  ofPopMatrix();

  ofPopStyle();
}

void ofApp::drawSpecimen() {
  ofPushMatrix();
  ofTranslate(specimenPos.x, specimenPos.y);
  ofSetColor(250);

  for (int i = 0; i < specimenPaths.size(); i++) {
    vector<ofPath> rowPaths = specimenPaths[i];
    ofRectangle r = neuroFont.getStringBoundingBox(SPECIMEN_ROWS[i], 36);

    ofPushMatrix();
    ofTranslate(floor(-r.width * 0.5f), 0);
    for (ofPath & path : rowPaths) {
      path.draw();
    }
    ofPopMatrix();

    ofTranslate(0, 66);
  }

  ofPopMatrix();
}

void ofApp::drawBadConnection() {
}

void ofApp::updateDimensions() {
  float w = ofGetWidth();
  float h = ofGetHeight();

  titlePos.x = w * 0.025;
  titlePos.y = h * 0.14;

  infoPos.x = w * 0.03;
  infoPos.y = h * 0.3;

  specimenPos.x = w * 0.7;
  specimenPos.y = h * 0.18;
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
