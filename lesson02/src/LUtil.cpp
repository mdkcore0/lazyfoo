#include "LUtil.h"

using namespace std;

int gColorMode = COLOR_MODE_CYAN;
GLfloat gProjectionScale =1.f;

bool initGL()
{
    // initialize projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

    // initializee modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);

    // check for error
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        cout << "Error initializing OpenGl! " << gluErrorString(error) << endl;
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

    // reset modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // move to center of the screen
    glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f);

    // render quad
    if (gColorMode == COLOR_MODE_CYAN) {
        // solid cyan
        glBegin(GL_QUADS);
            glColor3f(0.f, 1.f, 1.f);
            glVertex2f(-50.f, -50.f);
            glVertex2f( 50.f, -50.f);
            glVertex2f( 50.f,  50.f);
            glVertex2f(-50.f,  50.f);
        glEnd();
    } else {
        // rygb mix
        glBegin(GL_QUADS);
            glColor3f(1.f, 0.f, 0.f);
            glVertex2f(-50.f, -50.f);

            glColor3f(1.f, 1.f, 0.f);
            glVertex2f( 50.f, -50.f);

            glColor3f(0.f, 1.f, 0.f);
            glVertex2f( 50.f,  50.f);

            glColor3f(0.f, 0.f, 1.f);
            glVertex2f(-50.f,  50.f);
        glEnd();
    }

    // update screen
    glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y)
{
    if (key == 'q') {
        // toggle color mode
        if (gColorMode == COLOR_MODE_CYAN)
            gColorMode = COLOR_MODE_MULTI;
        else
            gColorMode = COLOR_MODE_CYAN;
    } else if (key == 'e') {
        // cycle through projection scales
        if (gProjectionScale == 1.f)
            // zoom out
            gProjectionScale = 2.f;
        else if (gProjectionScale == 2.f)
            // zoom in
            gProjectionScale = 0.5f;
        else if (gProjectionScale == 0.5f)
            // regular zoom
            gProjectionScale = 1.f;
    }

    // update projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, SCREEN_WIDTH * gProjectionScale, SCREEN_HEIGHT * gProjectionScale,
            0.0, 1.0, -1.0);
}
