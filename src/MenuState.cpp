#include "MenuState.hpp"
#include "Printable.hpp"

#include "ExitState.hpp"

namespace Llama
{
    MenuState::MenuState(GameEngine* eng)
    {
        m_engine = eng; // If I ever get tempted to move this to parameter list: you can't if it's inherited slot. This one is... -.-

        m_win.Init("Drunken Llama Prophecy v.0.0.1", 1024, 768);
        Printable::SetWindowDimensions(1024, 768);
        m_image.Init("ludek.png", m_win);

        m_musicManager.Insert("MenuMusic1", new Sounds::BGM("media/MainMenu.ogg"));
        m_musicManager.Insert("MenuMusic2", new Sounds::BGM("media/beatdown.ogg"));
        m_musicManager.Insert("MenuMusic3", new Sounds::BGM("media/fanfare-1.ogg"));
        m_musicIterator = m_musicManager.Beginning();
        m_musicIterator->second->Play();
    }

    void MenuState::Pause()
    {
        GameState::Pause();
    }
    void MenuState::Resume()
    {
        GameState::Resume();
    }
    void MenuState::HandleEvents(SDL_Event& event)
    {
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                int mX = event.button.x;
                int mY = event.button.y;

                if( (mX < imgX) || (mX > imgX + m_image.GetW()) || (mY < imgY) || (mY > imgY + m_image.GetH()))
                {
                    Sounds::BGM::Toggle();
                }
                else
                {
                    //ChangeState(new ExitState(m_engine, m_win, this));
                    ++m_musicIterator;
                    if(m_musicIterator == m_musicManager.End())
                    {
                        m_musicIterator = m_musicManager.Beginning();
                    }
                    m_musicIterator->second->Play();
                }
            }
        }
    }
    void MenuState::Update()
    {

    }
    void MenuState::Draw()
    {
        m_win.ClearScreen();
        m_image.Draw(imgX, imgY);
        m_win.DrawEverything();
    }
}
