#ifndef ANIMATIONHANDLER_HPP
#define ANIMATIONHANDLER_HPP
#include <utility>
#include <SDL2/SDL.h>
#include "Window.hpp"
#include "Texture.hpp"
namespace Llama
{
    class AnimationHandler
    {

        public:
            enum Animations { IDLE = 0, WALK_RIGHT, WALK_LEFT, ATTACK_ANIM, ATTACK_LEFT, ATTACK_RIGHT};
            AnimationHandler();
            AnimationHandler(const char*, Window&, int, int);
            virtual ~AnimationHandler();

            void Draw(std::pair<int,int> coords, int offsetx = 0, int offsety = 0);
            bool IsIdle()           {   return m_idle;  }
            int  getFrame()         {   return m_framecounter;  }
            int  currentAnimation() {   return m_currentAnim;   }
            int  getAnimationLength(){  return m_animationLength;}
            void InitiateAnimation(Animations);
        protected:
        private:
            SDL_Rect  m_rect;
            Window*   m_win;
            const int m_animationLength = 16;
            int     m_currentAnim;
            Texture m_tex;
            int     m_framecounter;
            bool    m_idle;
    };
}
#endif // ANIMATIONHANDLER_H
