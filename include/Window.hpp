#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <exception>
#include <string>
#include "Logger.hpp"
/**
  * Window is a wrapper class for SDL_Window and its SDL_Renderer.
  * Window makes it easy to use Renderer specific for window.
  * It also holds its width and height.
  * If Window can not be allocated, a WindowException is thrown.
  * Window is intended to be used as a ready object; it does not have to be used as pointer.
  *
  */
namespace Llama
{

    class Window
    {
        //WindowException class. Shows SDL_Error. Declaration of class + creation of private instance
        class WindowException : public std::exception
        {
            virtual const char* what() const throw()
            {
                //Save the information to log
                Logger::Get()->Log("Window has thrown an exception:");

                std::string returned = "Initialization of Window failed! SDL_Error: ";
                returned = returned + SDL_GetError();

                Logger::Get()->Log(returned);

                return returned.c_str();
            }
        }WinException;

    public:
        Window();
        Window(const char* name, int w, int h);

        ~Window();
        //Create window
        void Init(const char*, int, int );
        //Clear renderer
        void ClearScreen();
        //Render all to window
        void DrawEverything();

        SDL_Renderer* getRenderer() { return m_renderer; }
        //Automatic conversion to SDL_Window*
        operator SDL_Window*() { return m_window; }

        int GetW() {return screenWidth; }
        int GetH() {return screenHeight; }

    private:
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;

        int screenWidth;
        int screenHeight;
    };
}
#endif // WINDOW_H

