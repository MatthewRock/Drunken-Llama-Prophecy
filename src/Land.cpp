#include "Land.hpp"
#include <iostream>
#include "Collision.hpp"

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
    void Land::DrawInProximity(int x, int y, int offsetx = 0, int offsety = 0)
    {
        //Character will be the center of action.
        int newx = x - 11;
        int newy = y - 11;
        //If we got out of map, correct it.
        //TODO: Correct for going out of max bounds too
        if(newx < 0) newx = 0;
        if(newy < 0) newy = 0;
        // Know when to stop looping
        int finishx = newx + 22;
        int finishy = newy + 22;
        bool flag = (y % 2 == 1 ? true : false);
        int i = 0, j = 0;
        //Print tiles
        for(; newx < finishx; ++newx)
        {
            for(int yy = newy; yy < finishy; ++yy)
            {
                HexType type;
                //Get type and coords
                if(yy%2==1 && flag)
                    type = m_Graph.GetHexType(newx, yy);
                else
                    type = m_Graph.GetHexType(newx-1, yy);
                auto cords = coords[i][j];
                //Finally print
                m_HexTextureManager.GetElement(type)->Draw(cords.first + offsetx, cords.second + offsety);
                j = (j + 1) % 22;
            }
            ++i;
        }
    }
    std::pair<int,int> Land::CheckCollision(SDL_Event& event)
    {
        int distances[20][20];
        for(int i = 0; i < 20; ++i)
        {
            for(int j = 0; j < 20; ++j)
            {
                distances[i][j] = Collision::MouseHexCollision(event, coords[i][j]);
            }
        }
        int min, x = 0, y = 0;
        min = distances[0][0];
        for(int i = 0; i < 20; ++i)
        {
            for(int j = 0; j < 20; ++j)
            {
                if(min > distances[i][j])
                {
                    min = distances[i][j];
                    x = i;
                    y = j;
                }
            }
        }
        //TODO: Make it according to camera!!
        m_Graph.InsertHex(x,y,HEX_MAGIC);
        //TODO: When character class is ready, make him move.
        //return std::make_pair(x,y);

    }
    void Land::MoveCharacterAccordingly(SDL_Event& event, PlayableCharacter& character)
    {
        //Get distance to every hex's middle
        int distances[20][20];
        for(int i = 0; i < 20; ++i)
        {
            for(int j = 0; j < 20; ++j)
            {
                distances[i][j] = Collision::MouseHexCollision(event, coords[i][j]);
            }
        }
        //Find the hex with closest middle point; we clicked on this hex
        int min, x = 0, y = 0;
        min = distances[0][0];
        for(int i = 0; i < 20; ++i)
        {
            for(int j = 0; j < 20; ++j)
            {
                if(min > distances[i][j])
                {
                    min = distances[i][j];
                    x = i;
                    y = j;
                }
            }
        }
        x += character.GetPosition().first - 9;
        y += character.GetPosition().second - 9;

        if(y%2==0 && character.GetPosition().second%2==1)
            ++x;
        //Now move character to that tile.
        character.Teleport(x,y);
// TODO (malice#1#): Make it simpler.
    }
}
