#include "PlayableCharacter.hpp"
namespace Llama
{
    PlayableCharacter::PlayableCharacter(std::string n, const char* filename, Window& win, int x, int y) : m_tex(filename, win, 63, 63)
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

    void PlayableCharacter::Order(Orders ord, int x, int y)
    {
        m_ordersQueue.push(std::make_tuple(ord, x, y));

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
    void PlayableCharacter::Execute()
    {
        if(!m_ordersQueue.empty())
        {
            OrderExecutor(m_ordersQueue.front());
            m_ordersQueue.pop();
        }
    }
    void PlayableCharacter::OrderExecutor(std::tuple<Orders, int, int> ord)
    {
        switch(std::get<0>(ord))
        {
            case MOVE:
                Move(std::get<1>(ord), std::get<2>(ord));
            break;
            default:
            break;
        }
    }
    void PlayableCharacter::Teleport(int x,int y)
    {
        m_position.first  = x;
        m_position.second = y;
    }
    std::pair<int, int> PlayableCharacter::GetAnimationOffset()
    {
        return std::make_pair( ((m_translocation.first + ((m_translocation.second != 0) ? (m_position.second % 2) - 0.5 : 0) )  * 56  )* (m_tex.getAnimationLength() - m_tex.getFrame()) / m_tex.getAnimationLength()  , (m_translocation.second * 41) * ( m_tex.getAnimationLength()- m_tex.getFrame()) / m_tex.getAnimationLength());
    }
}
