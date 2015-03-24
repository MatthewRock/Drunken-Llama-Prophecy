#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "GameState.hpp"

#include <string>
#include <vector>
#include "World.hpp"
#include "Window.hpp"
#include "Texture.hpp"

namespace Llama
{
    class MenuState : public GameState
    {
        public:
            MenuState();
            ~MenuState() = default;

            void Pause();
            void Resume();
            void HandleEvents(SDL_Event& event);
            void Update(GameEngine* eng);
            void Draw();

        protected:
        private:
            Window m_win;
            Texture m_image;
            int imgX = 100, imgY = 100;
    };
}
#endif // MENUSTATE_HPP
