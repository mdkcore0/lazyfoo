#include <IL/il.h>
#include <IL/ilu.h>
#include <string.h>

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

bool LTexture::loadPixelsFromFile(string path)
{
    // deallocate texture data
    freeTexture();

    // texture loading success
    bool pixelsLoaded = false;

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

            // allocate memoru for texture data
            GLuint size = texWidth * texHeight;
            m_pixels = new GLuint[size];

            // get image dimensions
            m_imageWidth = imgWidth;
            m_imageHeight = imgHeight;
            m_textureWidth = texWidth;
            m_textureHeight = texHeight;

            // copy pixels
            memcpy(m_pixels, ilGetData(), size * 4);
            pixelsLoaded = true;
        }

        // delete file from memory
        ilDeleteImages(1, &imgID);
    }

    // report error
    if (!pixelsLoaded) {
        cout << "Unable to load " << path << endl;
    }

    return pixelsLoaded;
}

bool LTexture::loadTextureFromPixels32()
{
    // loading flag
    bool success = true;

    // there is loaded pixels
    if (m_textureID == 0 && m_pixels != nullptr) {
        // generate texture ID
        glGenTextures(1, &m_textureID);

        // bind texture ID
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        // generate texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_textureWidth, m_textureHeight,
                0, GL_RGBA, GL_UNSIGNED_BYTE, m_pixels);

        // set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);

        // check for error
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            cout << "Error loading texture from " << m_pixels << " pixels!" <<
                gluErrorString(error) << endl;
            success = false;
        } else {
            // release pixels;
            delete []m_pixels;
            m_pixels = nullptr;
        }
    }
    // error
    else {
        cout << "Cannot load texture from current pixels!" << endl;

        // texture already exists
        if (m_textureID != 0)
            cout << "A texture is already loaded!" << endl;
        else if (m_pixels == nullptr)
            cout << "No pixels to create texture from!" << endl;

        success = false;
    }

    return success;
}

bool LTexture::loadTextureFromFileWithColorKey(std::string path,
        GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
    // load pixels
    if (!loadPixelsFromFile(path))
        return false;

    // go through pixels
    GLuint size = m_textureWidth * m_textureHeight;
    int i;
    for (i = 0; i < (int)size; i++) {
        // get pixel colors
        GLubyte *colors = (GLubyte *)&m_pixels[i];

        // color matches
        if (colors[0] == r && colors[1] == g && colors[2] == b &&
                (0 == a || colors[3] == a)) {
            // make transparent
            colors[0] = 255;
            colors[1] = 255;
            colors[2] = 255;
            colors[3] = 000;
        }
    }

    // create texture
    return loadTextureFromPixels32();
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

void LTexture::render(GLfloat x, GLfloat y, LFRect *clip, LFRect *stretch,
        GLfloat degrees)
{
    if (m_textureID != 0) {
        // remove any previous transformations
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

        // handle stretching
        if (stretch != NULL) {
            quadWidth = stretch->w;
            quadHeight = stretch->h;
        }

        // move to rendering point
        //glTranslatef(x, y, 0.f);
        glTranslatef(x + quadWidth / 2.f, y + quadHeight / 2.f, 0.f);

        // rotate around rendering point
        glRotatef(degrees, 0.f, 0.f, 1.f);

        // set texture ID
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        // render textured quad
        glBegin(GL_QUADS);
            glTexCoord2f(texLeft, texTop);
            glVertex2f(-quadWidth / 2.f, -quadHeight / 2.f);

            glTexCoord2f(texRight, texTop);
            glVertex2f(quadWidth / 2.f, -quadHeight / 2.f);

            glTexCoord2f(texRight, texBottom);
            glVertex2f(quadWidth / 2.f, quadHeight / 2.f);

            glTexCoord2f(texLeft, texBottom);
            glVertex2f(-quadWidth / 2.f, quadHeight / 2.f);
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
