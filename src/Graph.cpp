#include "Graph.hpp"

namespace Llama
{
    int Graph::CoordsToIndex(int x, int y)
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
    void Graph::AStar(int startIndex, int goalIndex, std::unordered_map<int, int>& came_from, std::unordered_map<int, int> cost_so_far)
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
                if(next < 0 || !m_Hexes[next].Passable()) // If neighbour doesn't exist or is inpassable
                {}//do nothing
                else
                {
                    int new_cost = cost_so_far[current] + m_Hexes[next].Cost();

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
    }
}
