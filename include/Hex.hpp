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

    struct Hex
    {
        Hex(HexType typee) : type(typee){}
        HexType type;
        bool Passable()
        {
            return (type != HEX_LAVA) && (type != HEX_WATER);
        }
        inline unsigned int Cost()
        {
            return 1;
        }
        static const int WIDTH = 56;
        static const int HEIGHT = 82;
        private:
            int x, y;
    };
}
#endif // HEX_HPP
