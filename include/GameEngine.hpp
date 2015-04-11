#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include "Initializer.hpp"

#include <vector> // For stack of states
#include <memory> // unique_ptr
#include "GameState.hpp"
#include "Window.hpp"
#include "Timer.hpp"
/// \brief Main engine class.

//Private inheritance of Initializer ensures initialization of systems before game starts
namespace Llama
{
    class GameEngine : private Initializer
    {
        public:
            GameEngine();
            ~GameEngine() = default;

            inline void Run()
            {
                while(IsRunning())
                {
                    //m_fpsCapTimer.Start();
                    HandleEvents();
                    Update();
                    Draw();
//                    if(m_fpsCapTimer.GetTicks() < 1000 / MAX_FPS)
//                        SDL_Delay((1000 / MAX_FPS) - m_fpsCapTimer.GetTicks());
                }
            }

            void ChangeState(GameState* state);
            void ChangeStateDestructively(GameState* state);
            void PushState(GameState* state);
            void PopState();
            Window* GetWindowPointer() { return &m_win; }
            inline void Quit() { m_running = false; }

        private:
            void Update();
            void HandleEngineEvents();
            void HandleEvents();
            void Draw();

            inline bool IsRunning() { return (m_running && !m_states.empty()); }
            Window m_win;
            std::vector<std::unique_ptr<GameState> > m_states;
            bool m_running;
            SDL_Event m_gameEvent;
            const int MAX_FPS = 30;
            Timer<> m_fpsCapTimer;

            //A vector of pairs: regex, and code (enum) for matching option.
    };
}
#endif // GAMEENGINE_HPP
