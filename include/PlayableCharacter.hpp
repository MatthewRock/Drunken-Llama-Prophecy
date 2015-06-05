#ifndef PLAYABLECHARACTER_H
#define PLAYABLECHARACTER_H

#include <utility>
#include <tuple>
#include <queue>
#include "Character.hpp"
#include "AnimationHandler.hpp"
namespace Llama
{
    class PlayableCharacter : public Character
    {
        public:
            ///brief Enum for orders. All except move: To be implemented ;______;
            enum Orders { MOVE, ATTACK, INTERACT};
            PlayableCharacter() = default;
            PlayableCharacter(std::string, const char*, Window&, int, int);
            ~PlayableCharacter() = default;

            void Draw();
            ///\brief Inserts order with directional parameters on queue
            ///\param Order flag and
            ///\param Two ints. X and Y components of direction vector for desired order
            void Order(Orders, int, int);
            ///\brief Moves character in desired direction
            ///\param Two ints. X and Y components of translocation vector
            void Move(int, int);
            ///\brief Executes first order stored in queue. In case of empty queue does nothing
            void Execute();
            void Teleport(int,int);
            std::pair<int, int> GetPosition()       {   return m_position;  }
            std::pair<int, int> GetAnimationOffset();
            bool IsIdle()                           {   return m_tex.IsIdle();}
        protected:
        private:
        void OrderExecutor(std::tuple<Orders, int, int>);
        std::pair<int, int> m_position;
        std::pair<int, int> m_translocation;
        AnimationHandler m_tex;
        ///Queue of tuples: orders and directional parameters
        std::queue<std::tuple<Orders, int, int>>    m_ordersQueue;
    };
}
#endif // PLAYABLECHARACTER_H
