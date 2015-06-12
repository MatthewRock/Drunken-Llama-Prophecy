#include "Initializer.hpp"

#define IMG_INIT_FLAGS IMG_INIT_PNG

/// \brief Initializes SDL systems.
Initializer::Initializer()
{
    LOG_STRING("Initializer commenced");
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        throw InitException;
    }
    LOG_STRING("SDL systems loaded.");
    if(!(IMG_Init(IMG_INIT_FLAGS) & IMG_INIT_FLAGS))
    {
        throw InitException;
    }
    LOG_STRING("Images system loaded.");

    if(Sounds::Init())
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
/// \brief Closes all SDL systems.
Initializer::~Initializer()
{
    LOG_STRING("Initializer shutting down.");
    IMG_Quit();
    Sounds::Close();
    SDL_Quit();
}

