#include "PlayState.hpp"
#include "Logger.hpp"
#include <sstream>
#include <cmath>
#include "PauseState.hpp"
#include <string>

namespace Llama
{
// TODO (malice#1#): Change this from magic number to some actual map size

    PlayState::PlayState(GameEngine* eng) : m_win(eng->GetWindowPointer()), m_Map(100, 100), m_Character("Pszemek","media/CharSprites/mon3_sprite_base.png", *m_win, 25, 25)
    {
        m_engine = eng;

        m_MusicManager.Insert(0, new Sounds::BGM("media/gamemusic.ogg"));

        m_Map.InsertTexture(HEX_LAVA, new Texture("media/Tile/tileLava_tile.png", *m_win));
        m_Map.InsertTexture(HEX_MAGIC, new Texture("media/Tile/tileMagic_tile.png", *m_win));
        m_Map.InsertTexture(HEX_WATER, new Texture("media/Tile/tileWater_tile.png", *m_win));
        m_Map.InsertTexture(HEX_ROCK, new Texture("media/Tile/tileRock_tile.png", *m_win));
        m_Map.InsertTexture(HEX_DIRT, new Texture("media/Tile/tileDirt_tile.png", *m_win));

// TODO (malice#1#): Make drawing Hexes simple and easy

        m_hexWidth = 56;
        m_hexHeight = 82;

        m_musIterator = m_MusicManager.Beginning();
        m_charX = 8;
        m_charY = 10;

        for(int i = 20; i < 40; ++i)
        {
            for(int j = 20; j < 60; ++j)
                j % 2 == 0 ? m_Map.InsertHex(i,j,HEX_LAVA) : m_Map.InsertHex(i,j,HEX_ROCK);
        }
        for(int i = 40 ; i < 60; ++i)
        {
            for(int j = 20; j < 60; ++j)
                m_Map.InsertHex(i,j,HEX_LAVA);
        }
        m_Map.InsertHex(25,25,HEX_MAGIC);
        m_Map.InsertHex(25,26,HEX_MAGIC);
        m_Map.InsertHex(24,26,HEX_MAGIC);

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
        int movedX = 0, movedY = 0;
        if(event.type == SDL_KEYDOWN && m_Character.IsIdle())
        {
            switch(event.key.keysym.sym)
            {
                if(m_Character.IsIdle())
                {
                case SDLK_q:
                    m_Character.Order(Character::MOVE, (m_Character.GetPosition().second % 2 == 1) ? --movedX : 0, --movedY );
                break;
                case SDLK_w:
                    m_Character.Order(Character::MOVE, 0, --movedY );
                break;
                case SDLK_e:
                    m_Character.Order(Character::MOVE, (m_Character.GetPosition().second % 2 == 0) ? ++movedX : 0, --movedY);
                break;
                case SDLK_z:
                    m_Character.Order(Character::MOVE, (m_Character.GetPosition().second % 2 == 1) ? --movedX : 0, ++movedY);
                break;
                case SDLK_c:
                    m_Character.Order(Character::MOVE, (m_Character.GetPosition().second % 2 == 0) ? ++movedX : 0, ++movedY);
                break;
                case SDLK_s:
                    m_Character.Order(Character::MOVE, 0, ++movedY);
                break;
                case SDLK_a:
                    m_Character.Order(Character::MOVE, --movedX, 0);
                break;
                case SDLK_d:
                    m_Character.Order(Character::MOVE, ++movedX, 0);
                break;
                case SDLK_SPACE:
                    m_Character.Order(Character::ATTACK, 0, 0);
                break;
                }
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
        m_Camera.UpdateXY(movedX * Hex::WIDTH, movedY * Hex::HEIGHT);


        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            //m_Map.CheckCollision(event);
            m_Map.MoveCharacterAccordingly(event, m_Character);
        }

        if(m_Character.IsIdle())
        {
            m_Character.Execute();
        }

    }
    void PlayState::Update()
    {
        if(!Sounds::BGM::Playing())
            m_musIterator->second->Play();
    }
    void PlayState::Draw()
    {
        m_Map.DrawInProximity(m_Character.GetPosition().first, m_Character.GetPosition().second, m_Character.GetAnimationOffset().first, m_Character.GetAnimationOffset().second);

        //auto tempCords = CalculateXY(m_charX, m_charY);
        //auto tempCords = CalculateXY(9, 8);
        //CorrectForChar(tempCords);
        m_Character.Draw(/*tempCords.first, tempCords.second*/);

    }
}
