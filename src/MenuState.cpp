#include "MenuState.hpp"
#include "Printable.hpp"

#include "ExitState.hpp"

namespace Llama
{
    Button::Button(Window& window,const char* identifier, const char* filename, const char* filenameh, int x, int y) : m_x(x), m_y(y), m_tex(filename, window), m_texh(filenameh, window), m_lit(false), m_identifier(identifier)
    {
    }

    void Button::Draw()
    {
        if(m_lit)
            DrawHighlighted();
        else
            m_tex.Draw(m_x, m_y);
    }
    void Button::DrawHighlighted()
    {
        m_texh.Draw(m_x, m_y);
    }
    bool Button::IsInBoundary(int x, int y)
    {
        if((x > m_x) && (x < m_x+m_tex.GetW()) && (y > m_y) && (y < m_y+m_tex.GetH()))
            return true;
        else
            return false;
    }

    MenuState::MenuState(GameEngine* eng)
    {
        m_engine = eng; // If I ever get tempted to move this to parameter list: you can't if it's inherited slot. This one is... -.-

        m_win.Init("Drunken Llama Prophecy v.0.0.1", 1024, 768);
        Printable::SetWindowDimensions(1024, 768);
        m_menu.Init("media/Menu.png", m_win);

        m_musicManager.Insert("MenuMusic1", new Sounds::BGM("media/MainMenu.ogg"));
        m_musicManager.Insert("MenuMusic2", new Sounds::BGM("media/beatdown.ogg"));
        m_musicManager.Insert("MenuMusic3", new Sounds::BGM("media/fanfare-1.ogg"));
        m_musicIterator = m_musicManager.Beginning();
        m_musicIterator->second->Play();

        m_buttons.push_back(std::unique_ptr<Button>(new Button(m_win, "NewGame", "media/Button1.png", "media/Button1h.png", 276, 150)));
        m_buttons.push_back(std::unique_ptr<Button>(new Button(m_win, "LoadGame", "media/Button2.png", "media/Button2h.png", 276, 200)));
        m_buttons.push_back(std::unique_ptr<Button>(new Button(m_win, "Credits", "media/CreditsButton.png", "media/Creditsh.png", 276, 250)));
        m_buttons.push_back(std::unique_ptr<Button>(new Button(m_win, "Exit", "media/EndButton.png", "media/EndButtonh.png", 276, 300)));
        m_highlightedButton = m_buttons.begin();
    }

    void MenuState::Pause()
    {
        GameState::Pause();
    }
    void MenuState::Resume()
    {
        GameState::Resume();
    }

    void MenuState::HighlightUp()
    {
        if(m_highlightedButton > m_buttons.begin())
            m_highlightedButton--;
        else
            m_highlightedButton = m_buttons.end()-1;
    }
    void MenuState::HighlightDown()
    {
        if(m_highlightedButton < m_buttons.end()-1)
            m_highlightedButton++;
        else
            m_highlightedButton = m_buttons.begin();
    }
    void MenuState::HandleKeyboardInput(Uint32 keysym)
    {
        if(keysym == SDLK_UP)
        {
            HighlightUp();
        }
        else
            if(keysym == SDLK_DOWN)
            {
                HighlightDown();
            }
            //else
            //    if(event.key.keysym ==)
    }
    void MenuState::HandleEvents(SDL_Event& event)
    {
        if(event.type == SDL_KEYDOWN)
            HandleKeyboardInput(event.key.keysym.sym);
        else
            if(event.type == SDL_MOUSEMOTION)
            {
                int mX = event.button.x;
                int mY = event.button.y;
                for(auto i = m_buttons.begin(); i < m_buttons.end(); i++)
                {
                    if((*i)->IsInBoundary(mX, mY))
                        m_highlightedButton = i;
                }
            }
       /* if(event.type == SDL_MOUSEBUTTONDOWN)
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
        }*/
    }
    void MenuState::Update()
    {

    }
    void MenuState::Draw()
    {
        m_win.ClearScreen();
        m_menu.Draw(0, 0);
        for(auto i = m_buttons.begin(); i < m_buttons.end(); i++)
        {
            if(i == m_highlightedButton)
                (*i)->DrawHighlighted();
            else
                (*i)->Draw();
        }
        m_win.DrawEverything();
    }
}
