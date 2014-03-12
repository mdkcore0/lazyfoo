#include <IL/il.h>
#include <IL/ilu.h>

#include "LUtil.h"
#include "LTexture.h"

using namespace std;

// stretched texture
LTexture gStretchedTexture;

// stretch size
LFRect gStretchRect = {0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT};

// texture filtering
GLenum gFiltering = GL_LINEAR;

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

    // set blending
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
    // load and color key texture
    if (!gStretchedTexture.loadTextureFromFile("./images/mini_opengl.png")) {
        cout << "Unable to load mini texture!" << endl;
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

    // render texture stretched
    gStretchedTexture.render(0.f, 0.f, NULL, &gStretchRect);

    // update screen
    glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y)
{
    if (key == 'q') {
        // bind texture for modification
        glBindTexture(GL_TEXTURE_2D, gStretchedTexture.getTextureID());

        // toggle linear/nearest filtering
        if (gFiltering != GL_LINEAR) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            gFiltering = GL_LINEAR;
        } else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

            gFiltering = GL_NEAREST;
        }
    }

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}
