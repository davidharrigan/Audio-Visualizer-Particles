#include "Particle.h"

ofPoint getVelocity(float length, float angle) {
    ofPoint p;
    p.x = length * cos(angle);
    p.y = length * sin(angle);
    return p;
}

Particle::Particle() {
   emitterCenter = ofPoint (ofGetWidth() / 2, ofGetHeight() / 2);
}

void Particle::setup(Param p) {
    param = p;
    frequencies = new float[param.numParticles];
    
    for (int i=0; i<param.numParticles; i++) {
        frequencies[i] = 0;
    }

    for (int i=0; i<param.numParticles; i++) {
        ofPoint pnt, p;
        float angle = i * (M_TWO_PI / param.numParticles);
        pnt.x = cos(angle) * param.emitterRad;
        pnt.y = sin(angle) * param.emitterRad;
        p.x = 0;
        p.y = 0;

        pos.push_back(emitterCenter + pnt);
        vel.push_back(p);
    }
}

void Particle::update(float *freq, int start) {
  float curFreqRange = 0;
  int curParticle = 0;
  int size = 256/8; 
  int skips = param.numParticles / size;

  for (int i=0; i < param.numParticles; i++) {
    for (int j=0; j<size && i<param.numParticles; j++) {
      float angle = i * (M_TWO_PI / param.numParticles);
      vel[i] = getVelocity(param.direction * param.sensitivity * freq[j+start], angle);
      frequencies[i] = freq[j+start];
      i++;
    }
    i--;
  }
}

void Particle::draw() {
    for (int i=0; i<param.numParticles; i++) {
        ofColor color = param.color;
        float size = ofMap(frequencies[i], 0, 1, 0.5, 12);
        float hue = ofMap(frequencies[i], 0, 1, 100, 300);

        if (param.sensitivity < 1) {
          size *= param.sensitivity;
        }

        color.setHue(hue);
        ofSetColor(color);
        ofCircle(pos[i] + (pos[i] * vel[i]), size);
    }
}