#ifndef LAND_H
#define LAND_H

#include "Texture.hpp"
#include "Manager.hpp"
#include "Graph.hpp"

namespace Llama
{
    class Land
    {
        public:
            Land(int w, int h) : m_Graph(w,h){};
            void InsertTexture(HexType type, Texture* texture);
            void InsertHex(int x, int y, HexType type);
            void DrawInProximity(int x, int y);
        protected:

        private:
            Manager<HexType, Texture> m_HexTextureManager;
            Graph m_Graph;
    };
}
#endif // LAND_H
