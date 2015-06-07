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
            void Pause(){};
            void Resume(){};

            void HandleEvents(SDL_Event& event);
            void Update();
            void Draw();

        protected:
        private:
            void CorrectForChar(std::pair<int, int>& pr);
            std::pair<int, int> CalculateXY(int, int);
            Window* m_win; // Non-owning Window ptr.
            Manager<int,Sounds::BGM> m_MusicManager;
            Camera m_Camera;
            GameLogic m_Logic;

            Land m_Map;
            PlayableCharacter m_Character;
            int m_hexWidth;
            int m_hexHeight;
            int m_charX, m_charY;
            decltype(m_MusicManager.Beginning()) m_musIterator;
    };
}
#endif // PLAYSTATE_HPP
