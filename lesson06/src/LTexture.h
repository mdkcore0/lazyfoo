#ifndef __LTEXTURE_H__
#define __LTEXTURE_H__

#include <iostream>
#include <string>

#include "LOpenGL.h"

class LTexture
{
public:
    LTexture();
    ~LTexture();

    bool loadTextureFromFile(std::string path);
    bool loadTextureFromPixels32(GLuint *pixels, GLuint width, GLuint height);
    void freeTexture();

    void render(GLfloat x, GLfloat y);

    GLuint getTextureID();
    GLuint textureWidth();
    GLuint textureHeight();

private:
    GLuint m_textureID;
    GLuint m_textureWidth;
    GLuint m_textureHeight;
};

#endif
