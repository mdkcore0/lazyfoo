#include <IL/il.h>

#include "LTexture.h"

using namespace std;

LTexture::LTexture()
{
    m_textureID = 0;
    m_textureWidth = 0;
    m_textureHeight = 0;
}

LTexture::~LTexture()
{
    freeTexture();
}

bool LTexture::loadTextureFromFile(string path)
{
    bool textureLoaded = false;

    // generate and set current image ID
    ILuint imgID = 0;
    ilGenImages(1, &imgID);
    ilBindImage(imgID);

    // load image
    ILboolean success = ilLoadImage(path.c_str());

    // image loaded successfully
    if (success == IL_TRUE) {
        // convert image to RGBA
        success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

        if (success == IL_TRUE) {
            // create texture from pixels
            textureLoaded = loadTextureFromPixels32((GLuint *)ilGetData(),
                    (GLuint)ilGetInteger(IL_IMAGE_WIDTH),
                    (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
        }

        // delete file from memory
        ilDeleteImages(1, &imgID);
    }

    // report error
    if (!textureLoaded)
        cout << "Unable to load " << path << endl;

    return textureLoaded;
}

bool LTexture::loadTextureFromPixels32(GLuint *pixels, GLuint width, GLuint height)
{
    freeTexture();

    m_textureWidth = height;
    m_textureHeight = height;

    // generate texture ID
    glGenTextures(1, &m_textureID);

    // bind texture ID
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // generate texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, pixels);

    // set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // check for error
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        cout << "Error loading texture from " << pixels << " pixels"
            << gluErrorString(error) << endl;
        return false;
    }

    return true;
}

void LTexture::freeTexture()
{
    if (m_textureID != 0) {
        glDeleteTextures(1, &m_textureID);
        m_textureID = 0;
    }

    m_textureWidth = 0;
    m_textureHeight = 0;
}

void LTexture::render(GLfloat x, GLfloat y, LFRect *clip)
{
    if (m_textureID != 0) {
        // remove anu previous transformations
        glLoadIdentity();

        // texture coordinates
        GLfloat texTop = 0.1f;
        GLfloat texBottom = 0.1f;
        GLfloat texLeft = 0.1f;
        GLfloat texRight = 0.1f;

        // vertex coordinates
        GLfloat quadWidth = m_textureWidth;
        GLfloat quadHeight = m_textureHeight;

        // handle clipping
        if (clip != NULL) {
            // texture coordinates
            texLeft = clip->x / m_textureWidth;
            texRight = (clip->x + clip->w) / m_textureWidth;
            texTop = clip->y / m_textureHeight;
            texBottom = (clip->y + clip->h) / m_textureHeight;

            // vertex coordinates
            quadWidth = clip->w;
            quadHeight = clip->h;
        }

        // move to rendering point
        glTranslatef(x, y, 0.f);

        // set texture ID
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        // render textured quad
        glBegin(GL_QUADS);
            glTexCoord2f(texLeft, texTop);
            glVertex2f(0.f, 0.f);

            glTexCoord2f(texRight, texTop);
            glVertex2f(quadWidth, 0.f);

            glTexCoord2f(texRight, texBottom);
            glVertex2f(quadWidth, quadHeight);

            glTexCoord2f(texLeft, texBottom);
            glVertex2f(0.f, quadHeight);
        glEnd();
    }
}

GLuint LTexture::getTextureID()
{
    return m_textureID;
}

GLuint LTexture::textureWidth()
{
    return m_textureWidth;
}

GLuint LTexture::textureHeight()
{
    return m_textureHeight;
}
