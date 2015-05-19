#ifndef LAND_H
#define LAND_H

#include "Texture.hpp"
#include "Manager.hpp"
#include <vector>
#include <array>
#include <cstdlib> //abs
#include <PriorityQueue.hpp>
#include <map>

namespace Llama
{
    class Land
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
            unsigned x,y;
            HexType type;
            bool Passable()
            {
                return (type != HEX_LAVA) && (type != HEX_WATER);
            }
            inline unsigned int cost()
            {
                return 1;
            }
        };
        public:
            Land();
        protected:
            std::pair<int, int> CalculateXY(int, int);
            int m_Width, m_Height;
        private:
            Manager<HexType, Texture> m_HexTextureManager;
            std::vector<Hex> m_Hexes;
            int CoordsToIndex(int x, int y)
            {
                if(x < 0 || y < 0)
                    return -1;
                else
                {
                    int index = x + m_Width * y;
                    if(index >= m_Hexes.size())
                        return -1;
                    else
                        return index;
                }
            }

        /// \brief returns array of 6 IDs of index's neighbours. -1 indicates no neighbour on this position.
        std::array<int, 6> graphNeigbours(int index)
        {
            int y = index / m_Width;
            int x = index % m_Width;
            if(y % 2 == 0)
            {
                return {CoordsToIndex(x-1, y-1),
                        CoordsToIndex(x,   y-1),
                        CoordsToIndex(x-1, y),
                        CoordsToIndex(x+1, y),
                        CoordsToIndex(x-1, y+1),
                        CoordsToIndex(x,   y+1)};
            }
            else
            {
                return {CoordsToIndex(x,   y-1),
                        CoordsToIndex(x+1, y-1),
                        CoordsToIndex(x-1, y),
                        CoordsToIndex(x+1, y),
                        CoordsToIndex(x,   y+1),
                        CoordsToIndex(x+1, y+1)};
            }
        }
        inline unsigned int Heuristic(int startIndex, int endIndex)
        {
            int x1,y1,x2,y2;
            x1 = startIndex % m_Width;
            y1 = startIndex / m_Width;
            x2 = startIndex % m_Width;
            y2 = startIndex / m_Width;
            return abs(x1 - x2) + abs(y1 - y2);
        }

        void AStar(int startIndex, int goalIndex, std::unordered_map<int, int>& came_from, std::unordered_map<int, int> cost_so_far)
        {
            PriorityQueue<int> frontier;//queue of indexes
            frontier.put(startIndex, 0);

            came_from[startIndex] = startIndex;
            cost_so_far[startIndex] = 0;
            while(!frontier.empty())
            {
                auto current = frontier.get();
                if(current == goalIndex)
                    break;

                for(auto next : graphNeigbours(current))
                {
                    int new_cost = cost_so_far[current] + 1;//TODO: CHange this to written function next(curr. in Hex)

                    if(!cost_so_far.count(next) || new_cost < cost_so_far[next])
                    {
                        cost_so_far[next] = new_cost;
                        int priority = new_cost + Heuristic(next, goalIndex);
                        frontier.put(next, priority);
                        came_from[next] = current;
                    }
                }
            }
        }
        //TODO: Move this to separate class.
    };
}

#endif // LAND_H
