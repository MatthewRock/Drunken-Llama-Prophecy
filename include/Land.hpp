#ifndef LAND_H
#define LAND_H

#include "Texture.hpp"
#include "Manager.hpp"
#include "Graph.hpp"
#include "Camera.hpp"
#include "PlayableCharacter.hpp"
#include "Monster.hpp"
#include "Window.hpp"
#include <fstream>
#include <vector>

namespace Llama
{
    class Land
    {

        public:
            Land(int w, int h) : m_Graph(w,h)
            {
                for(int i = 0; i < 22; ++i)
                {
                    for(int j = 0; j < 22; ++j)
                    {
                        coords[i][j] = m_Graph.CalculateXY(i-2,j-1);
                    }
                }
            };
            Land(std::string pathname) : m_Graph(pathname)
            {
                for(int i = 0; i < 22; ++i)
                {
                    for(int j = 0; j < 22; ++j)
                    {
                        coords[i][j] = m_Graph.CalculateXY(i-2,j-1);
                    }
                }
            }
            void InsertTexture(HexType type, Texture* texture);
            void InsertHex(int x, int y, HexType type);
            void DrawInProximity(int x, int y, int offsetx, int offsety);
            std::pair<int,int> CheckCollision(SDL_Event& event, int offsetx, int offsety);
            void MoveCharacterAccordingly(SDL_Event& event, PlayableCharacter& character);
            inline void Resize(int x, int y) { m_Graph.Resize(x,y); }
            void PrintMap(std::ostream& stream);
            void InsertMonster(MonsterType, int, int, Window&);
            void FishAI(int x, int y);
        protected:

        private:
            std::vector<std::unique_ptr<Monster> > m_Monsters;
            Manager<HexType, Texture> m_HexTextureManager;
            Graph m_Graph;
            ///Stores screen coordinates for hexes. 0 indexes are off screen, 1 are first visible
            std::pair<int,int>coords[22][22];
    };
}
#endif // LAND_H
