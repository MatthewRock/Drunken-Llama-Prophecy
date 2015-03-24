#ifndef EXITSTATE_HPP
#define EXITSTATE_HPP

#include "GameState.hpp"

namespace Llama
{
    class GameEngine;

    class ExitState : public GameState
    {
        public:
            ExitState(Window& win);

            void Pause();
            void Resume();

            void Update(GameEngine* engine);
            void HandleEvents(SDL_Event& event);
            void Draw();

            ~ExitState();
        protected:
        private:
    };
}

#endif // EXITSTATE_HPP
