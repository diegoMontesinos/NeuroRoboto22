//
//  MuseStatus.hpp
//  NeuroRoboto22
//
//  Created by Diego Andrés Gómez Montesinos on 25/10/22.
//

#pragma once

enum MuseQuality {
  GOOD_QUALITY = 1,
  MEDIUM_QUALITY = 2,
  BAD_QUALITY = 4
};

class MuseStatus
{
  private:
    float batteryLevel;

    bool touchingForehead;
    
    int frontLeft;
    int frontRight;
    int backLeft;
    int backRight;

  public:
    MuseStatus();

    float getBatteryLevel() { return batteryLevel; }
    void setBatteryLevel(float level) { batteryLevel = level; }

    bool isTouchingForehead() { return touchingForehead; }
    void setIsTouchingForehead(bool isTouchingForehead) { touchingForehead = isTouchingForehead; }

    int getFrontLeft() { return frontLeft; }
    void setFrontLeft(int value) { frontLeft = value; }
    int getFrontRight() { return frontRight; }
    void setFrontRight(int value) { frontRight = value; }
    int getBackLeft() { return backLeft; }
    void setBackLeft(int value) { backLeft = value; }
    int getBackRight() { return backRight; }
    void setBackRight(int value) { backRight = value; }

    bool hasBadConnection();
};
