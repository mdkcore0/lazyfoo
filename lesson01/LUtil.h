#ifndef __LUTIL_H__
#define __LUTIL_H__

#include "LOpenGL.h"
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;

bool initGL();

void update();
void render();

#endif
