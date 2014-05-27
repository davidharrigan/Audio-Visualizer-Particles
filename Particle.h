#pragma once

#include "ofMain.h"

class Particle {
public:
   Particle();
   void setup();
   void update(float dt, float* freq);
   void draw();

   vector<ofPoint> pos;
   vector<ofPoint> vel;
   int numParticles;
   float time;
   bool live;
   int direction;
   int range;
   int sections;

   // Initial setup
   ofPoint emitterCenter;
   float emitterRad;
   float velRad;
   float lifeTime;
   float rotate;
   float force; //Attraction/repulsion force inside emitter
   float spinning; //spinning force inside emitter
   float friction; //friction, in the rance 0 - 1
   float frequency;
   ofColor color;
};