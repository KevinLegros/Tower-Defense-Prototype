#ifndef _SPRITELOADER_HPP_
#define _SPRITELOADER_HPP_

#include <SDL.h>
#include <SDL_image.h>

class SpriteLoader {
    public:
        SpriteLoader();

    public:
        static SDL_Surface* loadPNG(char* File);
        static SDL_Surface* loadBMP(char* File);

        static bool render(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);

        static bool render(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);

        static bool makeTransparent(SDL_Surface* Surf_Dest, int R, int G, int B);
};

#endif
