#ifndef EXITSTATE_HPP
#define EXITSTATE_HPP

#include "GameState.hpp"
#include "Window.hpp"

namespace Llama
{
    class GameEngine;

    class ExitState : public GameState
    {
        public:
            ExitState(GameEngine* eng, Window& win, GameState* parent);

            void Pause();
            void Resume();

            void Update();
            void HandleEvents(SDL_Event& event);
            void Draw();

            ~ExitState() = default;
        protected:
        private:
            Window* m_win;
            GameState* m_parent;
// TODO (malice#1#): Add: "Are you sure you want to exit?" And two buttons: Yes|No

    };
}

#endif // EXITSTATE_HPP
