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
            Land();
        protected:
            std::pair<int, int> CalculateXY(int, int);
        private:
            Manager<HexType, Texture> m_HexTextureManager;
            Graph m_Graph;
    };
}
#endif // LAND_H
