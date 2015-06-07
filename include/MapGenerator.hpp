#ifndef MAPGENERATOR_HPP
#define MAPGENERATOR_HPP

#include "Land.hpp"
#include "GameState.hpp"

namespace Llama
{
    class MapGenerator final : public GameState
    {
        public:
            MapGenerator(Window* win);
            ~MapGenerator();
            void Pause() override;
            void Resume() override;

            void HandleEvents(SDL_Event& event) override;
            void Update() override;
            void Draw() override;

        protected:
        private:
            Window* m_win;
            Land m_Map;
            int m_MapSize;
            int m_EditorPosX, m_EditorPosY;
            HexType m_CurrentHex;
    };
}
#endif // MAPGENERATOR_HPP
