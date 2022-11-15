//
//  MuseStatus.cpp
//  NeuroRoboto22
//
//  Created by Diego Andrés Gómez Montesinos on 25/10/22.
//

#include "MuseStatus.hpp"

MuseStatus::MuseStatus():
  batteryLevel(0),
  touchingForehead(false),
  frontLeft(BAD_QUALITY),
  frontRight(BAD_QUALITY),
  backLeft(BAD_QUALITY),
  backRight(BAD_QUALITY) {}

bool MuseStatus::hasBadConnection() {
  if (!touchingForehead) return true;
  
  // At least 2 sensors have bad quality, the muse has bad quality
  int count = 0;
  count = frontLeft == BAD_QUALITY ? count + 1 : count;
  count = frontRight == BAD_QUALITY ? count + 1 : count;
  count = backLeft == BAD_QUALITY ? count + 1 : count;
  count = backRight == BAD_QUALITY ? count + 1: count;
  if (count >= 2) {
    return true;
  }

  return false;
}
