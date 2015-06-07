#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "GameState.hpp"
#include "Window.hpp"
#include "Manager.hpp"
#include "PlayableCharacter.hpp"
#include <utility> // std::pair
#include "Sounds.hpp"
#include "Land.hpp"
#include "GameLogic.hpp"
namespace Llama
{
    class PlayState : public GameState
    {
        public:
            PlayState(GameEngine* eng);
            ~PlayState() = default;
            void Pause(){GameState::Pause();};
            void Resume(){GameState::Resume();};

            void HandleEvents(SDL_Event& event);
            void Update();
            void Draw();
        protected:
        private:
            Window* m_win; // Non-owning Window ptr.
            Manager<int,Sounds::BGM> m_MusicManager;
            GameLogic m_Logic;

            Land m_Map;
            PlayableCharacter m_Character;
            int m_hexWidth;
            int m_hexHeight;
            decltype(m_MusicManager.Beginning()) m_musIterator;
    };
}
#endif // PLAYSTATE_HPP
