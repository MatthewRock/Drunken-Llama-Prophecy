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
        //If we got out of map, correct it.
        //TODO: Correct for going out of max bounds too
        if(newx < 0) newx = 0;
        if(newy < 0) newy = 0;
        // Know when to stop looping
        int finishx = newx + 20;
        int finishy = newy + 20;

        int i = 0, j = 0;
        //Print tiles
        for(; newx < finishx; ++newx)
        {
            for(int yy = newy; yy < finishy; ++yy)
            {
                //Get type and coords
                auto type = m_Graph.GetHexType(newx, yy);
                auto cords = coords[i][j];
                //Finally print
                m_HexTextureManager.GetElement(type)->Draw(cords.first, cords.second);
                j = (j + 1) % 20;
            }
            ++i;
        }
    }
    void Land::DrawInProximityDebug(int x, int y)
    {
        //Character will be the center of action.
        int newx = x - 10;
        int newy = y - 10;
        //If we got out of map, correct it.
        //TODO: Correct for going out of max bounds too
        if(newx < 0) newx = 0;
        if(newy < 0) newy = 0;
        // Know when to stop looping
        int finishx = newx + 5;
        int finishy = newy + 5;

        int i = 0, j = 0;
        //Print tiles
        for(; newx < finishx; ++newx)
        {
            for(int yy = newy; yy < finishy; ++yy)
            {
                //Get type and coords
                auto type = m_Graph.GetHexType(newx, yy);
                auto cords = coords[i][j];
                //Finally print
                m_HexTextureManager.GetElement(type)->DebugDrawOutline(cords.first, cords.second);
                j = (j + 1) % 20;
            }
            ++i;
        }
    }
}
// TODO (malice#1#): Fix segfault. Segfault's because w of texture is set to some huge number, not sure why.
