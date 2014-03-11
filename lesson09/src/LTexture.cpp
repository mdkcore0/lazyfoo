#include <IL/il.h>
#include <IL/ilu.h>

#include "LTexture.h"

using namespace std;

LTexture::LTexture()
{
    m_textureID = 0;
    m_pixels = nullptr;

    m_textureWidth = 0;
    m_textureHeight = 0;

    m_imageWidth = 0;
    m_imageHeight = 0;
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
            // initialize dimensions
            GLuint imgWidth = (GLuint)ilGetInteger(IL_IMAGE_WIDTH);
            GLuint imgHeight = (GLuint)ilGetInteger(IL_IMAGE_HEIGHT);

            // calculate required texture dimensions
            GLuint texWidth = powerOfTwo(imgWidth);
            GLuint texHeight = powerOfTwo(imgHeight);

            // texture is the wrong size
            if (imgWidth != texWidth || imgHeight != texHeight) {
                // place image at upper left
                iluImageParameter(ILU_PLACEMENT, ILU_UPPER_LEFT);

                // resize image
                iluEnlargeCanvas((int)texWidth, (int)texHeight, 1);
            }

            // create texture from pixels
            textureLoaded = loadTextureFromPixels32((GLuint *)ilGetData(),
                    imgWidth, imgHeight, texWidth, texHeight);
        }

        // delete file from memory
        ilDeleteImages(1, &imgID);
    }

    // report error
    if (!textureLoaded)
        cout << "Unable to load " << path << endl;

    return textureLoaded;
}

bool LTexture::loadTextureFromPixels32(GLuint *pixels, GLuint imgWidth,
            GLuint imgHeight, GLuint texWidth, GLuint texHeight)

{
    freeTexture();

    // get image dimensions
    m_imageWidth = imgWidth;
    m_imageHeight = imgHeight;
    m_textureWidth = texWidth;
    m_textureHeight = texHeight;

    // generate texture ID
    glGenTextures(1, &m_textureID);

    // bind texture ID
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // generate texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_textureWidth, m_textureHeight, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, pixels);

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

    if (m_pixels != nullptr) {
        delete[] m_pixels;
        m_pixels = nullptr;
    }

    m_textureWidth = 0;
    m_textureHeight = 0;

    m_imageWidth = 0;
    m_imageHeight = 0;
}

void LTexture::render(GLfloat x, GLfloat y, LFRect *clip)
{
    if (m_textureID != 0) {
        // remove anu previous transformations
        glLoadIdentity();

        // texture coordinates
        GLfloat texTop = 0.f;
        GLfloat texBottom = (GLfloat)m_imageHeight / (GLfloat)m_textureHeight;
        GLfloat texLeft = 0.f;
        GLfloat texRight = (GLfloat)m_imageWidth / (GLfloat)m_textureWidth;

        // vertex coordinates
        GLfloat quadWidth = m_imageWidth;
        GLfloat quadHeight = m_imageHeight;

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

bool LTexture::lock() {
    if (m_pixels == nullptr && m_textureID != 0) {
        // allocate memoru for texture data
        GLuint size = m_textureWidth * m_textureHeight;
        m_pixels = new GLuint[size];

        // set current texture
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        // get pixels
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_pixels);

        // unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);

        return true;
    }

    return false;
}

bool LTexture::unlock()
{
    if (m_pixels != nullptr && m_textureID != 0) {
        // set current texture
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        // update texture
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_textureWidth, m_textureHeight,
                GL_RGBA, GL_UNSIGNED_BYTE, m_pixels);

        // delete pixels
        delete []m_pixels;
        m_pixels = nullptr;

        // unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);

        return true;
    }

    return false;
}

GLuint *LTexture::getPixelData32()
{
    return m_pixels;
}

GLuint LTexture::getPixel32(GLuint x, GLuint y)
{
    return m_pixels[y * m_textureWidth + x];
}

void LTexture::setPixel32(GLuint x, GLuint y, GLuint pixel)
{
    m_pixels[y * m_textureWidth + x] = pixel;
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

GLuint LTexture::imageWidth()
{
    return m_imageWidth;
}

GLuint LTexture::imageHeight()
{
    return m_imageHeight;
}

GLuint LTexture::powerOfTwo(GLuint num)
{
    if (num != 0) {
        num--;
        num |= (num >> 1); // or first 2 bits
        num |= (num >> 2); // or next 2 bits
        num |= (num >> 4); // or next 4 bits
        num |= (num >> 8); // or next 8 bits
        num |= (num >> 16); // or next 16 bits
        num++;
    }

    return num;
}
