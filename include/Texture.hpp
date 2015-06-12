#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <exception>
#include <string>
#include "Logger.hpp"
#include <memory>

class Window;
/**
  * Wrapper class for SDL_Texture
  * Texture is loading an image using SDL_image.h
  * This option needs to be initialized, and it will be - in gameEngine, just before everything else.
  */
class Texture
{
    //Texture exception class, used in file initialization
    class TextureException : public std::exception
    {
        virtual const char* what() const throw()
        {
            Logger::Get()->Log("Texture has thrown an exception:");

            std::string returned = "Initialization of Texture failed! SDL_Error: ";
            returned = returned + SDL_GetError();

            Logger::Get()->Log(returned);

            return returned.c_str();
        }
    }TexException;

public:
    Texture();
    Texture(const char*, Window&);

    ~Texture() = default;
    /// \brief Load texture from file.
    void Init(const char*, Window& );
    //Draw texture on screen using Window's renderer, at coordinates of x and y
    void Draw(Window& win, int x = 0, int y = 0);
    void Draw(int x = 0, int y = 0);

    //Converter. It's going to be used in Draw(), it is natural that Texture should be able to take form of ordinary SDL_Texture*.
    operator SDL_Texture*() {return m_texture.get();}

    //Getters
    inline int GetW() {return m_rect.w;}
    inline int GetH() {return m_rect.h;}
    inline bool IsNull() {return (m_texture == nullptr);}

private:
    //Load texture from file.
    void loadTexture(const char* path, SDL_Renderer*);

    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_texture;
    //Pointer to window that we will draw to. Read-only.
    Window* m_win;
    //Width and height.
    SDL_Rect m_rect;
};
#endif // TEXTURE_H
