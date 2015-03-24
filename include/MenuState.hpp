#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "GameState.hpp"

#include <string>
#include <vector>
#include "World.hpp"
#include "Window.hpp"
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
    };
}
#endif // MENUSTATE_HPP
