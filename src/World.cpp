#include "World.hpp"

#include "Logger.hpp"
#include "GameEngine.hpp"
namespace Llama
{
    World::World(Csout& csout)
    {
    }
    void World::Pause()
    {
        GameState::Pause();
    }
    void World::Resume()
    {
        GameState::Resume();
    }
    void World::HandleEvents(std::string command)
    {
    }
    void World::Update(GameEngine* eng)
    {
    }
    void World::Draw(Csout& csout)
    {
    }
}
