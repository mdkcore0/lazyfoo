#include <IL/il.h>
#include <IL/ilu.h>

#include "LUtil.h"
#include "LTexture.h"

using namespace std;

// non-power-of-two texture
LTexture gNon2NTexture;

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

    // initialize DevIL and DevILU
    ilInit();
    iluInit();
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
    if (!gNon2NTexture.loadTextureFromFile("./images/opengl.png")) {
        cout << "Unable to load non-power-of-two texture!" << endl;
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

    // render OpenGL texture
    gNon2NTexture.render((SCREEN_WIDTH - gNon2NTexture.imageWidth()) / 2.f,
            (SCREEN_HEIGHT - gNon2NTexture.imageHeight()) / 2.f);

    // update screen
    glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y)
{
}
