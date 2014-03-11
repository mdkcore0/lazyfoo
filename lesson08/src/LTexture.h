#ifndef __LTEXTURE_H__
#define __LTEXTURE_H__

#include <iostream>
#include <string>

#include "LOpenGL.h"
#include "LFRect.h"

class LTexture
{
public:
    LTexture();
    ~LTexture();

    bool loadTextureFromFile(std::string path);
    bool loadTextureFromPixels32(GLuint *pixels, GLuint imgWidth,
            GLuint imgHeight, GLuint texWidth, GLuint texHeight);
    void freeTexture();

    void render(GLfloat x, GLfloat y, LFRect *clip = NULL);

    GLuint getTextureID();
    GLuint textureWidth();
    GLuint textureHeight();

    GLuint imageWidth();
    GLuint imageHeight();

private:
    GLuint powerOfTwo(GLuint num);

    GLuint m_textureID;
    GLuint m_textureWidth;
    GLuint m_textureHeight;

    GLuint m_imageWidth;
    GLuint m_imageHeight;
};

#endif
