#include "PlayState.hpp"
#include "Logger.hpp"
#include <sstream>
#include <cmath>
#include "PauseState.hpp"
#include <string>

namespace Llama
{
    PlayState::PlayState(GameEngine* eng) : m_win(eng->GetWindowPointer()), m_Map(100, 100)
    {
        m_engine = eng;

        m_MusicManager.Insert(0, new Sounds::BGM("media/gamemusic.ogg"));

        m_Map.InsertTexture(HEX_LAVA, new Texture("media/Tile/tileLava_tile.png", *m_win));
        m_Map.InsertTexture(HEX_MAGIC, new Texture("media/Tile/tileMagic_tile.png", *m_win));
        m_Map.InsertTexture(HEX_WATER, new Texture("media/Tile/tileWater_tile.png", *m_win));
        m_Map.InsertTexture(HEX_ROCK, new Texture("media/Tile/tileRock_tile.png", *m_win));

        m_Character = std::unique_ptr<Texture>(new Texture("media/Tile/alienBeige.png", *m_win));
// TODO (malice#1#): Make drawing Hexes simple and easy

        m_hexWidth = 56;
        m_hexHeight = 82;

        m_musIterator = m_MusicManager.Beginning();
        m_charX = 8;
        m_charY = 10;

        for(int i = 0; i < 30; ++i)
        {
            for(int j = 0; j < 30; ++j)
                m_Map.InsertHex(i,j,HEX_DIRT);
        }
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
        m_Map.DrawInProximity(m_charX, m_charY);
        auto tempCords = CalculateXY(m_charX, m_charY);
        CorrectForChar(tempCords);
        m_Character->Draw(tempCords.first, tempCords.second);

    }
}
