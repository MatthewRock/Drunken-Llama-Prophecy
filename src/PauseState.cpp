#include "PauseState.hpp"
#include "MapGenerator.hpp"

namespace Llama
{

    PauseState::PauseState(GameEngine* eng)
    {
        m_engine = eng;
        m_win = m_engine->GetWindowPointer();

        m_menu.Init("media/Menu/Pause/PauseMenu.png", *m_win);
        AddButton("Resume", "media/Menu/ResumeButton.png", "media/Menu/ResumeButtonh.png", 276, 250);
        AddButton("Save", "media/Menu/SaveButton.png", "media/Menu/SaveButtonh.png", 276, 300);
        AddButton("Exit", "media/Menu/EndButton.png", "media/Menu/EndButtonh.png", 276, 350);
        m_highlightedButton = 0;
    }
    PauseState::~PauseState()
    {

    }

    void PauseState::Pause()
    {
        GameState::Pause();
    }
    void PauseState::Resume()
    {
        GameState::Resume();
    }
    void PauseState::SelectionSwitch(int selection)
    {
        switch(selection)
        {
            case PAUSE_RESUME:
                Exit();
                break;
            case PAUSE_SAVE:
                m_engine->CrushWithState(new MapGenerator(m_engine));
            break;
            case PAUSE_EXIT:
                MenuState::Close();
                break;
            default:
                break;
        }
    }
    void PauseState::Close()
    {
        Exit();
    }
    void PauseState::Draw()
    {
        m_menu.Draw(182, 133);
        DrawButtons();
    }
}
