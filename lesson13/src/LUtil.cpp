#include <IL/il.h>
#include <IL/ilu.h>

#include "LUtil.h"
#include "LTexture.h"

using namespace std;

// OpenGL texture
LTexture gRotatingTexture;

// angle
GLfloat gAngle = 0.f;

// transformation state
int gTransformationCombo = 0;

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
    if (!gRotatingTexture.loadTextureFromFile("./images/texture.png")) {
        cout << "Unable to load OpenGL texture!" << endl;
        return false;
    }

    return true;
}

void update()
{
    // rotate
    gAngle += 360.f / SCREEN_FPS;

    // cap angle
    if (gAngle > 360.f)
        gAngle -= 360.f;
}

void render()
{
    // clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // reset transformation
    glLoadIdentity();

    // render current scene transformation arrow
    switch (gTransformationCombo) {
        case 0:
            glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f);
            glRotatef(gAngle, 0.f, 0.f, 1.f);
            glScalef(2.f, 2.f, 0.f);
            glTranslatef(gRotatingTexture.imageWidth() / -2.f,
                    gRotatingTexture.imageHeight() / -2.f, 0.f);
            break;
        case 1:
            glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f);
            glRotatef(gAngle, 0.f, 0.f, 1.f);
            glTranslatef(gRotatingTexture.imageWidth() / -2.f,
                    gRotatingTexture.imageHeight() / -2.f, 0.f);
            glScalef(2.f, 2.f, 0.f);
            break;
        case 2:
            glScalef(2.f, 2.f, 0.f);
            glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f);
            glRotatef(gAngle, 0.f, 0.f, 1.f);
            glTranslatef(gRotatingTexture.imageWidth() / -2.f,
                    gRotatingTexture.imageHeight() / -2.f, 0.f);
            break;
        case 3:
            glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f);
            glRotatef(gAngle, 0.f, 0.f, 1.f);
            glScalef(2.f, 2.f, 0.f);
            break;
        case 4:
            glRotatef(gAngle, 0.f, 0.f, 1.f);
            glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f);
            glScalef(2.f, 2.f, 0.f);
            glTranslatef(gRotatingTexture.imageWidth() / -2.f,
                    gRotatingTexture.imageHeight() / -2.f, 0.f);
            break;
    }

    // render texture
    gRotatingTexture.render(0.f, 0.f);

    // update screen
    glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y)
{
    if (key == 'q') {
        // reset rotation
        gAngle = 0.f;

        // cycle through combinations
        gTransformationCombo++;
        if (gTransformationCombo > 4)
            gTransformationCombo = 0;
    }
}
