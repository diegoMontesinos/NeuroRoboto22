//
//  NeuroFont.cpp
//  NeuroRoboto22
//
//  Created by Diego Andrés Gómez Montesinos on 26/10/22.
//

#include <cmath>
#include "NeuroFont.hpp"

const std::string NeuroFont::ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789¿?¡!+-";

void NeuroFont::setup(std::string const & fontName, int const size) {
  fontSize = size;
  fontSrc.load(fontName, fontSize, true, true, true);
}

void NeuroFont::update(Muse const & muse) {
  concentration(muse);
  mellow(muse);
  stress(muse);
}

void NeuroFont::concentration(Muse const & muse) {
  float concentration = muse.getConcentration();
  spacing = ofMap(concentration, 0, 100, 7.0, 4.0);
}

void NeuroFont::mellow(Muse const & muse) {
  float alpha = muse.getAlpha();
  float mellow = muse.getMellow();

  ampSin = ofMap(mellow, 0, 100, 0.5, 4.0);
  ampCos = ofMap(abs(alpha), 0, 1.0, 0.5, 8.0);
}

void NeuroFont::stress(Muse const & muse) {
  float theta = muse.getTheta();
  float alpha = muse.getAlpha();
  float beta = muse.getBeta();
  float gamma = muse.getGamma();

//  float stress = muse.calculateStressLevel(alpha, theta);
//  noiseStep = ofMap(abs(beta), 0.0, 1.0, 1.0, 16.0);
//  noiseScale = ofMap(stress, 0.0, 10.0, 1.0, 5.0);
//
//  offsetX = ofMap(abs(gamma), 0.0, 1.0, 0.03, 0.07);
//  offsetY = ofMap(abs(theta), 0.0, 1.0, 0.04, 0.06);
}

ofPath NeuroFont::getInitialPath(uint32_t character) {
  ofPath path = fontSrc.getCharacterAsPoints(character, true, false);
  path.setMode(ofPath::POLYLINES);
  path.setFilled(true);

  return path;
}

ofPath NeuroFont::updatePath(ofPath const & path, float size) {
  ofPath newPath;
  newPath.setMode(ofPath::POLYLINES);

  std::vector<ofPolyline> polylines = path.getOutline();
  for (ofPolyline & polyline : polylines) {
    ofPolyline temp = polyline.getResampledBySpacing(spacing);

    glm::vec2 centroid = temp.getCentroid2D();

    float angleResSin = (PI * 4.5) / temp.getBoundingBox().width;
    float angleResCos = (PI * 4.0) / static_cast<float>(temp.size());

    for(int i = 0; i < (int)temp.size(); i++) {
      glm::vec2 p = temp.getVertices()[i];
      glm::vec2 v = p - centroid;
      
      float noiseVal = ofNoise(p.y * offsetX, p.x * offsetY, ofGetFrameNum() * offsetZ);
      noiseVal = isfinite(noiseVal) ? noiseVal : 0.5;
      float s = ofMap(noiseVal, 0.0, 1.0, -noiseStep * 1.5, noiseStep);

      v = glm::normalize(v);
      v *= s * noiseScale;

      float offSin = sin(p.x * angleResSin) * ampSin;
      float offCos = cos(i * angleResCos) * ampCos;

      p.x += (v.x + offCos);
      p.y += (v.y + offSin);

      if (i == 0) {
        newPath.moveTo(p);
      } else {
        newPath.lineTo(p);
      }
    }
    newPath.close();
  }

  float scale = size / static_cast<float>(fontSize);
  newPath.scale(scale, scale);

  return newPath;
}
