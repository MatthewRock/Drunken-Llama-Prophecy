#include "Monster.hpp"
#include <tuple>
#include <utility>
namespace Llama
{
    Monster::Monster(const char* filename, Window& m_win, int x, int y, int health, int attack, int defence, int experience) : Character(filename, m_win, x, y, health, attack, defence, experience)
    {
        m_translocation = std::make_pair(0, 0);
        m_position = std::make_pair(x, y);
    }

    void Monster::Order(Orders ord, int x, int y)
    {
        Character::OrderExecutor(std::make_tuple(ord, x, y));
    }
    void Monster::Attack(int x, int y)
    {
        Character::Attack(x - GetPosition().first + ((GetPosition().second % 2 == 0) ? -1 : 0), 0);
    }
    void Monster::Draw(int x, int y, int offsetx, int offsety)
    {
        m_tex.Draw(std::make_pair(m_position.first - x + (((m_position.second % 2 == 1) && (y % 2 == 0)  )? 8 : 9), m_position.second - y + 9), (m_stats.hp - m_damage)*48/m_stats.hp ,offsetx - GetAnimationOffset().first, offsety - GetAnimationOffset().second);
    }
}
