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
  setupGUI();

  address = LocalAddressGrabber::getIpAddress("en0");

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

void ofApp::setupGUI() {
  gui.setup();
  gui.add(titlePosX.setup("titlePosX", 0.025, 0.0, 1.0));
  gui.add(titlePosY.setup("titlePosY", 0.12, 0.0, 1.0));
  gui.add(infoPosX.setup("infoPosX", 0.025, 0.0, 1.0));
  gui.add(infoPosY.setup("infoPosY", 0.28, 0.0, 1.0));
  gui.add(specimenPosX.setup("specimenPosX", 0.7, 0.0, 1.0));
  gui.add(specimenPosY.setup("specimenPosY", 0.14, 0.0, 1.0));
  gui.add(levelsPosX.setup("levelsPosX", 0.025, 0.0, 1.0));
  gui.add(levelsPosY.setup("levelsPosY", 0.66, 0.0, 1.0));
  gui.add(levelsW.setup("levelsW", 0.19, 0.0, 1.0));
  gui.add(levelsH.setup("levelsH", 0.04, 0.0, 1.0));
  gui.add(graphsPosX.setup("graphsPosX", 0.46, 0.0, 1.0));
  gui.add(graphsPosY.setup("graphsPosY", 0.62, 0.0, 1.0));
  gui.add(graphsW.setup("graphsW", 0.42, 0.0, 1.0));
  gui.add(graphsH.setup("graphsH", 0.22, 0.0, 1.0));

  titlePosX.addListener(this, &ofApp::onSliderChange);
  titlePosY.addListener(this, &ofApp::onSliderChange);
  infoPosX.addListener(this, &ofApp::onSliderChange);
  infoPosY.addListener(this, &ofApp::onSliderChange);
  specimenPosX.addListener(this, &ofApp::onSliderChange);
  specimenPosY.addListener(this, &ofApp::onSliderChange);
  levelsPosX.addListener(this, &ofApp::onSliderChange);
  levelsPosY.addListener(this, &ofApp::onSliderChange);
  levelsW.addListener(this, &ofApp::onSliderChange);
  levelsH.addListener(this, &ofApp::onSliderChange);
  graphsPosX.addListener(this, &ofApp::onSliderChange);
  graphsPosY.addListener(this, &ofApp::onSliderChange);
  graphsW.addListener(this, &ofApp::onSliderChange);
  graphsH.addListener(this, &ofApp::onSliderChange);
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
  drawGraphs();

  if (muse.status.hasBadConnection()) {
    drawBadConnection();
  }

  if (showDebug) {
    gui.draw();

    stringstream ss;
    ss << "FPS: " << ofToString(ofGetFrameRate(), 0) << endl;
    ss << "IP: " << address << endl;
    ofDrawBitmapString(ss.str().c_str(), 20, 20);
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

void ofApp::drawGraphs() {
  ofPushStyle();
  
  ofNoFill();
  ofSetColor(255);
  
  ofDrawRectangle(graphsRect);
  
  ofPopStyle();
}

void ofApp::drawBadConnection() {
}

void ofApp::updateDimensions() {
  float w = ofGetWidth();
  float h = ofGetHeight();

  titlePos.x = w * titlePosX;
  titlePos.y = h * titlePosY;

  infoPos.x = w * infoPosX;
  infoPos.y = h * infoPosY;

  specimenPos.x = w * specimenPosX;
  specimenPos.y = h * specimenPosY;

  levelsPos.x = w * levelsPosX;
  levelsPos.y = h * levelsPosY;
  levelRect.width = w * levelsW;
  levelRect.height = h * levelsH;

  graphsRect.x = w * graphsPosX;
  graphsRect.y = h * graphsPosY;
  graphsRect.width = w * graphsW;
  graphsRect.height = h * graphsH;
}

void ofApp::keyReleased(int key) {
  if (key == F_KEY) {
    ofToggleFullscreen();
    updateDimensions();
  }

  if (key == D_KEY) {
    showDebug = !showDebug;
  }
}

void ofApp::onSliderChange(float& f) {
  updateDimensions();
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
