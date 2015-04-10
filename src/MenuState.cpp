#include "MenuState.hpp"
#include "Printable.hpp"

#include "ExitState.hpp"
#include "PlayState.hpp" // For "New game"

namespace Llama
{
    Button::Button(Window& window,const char* identifier, const char* filename, const char* filenameh, int x, int y)
                  : m_x(x), m_y(y), m_tex(filename, window), m_texh(filenameh, window), m_lit(false), m_identifier(identifier)
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

        m_highlightedButton = 0;
    }

    MenuState::~MenuState()
    {
        m_musicIterator->second->Stop();
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
        m_highlightedButton = (++m_highlightedButton) % HighlightedOptions::OPTION_N;
    }
    void MenuState::HighlightDown()
    {
        --m_highlightedButton;
        if(0 > m_highlightedButton)
            m_highlightedButton = OPTION_N - 1;
    }
    void MenuState::HandleKeyboardInput(Uint32 keysym)
    {
        //Highlighting based on arrow movement(kbd)
        if(keysym == SDLK_UP)
        {
            //Inverted gravity! Woohoo!
            HighlightDown();
        }
        else if(keysym == SDLK_DOWN)
        {
            //It doesn't have to make sense if it works.
            HighlightUp();
        }
        else if(keysym == SDLK_RETURN)
        {
            switch(m_highlightedButton)
            {
                case OPTION_MAIN_MENU:
                    ChangeStateDestructively(new PlayState(m_engine, std::move(m_win)));
                    break;
                default:
                    //DoNothing
                    break;
            }
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
            //Highlighting buttons on mouse hover
            {
                unsigned mX = event.button.x;
                unsigned mY = event.button.y;
                for(unsigned i = 0; i < m_buttons.size(); ++i)
                {
                    if(m_buttons.at(i)->IsInBoundary(mX, mY))
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
        for(auto i = 0; i < m_buttons.size(); i++)
        {
            if(i == m_highlightedButton)
                m_buttons.at(i)->DrawHighlighted();
            else
                m_buttons.at(i)->Draw();
        }
        m_win.DrawEverything();
    }
}
