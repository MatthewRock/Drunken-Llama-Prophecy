#include "MenuState.hpp"
#include "Printable.hpp"
#include "GameEngine.hpp"
#include "PlayState.hpp" // For "New game"
#include "Credits.hpp"

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

MenuState::MenuState(GameEngine* eng) : m_win(eng->GetWindowPointer())
{
    m_engine = eng; // If I ever get tempted to move this to parameter list: you can't if it's inherited slot. This one is... -.-

    m_menu.Init("media/Menu/Main/Menu.png", *m_win);

    m_musicManager.Insert("MenuMusic1", new Sounds::BGM("media/MainMenu.ogg"));
    m_musicManager.Insert("MenuMusic2", new Sounds::BGM("media/beatdown.ogg"));
    m_musicManager.Insert("MenuMusic3", new Sounds::BGM("media/fanfare-1.ogg"));
    m_musicIterator = m_musicManager.Beginning();
    m_musicIterator->second->Play();

    AddButton("NewGame", "media/Menu/Button1.png", "media/Menu/Button1h.png", 276, 150);
    AddButton("LoadGame", "media/Menu/Button2.png", "media/Menu/Button2h.png", 276, 200);
    AddButton("Settings", "media/Menu/SettingsButton.png", "media/Menu/SettingsButtonh.png", 276, 250);
    AddButton("Credits", "media/Menu/CreditsButton.png", "media/Menu/Creditsh.png", 276, 300);
    AddButton("Exit", "media/Menu/EndButton.png", "media/Menu/EndButtonh.png", 276, 350);
    m_highlightedButton = 0;
}

MenuState::~MenuState()
{
}

void MenuState::Pause()
{
    GameState::Pause();
}
void MenuState::Resume()
{
    GameState::Resume();
    m_musicIterator->second->Play();
}

void MenuState::HighlightUp()
{
    ++m_highlightedButton;
    m_highlightedButton = m_highlightedButton % m_buttons.size();
}
void MenuState::HighlightDown()
{
    --m_highlightedButton;
    if(0 > m_highlightedButton)
        m_highlightedButton = m_buttons.size() - 1;
}
void MenuState::AddButton(const char* identifier, const char* filename, const char* filenameh, int x, int y)
{
    m_buttons.push_back(std::unique_ptr<Button>(new Button(*m_win, identifier, filename, filenameh, x, y)));
}
void MenuState::SelectionSwitch(int selection)
{
    switch(selection)
    {
        case OPTION_MAIN_MENU:
            ChangeStateDestructively(new PlayState(m_engine));
            break;
        case OPTION_CREDITS:
            ChangeState(new CreditsState(m_engine));
            break;
        case OPTION_LOADGAME:
            ChangeStateDestructively(new PlayState(m_engine, "media/SavedMap.map.save3"));
        break;
        case OPTION_EXIT:
            Close();
            break;
        default:
            ++m_musicIterator;
            if(m_musicIterator == m_musicManager.End())
            {
                m_musicIterator = m_musicManager.Beginning();
            }
            m_musicIterator->second->Play();
            break;
    }
}
void MenuState::Close()
{
    m_engine->Quit();
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
    else if(keysym == SDLK_ESCAPE)
    {
        this->Close();
    }
    else if(keysym == SDLK_RETURN)
    {
        this->SelectionSwitch(m_highlightedButton);
        /*{
            case OPTION_MAIN_MENU:
                ChangeStateDestructively(new PlayState(m_engine, std::move(m_win)));
                break;
            case OPTION_EXIT:
                Exit();
                break;
            case OPTION_LOADGAME:
                m_musicIterator++;
                if(m_musicIterator == m_musicManager.End())
                {
                    m_musicIterator = m_musicManager.Beginning();
                }
                m_musicIterator->second->Play();
                break;
            default:
                //DoNothing
                break;
        }*/
    }
    //else
        //    if(event.key.keysym ==)
}
void MenuState::HandleMouseInput(SDL_Event& event)
{

    int mX = event.button.x;
    int mY = event.button.y;
    int selection = -1;
    for(unsigned i = 0; i < m_buttons.size(); ++i)
    {
        if(m_buttons.at(i)->IsInBoundary(mX, mY))
            selection = i;
    }
    this->SelectionSwitch(selection);
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
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        if(event.button.button == SDL_BUTTON_LEFT)
        {
            HandleMouseInput(event);
        }
    }
}
void MenuState::Update()
{

}
void MenuState::DrawButtons()
{
    for(unsigned i = 0; i < m_buttons.size(); i++)
    {
        if(i == m_highlightedButton)
            m_buttons.at(i)->DrawHighlighted();
        else
            m_buttons.at(i)->Draw();
    }
}
void MenuState::Draw()
{
    m_menu.Draw(0, 0);
    DrawButtons();
}

