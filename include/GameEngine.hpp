#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include "Initializer.hpp"

#include <vector> // For stack of states
#include <memory> // unique_ptr
#include "GameState.hpp"
#include "Window.hpp"
#include "Timer.hpp"
#include "Texture.hpp"
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
                try
                {
                    while(IsRunning())
                    {
                        HandleEvents();
                        Update();
                        Draw();
                    }
                }
                catch(std::exception const & ex)
                {
                    LOG_STRING("Exception thrown. Program will terminate. Exception in next line.");
                    LOG_STRING(ex.what());
                    Window ErrorWindow("Oh no! Something went wrong!", 320, 320);
                    Texture ErrorTexture("media/CreditsButton.png",ErrorWindow);
                    ErrorWindow.ClearScreen();
                    ErrorTexture.Draw(0,0);
                    ErrorWindow.DrawEverything();
                    SDL_Delay(1000);
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
