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
                Stats(int health, int attack, int defence, int experience) : hp(health), str(attack), def(defence), exp(experience) {};
                int hp;
                int str;
                int def;
                int exp;
            };
            virtual void Order(Orders, int, int) = 0;
            std::pair<int, int> GetPosition()       {   return m_position;  }
            ///\brief Moves character in desired direction
            ///\param Two ints. X and Y components of translocation vector
            void Move(int, int);
            ///\brief Attacks(for now only animation) in specified direction(for now only right/left)
            virtual void Attack(int, int);
            bool IsIdle()                           {   return m_tex.IsIdle();}
            void Teleport(int,int);
            std::pair<int, int> GetAnimationOffset();
            Stats GetStats() {return m_stats;}
            void Damage(int dmg)    { m_damage += dmg/m_stats.def; }
            bool IsDead()    {return (m_stats.hp - m_damage <= 0); }
            void Die();
            void Heal()     {   m_damage -= (m_damage == 0) ? 0: 1;}

            Character() = default;
            Character(const char* filename, Window& win, int x, int y, int health, int attack, int defence, int experience) : m_tex(filename, win, 63, 63), m_stats(health, attack, defence, experience), m_damage(0)
            {
                m_position = std::make_pair(x,y);
            }
            ~Character() = default;
        protected:
            std::pair<int, int> m_translocation;
            void OrderExecutor(std::tuple<Orders, int, int>);
            AnimationHandler m_tex;
            Stats           m_stats;
            int             m_damage;
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
