#include "Particle.h"
#include <iostream>

ofPoint getVelocity(float length, float angle) {
   ofPoint p;
   float theta = 90 - ((180 - angle) / 2);
   float y = length * sin(angle);
   p.y = y * cos(theta);
   p.x = length - y * sin(theta);
   return p;
}

Particle::Particle() {
   live = false;

   sections = 4;
   emitterCenter = ofPoint (ofGetWidth() / 2, ofGetHeight() / 2);
   numParticles = 32;
}

void Particle::setup() {
   emitterRad = 40;
   color = ofColor::red;

   for (int i=0; i<numParticles; i++) {
       ofPoint pnt, p;
       float angle = i * (M_TWO_PI / numParticles);
       pnt.x = cos(angle) * emitterRad;
       pnt.y = sin(angle) * emitterRad;
       p.x = 1;
       p.y = 1;
       pos.push_back(emitterCenter + pnt);
       vel.push_back(p);
       vel[i].rotateRad(0, 0, angle);
   }
   time = 0;
   live = True;
}

void Particle::update(float dt, float *freq) {
   direction = 1;
   float curFreqRange = 0;
   int bucketCount = numParticles / sections;
   int curParticle = 0;

   for (int i=0; i<128; i++) {
       curFreqRange += freq[i];
       if (i % (128/bucketCount) == 0) {
           curFreqRange /= (128/numParticles);
           
           for (int j=0; j<sections; j++) {
               int cur = curParticle + (j * bucketCount);
               vel[cur] = getVelocity(curFreqRange, M_TWO_PI/cur);
           }
           curParticle++;
           curFreqRange = 0;
       }
   }

}



void Particle::draw() {
   float size = 1;
   float hue = ofMap(time, 0, lifeTime, 128, 255);
   color.setHue(hue);
   for (int i=0; i<numParticles; i++) {
       ofSetColor(color);
       ofCircle(pos[i] + (pos[i] * vel[i] * 0.5), size);
   }
}