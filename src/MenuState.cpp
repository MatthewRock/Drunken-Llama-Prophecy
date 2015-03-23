#include "MenuState.hpp"

#include "csout.hpp"

namespace Llama
{
    MenuState::MenuState(Csout& csout) : userInput(-1)
    {
    }

    void MenuState::Pause()
    {
        GameState::Pause();
    }
    void MenuState::Resume()
    {
        GameState::Resume();
    }
    void MenuState::HandleEvents(std::string command)
    {

    }
    void MenuState::Update(GameEngine* eng)
    {

    }
    void MenuState::Draw(Csout& csout)
    {
    }
}
