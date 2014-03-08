#include "LUtil.h"

using namespace std;

// camera position
GLfloat gCameraX = 0.f;
GLfloat gCameraY = 0.f;

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

    // save the default modelview matrix (a copy of the matrix for future use)
    glPushMatrix();

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

    // pop default matrix onto current matrix
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // save default matrix again
    glPushMatrix();

    // move to center of the screen
    glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f);

    // NOTE: on GLUT, the viewport coordinates y+ is up and y- is down

    // red quad
    glBegin(GL_QUADS);
        glColor3f(1.f, 0.f, 0.f);
        glVertex2f(-SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
        glVertex2f( SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
        glVertex2f( SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f);
        glVertex2f(-SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f);
    glEnd();

    // move to the right of the screen
    glTranslatef(SCREEN_WIDTH, 0.f, 0.f);

    // green quad
    glBegin(GL_QUADS);
        glColor3f(0.f, 1.f, 0.f);
        glVertex2f(-SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
        glVertex2f( SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
        glVertex2f( SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f);
        glVertex2f(-SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f);
    glEnd();

    // move to the lower right of the screen
    glTranslatef(0.f, SCREEN_HEIGHT, 0.f);

    // blue quad
    glBegin(GL_QUADS);
        glColor3f(0.f, 0.f, 1.f);
        glVertex2f(-SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
        glVertex2f( SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
        glVertex2f( SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f);
        glVertex2f(-SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f);
    glEnd();

    // move below the screen
    glTranslatef(-SCREEN_WIDTH, 0.f, 0.f);

    glBegin(GL_QUADS);
        glColor3f(1.f, 1.f, 0.f);
        glVertex2f(-SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
        glVertex2f( SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
        glVertex2f( SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f);
        glVertex2f(-SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f);
    glEnd();

    // update screen
    glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y)
{
    if (key == 'w')
        gCameraY -= 16.f;
    else if (key == 's')
        gCameraY += 16.f;
    else if (key == 'a')
        gCameraX -= 16.f;
    else if (key == 'd')
        gCameraX += 16.f;

    // take saved matrix off the stack and reset it
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glLoadIdentity();

    // move camera to position
    glTranslatef(-gCameraX, -gCameraY, 0.f);

    // save default matrix again with camera translation
    glPushMatrix();
}
