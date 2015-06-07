#include "MapGenerator.hpp"

namespace Llama
{
    MapGenerator::MapGenerator(Window* win) : m_win(win), m_Map(40,40)
    {
        m_MapSize = 40;
        m_EditorPosX = m_EditorPosY = 20;
        m_CurrentHex = HexType::HEX_DIRT;//Equal to zero, but oh well, -fpermissive forbids me to put zero.
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
    }

    void MapGenerator::Pause()
    {

    }
    void MapGenerator::Resume()
    {

    }
    void MapGenerator::HandleEvents(SDL_Event& event)
    {
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_r://Make map 2x bigger
                    m_MapSize *= 2;
                    m_Map.Resize(m_MapSize, m_MapSize);
                break;
                case SDLK_TAB://Get next hex
                    m_CurrentHex = static_cast<HexType>( (static_cast<int>(m_CurrentHex) + 1)% static_cast<int>(HexType::HEX_N) );
                break;
                case SDLK_BACKQUOTE://Get previous hex
                    if(m_CurrentHex == 0)
                        m_CurrentHex = HexType::HEX_N;
                    m_CurrentHex = static_cast<HexType>(static_cast<int>(m_CurrentHex) - 1);
                break;
                //movement
                case SDLK_w:
                    m_EditorPosY-=2;
                break;
                case SDLK_d:
                    ++m_EditorPosX;
                break;
                case SDLK_s:
                    m_EditorPosY+=2;
                break;
                case SDLK_a:
                    --m_EditorPosX;
                break;
                default:
                break;
            }
        }
        else if(event.button.state == SDL_PRESSED)
        {
            auto coords = m_Map.CheckCollision(event, m_EditorPosX, m_EditorPosY);

            switch(event.button.button)
            {
                case SDL_BUTTON_LEFT://Insert hex at mouse position
                    m_Map.InsertHex(coords.first, coords.second, m_CurrentHex);
                break;
                case SDL_BUTTON_RIGHT:
                    m_Map.InsertHex(coords.first, coords.second, HEX_DIRT);
                break;
                default:
                break;
            }
        }
    }
    void MapGenerator::Update()
    {

    }
    void MapGenerator::Draw()
    {
        m_Map.DrawInProximity(m_EditorPosX, m_EditorPosY,0,0);
    }
    MapGenerator::~MapGenerator()
    {
        //Save map to file...
        std::ofstream mapfile("media/SavedMap.map");
        if(mapfile.is_open())
        {
            mapfile << m_MapSize << std::endl;
            m_Map.PrintMap(mapfile);

            mapfile.close();
        }
    }
}
