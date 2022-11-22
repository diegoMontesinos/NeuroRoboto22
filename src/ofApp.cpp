#include "ofApp.h"

const vector<string> ofApp::SPECIMEN_ROWS = {
  "A  B  C  D  E  F  G  H  I  J",
  "K  L  M  N  O  P  Q  R  S  T",
  "U  V  W  X  Y  Z",
  "a  b  c  d  e  f  g  h  i  j",
  "k  l  m  n  o  p  q  r  s  t",
  "u  v  w  x  y  z",
  "0  1  2  3  4  5  6  7  8  9",
  "@  #  *  +  -  ? ¡ !"
};

void ofApp::setup() {
  ofSetWindowTitle("NeuroRoboto - 2022");
  ofSetVerticalSync(true);

  muse.setup();
  neuroFont.setup("Roboto-Medium.ttf", 180);

  updateDimensions();

  // Title
  initialTitlePaths = neuroFont.getStrPaths("Neuro\nRoboto");
  titlePaths = initialTitlePaths;

  // Info
  infoFont.load("RobotoMono-Regular.ttf", infoSize, true, true, true);

  // Specimen
  for (string specimenRow : SPECIMEN_ROWS) {
    vector<ofPath> rowPaths = neuroFont.getStrPaths(specimenRow);
    initialSpecimenPaths.push_back(rowPaths);
    specimenPaths.push_back(rowPaths);
  }

  // Levels
  levelsFont.load("RobotoMono-Regular.ttf", levelsSize, true, true, true);

  // Head
  headModel.loadModel("head.obj");
  headModel.setScale(0.68, 0.68, 0.68);
  headModel.setPosition(0, 0, 10);

  headModel.setRotation(1, -20, 0, 1, 0);
}

void ofApp::update() {
  muse.update();

  neuroFont.update(muse);

  if (!muse.status.hasBadConnection()) {
    headModel.setRotation(0, muse.rotation.x, 1, 0, 0);
    headModel.setRotation(1, muse.rotation.y, 0, 1, 0);
  }

  titlePaths = neuroFont.updatePaths(initialTitlePaths, titleSize);

  specimenPaths.clear();
  for (vector<ofPath> specimenRow : initialSpecimenPaths) {
    vector<ofPath> rowPaths = neuroFont.updatePaths(specimenRow, specimenSize);
    specimenPaths.push_back(rowPaths);
  }
}

void ofApp::draw() {
  ofBackgroundGradient(ofColor(18), ofColor(8));

  drawHead();
  drawTitle();
  drawInfo();
  drawSpecimen();
  drawLevels();
  // drawGraphs();

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

  infoFont.drawString(info.str(), infoPos.x, infoPos.y);
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
    ofRectangle r = neuroFont.getStringBoundingBox(SPECIMEN_ROWS[i], specimenSize);

    ofPushMatrix();
    ofTranslate(floor(-r.width * 0.5f), 0);
    for (ofPath & path : rowPaths) {
      path.draw();
    }
    ofPopMatrix();

    ofTranslate(0, specimenSize * 1.25f);
  }

  ofPopMatrix();
}

void ofApp::drawLevels() {
  ofPushStyle();
  ofPushMatrix();

  ofTranslate(levelsPos);
  ofSetColor(250);

  drawLevel(muse.getMellow() / 100.0, "Tranquilidad");
  ofTranslate(0, levelRect.height * 2.25);

  drawLevel(muse.getConcentration() / 100.0, "Concentración");
  ofTranslate(0, levelRect.height * 2.25);

  drawLevel(ofClamp(muse.getStress(), 0, 100) / 100.0, "Estrés");

  ofPopMatrix();
  ofPopStyle();
}

void ofApp::drawLevel(float level, string const & label) {
  ofSetLineWidth(4.0);
  ofNoFill();
  ofDrawRectangle(levelRect);

  ofFill();
  ofSetLineWidth(1.0);

  ofDrawRectangle(2, 0, level * (levelRect.width - 4), levelRect.height);
  levelsFont.drawString(label, 0, levelRect.height + levelsSize + 10);
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

  specimenPos.x = w * 0.5;
  specimenPos.y = h * 0.1;

  levelsPos.x = w * 0.03;
  levelsPos.y = h * 0.6;

  levelRect.width = w * 0.24;
  levelRect.height = h * 0.04;
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
