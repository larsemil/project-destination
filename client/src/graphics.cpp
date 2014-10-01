#include <cmath>
#include <cstdio>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
//#include "functions.hpp"

/* Credit to pnaxighn and krumms on gamedev.net */
GLuint LoadTexture(const char* filename, int wrap)
{
    GLuint retval;
    SDL_Surface* surface;
    void* raw;
    int w, h, i, j, bpp;
    Uint8 *srcPixel, *dstPixel;
    Uint32 truePixel;
    GLenum errorCode;

    surface = IMG_Load(filename);

    if (!surface)
    {
        printf("SDL_Image load error: %s\n", IMG_GetError());
        return 0;
    }

    if (surface->format->BytesPerPixel < 2)
    {
        printf("Bad image -- not true color!\n");
        SDL_FreeSurface(surface);
        return 0;
    }

    w = surface->w;
    h = surface->h;

    raw = (void*)malloc(w * h * 4);
    dstPixel = (Uint8*)raw;

    SDL_LockSurface(surface);

    bpp = surface->format->BytesPerPixel;

    for (i = h - 1; i >= 0; --i)
    {
        for (j = 0; j < w; ++j)
        {
            srcPixel = (Uint8*)surface->pixels + i * surface->pitch + j * bpp;
            switch (bpp)
            {
                case 1:
                    truePixel = *srcPixel;
                    break;
                case 2:
                    truePixel = *(Uint16*)srcPixel;
                    break;
                case 3:
                    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                    {
                        truePixel = srcPixel[0] << 16 | srcPixel[1] << 8
                            | srcPixel[2];
                    }
                    else 
                    {
                        truePixel = srcPixel[0] | srcPixel[1] << 8
                            | srcPixel[2] << 16;
                    }
                    break;
                case 4:
                    truePixel = *(Uint32*)srcPixel;
                    break;
                default:
                    printf("Image bpp of %d unusable\n", bpp);
                    SDL_UnlockSurface(surface);
                    SDL_FreeSurface(surface);
                    free(raw);
                    return 0;
            }

            SDL_GetRGBA(truePixel, surface->format, &(dstPixel[0]),
                    &(dstPixel[1]), &(dstPixel[2]), &(dstPixel[3]));
            dstPixel += 4;
        }
    }
            
    SDL_UnlockSurface(surface);
    SDL_FreeSurface(surface);

    while (glGetError()) { ; }

    glGenTextures(1, &retval);
    glBindTexture(GL_TEXTURE_2D, retval);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            wrap ? GL_REPEAT : GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
            wrap ? GL_REPEAT : GL_CLAMP);

    errorCode = glGetError();
    if (errorCode != 0)
    {
        if (errorCode == GL_OUT_OF_MEMORY)
        {
            printf("Out of texture memory!\n");
        }

        glDeleteTextures(1, &retval);
        free(raw);
        return 0;
    }

    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, w, h, GL_RGBA, GL_UNSIGNED_BYTE,
            (Uint8*)raw);

    errorCode = glGetError();
    if (errorCode != 0)
    {
        if (errorCode == GL_OUT_OF_MEMORY)
        {
            printf("Out of texture memory!\n");
        }

        glDeleteTextures(1, &retval);
        free(raw);
        return 0;
    }

    return retval;
}

float deg2rad(float val)
{
  return (2 * M_PI * val) / 360.0;
}
