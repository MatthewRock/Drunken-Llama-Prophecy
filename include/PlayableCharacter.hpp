#ifndef PLAYABLECHARACTER_H
#define PLAYABLECHARACTER_H

#include <utility>
#include <tuple>
#include <queue>
#include "Character.hpp"
#include "AnimationHandler.hpp"
#include "SDL2/SDL.h"
#include "GameLogic.hpp"
namespace Llama
{
    class PlayableCharacter : public Character
    {
        public:
            PlayableCharacter() = default;
            PlayableCharacter(std::string, const char*, Window&, int, int,GameLogic&);
            ~PlayableCharacter() = default;

            void Draw();
            ///\brief Inserts order with directional parameters on queue
            ///\param Order flag and
            ///\param Two ints. X and Y components of direction vector for desired order
            void Order(Orders, int, int);

            ///\brief Executes first order stored in queue. In case of empty queue does nothing
            void Execute();
            void HandleEvents(SDL_Event& event);
        protected:
        private:
        ///Queue of tuples: orders and directional parameters
        std::queue<std::tuple<Orders, int, int>>    m_ordersQueue;

    };
}
#endif // PLAYABLECHARACTER_H
