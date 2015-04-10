#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "GameState.hpp"
#include "Window.hpp"
#include "Manager.hpp"
#include "Texture.hpp"
#include <utility>

namespace Llama
{
    class PlayState : public GameState
    {
        public:
            PlayState(GameEngine* eng, Window&& win);
            ~PlayState() = default;
            void Pause(){};
            void Resume(){};

            void HandleEvents(SDL_Event& event){};
            void Update(){};
            void Draw();

        protected:
        private:
            std::pair<int, int> CalculateXY(int, int);
            Window m_win;
            Manager<int,Texture> m_TileManager;

            int m_hexWidth;
            int m_hexHeight;
    };
}
#endif // PLAYSTATE_HPP
