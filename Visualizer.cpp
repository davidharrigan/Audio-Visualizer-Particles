#include "Visualizer.h"

//--------------------------------------------------------------
void Visualizer::setup() {

    // Setup the audio component
    song.loadSound("OH LAWD.mp3");
    song.setVolume(1.0f);
    fftSmoothed = new float[8192];
    for (int i=0; i < 8192; i++) {
        fftSmoothed[i] = 0;
    }
    nBandsToGet = 256;

    ofEnableSmoothing();
    ofSetFrameRate(80);

    // Allocate drawing buffer
    int w = ofGetWidth();
    int h = ofGetHeight();
    fbo.allocate(w, h, GL_RGB32F_ARB);

    // Fill buffer with white color
    fbo.begin();
    ofBackground(255,255,255);
    fbo.end();

    // Create particles
    Particle bass;
    Param bassParam;
    bassParam.sections = 8;
    bassParam.numParticles = 256;
    bassParam.sensitivity = 0.8;
    bassParam.emitterRad = 30;
    bassParam.direction = 1;
    bassParam.nBands = nBandsToGet;
    bassParam.color = ofColor(10, 20, 255);
    bassParam.rotationSpeed = 20;
    bass.setup(bassParam);

    Particle mid1;
    Param mid1Param;
    mid1Param.sensitivity = 1.4;
    mid1Param.emitterRad = 60;
    mid1Param.direction = 1;
    mid1Param.sections = 16;
    mid1Param.nBands = nBandsToGet;
    mid1Param.color = ofColor(255, 50, 124);
    mid1Param.numParticles = 1024;
    mid1Param.rotationSpeed = -20;
    mid1.setup(mid1Param);

    Particle mid2;
    Param mid2Param;
    mid2Param.sensitivity = 1.4;
    mid2Param.emitterRad = 140;
    mid2Param.direction = -1;
    mid2Param.sections = 16;
    mid2Param.nBands = nBandsToGet;
    mid2Param.color = ofColor(10, 10, 255);
    mid2Param.numParticles = 512;
    mid2Param.rotationSpeed = 30;
    mid2.setup(mid2Param);

    Particle mid3;
    Param mid3Param;
    mid3Param.sensitivity = 6;
    mid3Param.emitterRad = 200;
    mid3Param.direction = 1;
    mid3Param.sections = 16;
    mid3Param.nBands = nBandsToGet;
    mid3Param.color = ofColor(10, 100, 255);
    mid3Param.numParticles = 1024;
    mid3Param.rotationSpeed = -10;
    mid3.setup(mid3Param);
    
    Particle mid4;
    Param mid4Param;
    mid4Param.sensitivity = 12;
    mid4Param.emitterRad = 240;
    mid4Param.direction = 1;
    mid4Param.sections = 16;
    mid4Param.nBands = nBandsToGet;
    mid4Param.color = ofColor(0, 255, 255);
    mid4Param.numParticles = 1024;
    mid4Param.rotationSpeed = -30;
    mid4.setup(mid4Param);

    Particle mid5;
    Param mid5Param;
    mid5Param.sensitivity = 14;
    mid5Param.emitterRad = 300;
    mid5Param.direction = 1;
    mid5Param.sections = 16;
    mid5Param.nBands = nBandsToGet;
    mid5Param.color = ofColor(100, 0, 255);
    mid5Param.numParticles = 512;
    mid5Param.rotationSpeed = 40;
    mid5.setup(mid5Param);

    Particle mid6;
    Param mid6Param;
    mid6Param.sensitivity = 24;
    mid6Param.emitterRad = 330;
    mid6Param.direction = 1;
    mid6Param.sections = 16;
    mid6Param.nBands = nBandsToGet;
    mid6Param.color = ofColor(40, 255, 110);
    mid6Param.numParticles = 1024;
    mid6Param.rotationSpeed = 20;
    mid6.setup(mid6Param);

    Particle high;
    Param highParam;
    highParam.sensitivity = 40;
    highParam.emitterRad = 380;
    highParam.direction = -1;
    highParam.sections = 16;
    highParam.nBands = nBandsToGet;
    highParam.color = ofColor(40, 250, 255);
    highParam.numParticles = 1024;
    highParam.rotationSpeed = -40;
    high.setup(highParam);


    particles.push_back(bass);
    particles.push_back(mid1);
    particles.push_back(mid2);
    particles.push_back(mid3);
    particles.push_back(mid4);
    particles.push_back(mid5);
    particles.push_back(mid6);
    particles.push_back(high);

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
       fftSmoothed[i] *= 0.94f;

       if (fftSmoothed[i] < val[i]) {
           fftSmoothed[i] = val[i];
       }
       curAvgVolume += fftSmoothed[i];
   }
   curAvgVolume /= nBandsToGet;

    // Update the particles
    for (int i=0; i<particles.size(); i++) {
        particles[i].update(fftSmoothed, i * (nBandsToGet / particles.size()));
    }
}

//--------------------------------------------------------------
void Visualizer::draw() {

   float volume = ofMap(curAvgVolume, 0, 1, 40, 210);
   ofColor inColor = ofColor(volume, volume+40, volume);
   ofColor outColor = ofColor(volume, volume-20, volume);
   
   fbo.begin();
   ofRect(0, 0, ofGetWidth(), ofGetHeight());
   ofBackgroundGradient(inColor, outColor, OF_GRADIENT_CIRCULAR);

   //ofEnableAlphaBlending();
   for (int i=0; i<particles.size(); i++) {
        ofPushMatrix();
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            ofRotate(ofGetElapsedTimef() * particles[i].param.rotationSpeed);
            ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
            particles[i].draw();
        ofPopMatrix();
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