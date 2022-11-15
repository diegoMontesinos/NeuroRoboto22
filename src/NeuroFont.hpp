//
//  NeuroFont.hpp
//  NeuroRoboto22
//
//  Created by Diego Andrés Gómez Montesinos on 26/10/22.
//

#pragma once

#include "ofMain.h"
#include "Muse.hpp"

class NeuroFont
{
  private:
    static const std::string ALPHABET;

    ofTrueTypeFont fontSrc;
    int fontSize;

    // Modifiers
    float noiseStep = 0.5;
    float noiseScale = 0.5;
    float ampCos = 0.0;
    float ampSin = 0.0;

    // Noise
    float offsetX = 0.03;
    float offsetY = 0.04;
    float offsetZ = 0.04;
    float ampNoiseSin = 2.0;
    float spacing = 1.0;

    void concentration(Muse const & muse);
    void mellow(Muse const & muse);
    void stress(Muse const & muse);

  public:
    void setup(std::string const & fontName, int const size);
    void update(Muse const & muse);

    ofPath getInitialPath(uint32_t character);

    ofPath updatePath(ofPath const & path, float size);
};
