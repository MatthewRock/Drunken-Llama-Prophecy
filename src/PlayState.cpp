#include "PlayState.hpp"
#include "Logger.hpp"

namespace Llama
{
    PlayState::PlayState(GameEngine* eng, Window&& win) : m_win(std::move(win))
    {
        m_engine = eng;
        LOG_STRING("Entered PlayState");
        m_TileManager.Insert(0, new Texture("media/Tile/tileLava_tile.png", m_win));
//m_TileManager.Insert(1, new Texture("media/Tile/tileSnow_tile.png", m_win));
        m_hexHeight = m_TileManager[0]->GetH();
        m_hexWidth  = m_TileManager[0]->GetW();
    }

    void PlayState::Draw()
    {
        m_win.ClearScreen();
        m_TileManager.GetElement(0)->Draw(150, 150);
        m_TileManager.GetElement(0)->Draw(150 + m_hexWidth, 150);
        m_TileManager.GetElement(0)->Draw(150 + 2 * m_hexWidth, 150);
        m_TileManager.GetElement(0)->Draw(150 + m_hexWidth / 2, 150 - m_hexHeight / 2);
        m_TileManager.GetElement(0)->Draw(150 + 1.5 * m_hexWidth, 150 - m_hexHeight / 2);
        m_TileManager.GetElement(0)->Draw(150 + .5 * m_hexWidth, 150 + m_hexHeight / 2);
        m_TileManager.GetElement(0)->Draw(150 + 1.5 * m_hexWidth, 150 + m_hexHeight / 2);
        m_win.DrawEverything();
    }
}
