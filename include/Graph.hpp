#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Hex.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <array>
#include <unordered_map>
#include <stack>

namespace Llama
{
    class Graph
    {
        typedef int Index;
        public:
            Graph(int w, int h, std::vector<Hex>&& hexes = {}) : m_Width(w), m_Height(h), m_Hexes(hexes)
            {
                m_Hexes.resize(m_Width * m_Height);
            }
            ~Graph() = default;

            Index CoordsToIndex(int x, int y);
            void InsertHex(int x, int y, HexType type);
            /// \return Type of hex at x,y.
            HexType GetHexType(int x, int y) { return m_Hexes[CoordsToIndex(x,y)].type; };

            /// \return Stack with path(bottom tile is goal, top first one to go). Stack is empty when no path can be found.
            std::stack<Index> AStar(Index startIndex, Index goalIndex);

            /// \brief Changes x and y in our coordinate system to x and y that it should have on screen to print.
            /// \return Pair(x,y) of coordinates for SDL to print.
            std::pair<int, int> CalculateXY(int x, int y)
            {
                std::pair<int, int> result;
                result.first = (y % 2 == 0) ? x * Hex::WIDTH : x * Hex::WIDTH - (.5 * Hex::WIDTH);
                //Correcting offset
                result.first -= 4;

                result.second = (y - 1) * .5 * Hex::HEIGHT;
                return result;
            }
        protected:
        private:
            int m_Width, m_Height;
            std::vector<Hex> m_Hexes;

            /// \return Array of 6 IDs of index's neighbours. -1 indicates no neighbour on this position.
            std::array<int, 6> graphNeigbours(Index index)
            {
                int y = index / m_Width;
                int x = index % m_Width;
                if(y % 2 == 1)
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
            inline unsigned int Heuristic(Index startIndex, Index endIndex)
            {
                int x1,y1,x2,y2;
                x1 = startIndex % m_Width;
                y1 = startIndex / m_Width;
                x2 = startIndex % m_Width;
                y2 = startIndex / m_Width;
                return abs(x1 - x2) + abs(y1 - y2);
            }
    };
}
#endif // GRAPH_HPP
