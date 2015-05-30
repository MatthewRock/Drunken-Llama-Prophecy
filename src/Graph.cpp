#include "Graph.hpp"
#include <iostream>
#include <assert.h>

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
    std::stack<Graph::Index> Graph::AStar(int startIndex, int goalIndex)
    {
        PriorityQueue<Index> frontier;//queue of indexes
        std::unordered_map<Index, Index> came_from; // map of where you came from(calling came_from[vertice] gives you previousely attended vertice
        std::unordered_map<Index, int> cost_so_far; // Map of total cost of path, needed for algorithm.
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
        //Perform "stack undwinding" to record path to target.
        std::stack<Index> path;
        Index previousOne = came_from[goalIndex];
        //If path was found
        if(previousOne != startIndex)
        {
            path.push(goalIndex); // Add destination to the end. It's last tile we reach.
        }
        //Reconstruct path, as a stack. Top is first tile to go to.
        while(previousOne != startIndex)
        {
            path.push(previousOne);
            previousOne = came_from[previousOne];
        }
        return path;
    }
    void Graph::InsertHex(int x, int y, HexType type)
    {
        //It has to be within bounds
        assert(x < m_Width);
        assert(y < m_Height);

        m_Hexes[CoordsToIndex(x,y)] = Hex(type);
    }
}
