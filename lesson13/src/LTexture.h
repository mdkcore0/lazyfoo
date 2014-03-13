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
    bool loadPixelsFromFile(std::string path);
    bool loadTextureFromPixels32();
    bool loadTextureFromFileWithColorKey(std::string path,
            GLubyte r, GLubyte g, GLubyte b, GLubyte a = 000);
    void freeTexture();

    void render(GLfloat x, GLfloat y, LFRect *clip = NULL, LFRect *stretch = NULL);

    bool lock();
    bool unlock();

    GLuint *getPixelData32();
    GLuint getPixel32(GLuint x, GLuint y);
    void setPixel32(GLuint x, GLuint y, GLuint pixel);

    GLuint getTextureID();
    GLuint textureWidth();
    GLuint textureHeight();

    GLuint imageWidth();
    GLuint imageHeight();

private:
    GLuint powerOfTwo(GLuint num);

    GLuint m_textureID;

    // current pixels
    GLuint *m_pixels;

    GLuint m_textureWidth;
    GLuint m_textureHeight;

    GLuint m_imageWidth;
    GLuint m_imageHeight;
};

#endif
