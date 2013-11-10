#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <GL/gl.h>
#include <SDL2/SDL.h>

class Image
{
public:
    Image(SDL_Surface* surface);
    ~Image();
    const SDL_Surface* getSurface() const;

private:
    SDL_Surface* surface;
};

class GLTexture
{
public:
    GLTexture(const Image &image);
    ~GLTexture();
    GLuint get();
    void bind() const;
    static void unbind();
    int getWidth();
    int getHeight();

private:
    int bpp, w, h;
    GLenum format;
    GLuint texture;
};

#endif // IMAGE_H_INCLUDED
