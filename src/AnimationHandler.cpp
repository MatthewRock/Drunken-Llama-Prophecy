#include "AnimationHandler.hpp"
namespace Llama
{
    AnimationHandler::AnimationHandler()
    {
        //ctor
    }
    AnimationHandler::AnimationHandler(const char* filename, Window& win) : m_tex(filename, win), m_idle(true), m_framecounter(0)
    {

    }

    AnimationHandler::~AnimationHandler()
    {
        //dtor
    }

    void AnimationHandler::InitiateAnimation()
    {
        m_idle = false;

    }

    void AnimationHandler::Draw(std::pair<int,int> coords)
    {   // 56 - hexWidth, 82 - hexHeight



        m_tex.Draw(((coords.second % 2 == 0) ? coords.first * 56 : coords.first * 56 - (.5 * 56)) + 11, (coords.second - 1) * .5 * 82 - 15);
        if(!m_idle)
        {
                if(++m_framecounter > m_animationLength - 1)
                    {
                        m_framecounter = 0;
                        m_idle = true;
                    }
        }

    }
}
