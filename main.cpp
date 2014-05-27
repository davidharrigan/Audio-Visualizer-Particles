#include "ofMain.h"
#include "Visualizer.h"


int main() {
    ofSetupOpenGL(1024, 768, OF_WINDOW);

    if (!ofGLCheckExtension("GL_ARB_geometry_shader4") && !ofGLCheckExtension("GL_EXT_geometry_shader4") && !ofIsGLProgrammableRenderer()) {
        ofLogFatalError() << "geometry shaders not supported on this graphics card";
        return EXIT_FAILURE;
    }

    ofRunApp(new Visualizer());
}
