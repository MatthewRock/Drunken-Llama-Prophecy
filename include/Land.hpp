#ifndef LAND_H
#define LAND_H

#include "Texture.hpp"
#include "Manager.hpp"

namespace Llama
{
    class Land
    {
        enum HexType
        {
            HEX_DIRT,
            HEX_AUTUMN,
            HEX_LAVA,
            HEX_MAGIC,
            HEX_ROCK,
            HEX_STONE,
            HEX_WATER,
            HEX_SAND,
            HEX_SNOW,
            HEX_GRASS,
        };

        public:
            Land();
        protected:
        private:
            Manager<HexType, Texture> m_HexTextureManager;

    };
}

#endif // LAND_H
