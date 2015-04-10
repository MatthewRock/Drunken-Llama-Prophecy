#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "GameState.hpp"

#include <string>
#include <vector>
#include <memory>
#include "World.hpp"
#include "Window.hpp"
#include "Texture.hpp"
#include "Sounds.hpp"
#include "Manager.hpp"

namespace Llama
{
    class Button
    {
        public:
//            void Init(Window*,const char*, const char*, int, int);    //Not sure if needed. Leaving just in case.

            void Draw();                                                //Duh
            void DrawHighlighted();                                     //Draws highlight texture (meant to be called when cursor is over the button)
            bool IsInBoundary(int x, int y);                            //Checks if specified location is in boundary of button
            operator const char*()  {return m_identifier;}

            Button() = default;
            Button(Window&,const char*, const char*, const char*, int, int);
            ~Button() = default;

            inline void Light() { m_lit = true;}
            inline void BindInDarkness() { m_lit = false;}
        private:
            int m_x;
            int m_y;
            Texture m_tex;
            Texture m_texh;
            bool m_lit;
            const char* m_identifier;
    };
    class MenuState : public GameState
    {
        enum HighlightedOptions
        {
            OPTION_MAIN_MENU,
            OPTION_LOADGAME,
            //OPTION_SETTINGS,
            OPTION_CREDITS,
            OPTION_EXIT,
            OPTION_N,
        };
        public:
            MenuState(GameEngine* eng);
            ~MenuState();

            void Pause();
            void Resume();
            void HandleEvents(SDL_Event& event);
            void Update();
            void Draw();

        protected:
            void HandleKeyboardInput(Uint32 keysym);
            void HighlightUp();
            void HighlightDown();

        private:
            Window m_win;
            Texture m_menu;
            std::vector<std::unique_ptr<Button>>    m_buttons;         //container for buttons in menu
            Manager<std::string, Sounds::BGM>       m_musicManager;
            int                                     m_highlightedButton;
            decltype(m_musicManager.Beginning())    m_musicIterator;
    };
}
#endif // MENUSTATE_HPP
//TODO(morgoth): React to mouse clicks, keyboard support, SettingsMenuState, PauseMenuState etc.
//TODO(morgoth): DOCUMENTATION!!!!!!!!
