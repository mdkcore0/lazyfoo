#include "LUtil.h"

using namespace std;

// viewport mode
int glViewportMode = VIEWPORT_MODE_FULL;

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
    glLoadIdentity();

    // move to center of the screen
    glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f);

    // NOTE: on GLUT, the viewport coordinates y+ is up and y- is down
    // full view
    if (glViewportMode == VIEWPORT_MODE_FULL) {
        // fill the screen
        glViewport(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);

        // red quad
        glBegin(GL_QUADS);
            glColor3f(1.f, 0.f, 0.f);
            glVertex2f(-SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f);
            glVertex2f( SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f);
            glVertex2f( SCREEN_WIDTH / 2.f,  SCREEN_HEIGHT / 2.f);
            glVertex2f(-SCREEN_WIDTH / 2.f,  SCREEN_HEIGHT / 2.f);
        glEnd();
    }
    // viewport at center of screen
    else if (glViewportMode == VIEWPORT_MODE_HALF_CENTER) {
        // center viewport
        glViewport(SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 4.f, SCREEN_WIDTH / 2.f,
                SCREEN_HEIGHT / 2.f);

        // green quad
        glBegin(GL_QUADS);
            glColor3f(0.f, 1.f, 0.f);
            glVertex2f(-SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f);
            glVertex2f( SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f);
            glVertex2f( SCREEN_WIDTH / 2.f,  SCREEN_HEIGHT / 2.f);
            glVertex2f(-SCREEN_WIDTH / 2.f,  SCREEN_HEIGHT / 2.f);
        glEnd();
    }
    // viewport centered at the top
    else if (glViewportMode == VIEWPORT_MODE_HALF_TOP) {
        // viewport at top
        glViewport(SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 2.f, SCREEN_WIDTH / 2.f,
                SCREEN_HEIGHT / 2.f);

        // blue quad
        glBegin(GL_QUADS);
            glColor3f(0.f, 0.f, 1.f);
            glVertex2f(-SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f);
            glVertex2f( SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f);
            glVertex2f( SCREEN_WIDTH / 2.f,  SCREEN_HEIGHT / 2.f);
            glVertex2f(-SCREEN_WIDTH / 2.f,  SCREEN_HEIGHT / 2.f);
        glEnd();
    }
    // four viewports
    else if (glViewportMode == VIEWPORT_MODE_QUAD) {
        // bottom left red quad
        glViewport(0.f, 0.f, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);

        glBegin(GL_QUADS);
            glColor3f(1.f, 0.f, 0.f);
            glVertex2f(-SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
            glVertex2f( SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
            glVertex2f( SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f);
            glVertex2f(-SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f);
        glEnd();

        // bottom right green quad
        glViewport(SCREEN_WIDTH / 2.f, 0.f, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);

        glBegin(GL_QUADS);
            glColor3f(0.f, 1.f, 0.f);
            glVertex2f(-SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
            glVertex2f( SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
            glVertex2f( SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f);
            glVertex2f(-SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f);
        glEnd();

        // top left blue quad
        glViewport(0.f, SCREEN_HEIGHT / 2.f, SCREEN_WIDTH / 2.f,
                SCREEN_HEIGHT / 2.f);

        glBegin(GL_QUADS);
            glColor3f(0.f, 0.f, 1.f);
            glVertex2f(-SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
            glVertex2f( SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
            glVertex2f( SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f);
            glVertex2f(-SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f);
        glEnd();

        // top right yellow quad
        glViewport(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, SCREEN_WIDTH / 2.f,
                SCREEN_HEIGHT / 2.f);

        glBegin(GL_QUADS);
            glColor3f(1.f, 1.f, 0.f);
            glVertex2f(-SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
            glVertex2f( SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
            glVertex2f( SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f);
            glVertex2f(-SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f);
        glEnd();
    }
    // viewport with radar subview port
    else if (glViewportMode == VIEWPORT_MODE_RADAR) {
        // full size quad
        glViewport(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);

        glBegin(GL_QUADS);
            glColor3f(1.f, 1.f, 1.f);
            glVertex2f(-SCREEN_WIDTH / 8.f, -SCREEN_HEIGHT / 8.f);
            glVertex2f( SCREEN_WIDTH / 8.f, -SCREEN_HEIGHT / 8.f);
            glVertex2f( SCREEN_WIDTH / 8.f,  SCREEN_HEIGHT / 8.f);
            glVertex2f(-SCREEN_WIDTH / 8.f,  SCREEN_HEIGHT / 8.f);

            glColor3f(0.f, 0.f, 0.f);
            glVertex2f(-SCREEN_WIDTH / 16.f, -SCREEN_HEIGHT / 16.f);
            glVertex2f( SCREEN_WIDTH / 16.f, -SCREEN_HEIGHT / 16.f);
            glVertex2f( SCREEN_WIDTH / 16.f,  SCREEN_HEIGHT / 16.f);
            glVertex2f(-SCREEN_WIDTH / 16.f,  SCREEN_HEIGHT / 16.f);
        glEnd();

        // radar quad
        glViewport(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, SCREEN_WIDTH / 2.f,
                SCREEN_HEIGHT / 2.f);

        glBegin(GL_QUADS);
            glColor3f(1.f, 1.f, 1.f);
            glVertex2f(-SCREEN_WIDTH / 8.f, -SCREEN_HEIGHT / 8.f);
            glVertex2f( SCREEN_WIDTH / 8.f, -SCREEN_HEIGHT / 8.f);
            glVertex2f( SCREEN_WIDTH / 8.f,  SCREEN_HEIGHT / 8.f);
            glVertex2f(-SCREEN_WIDTH / 8.f,  SCREEN_HEIGHT / 8.f);

            glColor3f(0.f, 0.f, 0.f);
            glVertex2f(-SCREEN_WIDTH / 16.f, -SCREEN_HEIGHT / 16.f);
            glVertex2f( SCREEN_WIDTH / 16.f, -SCREEN_HEIGHT / 16.f);
            glVertex2f( SCREEN_WIDTH / 16.f,  SCREEN_HEIGHT / 16.f);
            glVertex2f(-SCREEN_WIDTH / 16.f,  SCREEN_HEIGHT / 16.f);
        glEnd();
    }

    // update screen
    glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y)
{
    if (key == 'q') {
        // cycle through viewport modes
        glViewportMode++;

        if (glViewportMode > VIEWPORT_MODE_RADAR)
            glViewportMode = VIEWPORT_MODE_FULL;
    }
}
