#include "Initializer.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include "Logger.hpp"

#define

namespace Llama
{
    Initializer::Initializer()
    {
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            throw std::runtime_error("Initializing SDL failed! :(\n");
        }

        if(IMG_Init())

    }

    Initializer::~Initializer()
    {

    }

}
