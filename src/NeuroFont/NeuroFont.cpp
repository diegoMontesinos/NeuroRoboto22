//
//  NeuroFont.cpp
//  NeuroRoboto22
//
//  Created by Diego Andrés Gómez Montesinos on 26/10/22.
//

#include <cmath>
#include "NeuroFont.hpp"

void NeuroFont::setup(std::string const & fontName, int const size) {
  fontSize = size;
  fontSrc.load(fontName, fontSize, false, false, true);
  fontSrc.setLineHeight(fontSrc.getLineHeight() * 0.76);
}

void NeuroFont::update(Muse const & muse) {
  concentration(muse);
  mellow(muse);
  stress(muse);
}

void NeuroFont::concentration(Muse const & muse) {
  float concentration = muse.getConcentration();
  spacing = ofMap(concentration, 0, 100.0, 12.0, 6.0);
}

void NeuroFont::mellow(Muse const & muse) {
  float alpha = muse.getAlpha();
  float mellow = muse.getMellow();

  ampCos = ofMap(abs(alpha), 0.1, 0.7, 0.4, 16.0);
  ampSin = ofMap(mellow, 0, 100, 0.6, 16.0);
}

void NeuroFont::stress(Muse const & muse) {
  float theta = muse.getTheta();
  float beta = muse.getBeta();
  float gamma = muse.getGamma();
  float stress = muse.getStress();

  noiseStep = ofMap(abs(beta), 0.1, 0.7, 2.0, 8.0);
  noiseScale = ofMap(abs(stress), 0.0, 1.0, 0.1, 4.0);

  offsetX = ofMap(abs(gamma), 0.0, 0.5, 0.03, 0.095);
  offsetY = ofMap(abs(theta), 0.0, 1.0, 0.03, 0.095);
}

ofPath NeuroFont::getCharPath(uint32_t character) {
  ofPath path = fontSrc.getCharacterAsPoints(character, true, false);
  path.setFilled(true);

  return path;
}

std::vector<ofPath> NeuroFont::getStrPaths(std::string const & str) {
  std::vector<ofPath> paths = fontSrc.getStringAsPoints(str, true, false);
  for (ofPath & path : paths) {
    path.setFilled(true);
  }

  return paths;
}

ofPath NeuroFont::updatePath(ofPath const & path, float size) {
  ofPath newPath;

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

std::vector<ofPath> NeuroFont::updatePaths(std::vector<ofPath> const & paths, float size) {
  std::vector<ofPath> newPaths;

  for (ofPath path : paths) {
    ofPath newPath = updatePath(path, size);
    newPaths.push_back(newPath);
  }

  return newPaths;
}

ofRectangle NeuroFont::getStringBoundingBox(string const & str, float size) {
  float scale = size / static_cast<float>(fontSize);

  ofRectangle r = fontSrc.getStringBoundingBox(str, 0, 0);
  r.x *= scale;
  r.y *= scale;
  r.width *= scale;
  r.height *= scale;

  return r;
}
