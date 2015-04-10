#include "PlayState.hpp"
#include "Logger.hpp"
#include <sstream>

namespace Llama
{
    PlayState::PlayState(GameEngine* eng, Window&& win) : m_win(std::move(win))
    {
        m_engine = eng;

        m_MusicManager.Insert(0, new Sounds::BGM("media/MainMenu.ogg"));//("media/music/Desire.mp3"));
        m_MusicManager.Insert(1, new Sounds::BGM("media/music/BlueOcean.mp3"));
        m_MusicManager.Insert(2, new Sounds::BGM("media/music/Sun.mp3"));

        m_TileManager.Insert(0, new Texture("media/Tile/tileLava_tile.png", m_win));
        m_TileManager.Insert(1, new Texture("media/Tile/tileMagic_tile.png", m_win));
        m_TileManager.Insert(2, new Texture("media/Tile/tileWater_tile.png", m_win));
        m_TileManager.Insert(3, new Texture("media/Tile/tileRock_tile.png", m_win));
        m_hexWidth = m_TileManager[0]->GetW() - 9;
        m_hexHeight = m_TileManager[0]->GetH() - 6;
        m_musIterator = m_MusicManager.Beginning();
    }
    std::pair<int, int> PlayState::CalculateXY(int x, int y)
    {
        std::pair<int, int> result;
        result.first = y % 2 == 0 ? x * m_hexWidth : x * m_hexWidth - (.5 * m_hexWidth);
        //Correcting offset
        result.first -= 4;
        result.second = (y - 1) * .5 * m_hexHeight;
        //Because height isn't evenly divisible, it starts to leave bigger gaps every 2 rows. This solution makes everything look better
        for(int i = 3; i < 20; i = i+2)
            if(y >= i)
                result.second -= 1;
            else break;
        return result;
    }
    void PlayState::HandleEvents(SDL_Event& event)
    {
        if(event.type == SDL_KEYDOWN)
        {
            if(event.key.keysym.sym == SDLK_n)
            {
                m_musIterator++;
                if(m_musIterator == m_MusicManager.End())
                {
                    m_musIterator = m_MusicManager.Beginning();
                }
                m_musIterator->second->Play();
            }
        }
    }
    void PlayState::Update()
    {
        if(!Sounds::BGM::Playing())
            m_musIterator->second->Play();
    }
    void PlayState::Draw()
    {
        m_win.ClearScreen();
        //m_TileManager.GetElement(3)->Draw(CalculateX(0), CalculateY(1));
        auto tempCords = CalculateXY(0, 0);
        for(int i = 0; i < 20;++i)//m_win.GetW() / m_hexWidth; ++i)
            for(int j = 0; j < 20;++j)//m_win.GetH() / m_hexHeight; ++j)
            {
                tempCords = CalculateXY(i,j);
                m_TileManager.GetElement(0)->Draw(tempCords.first, tempCords.second);
            }
        tempCords = CalculateXY(9,9);
        m_TileManager.GetElement(3)->Draw(tempCords.first, tempCords.second);
        tempCords = CalculateXY(8,10);
        m_TileManager.GetElement(2)->Draw(tempCords.first, tempCords.second);
        tempCords = CalculateXY(8,9);
        m_TileManager.GetElement(1)->Draw(tempCords.first, tempCords.second);
        m_win.DrawEverything();
    }
}
