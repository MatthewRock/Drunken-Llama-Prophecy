#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include "Initializer.hpp"

#include <vector> // For stack of states
#include <memory> // unique_ptr
#include "GameState.h"

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
                    HandleEvents();
                    Update();
                    Draw();
                }
            }

            void ChangeState(GameState* state);
            void PushState(GameState* state);
            void PopState();
            inline void Quit() { m_running = false; }

        private:
            void Update();
            void HandleEngineEvents(std::string ch);
            void HandleEvents();
            void Draw();

            inline bool IsRunning() { return m_running; }

            std::vector<std::unique_ptr<GameState> > m_states;
            bool m_running;
            //A vector of pairs: regex, and code (enum) for matching option.
    };
}
#endif // GAMEENGINE_HPP