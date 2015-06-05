#include "PlayableCharacter.hpp"
namespace Llama
{
    PlayableCharacter::PlayableCharacter(std::string n, const char* filename, Window& win, int x, int y) : m_tex(filename, win)
    {
        m_position = std::make_pair(x, y);
        m_translocation = std::make_pair(0, 0);
        Setname(n);
    }
    void PlayableCharacter::Draw()
    {
        m_tex.Draw(std::make_pair(9,8));
        if(m_tex.IsIdle())
            m_translocation = std::make_pair(0, 0);
    }

    void PlayableCharacter::Move(int x, int y)
    {
        if(m_tex.IsIdle())
        {
            m_translocation = std::make_pair(x, y);
            m_position.first += x;
            m_position.second += y;
            m_tex.InitiateAnimation();
        }
    }
    void PlayableCharacter::Teleport(int x,int y)
    {
        m_position.first  = x;
        m_position.second = y;
    }
    std::pair<int, int> PlayableCharacter::GetAnimationOffset()
    {
        return std::make_pair( ((m_translocation.first + ((m_translocation.second != 0) ? (m_position.second % 2) - 0.5 : 0) )  * 56  )* (m_tex.getAnimationLength() - m_tex.getFrame()) / m_tex.getAnimationLength()  , (m_translocation.second * 46) * ( m_tex.getAnimationLength()- m_tex.getFrame()) / m_tex.getAnimationLength());
    }
}
