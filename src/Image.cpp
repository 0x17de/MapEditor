#include "Image.h"

Image::Image(SDL_Surface *surface)
:
    surface(surface)
{}

Image::~Image()
{
    SDL_FreeSurface(surface);
}

const SDL_Surface* Image::getSurface() const
{
    return surface;
}

GLTexture::GLTexture(const Image &image)
{
    const SDL_Surface* surface = image.getSurface();
    bbp = surface->format->BytesPerPixel;
    w = surface->w;
    h = surface->h;

    format = surface->format->BytesPerPixel == 4 ?
        SDL_BYTEORDER == SDL_BIG_ENDIAN ? GL_BGRA : GL_RGBA
    :
        SDL_BYTEORDER == SDL_BIG_ENDIAN ? GL_BGR : GL_RGB;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, bbp, w, h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLTexture::~GLTexture()
{
    glDeleteTextures(1, &texture);
}

GLuint GLTexture::get()
{
    return texture;
}

int GLTexture::getWidth()
{
    return w;
}

int GLTexture::getHeight()
{
    return h;
}
