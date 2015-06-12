#ifndef INITIALIZER_HPP
#define INITIALIZER_HPP

#include <exception>
#include "Logger.hpp"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Sounds.hpp"


/** \brief Class that will be either created once, or inherited privately. This will allow to use RAII to initialize and close systems.
           Voila! No WTFs when encountering some strange functions!
 */
class Initializer
{
    class InitializerException: public std::exception
    {
        virtual const char* what() const throw()
        {
            LOG_STRING("Initializer has thrown an exception: ");
            std::string returned = "Initialization of SDL Modules failed! SDL_Error: ";
            returned = returned + SDL_GetError();
            LOG_STRING(returned);
            return returned.c_str();
        }
    }InitException;
    public:
        //Everything we need will be initialized in Initializer's constructor,
        Initializer();
        //And deleted in destructor.
        ~Initializer();
    protected:
    private:
};
#endif // INITIALIZER_HPP
