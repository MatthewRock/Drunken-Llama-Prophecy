#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "GameObject.hpp"
namespace Llama
{
    class Character : public GameObject
    {
        public:
            virtual void Draw() = 0;

            Character();
            virtual ~Character();
        protected:
        private:
    };
}
#endif // CHARACTER_H
