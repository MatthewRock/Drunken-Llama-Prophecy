#ifndef WORLD_HPP
#define WORLD_HPP


/** \brief Aggregate class, that holds map and Player. Maybe even some "managers"
 */

#include <memory>
#include "Player.hpp"
#include "GameState.h"

#include <map>
#include <utility> // std::pair
#include "Command.hpp" // Template for command Pattern classes

namespace Llama
{
    //List of commands that can be used and sent in the World.
    class World : public GameState
    {
        public:
            World(Csout& csout);
            void Pause();
            void Resume();
            void Update(GameEngine* eng);
            void Draw(Csout& csout);

        protected:
        private:
            std::unique_ptr<Command> m_command;

            // This vector will simulate 2D-array that will be extensible.
//            std::map<std::pair<int, int>, Place> m_map;
    };
}
#endif // WORLD_HPP
