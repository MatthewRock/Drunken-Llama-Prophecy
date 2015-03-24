#include "Texture.hpp"
#include "Window.hpp"
namespace Llama
{
    Texture::Texture()
    {
        m_texture = nullptr;
        m_win = nullptr;
    }

    Texture::Texture(const char* path, Window& win) : m_win(&win)
    {
        loadTexture(path, win.getRenderer() );
    }

    Texture::Texture(const Texture& source)
    {
        m_texture = source.m_texture;
        m_win = source.m_win;
    }

    void Texture::loadTexture( const char* path, SDL_Renderer* renderer )
    {
        //Wrong argument passed
        if(nullptr == renderer )
        {
            m_texture = nullptr;
        }
        else
        {
        //We will be loading texture from surface. So, we load surface first
            SDL_Surface* loadedSurface = IMG_Load(path);

            //Always check for null
            if( nullptr == loadedSurface )
            {
                throw TexException;
            }
            else
            {
                //Now create texture from this surface
                m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface );
                //Always check for null
                if( nullptr == m_texture )
                {
                    throw TexException;
                }
                else
                {
                    //Copy clip_rect from surface, solving the issue of SDL_Texture not having clip_rect
                    m_rect = loadedSurface->clip_rect;
                }
                //Clean up
                SDL_FreeSurface( loadedSurface );
            }
        }
    }

    Texture::~Texture()
    {
        SDL_DestroyTexture( m_texture );
    }

    void Texture::Init(const char* path, Window& win)
    {
        loadTexture(path, win.getRenderer() );
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
        SDL_RenderCopy(win.getRenderer(), m_texture, &m_rect, &dest );
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
        SDL_RenderCopy(m_win->getRenderer(), m_texture, &m_rect, &dest );
    }
}
