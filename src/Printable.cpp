#include "Printable.hpp"

SDL_Rect Printable::WindowDimensions;

void Printable::SetWindowDimensions(int w, int h)
{
    WindowDimensions.x = 0;
    WindowDimensions.y = 0;
    WindowDimensions.w = w;
    WindowDimensions.h = h;
}
