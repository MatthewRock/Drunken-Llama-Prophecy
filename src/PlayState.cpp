#include "PlayState.hpp"
#include "Logger.hpp"
#include <sstream>
#include <cmath>
#include "PauseState.hpp"
#include <string>

namespace Llama
{
// TODO (malice#1#): Change this from magic number to some actual map size

    PlayState::PlayState(GameEngine* eng) : m_win(eng->GetWindowPointer()), m_Map(100, 100), m_Character("Pszemek","media/CharSprites/mon3_sprite_base.png", *m_win, 25, 25, m_Logic, m_Map)
    {
        m_engine = eng;

        m_MusicManager.Insert(0, new Sounds::BGM("media/gamemusic.ogg"));

        m_Map.InsertTexture(HEX_DIRT,   new Texture("media/Tile/tileDirt_tile.png", *m_win));
        m_Map.InsertTexture(HEX_AUTUMN, new Texture("media/Tile/tileAutumn_tile.png", *m_win));
        m_Map.InsertTexture(HEX_MAGIC,  new Texture("media/Tile/tileMagic_tile.png", *m_win));
        m_Map.InsertTexture(HEX_ROCK,   new Texture("media/Tile/tileRock_tile.png", *m_win));
        m_Map.InsertTexture(HEX_STONE,  new Texture("media/Tile/tileStone_tile.png", *m_win));
        m_Map.InsertTexture(HEX_WATER,  new Texture("media/Tile/tileWater_tile.png", *m_win));
        m_Map.InsertTexture(HEX_SAND,   new Texture("media/Tile/tileSand_tile.png", *m_win));
        m_Map.InsertTexture(HEX_SNOW,   new Texture("media/Tile/tileSnow_tile.png", *m_win));
        m_Map.InsertTexture(HEX_GRASS,  new Texture("media/Tile/tileGrass_tile.png", *m_win));
        m_Map.InsertTexture(HEX_LAVA,   new Texture("media/Tile/tileLava_tile.png", *m_win));

        m_musIterator = m_MusicManager.Beginning();

        for(int i = 20; i < 40; ++i)
        {
            for(int j = 20; j < 60; ++j)
                j % 2 == 0 ? m_Map.InsertHex(i,j,HEX_ROCK) : m_Map.InsertHex(i,j,HEX_ROCK);
        }
        for(int i = 40 ; i < 60; ++i)
        {
            for(int j = 20; j < 60; ++j)
                m_Map.InsertHex(i,j,HEX_LAVA);
        }
        m_Map.InsertHex(25,25,HEX_MAGIC);
        m_Map.InsertHex(25,26,HEX_MAGIC);
        m_Map.InsertHex(24,26,HEX_MAGIC);
        for(int x = 20; x < 29; ++x)
            m_Map.InsertHex(x,27,HEX_LAVA);
        m_Map.InsertMonster(MON_ORANGE, 20, 20, *m_win);
        m_Map.InsertMonster(MON_BLACK, 30, 70, *m_win);
        m_Logic.AddRule([](SDL_Event& event)
                        {
                            if(event.type == SDL_KEYDOWN)
                            {
                                if(event.key.keysym.sym == SDLK_TAB && event.key.repeat == 0)
                                {
                                    return true;
                                }
                                return false;
                            }
                            else if(event.type == SDL_MOUSEBUTTONDOWN)
                                return true;
                            else
                                return false;
                        });
        m_Logic.ProcessTurn();
    }
    PlayState::PlayState(GameEngine* eng, std::string pathname) : m_win(eng->GetWindowPointer()), m_Map(pathname), m_Character("Pszemek","media/CharSprites/mon3_sprite_base.png", *m_win, 25, 25, m_Logic, m_Map)
    {
        m_engine = eng;
        m_MusicManager.Insert(0, new Sounds::BGM("media/gamemusic.ogg"));

        m_Map.InsertTexture(HEX_DIRT,   new Texture("media/Tile/tileDirt_tile.png", *m_win));
        m_Map.InsertTexture(HEX_AUTUMN, new Texture("media/Tile/tileAutumn_tile.png", *m_win));
        m_Map.InsertTexture(HEX_MAGIC,  new Texture("media/Tile/tileMagic_tile.png", *m_win));
        m_Map.InsertTexture(HEX_ROCK,   new Texture("media/Tile/tileRock_tile.png", *m_win));
        m_Map.InsertTexture(HEX_STONE,  new Texture("media/Tile/tileStone_tile.png", *m_win));
        m_Map.InsertTexture(HEX_WATER,  new Texture("media/Tile/tileWater_tile.png", *m_win));
        m_Map.InsertTexture(HEX_SAND,   new Texture("media/Tile/tileSand_tile.png", *m_win));
        m_Map.InsertTexture(HEX_SNOW,   new Texture("media/Tile/tileSnow_tile.png", *m_win));
        m_Map.InsertTexture(HEX_GRASS,  new Texture("media/Tile/tileGrass_tile.png", *m_win));
        m_Map.InsertTexture(HEX_LAVA,   new Texture("media/Tile/tileLava_tile.png", *m_win));

        m_musIterator = m_MusicManager.Beginning();
        m_Map.InsertMonster(MON_ORANGE, 2, 1, *m_win);
        m_Map.InsertMonster(MON_BLACK, 30, 70, *m_win);

        m_Logic.AddRule([](SDL_Event& event)
                {
                    if(event.type == SDL_KEYDOWN)
                    {
                        if(event.key.keysym.sym == SDLK_TAB && event.key.repeat == 0)
                        {
                            return true;
                        }
                        return false;
                    }
                    else if(event.type == SDL_MOUSEBUTTONDOWN)
                        return true;
                    else
                        return false;
                });
        m_Logic.ProcessTurn();
    }

    void PlayState::HandleEvents(SDL_Event& event)
    {
        m_Logic.ProcessInput(event);
        if(!m_Character.IsDead())
            m_Character.HandleEvents(event);
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
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
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            //m_Map.CheckCollision(event);
            m_Map.MoveCharacterAccordingly(event, m_Character);
        }
    }

    void PlayState::Update()
    {
        if(!Sounds::BGM::Playing())
            m_musIterator->second->Play();
        if(m_Logic.AllowNextTurn())
        {
            if(m_Character.IsIdle())
            {
                m_Character.Execute();
                m_Character.Damage(m_Map.FishAI(m_Character.GetPosition().first, m_Character.GetPosition().second));
                if(m_Character.IsDead())
                    ChangeStateDestructively(new MenuState(m_engine));
                if(m_Map.GetHexType(m_Character.GetPosition().first, m_Character.GetPosition().second) == HEX_MAGIC)
                    m_Character.Heal();

            }
            m_Logic.ProcessTurn();
        }
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
