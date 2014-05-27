#include "Visualizer.h"

//--------------------------------------------------------------
void Visualizer::setup() {

   // Setup the audio component
   song.loadSound("/media/david/My Book/Downloads/Music/【IA】 Nihonbashi Koukashita R Keikaku -日本橋高架下Ｒ計画 FULL + mp3 link[mp3truck.com].mp3");
   song.setVolume(1.0f);
   fftSmoothed = new float[8192];
   for (int i=0; i < 8192; i++) {
       fftSmoothed[i] = 0;
   }
   nBandsToGet = 128;

   ofEnableSmoothing();
   ofSetFrameRate(60);

   // Allocate drawing buffer
   int w = ofGetWidth();
   int h = ofGetHeight();
   fbo.allocate(w, h, GL_RGBA32F_ARB);

   // Fill buffer with white color
   fbo.begin();
   ofBackground(255,255,255);
   fbo.end();

   // Setup parameters
   history = 0.9;
   time0 = ofGetElapsedTimef();
   bornRate = 700;
   bornCount = 0;

   // Create particles
   for (int i=0; i<1; i++) {
       Particle newP;
       newP.setup();
       particles.push_back(newP);
   }

   // Start the song
   song.play();
}

//-------------------------------------------
void Visualizer::update() {

   ofSoundUpdate();

   // grab the fft
   curAvgVolume = 0;
   float *val = ofSoundGetSpectrum(nBandsToGet);
   for (int i; i<nBandsToGet; i++) {
       fftSmoothed[i] *= 0.96f;

       if (fftSmoothed[i] < val[i]) {
           fftSmoothed[i] = val[i];
       }
       curAvgVolume += fftSmoothed[i];
   }
   curAvgVolume /= nBandsToGet;

   // Compute dt
   float time = ofGetElapsedTimef();
   float dt = ofClamp(time - time0, 0, 0.1);
   time0 = time;

   /*
   for (int i=0; i < low.size(); i++) {
       if (!particles[i].live) {
           particles[i].setup(0);
       }
   }*/

   // Update the particles
   for (int i=0; i<particles.size(); i++) {
       particles[i].update(dt, fftSmoothed);
   }

   if (curAvgVolume < 0.1) {
       particles[0].setup();
   }
}

//--------------------------------------------------------------
void Visualizer::draw() {

   float volume = ofMap(curAvgVolume, 0, 1, 20, 210);
   ofColor inColor = ofColor(volume, volume+20, volume);
   ofColor outColor = ofColor(volume, volume-10, volume);
   
   fbo.begin();
   ofRect(0, 0, ofGetWidth(), ofGetHeight());
   ofBackgroundGradient(inColor, outColor, OF_GRADIENT_CIRCULAR);

  // ofEnableAlphaBlending();
   for (int i=0; i<particles.size(); i++) {
       particles[i].draw();
   }
   //ofDisableAlphaBlending();
   fbo.end();

   ofSetColor(255,255,255);
   fbo.draw(0, 0);
}

//--------------------------------------------------------------
void Visualizer::keyPressed(int key) {

}

//--------------------------------------------------------------
void Visualizer::keyReleased(int key) {

}

//--------------------------------------------------------------
void Visualizer::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void Visualizer::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void Visualizer::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void Visualizer::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void Visualizer::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void Visualizer::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void Visualizer::dragEvent(ofDragInfo dragInfo) {

}