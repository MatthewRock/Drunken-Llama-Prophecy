#ifndef MAPGENERATOR_HPP
#define MAPGENERATOR_HPP

#include "Land.hpp"
#include "GameState.hpp"

class MapGenerator final : public GameState
{
    public:
        MapGenerator(GameEngine* eng);
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
        bool m_DrawContinuously;
        bool m_DeleteContinuously;
};
#endif // MAPGENERATOR_HPP
