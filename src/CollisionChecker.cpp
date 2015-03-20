#include "CollisionChecker.hpp"
#include "Block.hpp"

int CollisionChecker::CheckCollisionWithBorder(Ball& ball)
{
    int result = COLLISION_NONE;

    if( ball.GetX() < 0 || ball.GetX() > Printable::MaxX() - ball.GetW() )
    {
        result = COLLISION_X;
    }

    if( ball.GetY() < 0 )
    {
        result = COLLISION_TOP;
    }
    else if(ball.GetY() > Printable::MaxY() - ball.GetH() )
    {
        result = COLLISION_BOTTOM;
    }

    return result;
}

int CollisionChecker::CheckCollisionWithSprite(Block& block, int x, int y, int w, int h )
{
    int result = COLLISION_NONE;
    if(x > block.GetX() + block.GetW()
      || x + w < block.GetX()
      || y > block.GetY() + block.GetH()
      || y + h < block.GetY()
    )
    {

    }
    else
    {
        result = COLLISION_TRUE;
    }

    return result;
}
