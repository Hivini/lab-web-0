#include <stdio.h>
#include <SDL/SDL.h>
#include <emscripten.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

extern "C" int main(int argc, char **argv)
{
    printf("Hello, running now\n");
    return 0;
}
#ifdef __cplusplus
extern "C"
{
#endif

    EMSCRIPTEN_KEEPALIVE void createSquare(int argc, char **argv)
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Surface *screen = SDL_SetVideoMode(256, 256, 32, SDL_SWSURFACE);

#ifdef TEST_SDL_LOCK_OPTS
        EM_ASM("SDL.defaults.copyOnLock = false; SDL.defaults.discardOnLock = true; SDL.defaults.opaqueFrontBuffer = false;");
#endif

        if (SDL_MUSTLOCK(screen))
            SDL_LockSurface(screen);
        for (int i = 0; i < 256; i++)
        {
            for (int j = 0; j < 256; j++)
            {
#ifdef TEST_SDL_LOCK_OPTS
                // Alpha behaves like in the browser, so write proper opaque pixels.
                int alpha = 255;
#else
            // To emulate native behavior with blitting to screen, alpha component is ignored. Test that it is so by outputting
            // data (and testing that it does get discarded)
            int alpha = (i + j) % 255;
#endif
                *((Uint32 *)screen->pixels + i * 256 + j) = SDL_MapRGBA(screen->format, i, j, 255 - i, alpha);
            }
        }
        if (SDL_MUSTLOCK(screen))
            SDL_UnlockSurface(screen);
        SDL_Flip(screen);
        printf("Created square inverted square.");
        SDL_Quit();
    }

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    EMSCRIPTEN_KEEPALIVE void invertedSquare(int argc, char **argv)
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Surface *screen = SDL_SetVideoMode(256, 256, 32, SDL_SWSURFACE);

#ifdef TEST_SDL_LOCK_OPTS
        EM_ASM("SDL.defaults.copyOnLock = false; SDL.defaults.discardOnLock = true; SDL.defaults.opaqueFrontBuffer = false;");
#endif

        if (SDL_MUSTLOCK(screen))
            SDL_LockSurface(screen);
        for (int i = 255; i >= 0; i--)
        {
            for (int j = 255; j >= 0; j--)
            {
#ifdef TEST_SDL_LOCK_OPTS
                // Alpha behaves like in the browser, so write proper opaque pixels.
                int alpha = 255;
#else
            // To emulate native behavior with blitting to screen, alpha component is ignored. Test that it is so by outputting
            // data (and testing that it does get discarded)
            int alpha = (i + j) % 255;
#endif
                *((Uint32 *)screen->pixels + i * 256 + j) = SDL_MapRGBA(screen->format, j, i, 255 - i, alpha);
            }
        }
        if (SDL_MUSTLOCK(screen))
            SDL_UnlockSurface(screen);
        SDL_Flip(screen);

        printf("Created square inverted square.");

        SDL_Quit();
    }

#ifdef __cplusplus
}
#endif