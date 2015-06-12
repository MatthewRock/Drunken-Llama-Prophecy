#include "GameEngine.hpp"
#include "MenuState.hpp"
#include "Printable.hpp"
#include "Sounds.hpp"

GameEngine::GameEngine(std::string winName)
{
    m_running = true;
    m_win.Init(winName.c_str(), 1024, 768);
    Printable::SetWindowDimensions(1024, 768);
    m_states.emplace_back(new MenuState(this));
}

void GameEngine::Update()
{
    for(auto& x : m_states)
    {
        x->Update();
    }
    bool changed = false;
    for(auto it = m_states.begin(); it != m_states.end(); ++it)
    {
        if((*it)->WantsToExit())
        {
            m_states.erase(it--);
            changed = true;
        }
    }
    if(changed)
        (*(m_states.end() - 1))->Resume();
}

void GameEngine::HandleEvents()
{
    while(SDL_PollEvent(&m_gameEvent))
    {
        auto top = m_states.end();
        --top;
        (*top)->HandleEvents(m_gameEvent);
        HandleEngineEvents();
    }

}

void GameEngine::Draw()
{
    m_win.ClearScreen();
    for(auto& x : m_states)
    {
        x->Draw();
    }
    m_win.DrawEverything();
}

void GameEngine::HandleEngineEvents()
{
    //If x'd out
    if( m_gameEvent.type == SDL_QUIT)
    {
        m_running = false;
    }
    else if( m_gameEvent.type == SDL_KEYDOWN)
    {
        if(m_gameEvent.key.keysym.sym == SDLK_m && m_gameEvent.key.repeat == 0 )
            Sounds::BGM::MuteToggle();
        else if(m_gameEvent.key.keysym.sym == SDLK_EQUALS)
            Sounds::BGM::Louder();
        else if(m_gameEvent.key.keysym.sym == SDLK_MINUS)
            Sounds::BGM::Quieter();
    }
}
void GameEngine::ChangeState(GameState* state)
{
    m_states.push_back(std::unique_ptr<GameState>(state));
}

void GameEngine::ChangeStateDestructively(GameState* state)
{
    PopState();
    ChangeState(state);
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
}
void GameEngine::CrushWithState(GameState* state)
{
    decltype(m_states) emptyvec;
    std::swap(emptyvec, m_states);
    m_states.push_back(std::unique_ptr<GameState>(state));
}
