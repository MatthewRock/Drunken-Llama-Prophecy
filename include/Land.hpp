#ifndef LAND_H
#define LAND_H

#include "Texture.hpp"
#include "Manager.hpp"
#include "Graph.hpp"
#include "Camera.hpp"

namespace Llama
{
    class Land
    {
        public:
            Land(int w, int h) : m_Graph(w,h)
            {
                for(int i = 0; i < 20; ++i)
                {
                    for(int j = 0; j < 20; ++j)
                    {
                        coords[i][j] = m_Graph.CalculateXY(i,j);
                    }
                }
            };
            void InsertTexture(HexType type, Texture* texture);
            void InsertHex(int x, int y, HexType type);
            void DrawInProximity(int x, int y);
            std::pair<int,int> CheckCollision(SDL_Event& event);
        protected:

        private:
            Manager<HexType, Texture> m_HexTextureManager;
            Graph m_Graph;
            std::pair<int,int>coords[20][20];
    };
}
#endif // LAND_H
