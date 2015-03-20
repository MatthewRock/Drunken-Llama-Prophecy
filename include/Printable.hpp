#ifndef PRINTABLE_HPP
#define PRINTABLE_HPP

#include "SDL.h"

class Window;

/// \brief blueprint(abstract) class for everything that can be printed to screen.
class Printable
{
protected:
    static SDL_Rect WindowDimensions;
    SDL_Rect position; //Mainly for x and y, since w and h are taken from Texture.
    virtual ~Printable() = default;
public:

    virtual void Update() = 0;
    virtual void Draw() = 0;

    static void SetWindowDimensions(int width, int height);

    static inline int MaxY() { return WindowDimensions.h; }
    static inline int MaxX() { return WindowDimensions.w; }

    inline int GetX() { return position.x; }
    inline int GetY() { return position.y; }

    virtual int GetW() = 0;
    virtual int GetH() = 0;
};
#endif // PRINTABLE_HPP
