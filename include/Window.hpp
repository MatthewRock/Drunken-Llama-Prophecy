#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <exception>
#include <string>
#include "Logger.hpp"
#include <memory> // std::unique_ptr
/**
  * Window is a wrapper class for SDL_Window and its SDL_Renderer.
  * Window makes it easy to use Renderer specific for window.
  * It also holds its width and height.
  * If Window can not be allocated, a WindowException is thrown.
  * Window is intended to be used as automatic object; it does not have to be used as pointer.
  */
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
    Window() : m_window(nullptr, SDL_DestroyWindow), m_renderer(nullptr, SDL_DestroyRenderer){};
    Window(const char* name, int w, int h);
    Window(Window& other) = delete;
    Window(Window&& other);

    ~Window() = default;
    /// \brief Creates window with top-left text from \name, and \width and \height.
    void Init(const char* name, int width, int height);
    /// \brief After this function call, renderer(buffer) is clear.
    void ClearScreen();
    /// \brief Pushes changes to Window and draws it.
    void DrawEverything();
    /// \brief Changes background color to given RGBA values
    void ChangeBackgroundColor(int r, int g, int b, int a);
    /// \brief No idea why you'd want to use it.
    SDL_Renderer* getRenderer() { return m_renderer.get(); }
    /// \brief Automatic conversion to SDL_Window* . Only for SDL functions purposes.
    operator SDL_Window*() { return m_window.get(); }

    int GetW(){return screenWidth;}
    int GetH(){return screenHeight;}
private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;

    int screenWidth;
    int screenHeight;
};
#endif // WINDOW_H
