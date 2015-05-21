#ifndef HEX_HPP
#define HEX_HPP

namespace Llama
{
    enum HexType : unsigned char
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

// TODO (malice#1#): Remove x and y

    struct Hex
    {
        Hex(int xx, int yy, HexType typee) : x(xx), y(yy), type(typee){}
        unsigned x,y;
        HexType type;
        bool Passable()
        {
            return (type != HEX_LAVA) && (type != HEX_WATER);
        }
        inline unsigned int Cost()
        {
            return 1;
        }
    };
}
#endif // HEX_HPP
