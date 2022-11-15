//
//  Muse.hpp
//  NeuroRoboto22
//
//  Created by Diego Andrés Gómez Montesinos on 25/10/22.
//

#pragma once

#define OSC_PORT 5000

#include "ofxOsc.h"
#include "MuseStatus.hpp"

using std::vector;
using std::string;

class Muse
{
  private:
    // OSC Spec from https://musemonitor.com/FAQ.php#oscspec
    static const string BATTERY;
    static const string DELTA_ABS;
    static const string THETA_ABS;
    static const string ALHA_ABS;
    static const string BETA_ABS;
    static const string GAMMA_ABS;
    static const string MELLOW;
    static const string CONCENTRATION;
    static const string HORSESHOE;
    static const string TOUCHING;
    static const string BLINK;
    static const string JAW_CLENCH;

    static const int MAX_LIST_SIZE;
    static const long STRESS_AVG_SIZE;

    ofxOscReceiver receiver;

    MuseStatus status;

    vector<float> deltaValues;
    vector<float> thetaValues;
    vector<float> alphaValues;
    vector<float> betaValues;
    vector<float> gammaValues;

    vector<float> mellowValues;
    vector<float> concentrationValues;

    vector<float> stressValues;

    void handleOSCMessage(ofxOscMessage const & msg);
    void handleBatteryMessage(ofxOscMessage const & msg);
    void handleTouchingMessage(ofxOscMessage const & msg);
    void handleHorseshoeMessage(ofxOscMessage const & msg);
    void handleDataMessage(ofxOscMessage const & msg, vector<float>& list);

    void updateStress();
    vector<float> calcRatios(vector<float> a, vector<float> b) const;
    float getAvgRange(vector<float> const & list, long start, long end) const;

    float getSignalValue(vector<float> const & signal, float defaultVal) const;

  public:
    void setup();
    void update();

    float getAlpha() const;
    float getBeta() const;
    float getDelta() const;
    float getTheta() const;
    float getGamma() const;

    float getMellow() const;
    float getConcentration() const;
    float getStress() const;
};
