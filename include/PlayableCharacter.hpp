#ifndef PLAYABLECHARACTER_H
#define PLAYABLECHARACTER_H

#include <utility>
#include <tuple>
#include <queue>
#include <SDL2/SDL.h>
#include "Character.hpp"
#include "AnimationHandler.hpp"
#include "Land.hpp"
#include "GameLogic.hpp"
namespace Llama
{

    class PlayableCharacter : public Character
    {
        public:
            PlayableCharacter() = default;
            PlayableCharacter(std::string, const char*, Window&, int, int,GameLogic&, Land&);
            ~PlayableCharacter() = default;

            void Draw();
            ///\brief Inserts order with directional parameters on queue
            ///\param Order flag and
            ///\param Two ints. X and Y components of direction vector for desired order
            void Order(Orders, int, int);
            void Attack(int x, int y);
            ///\brief Executes first order stored in queue. In case of empty queue does nothing
            void Execute();
            void HandleEvents(SDL_Event& event);
        protected:
        private:
        Land* m_map;
        ///Queue of tuples: orders and directional parameters
        std::queue<std::tuple<Orders, int, int>>    m_ordersQueue;

    };
}
#endif // PLAYABLECHARACTER_H
