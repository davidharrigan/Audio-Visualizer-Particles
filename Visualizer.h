/*
*  summary:Example of how to use GPU for data processing. The data it�s going to be stored
*          on the color channels of the FBO�s textures. In this case we are going to use just
*          RED and GREEN channels on two textures. One for the position and the other one for
*          the velocity. For updating the informacion of those textures we are going to use
*          two FBO�s for each type of information. This pair of FBO will pass the information
*          from one to other in a techninc call PingPong.
*          After updating this information, we are going to use the textures allocated on GPU memory
*          for moving some vertex and then multiplied them in order to make little frames that hold
*          a texture of a spark of light.
*/

#pragma once

#include "ofMain.h"
#include "Particle.h"

class Visualizer : public ofBaseApp{
public:
   void setup();
   void update();
   void draw();

   void keyPressed  (int key);
   void keyReleased(int key);
   void mouseMoved(int x, int y );
   void mouseDragged(int x, int y, int button);
   void mousePressed(int x, int y, int button);
   void mouseReleased(int x, int y, int button);
   void windowResized(int w, int h);
   void dragEvent(ofDragInfo dragInfo);
   void gotMessage(ofMessage msg);

   vector<Particle> particles;
   ofFbo fbo;

   // Audio
   ofSoundPlayer song;
   float *fftSmoothed;
   int nBandsToGet;
   float curAvgVolume;
};