#include "ExitState.hpp"
#include "Sounds.hpp"
#include <cassert>

namespace Llama
{
    ExitState::ExitState(GameEngine* eng, Window& win, GameState* parent) : m_win(&win), m_parent(parent)
    {
        m_engine = eng;
        assert(m_engine);
        assert(m_parent);
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
    }
    void ExitState::Draw()
    {
    }
    void ExitState::Update()
    {
        m_parent->Exit();
        Exit();
        Sounds::SFX tempmus("media/xplod.wav");
        tempmus.Play();
        SDL_Delay(500);
    }
}
