#include "GameState.h"

#include "GameEngine.hpp"

namespace Llama
{
    void GameState::Pause()
    {
        m_paused = true;
    }
    void GameState::Resume()
    {
        m_paused = false;
    }

    void GameState::ChangeState(GameEngine* game, GameState* state)
    {
        game->ChangeState(state);
    }

}
