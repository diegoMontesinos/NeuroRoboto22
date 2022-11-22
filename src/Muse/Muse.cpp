//
//  Muse.cpp
//  NeuroRoboto22
//
//  Created by Diego Andrés Gómez Montesinos on 25/10/22.
//

#include <cmath>
#include "ofMain.h"
#include "Muse.hpp"

// OSC Spec from https://musemonitor.com/FAQ.php#oscspec
const string Muse::BATTERY = "/muse/batt";
const string Muse::DELTA_ABS = "/muse/elements/delta_absolute";
const string Muse::THETA_ABS = "/muse/elements/theta_absolute";
const string Muse::ALHA_ABS = "/muse/elements/alpha_absolute";
const string Muse::BETA_ABS = "/muse/elements/beta_absolute";
const string Muse::GAMMA_ABS = "/muse/elements/gamma_absolute";
const string Muse::MELLOW = "/muse/algorithm/mellow";
const string Muse::CONCENTRATION = "/muse/algorithm/concentration";
const string Muse::HORSESHOE = "/muse/elements/horseshoe";
const string Muse::TOUCHING = "/muse/elements/touching_forehead";
const string Muse::BLINK = "/muse/elements/blink";
const string Muse::JAW_CLENCH = "/muse/elements/jaw_clench";
const string Muse::ACCELEROMETER = "/muse/acc";
const string Muse::GYROSCOPE = "/muse/gyro";

const int Muse::MAX_LIST_SIZE = 120;
const long Muse::STRESS_AVG_SIZE = 10;

void Muse::setup() {
  ofLog() << "listening for osc messages on port " << OSC_PORT;
  receiver.setup(OSC_PORT);

  filter.begin(25);
  microsPerReading = 1000000 / 25;
  microsPrevious = ofGetElapsedTimeMicros();

  rotation.x = 0;
  rotation.y = 0;
}

void Muse::update() {
  updateRotation();

  while (receiver.hasWaitingMessages()) {
    ofxOscMessage m;
    receiver.getNextMessage(m);

    handleOSCMessage(m);
  }
}

void Muse::updateRotation() {
  unsigned long microsNow = ofGetElapsedTimeMicros();
  if (microsNow - microsPrevious >= microsPerReading) {
    filter.updateIMU(gyroX, gyroY, gyroZ, accX, accY, accZ);

    float pitch = filter.getPitch() * -1.0;
    float yaw = filter.getYaw() + 180;

    float deltaPitch = (pitch - rotation.x) * 0.075;
    float deltaYaw = (yaw - rotation.y) * 0.075;

    rotation.x += deltaPitch;
    rotation.y += deltaYaw;
  }
}

void Muse::handleOSCMessage(ofxOscMessage const & message) {
  string address = message.getAddress();

  // Status
  if (address == Muse::BATTERY) handleBatteryMessage(message);
  if (address == Muse::TOUCHING) handleTouchingMessage(message);
  if (address == Muse::HORSESHOE) handleHorseshoeMessage(message);

  // Raw Data and Algorithms
  if (address == Muse::DELTA_ABS) handleDataMessage(message, deltaValues);
  if (address == Muse::THETA_ABS) handleDataMessage(message, thetaValues);
  if (address == Muse::ALHA_ABS) handleDataMessage(message, alphaValues);
  if (address == Muse::BETA_ABS) handleDataMessage(message, betaValues);
  if (address == Muse::GAMMA_ABS) handleDataMessage(message, gammaValues);
  
  // Compute stress
  if (address == Muse::BETA_ABS) updateStress();
  
  // Algorithms
  if (address == Muse::MELLOW) handleDataMessage(message, mellowValues);
  if (address == Muse::CONCENTRATION) handleDataMessage(message, concentrationValues);

  // Accelerometer and gyroscope
  if (address == Muse::GYROSCOPE) handleGyroscopeMessage(message);
  if (address == Muse::ACCELEROMETER) handleAccelerometerMessage(message);
}

void Muse::handleBatteryMessage(ofxOscMessage const & message) {
  if (message.getTypeString() != "iiii") return;
  
  float level = static_cast<float>(message.getArgAsInt(0));
  status.setBatteryLevel(level / 100.0);
}

