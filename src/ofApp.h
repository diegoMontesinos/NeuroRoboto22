#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "Muse.hpp"
#include "NeuroFont.hpp"

#define F_KEY 102

class ofApp : public ofBaseApp
{
  private:
    // UI Sidebar
    ofRectangle sidebarDimensions;

    Muse muse;
    NeuroFont neuroFont;

    ofxAssimpModelLoader headModel;

    ofPath initialPath;
    ofPath path;

    void updateDimensions();

    void drawSidebar();

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
