#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "Muse.hpp"
#include "NeuroFont.hpp"

#define F_KEY 102

using std::vector;

class ofApp : public ofBaseApp
{
  private:
    Muse muse;
    NeuroFont neuroFont;

    ofxAssimpModelLoader headModel;

    // Title
    glm::vec2 titlePos;
    vector<ofPath> initialTitlePaths;
    vector<ofPath> titlePaths;

    // Info
    glm::vec2 infoPos;
    ofTrueTypeFont infoFont;

    // Especimen
    glm::vec2 specimenPos;
    static const vector<string> SPECIMEN_ROWS;
    vector<vector<ofPath>> initialSpecimenPaths;
    vector<vector<ofPath>> specimenPaths;

    void updateDimensions();

    void drawTitle();
    void drawInfo();
    void drawHead();
    void drawSpecimen();
    void drawBadConnection();

  public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};
