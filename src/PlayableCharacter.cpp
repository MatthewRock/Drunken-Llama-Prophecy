#include "PlayableCharacter.hpp"
namespace Llama
{
    PlayableCharacter::PlayableCharacter()
    {
        //ctor
    }
    PlayableCharacter::PlayableCharacter(std::string n, const char* filename, Window& win, int x, int y) : m_tex(filename, win)
    {
        m_position = std::make_pair(x, y);
        m_translocation = std::make_pair(0, 0);
        Setname(n);
    }
    PlayableCharacter::~PlayableCharacter()
    {
        //dtor
    }

    void PlayableCharacter::Draw()
    {
        m_tex.Draw(std::make_pair(9,8));
        if(m_tex.IsIdle())
            m_translocation = std::make_pair(0, 0);
    }

    void PlayableCharacter::Move(int x, int y)
    {
        m_translocation = std::make_pair(x, y);
        m_position.first += x;
        m_position.second += y;
    }
}
