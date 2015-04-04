#include "ExitState.hpp"
namespace Llama
{
    ExitState::ExitState(GameEngine* eng, Window& win, GameState* parent) : m_win(&win), m_parent(parent)
    {
        m_engine = eng;
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
        //event.type = SDL_QUIT;

    }
    void ExitState::Draw()
    {

    }
    void ExitState::Update()
    {
        m_parent->Exit();
        Exit();
    }
}
