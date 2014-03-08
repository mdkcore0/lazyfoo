#include "LUtil.h"
#include "LTexture.h"

using namespace std;

LTexture gCheckerBoardTexture;

bool initGL()
{
    // set the viewport
    glViewport(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);

    // initialize projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // multiply current matrix with an orthographic matrix
    glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

    // initializee modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);

    // enable texturing
    glEnable(GL_TEXTURE_2D);

    // check for error
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        cout << "Error initializing OpenGl! " << gluErrorString(error) << endl;
        return false;
    }

    return true;
}

bool loadMedia()
{
    // checkboard pixels
    const int CHECKBOARD_WIDTH = 128;
    const int CHECKBOARD_HEIGHT = 128;
    const int CHECKBOARD_PIXEL_COUNT = CHECKBOARD_WIDTH * CHECKBOARD_HEIGHT;
    GLuint checkerBoard[CHECKBOARD_PIXEL_COUNT];

    // go through pixels
    int i;
    for (i = 0; i < CHECKBOARD_PIXEL_COUNT; i++) {
        // get the individual color components
        GLubyte *colors = (GLubyte *)&checkerBoard[i];

        // if the 5th bit of the x and y offsets of the pixel do not match
        if ((i / 128 & 16) ^ (i % 128 & 16)) {
            // set pixel to white
            colors[0] = 0xFF;
            colors[1] = 0xFF;
            colors[2] = 0xFF;
            colors[3] = 0xFF;
        } else {
            // set pixel to red
            colors[0] = 0xFF;
            colors[1] = 0x00;
            colors[2] = 0x00;
            colors[3] = 0xFF;
        }
    }

    // load texture
    if (!gCheckerBoardTexture.loadTextureFromPixels32(checkerBoard,
                CHECKBOARD_WIDTH, CHECKBOARD_HEIGHT)) {
        cout << "Unable to load checkerboard texture!" << endl;
        return false;
    }

    return true;
}

void update()
{
}

void render()
{
    // clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // calculate centered offsets
    GLfloat x = (SCREEN_WIDTH - gCheckerBoardTexture.textureWidth()) / 2.f;
    GLfloat y = (SCREEN_HEIGHT - gCheckerBoardTexture.textureHeight()) / 2.f;

    // render checkerboard texture
    gCheckerBoardTexture.render(x, y);

    // update screen
    glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y)
{
}
