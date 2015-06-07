#ifndef MONSTER_H
#define MONSTER_H

#include "Character.hpp"

namespace Llama
{
    class Monster : public Character
    {
        public:
            void Order(Orders, int, int);
            void Draw();


            Monster() = default;
            Monster(const char*, Window&, int, int);
            ~Monster() = default;
        protected:
        private:
    };
}
#endif // MONSTER_H