void Muse::handleTouchingMessage(ofxOscMessage const & message) {
  if (message.getTypeString() != "i") return;

  int touching = message.getArgAsInt(0);
  status.setIsTouchingForehead(touching == 1);
}

void Muse::handleHorseshoeMessage(ofxOscMessage const & message) {
  if (message.getTypeString() != "ffff") return;

  int tp9 = static_cast<int>(message.getArgAsFloat(0));
  int af7 = static_cast<int>(message.getArgAsFloat(1));
  int af8 = static_cast<int>(message.getArgAsFloat(2));
  int tp10 = static_cast<int>(message.getArgAsFloat(3));

  status.setBackLeft(tp9);
  status.setFrontLeft(af7);
  status.setFrontRight(af8);
  status.setBackRight(tp10);
}

void Muse::handleDataMessage(ofxOscMessage const & message, vector<float>& list) {
  if (message.getTypeString() != "f") return;

  float data = message.getArgAsFloat(0);
  if (list.size() >= Muse::MAX_LIST_SIZE) {
    list.erase(list.begin());
  }

  list.push_back(data);
}

void Muse::handleGyroscopeMessage(ofxOscMessage const & message) {
  if (message.getTypeString() != "fff") return;

  gyroX = message.getArgAsFloat(0);
  gyroY = message.getArgAsFloat(1);
  gyroZ = message.getArgAsFloat(2);
}

void Muse::handleAccelerometerMessage(ofxOscMessage const & message) {
  if (message.getTypeString() != "fff") return;

  accX = message.getArgAsFloat(0);
  accY = message.getArgAsFloat(1);
  accZ = message.getArgAsFloat(2);
}

float Muse::getSignalValue(vector<float> const & signal, float defaultValue) const {
  long count = signal.size();
  if (count <= 0) return defaultValue;

  return signal[count - 1];
}

void Muse::updateStress() {
  vector<float> ratiosAB = calcRatios(alphaValues, betaValues);
  vector<float> ratiosTB = calcRatios(thetaValues, betaValues);
  
  long abCount = ratiosAB.size();
  long tbCount = ratiosTB.size();

  if (abCount < Muse::STRESS_AVG_SIZE || tbCount < Muse::STRESS_AVG_SIZE) {
    return;
  }

  float avgAB = getAvgRange(ratiosAB, abCount - Muse::STRESS_AVG_SIZE, abCount - 1);
  float avgTB = getAvgRange(ratiosTB, tbCount - Muse::STRESS_AVG_SIZE, tbCount - 1);

  float diffAB = avgAB - ratiosAB[abCount - 1];
  float diffTB = ratiosTB[tbCount - 1] - avgTB;

  float value = (diffAB + diffTB) * 0.5;
  if (stressValues.size() >= Muse::MAX_LIST_SIZE) {
    stressValues.erase(stressValues.begin());
  }

  stressValues.push_back(value);
}

vector<float> Muse::calcRatios(vector<float> a, vector<float> b) const {
  vector<float> ratios;

  for (int i = 0; i < a.size() && i < b.size(); i++) {
    ratios.push_back(a[i] / b[i]);
  }

  return ratios;
}

float Muse::getAvgRange(vector<float> const & list, long start, long end) const {
  float avg = 0.0;

  for (long i = start; i < end; i++) {
    avg += list[i];
  }

  return avg / (end - start);
}

float Muse::getAlpha() const {
  return getSignalValue(alphaValues, 0.0);
}

float Muse::getBeta() const {
  return getSignalValue(betaValues, 0.0);
}

float Muse::getDelta() const {
  return getSignalValue(deltaValues, 0.0);
}

float Muse::getTheta() const {
  return getSignalValue(thetaValues, 0.0);
}

float Muse::getGamma() const {
  return getSignalValue(gammaValues, 0.0);
}

float Muse::getMellow() const {
  return getSignalValue(mellowValues, 0.0);
}

float Muse::getConcentration() const {
  return getSignalValue(concentrationValues, 0.0);
}

float Muse::getStress() const {
  return getSignalValue(stressValues, 0.0);
}
