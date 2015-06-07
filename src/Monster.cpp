#include "Monster.hpp"
#include <tuple>
namespace Llama
{
    Monster::Monster(const char* filename, Window& m_win, int x, int y) : Character(filename, m_win, x, y)
    {
        //ctor
    }

    void Monster::Order(Orders ord, int x, int y)
    {
        Character::OrderExecutor(std::make_tuple(ord, x, y));
    }
    void Monster::Draw()
    {

    }
}
