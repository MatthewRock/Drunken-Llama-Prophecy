#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "GameState.hpp"

#include <string>
#include <vector>
#include "World.hpp"
#include "Window.hpp"
#include "Texture.hpp"
#include "Sounds.hpp"

namespace Llama
{
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
            Texture m_image;
            Sounds::BGM reallyNiceMusic;
            int imgX = 100, imgY = 100;
    };
}
#endif // MENUSTATE_HPP
