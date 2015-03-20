#ifndef COLLISIONCHECKER_HPP
#define COLLISIONCHECKER_HPP

#include "Ball.hpp"

class Block;

/// \brief Namespace containing enums and functions that allow checking for collision
namespace CollisionChecker
{
    //Types of collision
    enum
    {
        COLLISION_NONE,
        COLLISION_TOP,
        COLLISION_BOTTOM,
        COLLISION_LEFT,
        COLLISION_RIGHT,
        COLLISION_X,
        COLLISION_TRUE
    };
    //Check if rectangle collides with Block
    int CheckCollisionWithSprite(Block& block, int x, int y, int w, int h);

    //Check if ball collided with screen
    int CheckCollisionWithBorder(Ball& ball);

    template < class T >
    int CheckCollision(Ball& ball, T& block)
    {
        int collided = COLLISION_NONE;

        int ballY = ball.GetY() + ball.GetH()/2;
        int ballX = ball.GetX() + ball.GetW()/2;
        int r = ball.GetH()/2;

        if( (ballY + r < block.GetY())
            || ( ball.GetY() > block.GetY() + block.GetH())
            || (ball.GetX() > block.GetX() + block.GetW())
            || (ball.GetX() + r < block.GetX()) )
        {
            //No collision;
        }
        else
        {
            //TODO2: Improve this algorithm(buggy on corners)
            if(ballY <= block.GetY() - (block.GetH()/2))
            {
                collided = COLLISION_BOTTOM;
            }
              //Hit was from below the brick

            if(ballY >= block.GetY() + (block.GetH()/2))
            {
                collided = COLLISION_TOP;
            }
              //Hit was from above the brick

            if(ballX < block.GetX())
            {
                collided = COLLISION_LEFT;
            }
              //Hit was on left

            if(ballX > block.GetX())
            {
                collided = COLLISION_RIGHT;
            }
              //Hit was on right
        }
    return collided;
    }

    template < class T >
    int CheckCollisionWithMouse(T& block, int x, int y)
    {
        int result = COLLISION_NONE;

        if( x < block.GetX()
            || x > block.GetX() + block.GetW()
            || y < block.GetY()
            || y > block.GetY() + block.GetH())
        {
            //Nothing happened; no collision
        }
        else
        {
            result = COLLISION_TRUE;
        }

        return result;
    }

    template < class T >
    int CheckCollisionWithMouse(T* block, int x, int y)
    {
        int result = COLLISION_NONE;

        if( x < block->GetX()
            || x > block->GetX() + block->GetW()
            || y < block->GetY()
            || y > block->GetY() + block->GetH())
        {
            //Nothing happened; no collision
        }
        else
        {
            result = COLLISION_TRUE;
        }

        return result;
    }

}

#endif // COLLISIONCHECKER_HPP
