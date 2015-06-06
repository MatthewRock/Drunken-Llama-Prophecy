#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "GameObject.hpp"
namespace Llama
{
    class Character : public GameObject
    {
        public:
            ///brief Enum for orders. All except move: To be implemented ;______;
            enum Orders { MOVE, ATTACK, INTERACT};
            struct Stats
            {
                int hp;
            };
            virtual void Draw() = 0;
            virtual void Order(Orders, int, int) = 0;

            Character() = default;
            ~Character() = default;
        protected:
        private:
    };
}
#endif // CHARACTER_H
