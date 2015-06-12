#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <utility>
#include <SDL2/SDL.h>
#include <cmath>

namespace Collision
{
    int distance(int x1, int y1, int x2, int y2)
    {
        return sqrt(pow((x1-x2),2) + pow((y1-y2),2));
    }
    int MouseHexCollision(SDL_Event& event, std::pair<int,int>& hexCoords)
    {
        int dist = distance(event.button.x, event.button.y, hexCoords.first + 30, hexCoords.second+35);//26 = Hex::WIDTH/2,41 = Hex::HEIGHT/2, then x+4, y-6
        return dist;
        //radius of circle should be(from experiments):32
        //X of circle = x+4, y=y-6

        // Overall logic:
        // Draw a circle that will be drawn from centre of hex. It will have whole hex(and a bit of other hexes) in it

        // Check with which circles does mouse collide
        // Select the circle which has centre closest to mouse
        // It's this hex
        //However, this has to be done elsewhere; here we merely return distance from cursor
    }
}
#endif //COLLISION_HPP
