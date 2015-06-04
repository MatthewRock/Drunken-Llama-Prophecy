#include "Texture.hpp"
#include "Window.hpp"
#include <cassert>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cmath>
namespace Llama
{
    Texture::Texture() : m_texture(nullptr, SDL_DestroyTexture), m_win(nullptr)
    {}
    Texture::Texture(const char* path, Window& win) : m_texture(nullptr, SDL_DestroyTexture), m_win(&win)
    {
        loadTexture(path, win.getRenderer());
    }
//    Texture::Texture(const Texture& source)
//    {
//        m_texture = source.m_texture;
//        m_win = source.m_win;
//    }

    void Texture::loadTexture(const char* path, SDL_Renderer* renderer)
    {
        //Wrong argument passed
        assert(renderer);
        //We will be loading texture from surface. So, we load surface first
        SDL_Surface* loadedSurface = IMG_Load(path);

        //Always check for null
        if(!loadedSurface)
        {
            throw TexException;
        }
        else
        {
            //Now create texture from this surface
            m_texture = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>(SDL_CreateTextureFromSurface(renderer, loadedSurface), SDL_DestroyTexture);
            //Always check for null
            if(!m_texture)
            {
                throw TexException;
            }
            else
            {
                //Copy clip_rect from surface, solving the issue of SDL_Texture not having clip_rect
                m_rect = loadedSurface->clip_rect;
            }
            //Clean up
            SDL_FreeSurface(loadedSurface);
        }
    }
    void Texture::Init(const char* path, Window& win)
    {
        loadTexture(path, win.getRenderer());
        m_win = &win;
    }

    void Texture::Draw(Window& win, int x, int y )
    {
        //Create temporary destinaction rectangle using m_rect(texture width and height) and x and y into which we will be drawning
        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        dest.h = m_rect.h;
        dest.w = m_rect.w;
        //Render using Window's renderer.
        SDL_RenderCopy(win.getRenderer(), m_texture.get(), &m_rect, &dest);
    }

    void Texture::Draw(int x, int y)
    {

        //Create temporary destinaction rectangle using m_rect(texture width and height) and x and y into which we will be drawning
        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        dest.h = m_rect.h;
        dest.w = m_rect.w;
        //Render using Window's renderer.
        SDL_RenderCopy(m_win->getRenderer(), m_texture.get(), &m_rect, &dest );
    }
}
