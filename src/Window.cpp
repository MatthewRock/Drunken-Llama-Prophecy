#include "Window.hpp"
#include <cstdio>
namespace Llama
{
    Window::Window(const char* name, int w, int h) : m_window(nullptr, SDL_DestroyWindow), m_renderer(nullptr, SDL_DestroyRenderer)
    {
        Init(name, w, h);
    }
    Window::Window(Window&& other) : m_window(std::move(other.m_window)), m_renderer(std::move(other.m_renderer)), screenWidth(other.screenWidth), screenHeight(other.screenHeight)
    {}


    void Window::Init(const char* name, int w, int h )
    {
        // Set screen dimensions
        screenHeight = h;
        screenWidth = w;
        //Try to allocate window
        m_window = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN), SDL_DestroyWindow);
        if(!m_window)
        {
            //Window could not be created
            throw WinException;
        }
        else
        {
            //Create renderer for created window.
            m_renderer = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>(SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
            if(!m_renderer)
            {
                throw WinException;
            }
            /// \brief Uncomment this if you wish to change background color. By default color is black.
//            else
//            {
//                SDL_SetRenderDrawColor( m_renderer.get(), 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE );
//            }
        }
    }
    void Window::DrawEverything()
    {
        SDL_RenderPresent(m_renderer.get());
    }
    void Window::ClearScreen()
    {
        SDL_RenderClear(m_renderer.get());
    }
    void Window::ChangeBackgroundColor(int r, int g, int b, int a)
    {
        SDL_SetRenderDrawColor(m_renderer.get(), r, g, b, a);
    }
}
