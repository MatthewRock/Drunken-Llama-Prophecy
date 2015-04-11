#ifndef PAUSESTATE_HPP_INCLUDED
#define PAUSESTATE_HPP_INCLUDED
#include "GameEngine.hpp"
#include "MenuState.hpp"
#include <SDL2/SDL.h>
#include <memory>

namespace Llama
{
    class PauseState : public MenuState
    {
        enum PauseOptions
        {
            PAUSE_RESUME,
            PAUSE_SAVE,
            PAUSE_EXIT,
            PAUSE_N,
        };
        public:
            PauseState(GameEngine* eng);
            ~PauseState();

            void Pause();
            void Resume();
            void Draw();
        protected:
            void SelectionSwitch(int selection);
            void Close();
    };
}

#endif // PAUSESTATE_HPP_INCLUDED
