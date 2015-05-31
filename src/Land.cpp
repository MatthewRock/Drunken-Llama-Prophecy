#include "Land.hpp"
#include <iostream>

namespace Llama
{
    void Land::InsertTexture(HexType type, Texture* texture)
    {
        m_HexTextureManager.Insert(type, texture);
    }

    void Land::InsertHex(int x, int y, HexType type)
    {
        m_Graph.InsertHex(x,y,type);
    }
    //19x20(x,y) hexes grid fits on screen
    void Land::DrawInProximity(int x, int y)
    {
        //Character will be the center of action.
        int newx = x - 10;
        int newy = y - 10;

        if(newx < 0) newx = 0;
        if(newy < 0) newy = 0;

        int finishx = newx + 20;
        int finishy = newy + 20;


        for(; newx < finishx; ++newx)
        {
            for(int yy = newy; yy < finishy; ++yy)
            {
                auto type = m_Graph.GetHexType(newx, yy);
                auto coords = m_Graph.CalculateXY(newx, yy);
                m_HexTextureManager.GetElement(type)->Draw(coords.first, coords.second);
            }

        }

    }
}
// TODO (malice#1#): Fix segfault. Segfault's because w of texture is set to some huge number, not sure why.
