#pragma once

#include "LocalAddressGrabber.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
#include "Muse.hpp"
#include "NeuroFont.hpp"

#define D_KEY 100
#define F_KEY 102

using std::vector;

class ofApp : public ofBaseApp
{
  private:
    Muse muse;
    NeuroFont neuroFont;

    ofxAssimpModelLoader headModel;

    ofxPanel gui;
    bool showDebug = false;

    // Title
    glm::vec2 titlePos;
    ofxFloatSlider titlePosX;
    ofxFloatSlider titlePosY;
  
    float titleSize = 94;
    vector<ofPath> initialTitlePaths;
    vector<ofPath> titlePaths;

    // Info
    glm::vec2 infoPos;
    ofxFloatSlider infoPosX;
    ofxFloatSlider infoPosY;

    int infoSize = 24;
    ofTrueTypeFont infoFont;

    // Especimen
    glm::vec2 specimenPos;
    ofxFloatSlider specimenPosX;
    ofxFloatSlider specimenPosY;

    float specimenSize = 50;
    static const vector<string> SPECIMEN_ROWS;
    vector<vector<ofPath>> initialSpecimenPaths;
    vector<vector<ofPath>> specimenPaths;

    // Levels
    glm::vec2 levelsPos;
    ofxFloatSlider levelsPosX;
    ofxFloatSlider levelsPosY;
    ofxFloatSlider levelsW;
    ofxFloatSlider levelsH;

    int levelsSize = 24;
    ofRectangle levelRect;
    ofTrueTypeFont levelsFont;

    // Graphs
    ofxFloatSlider graphsPosX;
    ofxFloatSlider graphsPosY;
    ofxFloatSlider graphsW;
    ofxFloatSlider graphsH;
    ofRectangle graphsRect;

    string address;

    void setupGUI();

    void updateDimensions();

    void drawTitle();
    void drawInfo();
    void drawHead();
    void drawSpecimen();
    void drawLevels();
    void drawLevel(float level, string const &  label);
    void drawGraphs();
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

    void onSliderChange(float& f);
};
