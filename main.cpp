#include "GameEngine.hpp"

#include <iostream>
#include <vector>
#include <memory>
#include "Graph.hpp"

using namespace Llama;

int main(int argc, char* args[])
{
//    GameEngine DrunkenLlamaProphecy;
//
//    DrunkenLlamaProphecy.Run();

    std::vector<Hex> maciek;
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            maciek.push_back(Hex(i,j,HEX_DIRT));
        }
    }
    Graph testGraph(5,5,std::move(maciek));
    std::unordered_map<int,int> wojtek;
    std::unordered_map<int,int> pszemek;
    testGraph.AStar(testGraph.CoordsToIndex(0,0), testGraph.CoordsToIndex(4,0),wojtek, pszemek);

    for(auto x : wojtek)
    {
        std::cout << x.second << std::endl;
    }
    return 0;
}
