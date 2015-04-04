#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <string>
#include <SDL2/SDL.h>

namespace Llama
{
    class GameEngine;

    class GameState
    {
        public:

            //These two pure virtual functions have default implementations that can be called
            //in further implementations to pause/resume state(change paused flag)
            virtual void Pause() = 0;
            virtual void Resume() = 0;

            virtual void HandleEvents(SDL_Event& event) = 0;
            virtual void Update() = 0;
            virtual void Draw() = 0;

            void Exit()
            {
                m_WillToExit = true;
            }
            bool WantsToExit()
            {
                return m_WillToExit;
            }

            GameState()
            {
                m_paused = false;
                m_WillToExit = false;
                m_engine = nullptr;
            }

            virtual ~GameState() = default;

            //We shouldn't be able to copy nor move state. Each state has specified role and fits on stack.
            //Allowing this would create possibility to break it.

            GameState(const GameState& other) = delete;
            GameState(GameState&& other) = delete;
            GameState& operator=(const GameState& other) = delete;
            GameState& operator=(GameState&&) = delete;

            void ChangeState(GameState* state);
            inline bool IsPaused() { return m_paused; }
        protected:
            GameEngine* m_engine;

        private:
            int m_paused;
            bool m_WillToExit;
    };
}
#endif // GAMESTATE_HPP
