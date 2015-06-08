#include "Monster.hpp"
#include <tuple>
#include <utility>
namespace Llama
{
    Monster::Monster(const char* filename, Window& m_win, int x, int y, int health, int attack, int defence, int experience) : Character(filename, m_win, x, y, health, attack, defence, experience)
    {
        m_position = std::make_pair(x, y);
    }

    void Monster::Order(Orders ord, int x, int y)
    {
        Character::OrderExecutor(std::make_tuple(ord, x, y));
    }
    void Monster::Draw(int x, int y, int offsetx, int offsety)
    {
        m_tex.Draw(std::make_pair(m_position.first - x, m_position.second - y), offsetx, offsety);
    }
}
