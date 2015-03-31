#include "ExitState.hpp"
namespace Llama
{
    ExitState::ExitState(Window& win) : m_win(&win)
    {
    }

    void ExitState::Pause()
    {
        GameState::Pause();
    }
    void ExitState::Resume()
    {
        GameState::Resume();
    }
    void ExitState::HandleEvents(SDL_Event& event)
    {
        event.type = SDL_QUIT;
    }
    void ExitState::Draw()
    {

    }
    void ExitState::Update(GameEngine* eng)
    {

    }
}
