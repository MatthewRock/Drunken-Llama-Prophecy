#include "GameEngine.hpp"
#include "MenuState.hpp"

namespace Llama
{
    GameEngine::GameEngine()
    {
        m_running = true;
        m_states.emplace_back(new MenuState);
    }

    void GameEngine::Update()
    {
        for(auto& x : m_states)
        {
            x->Update(this);
        }
    }

    void GameEngine::HandleEvents()
    {
        while(SDL_PollEvent(&m_gameEvent))
        {
            HandleEngineEvents();
            for(auto& x : m_states)
            {
                x->HandleEvents(m_gameEvent);
            }
            HandleEngineEvents();
        }

    }

    void GameEngine::Draw()
    {
        for(auto& x : m_states)
        {
            x->Draw();
        }
    }

    void GameEngine::HandleEngineEvents()
    {
        //If x'd out
        if( m_gameEvent.type == SDL_QUIT)
        {
            m_running = false;
        }
        else if( m_gameEvent.type == SDL_KEYDOWN && m_gameEvent.key.repeat == 0 )
        {
        //If player pressed escape
            if( m_gameEvent.key.keysym.sym == SDLK_ESCAPE )
            {
                m_running = false;
            }
        }
    }
    void GameEngine::ChangeState(GameState* state)
    {
        if(!m_states.empty())
        {
            m_states.pop_back();
        }

        m_states.push_back(std::unique_ptr<GameState>(state));
    }
    void GameEngine::PushState(GameState* state)
    {
        if(!m_states.empty())
        {
            m_states.back()->Pause();
        }
        m_states.push_back(std::unique_ptr<GameState>(state));
    }
    void GameEngine::PopState()
    {
        if(!m_states.empty())
        {
            m_states.pop_back();
        }
        if(!m_states.empty())
        {
            m_states.back()->Resume();
        }
    }

}
