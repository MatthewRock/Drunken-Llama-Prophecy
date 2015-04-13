#ifndef CREDITS_HPP_INCLUDED
#define CREDITS_HPP_INCLUDED

#include <SDL2/SDL.h>
#include "GameState.hpp"
#include "Manager.hpp"
#include "Sounds.hpp"
#include "Window.hpp"
#include "Texture.hpp"

namespace Llama
{
    class CreditsState : public GameState
    {
        public:
            CreditsState(GameEngine* eng);
            ~CreditsState() = default;
            void HandleEvents(SDL_Event& event);
            void Draw();
            void Pause();
            void Resume();
            void Update();
        private:
            Manager<int, Sounds::BGM>               m_musicManager;
            decltype(m_musicManager.Beginning())    m_musicIterator;
            Window*                                 m_win;
            Texture                                 m_credits;
    };
}
#endif // CREDITS_HPP_INCLUDED
