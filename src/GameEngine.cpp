#include "GameEngine.hpp"
#include "MenuState.hpp"

namespace Llama
{
    GameEngine::GameEngine()
    {
        m_running = true;
        m_states.emplace_back(new MenuState(this));
    }

    void GameEngine::Update()
    {
        for(auto& x : m_states)
        {
            x->Update();
        }
        for(auto it = m_states.begin(); it != m_states.end(); ++it)
        {
            if((*it)->WantsToExit())
            {
                m_states.erase(it--);
            }

        }
    }

    void GameEngine::HandleEvents()
    {
        while(SDL_PollEvent(&m_gameEvent))
        {
            auto top = m_states.end();
            --top;
            (*top)->HandleEvents(m_gameEvent);
            //Previously: checking for all states' events.
//            for(auto& x : m_states)
//            {
//                x->HandleEvents(m_gameEvent);
//            }
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
        //Remove last element, with sanity check.
        if(!m_states.empty())
        {
            m_states.pop_back();
        }
        //If there are some states left, resume the top one.
        if(!m_states.empty())
        {
            m_states.back()->Resume();
        }
        //If last element happened to be the only element, "send signal" to close program.
        else
        {
            Quit();
        }
    }
}
