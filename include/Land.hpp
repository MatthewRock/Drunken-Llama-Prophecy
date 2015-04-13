#ifndef LAND_H
#define LAND_H

#include "Texture.hpp"
#include "Manager.hpp"

namespace Llama
{
    class Land
    {
        enum HexType : char
        {
            HEX_DIRT = 0,
            HEX_AUTUMN,
            HEX_LAVA,
            HEX_MAGIC,
            HEX_ROCK,
            HEX_STONE,
            HEX_WATER,
            HEX_SAND,
            HEX_SNOW,
            HEX_GRASS,
            HEX_N
        };
        struct Hex
        {
            unsigned x,y;
            char type;
        };
        public:
            Land();
        protected:
        private:
            Manager<HexType, Texture> m_HexTextureManager;


    };
}

#endif // LAND_H
