#ifndef WORLD_HPP
#define WORLD_HPP


/** \brief Aggregate class, that holds map and Player. Maybe even some "managers"
 */

#include <memory>
#include "GameState.hpp"

#include <map>
#include <utility> // std::pair
#include "Command.hpp" // Template for command Pattern classes

//List of commands that can be used and sent in the World.
class World : public GameState
{
    public:
        World();
        void Pause();
        void Resume();
        void Update(GameEngine* eng);
        void Draw();
        void HandleEvents(SDL_Event& event);

    protected:
    private:
        std::unique_ptr<Command> m_command;

        // This vector will simulate 2D-array that will be extensible.
//            std::map<std::pair<int, int>, Place> m_map;
};
#endif // WORLD_HPP
