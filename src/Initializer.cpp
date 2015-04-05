#include "Initializer.hpp"

#define IMG_INIT_FLAGS IMG_INIT_PNG

namespace Llama
{
    Initializer::Initializer()
    {
        LOG_STRING("Initializer commenced");
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            throw InitException;
        }
        if(!(IMG_Init(IMG_INIT_FLAGS) & IMG_INIT_FLAGS))
        {
            throw InitException;
        }
        if(!(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 )))
        {
            LOG_STRING("Warning! Sound disabled!");
        }
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            LOG_STRING("Warning! Linear texture filtering disabled!");
        }
        if(!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1"))
        {
            LOG_STRING("Warning! Vertical synchronization disabled!");
        }
    }


    Initializer::~Initializer()
    {
        LOG_STRING("Initializer shutting down.");
        IMG_Quit();
        Mix_Quit();
        SDL_Quit();
    }

}
