#include "GameEngine.hpp"

#include <iostream>
#include <vector>
#include <memory>
#include "Graph.hpp"

using namespace Llama;

int main(int argc, char* args[])
{
    GameEngine DrunkenLlamaProphecy;

    DrunkenLlamaProphecy.Run();

    std::vector<Hex> maciek;
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            maciek.push_back(Hex(i,j,HEX_DIRT));
        }
    }
    maciek[11] = Hex(1, 2, HEX_LAVA);
    maciek[12] = Hex(2, 2, HEX_LAVA);
    maciek[13] = Hex(3, 2, HEX_LAVA);
    Graph testGraph(5,5,std::move(maciek));

    std::stack<int> pszemek = testGraph.AStar(testGraph.CoordsToIndex(0,0), testGraph.CoordsToIndex(0,3));
    while(!pszemek.empty())
    {
        auto x = pszemek.top();
        std::cout << x << std::endl;
        pszemek.pop();
    }
    return 0;
}
