#include <IL/il.h>
#include <IL/ilu.h>

#include "LUtil.h"
#include "LTexture.h"

using namespace std;

// non-power-of-two texture
LTexture gCircleTexture;

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
    if (!gCircleTexture.loadTextureFromFile("./images/circle.png")) {
        cout << "Unable to load circle texture!" << endl;
        return false;
    }

    // lock texture for modificatio
    gCircleTexture.lock();

    // calculate target color
    GLuint targetColor;
    GLubyte *colors = (GLubyte *)&targetColor;

    colors[0] = 000;
    colors[1] = 255;
    colors[2] = 255;
    colors[3] = 255;

    // replace target color with transparent black
    GLuint *pixels = gCircleTexture.getPixelData32();
    GLuint pixelCount = gCircleTexture.textureWidth() * gCircleTexture.textureHeight();

    GLuint i;
    for (i = 0; i < pixelCount; i++) {
        if (pixels[i] == targetColor)
            pixels[i] = 0;
    }

    // diagonal lines
    GLuint x, y;
    int factor = 10;
    for (y = 0; y < gCircleTexture.imageHeight(); y++) {
        for (x = 0; x < gCircleTexture.imageWidth(); x++) {
            if (y % factor != x % factor)
                gCircleTexture.setPixel32(x, y, 0);
        }
    }

    // update texture
    gCircleTexture.unlock();

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
    gCircleTexture.render((SCREEN_WIDTH - gCircleTexture.imageWidth()) / 2.f,
            (SCREEN_HEIGHT - gCircleTexture.imageHeight()) / 2.f);

    // update screen
    glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y)
{
}
