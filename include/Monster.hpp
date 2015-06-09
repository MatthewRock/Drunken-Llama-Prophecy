#ifndef MONSTER_H
#define MONSTER_H

#include "Character.hpp"

namespace Llama
{
    enum MonsterType {  MON_BLACK, MON_ORANGE};
    class Monster : public Character
    {
        public:
            void Order(Orders, int, int);
            void Draw(int x, int y, int offsetx = 0, int offsety = 0);
            void Attack(int, int);

            Monster() = default;
            Monster(const char*, Window&, int, int, int, int, int, int);
            ~Monster() = default;
        protected:
        private:
    };
}
#endif // MONSTER_H
