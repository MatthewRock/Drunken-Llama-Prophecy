#include "Credits.hpp"
#include "MenuState.hpp"
#include "GameEngine.hpp"

CreditsState::CreditsState(GameEngine* eng) : m_win(eng->GetWindowPointer())
{
    m_engine = eng;
    m_credits.Init("media/Menu/Credits.png", *m_win);

    m_musicManager.Insert(0, new Sounds::BGM("media/music/Sad sad mlg air horn.ogg"));
    m_musicManager.Insert(1, new Sounds::BGM("media/music/SKRILLEX Scary.ogg"));
    m_musicManager.Insert(2, new Sounds::BGM("media/music/2SAD4ME.ogg"));
    m_musicIterator = m_musicManager.Beginning();

    m_musicIterator->second->Play(0);
}

void CreditsState::Pause()
{
    GameState::Pause();
}
void CreditsState::Resume()
{
    GameState::Resume();
}
void CreditsState::Update()
{
    if (!m_musicIterator->second->Playing())
    {
        ++m_musicIterator;
        if(m_musicIterator == m_musicManager.End())
        {
            m_musicIterator = m_musicManager.Beginning();
        }
        m_musicIterator->second->Play(0);
    }
}
void CreditsState::HandleEvents(SDL_Event& event)
{

    if (event.type == SDL_KEYDOWN)
        if (event.key.keysym.sym == SDLK_ESCAPE)
            Exit();
            //ChangeStateDestructively(new MenuState(m_engine));
        else
        {
            ++m_musicIterator;
            if(m_musicIterator == m_musicManager.End())
            {
                m_musicIterator = m_musicManager.Beginning();
            }
            m_musicIterator->second->Play(0);
        }
}
void CreditsState::Draw()
{
    m_credits.Draw(0,0);
}
