#include "PlayableCharacter.hpp"
namespace Llama
{
    PlayableCharacter::PlayableCharacter()
    {
        //ctor
    }
    PlayableCharacter::PlayableCharacter(std::string n, const char* filename, Window& win, int x, int y) : m_x(x), m_y(y)
    {
        SetName(n);
        m_tex.Init(filename, win);
    }
    PlayableCharacter::~PlayableCharacter()
    {
        //dtor
    }

    void PlayableCharacter::Draw()
    {
        m_tex.Draw(m_x, m_y);
    }
    void PlayableCharacter::Move()
    {


    }
}
