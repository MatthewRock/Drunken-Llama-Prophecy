#include "AnimationHandler.hpp"
#include <iostream>
namespace Llama
{
    AnimationHandler::AnimationHandler()
    {
        //ctor
    }
    AnimationHandler::AnimationHandler(const char* filename, Window& win, int w, int h) : m_tex(filename, win), m_idle(true), m_framecounter(0), m_win(&win), m_currentAnim(0)
    {
        m_rect.x = 0;
        m_rect.y = 0;
        m_rect.w = w;
        m_rect.h = h;
    }

    AnimationHandler::~AnimationHandler()
    {
        //dtor
    }

    void AnimationHandler::InitiateAnimation(Animations a)
    {
        switch(a)
        {
            case ATTACK_ANIM:
                m_currentAnim = (m_currentAnim == WALK_LEFT || m_currentAnim == ATTACK_LEFT) ? ATTACK_LEFT : ATTACK_RIGHT;
            case ATTACK_LEFT:
            case ATTACK_RIGHT:
            case DIE:
                m_rect.y = 64;
            break;
            default:
                m_currentAnim = a;
            break;
        }
        m_idle = false;

    }

    void AnimationHandler::Draw(std::pair<int,int> coords, int offsetx, int offsety)
    {   // 56 - hexWidth, 82 - hexHeight

        SDL_Rect dest;
        dest.x = ((coords.second % 2 == 0) ? coords.first * 56 : coords.first * 56 - (.5 * 56)) +offsetx/* m_rect.w/2*/;
        dest.y = (coords.second - 1) * .5 * 82 +offsety/*m_rect.h/2*/;
        dest.w = m_rect.w;
        dest.h = m_rect.h;

        //m_tex.Draw(((coords.second % 2 == 0) ? coords.first * 56 : coords.first * 56 - (.5 * 56)) + 11 - m_tex.GetW()/2, (coords.second - 1) * .5 * 82 - m_tex.GetH()/2);
        if(!m_idle)
        {
            if(m_framecounter % (m_animationLength / 2) == 0)
            {
                m_rect.x = 0;
            }
            else
            {
                if(m_framecounter % 2 == 0)
                {
                    m_rect.x = (m_framecounter % (m_animationLength / 2)) / 2 * (m_rect.w + 1);
                }
            }
            if(++m_framecounter > m_animationLength - 1)
            {
                m_rect.x = 0;
                m_rect.y = 0;
                m_framecounter = 0;
                m_idle = true;
            }
         //   std::cout << m_currentAnim << std::endl;
        }
        if(m_currentAnim == WALK_LEFT || m_currentAnim == ATTACK_LEFT)
            SDL_RenderCopyEx(m_win->getRenderer(), (m_tex), &m_rect, &dest, 0, NULL, SDL_FLIP_HORIZONTAL);
        else
            SDL_RenderCopy(m_win->getRenderer(), (m_tex), &m_rect, &dest);

    }
}
