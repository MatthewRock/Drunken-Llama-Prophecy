#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <AnimationHandler.hpp>
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
                int str;
                int def;
            };
            virtual void Draw() = 0;
            virtual void Order(Orders, int, int) = 0;
            std::pair<int, int> GetPosition()       {   return m_position;  }
            ///\brief Moves character in desired direction
            ///\param Two ints. X and Y components of translocation vector
            void Move(int, int);
            ///\brief Attacks(for now only animation) in specified direction(for now only right/left)
            void Attack(int, int);
            bool IsIdle()                           {   return m_tex.IsIdle();}
            void Teleport(int,int);
            std::pair<int, int> GetAnimationOffset();

            Character() = default;
            Character(const char* filename, Window& win) : m_tex(filename, win, 63, 63) {}
            ~Character() = default;
        protected:

            std::pair<int, int> m_translocation;
            void OrderExecutor(std::tuple<Orders, int, int>);
            AnimationHandler m_tex;

            std::pair<int, int> m_position;
            //Rage corner
            std::pair<int, int> MoveQ();
            std::pair<int, int> MoveW();
            std::pair<int, int> MoveE();
            std::pair<int, int> MoveA();
            std::pair<int, int> MoveS();
            std::pair<int, int> MoveD();
            std::pair<int, int> MoveZ();
            std::pair<int, int> MoveC();
        private:
    };
}
#endif // CHARACTER_H
