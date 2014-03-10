#include <IL/il.h>
#include <IL/ilu.h>

#include "LUtil.h"
#include "LTexture.h"

using namespace std;

LTexture gLoadedTexture;

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

    // initialize DevIL
    ilInit();
    ilClearColour(255, 255, 255, 000);

    // check for error
    ILenum ilError = ilGetError();
    if (ilError != IL_NO_ERROR) {
        cout << "Error initializing DevIL! " << iluErrorString(ilError) << endl;
        return false;
    }

    return true;
}

bool loadMedia()
{
    // load texture
    if (!gLoadedTexture.loadTextureFromFile("./images/texture.png")) {
        cout << "Unable to load file texture!" << endl;
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
    GLfloat x = (SCREEN_WIDTH - gLoadedTexture.textureWidth()) / 2.f;
    GLfloat y = (SCREEN_HEIGHT - gLoadedTexture.textureHeight()) / 2.f;

    // render checkerboard texture
    gLoadedTexture.render(x, y);

    // update screen
    glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y)
{
}
