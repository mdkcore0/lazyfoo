#include <IL/il.h>
#include <IL/ilu.h>

#include "LUtil.h"
#include "LTexture.h"

using namespace std;

// sprite texture
LTexture gArrowTexture;

// sprite are
LFRect gArrowClips[4];

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
    // set clip rectangles
    gArrowClips[0].x = 0.f;
    gArrowClips[0].y = 0.f;
    gArrowClips[0].w = 128.f;
    gArrowClips[0].h = 128.f;

    gArrowClips[1].x = 128.f;
    gArrowClips[1].y = 0.f;
    gArrowClips[1].w = 128.f;
    gArrowClips[1].h = 128.f;

    gArrowClips[2].x = 0.f;
    gArrowClips[2].y = 128.f;
    gArrowClips[2].w = 128.f;
    gArrowClips[2].h = 128.f;

    gArrowClips[3].x = 128.f;
    gArrowClips[3].y = 128.f;
    gArrowClips[3].w = 128.f;
    gArrowClips[3].h = 128.f;

    // load texture
    if (!gArrowTexture.loadTextureFromFile("./images/arrows.png")) {
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

    // render arrows
    gArrowTexture.render(0.f, 0.f, &gArrowClips[0]);
    gArrowTexture.render(SCREEN_WIDTH - gArrowClips[1].w, 0.f, &gArrowClips[1]);
    gArrowTexture.render(0.f, SCREEN_HEIGHT - gArrowClips[2].h, &gArrowClips[2]);
    gArrowTexture.render(SCREEN_WIDTH - gArrowClips[3].w,
            SCREEN_HEIGHT - gArrowClips[3].h, &gArrowClips[0]);

    // update screen
    glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y)
{
}
