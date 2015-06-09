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
        int newx = x - 10;
        int newy = y - 10;
        //If we got out of map, correct it.
        //TODO: Correct for going out of max bounds too
        if(newx < 0) newx = 0;
        if(newy < 0) newy = 0;
        // Know when to stop looping
        int finishx = newx + 22;
        int finishy = newy + 22;
        bool flag = (y % 2 == 0 ? true : false);
        int i = 0, j = 0;
        //Print tiles
        for(; newx < finishx; ++newx)
        {
            for(int yy = newy; yy < finishy; ++yy)
            {
                HexType type;
                if(newx * yy > m_Graph.Size())
                    return;
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
        for (auto &it : m_Monsters)
        {
            if((it->GetPosition().first - x < 11) && (it->GetPosition().first - x > -11) && (it->GetPosition().second - y < 11) && (it->GetPosition().second - y > -11) )
                it->Draw(x, y, offsetx, offsety);
        }
    }
    std::pair<int,int> Land::CheckCollision(SDL_Event& event, int offsetx, int offsety)
    {
        int distances[20][20];
        for(int i = 0; i < 20; ++i)
        {
            for(int j = 0; j < 20; ++j)
            {
                distances[i][j] = Collision::MouseHexCollision(event, coords[i+2][j+1]);
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
        x += offsetx - 9;
        y += offsety - 9;

        if(y%2==1 && offsety %2==0)
            ++x;

        return std::make_pair(x,y);
    }
    void Land::MoveCharacterAccordingly(SDL_Event& event, PlayableCharacter& character)
    {
        //Get distance to every hex's middle
        int distances[20][20];
        for(int i = 0; i < 20; ++i)
        {
            for(int j = 0; j < 20; ++j)
            {
                distances[i][j] = Collision::MouseHexCollision(event, coords[i+2][j+1]);
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

        if(y%2==1 && character.GetPosition().second%2==0)
            ++x;
        //Now move character to that tile.
        auto path = m_Graph.AStarPrim(m_Graph.CoordsToIndex(character.GetPosition().first, character.GetPosition().second), m_Graph.CoordsToIndex(x,y));
        while(!path.empty())
        {
            auto coords = path.front();
            path.pop();
            character.Order(Character::MOVE, coords.first, coords.second);
        }
    }
    void Land::PrintMap(std::ostream& stream)
    {
        m_Graph.PrintGraph(stream);
    }
    void Land::InsertMonster(MonsterType mtype, int x, int y, Window& win)
    {

        switch(mtype)
        {
            case MON_BLACK:
                m_Monsters.push_back(std::unique_ptr<Monster>(new Monster("media/CharSprites/MonsterBL.png", win, x, y, 5, 1, 1, 4)));
            break;
            case MON_ORANGE:
                m_Monsters.push_back(std::unique_ptr<Monster>(new Monster("media/CharSprites/MonsterO.png", win, x, y, 2, 1, 1, 1)));
            break;
        }
    }
    void Land::FishAI(int x, int y)
    {
        for(auto & it : m_Monsters)
        {
            if((it->GetPosition().first - x < 11) && (it->GetPosition().first - x > -11) && (it->GetPosition().second - y < 11) && (it->GetPosition().second - y > -11) )
                if((it->GetPosition().first - x <= 1) && (it->GetPosition().first - x >= -1) && (it->GetPosition().second - y <= 1) && (it->GetPosition().second - y >= -1) )
                {
                    it->Order(Character::ATTACK, it->GetPosition().first-x, it->GetPosition().second-y);
                }
                else
                {
                    auto coords = m_Graph.AStarPrim(m_Graph.CoordsToIndex(it->GetPosition().first, it->GetPosition().second), m_Graph.CoordsToIndex(x,y)).front();
                    it->Order(Character::MOVE, coords.first, coords.second);
                }
        }
    }
}
