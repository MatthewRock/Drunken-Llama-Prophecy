#ifndef ANIMATIONHANDLER_HPP
#define ANIMATIONHANDLER_HPP
#include <utility>
#include "Window.hpp"
#include "Texture.hpp"
namespace Llama
{
    class AnimationHandler
    {

        public:
            AnimationHandler();
            AnimationHandler(const char*, Window&);
            virtual ~AnimationHandler();

            void Draw(std::pair<int,int>);
            bool IsIdle()           {   return m_idle;  }
            int  getFrame()         {   return m_framecounter;  }
            int  currentAnimation() {   return m_currentAnim;   }
            int  getAnimationLength(){  return m_animationLength;}
            void InitiateAnimation();
        protected:
        private:
            const int m_animationLength = 15;
            int     m_currentAnim;
            Texture m_tex;
            int     m_framecounter;
            bool    m_idle;
    };
}
#endif // ANIMATIONHANDLER_H
