#include "GameState.hpp"
#include "GameEngine.hpp"

void GameState::Pause()
{
    m_paused = true;
}
void GameState::Resume()
{
    m_paused = false;
}
void GameState::ChangeState(GameState* state)
{
    m_engine->ChangeState(state);
}
void GameState::ChangeStateDestructively(GameState* state)
{
    m_engine->ChangeStateDestructively(state);
}
