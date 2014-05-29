#include "ofMain.h"
#include "Visualizer.h"


int main() {
    ofSetupOpenGL(1024, 768, OF_WINDOW);
    ofRunApp(new Visualizer());
}
