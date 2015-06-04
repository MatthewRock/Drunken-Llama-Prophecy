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
            bool IsIdle()     { return m_idle; }
        protected:
        private:
            Texture m_tex;
            int     m_framecounter;
            bool    m_idle;
    };
}
#endif // ANIMATIONHANDLER_H
