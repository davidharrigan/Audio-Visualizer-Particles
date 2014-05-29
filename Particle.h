#pragma once

#include "ofMain.h"

struct Param {
    float emitterRad;
    float sensitivity;
    int direction;
    int sections;
    int nBands;
    int numParticles;
    int rotationSpeed;
    ofColor color;
};

class Particle {
public:
   Particle();
   void setup(Param param);
   void update(float* freq, int start);
   void draw();

   vector<ofPoint> pos;
   vector<ofPoint> vel;
   int numParticles;
   float *frequencies;
   ofPoint emitterCenter;
   Param param;
};