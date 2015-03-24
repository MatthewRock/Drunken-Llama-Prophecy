#include "MenuState.hpp"
#include "Printable.hpp"

namespace Llama
{
    MenuState::MenuState()
    {
        m_win.Init("Drunken Llama Prophecy v.0.0.1", 1024, 768);
        Printable::SetWindowDimensions(1024, 768);
        m_image.Init("ludek.png", m_win);
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
                    //Do nothing, no collision
                }
                else
                {
                    event.type = SDL_QUIT;
// TODO (malice#1#): Fix this ugly hack

                }
            }
        }
    }
    void MenuState::Update(GameEngine* eng)
    {
        m_win.ClearScreen();
        m_image.Draw(imgX, imgY);
        m_win.DrawEverything();
    }
    void MenuState::Draw()
    {

    }
}
