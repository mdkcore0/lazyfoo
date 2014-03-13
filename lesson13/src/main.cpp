#include <iostream>

#include "LUtil.h"

using namespace std;

void runMainLoop(int val)
{
    // frame logic
    update();
    render();

    // run frame one more time
    glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, val);
}

int main(int argc, char **argv)
{
    // initialize FreeGLUT
    glutInit(&argc, argv);

    // create OpenGL 2.1 context
    glutInitContextVersion(2, 1);

    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("OpenGL");

    // do post window/contect creation initialization
    if (!initGL()) {
        cout << "Unable to initialize graphics library!" << endl;
        return 1;
    }

    // load media
    if (!loadMedia()) {
        cout << "Unable to load media!" << endl;
        return 2;
    }

    // set keyboard handler
    glutKeyboardFunc(handleKeys);

    // set rendering function
    glutDisplayFunc(render);

    // set main loop
    glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, 0);

    // start GLUT main loop
    glutMainLoop();

    return 0;
}
