#include "World.hpp"
#include "Logger.hpp"
#include "GameEngine.hpp"

World::World()
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
void World::HandleEvents(SDL_Event& event)
{
}
void World::Update(GameEngine* eng)
{
}
void World::Draw()
{
}
