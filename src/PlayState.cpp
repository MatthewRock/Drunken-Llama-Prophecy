#include "PlayState.hpp"
#include "Logger.hpp"
#include <sstream>
#include <cmath>
#include "PauseState.hpp"
namespace Llama
{
    PlayState::PlayState(GameEngine* eng) : m_win(eng->GetWindowPointer())
    {
        m_engine = eng;

        m_MusicManager.Insert(0, new Sounds::BGM("media/gamemusic.ogg"));

        m_TileManager.Insert(0, new Texture("media/Tile/tileLava_tile.png", *m_win));
        m_TileManager.Insert(1, new Texture("media/Tile/tileMagic_tile.png", *m_win));
        m_TileManager.Insert(2, new Texture("media/Tile/tileWater_tile.png", *m_win));
        m_TileManager.Insert(3, new Texture("media/Tile/tileRock_tile.png", *m_win));
        m_TileManager.Insert(4, new Texture("media/Tile/alienBeige.png", *m_win));
        m_TileManager.Insert(5, new Texture("media/Tile/Tiles/treeCactus_1.png", *m_win));
        m_TileManager.Insert(6, new Texture("media/Tile/Tiles/treeCactus_3.png", *m_win));
        m_TileManager.Insert(7, new Texture("media/Tile/Tiles/smallRockDirt.png", *m_win));

        m_hexWidth = m_TileManager[0]->GetW() - 9;
        m_hexHeight = m_TileManager[0]->GetH() - 7;
        m_musIterator = m_MusicManager.Beginning();
        m_charX = 8;
        m_charY = 10;
    }
    std::pair<int, int> PlayState::CalculateXY(int x, int y)
    {
        std::pair<int, int> result;
        result.first = (y % 2 == 0) ? x * m_hexWidth : x * m_hexWidth - (.5 * m_hexWidth);
        //Correcting offset
        result.first -= 4;

        result.second = (y - 1) * .5 * m_hexHeight;
        return result;
    }
    void PlayState::CorrectForChar(std::pair<int, int>& pr)
    {
        pr.first += 15;
        pr.second -= 15;
    }
    void PlayState::HandleEvents(SDL_Event& event)
    {
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_q:
                    m_charY--;
                    if(m_charY % 2 == 0)
                        m_charX--;
                break;
                case SDLK_w:
                    m_charY--;
                break;
                case SDLK_z:
                    m_charY++;
                    if(m_charY % 2 == 0)
                        m_charX--;
                break;
                case SDLK_c:
                    m_charY++;
                    if(m_charY % 2 == 1)
                        m_charX++;
                break;
                case SDLK_s:
                    m_charY++;
                break;
                case SDLK_a:
                    m_charX--;
                break;
                case SDLK_d:
                    m_charX++;
                break;
                case SDLK_e:
                    m_charY--;
                    if(m_charY % 2 == 1)
                        m_charX++;
                break;
                case SDLK_n:
                    m_musIterator++;
                    if(m_musIterator == m_MusicManager.End())
                    {
                        m_musIterator = m_MusicManager.Beginning();
                    }
                    m_musIterator->second->Play();
                break;
                case SDLK_ESCAPE:
                    ChangeState(new PauseState(m_engine));
                break;
                default:
                break;
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
        //m_TileManager.GetElement(3)->Draw(CalculateX(0), CalculateY(1));
        auto tempCords = CalculateXY(0, 0);
        for(int i = 0; i < 20;++i)
            for(int j = 0; j < 20;++j)
            {
                tempCords = CalculateXY(i,j);
                m_TileManager.GetElement(0)->Draw(tempCords.first, tempCords.second);
            }

        tempCords = CalculateXY(12, 12);
        m_TileManager.GetElement(7)->Draw(tempCords.first, tempCords.second);

        tempCords = CalculateXY(9,9);
        m_TileManager.GetElement(3)->Draw(tempCords.first, tempCords.second);
        CorrectForChar(tempCords);
        m_TileManager.GetElement(5)->Draw(tempCords.first, tempCords.second);

        tempCords = CalculateXY(8,10);
        m_TileManager.GetElement(2)->Draw(tempCords.first, tempCords.second);

        tempCords = CalculateXY(8,9);
        m_TileManager.GetElement(1)->Draw(tempCords.first, tempCords.second);
        CorrectForChar(tempCords);
        m_TileManager.GetElement(6)->Draw(tempCords.first, tempCords.second);

        tempCords = CalculateXY(m_charX, m_charY);
        CorrectForChar(tempCords);
        m_TileManager.GetElement(4)->Draw(tempCords.first, tempCords.second);

    }
}
