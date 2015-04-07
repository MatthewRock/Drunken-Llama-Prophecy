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

            Button() = default;
            Button(Window&,const char*, const char*, int, int);
            ~Button() = default;
        private:
            int m_x;
            int m_y;
            Texture m_tex;
            Texture m_texh;
    };
    class MenuState : public GameState
    {
        public:
            MenuState(GameEngine* eng);
            ~MenuState() = default;

            void Pause();
            void Resume();
            void HandleEvents(SDL_Event& event);
            void Update();
            void Draw();

        protected:
        private:
            Window m_win;
            Texture m_menu;
            std::vector<std::unique_ptr<Button>> m_buttons;         //container for buttons in menu
            decltype(m_buttons.begin()) m_highlightedButton;        //highlight for selection
            Manager<std::string, Sounds::BGM> m_musicManager;
            decltype(m_musicManager.Beginning()) m_musicIterator;
    };
}
#endif // MENUSTATE_HPP
//TODO(morgoth): React to mouse clicks, keyboard support, SettingsMenuState, PauseMenuState etc.
//TODO(morgoth): DOCUMENTATION!!!!!!!!
