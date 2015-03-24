#include "MenuState.hpp"
#include "Printable.hpp"
namespace Llama
{
    MenuState::MenuState()
    {
        m_win.Init("Drunken Llama Prophecy v.0.0.1", 1024, 768);
        Printable::SetWindowDimensions(1024, 768);
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

    }
    void MenuState::Update(GameEngine* eng)
    {
        m_win.ClearScreen();
        m_win.DrawEverything();
    }
    void MenuState::Draw()
    {
    }
}
