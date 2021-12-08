#include <iostream>

#include "catch.hpp"
#include "YAGL_Graph.hpp"
#include "YAGL_Algorithms.hpp"

#include <vector>
#include <type_traits>

TEST_CASE("recursive depth first search", "[dfs_test]")
{    
    // Define the graph types
    using key_type = int; using data_type = double;
    using graph_type = YAGL::Graph<key_type, data_type>;

    graph_type graph;

    //create a node
    using node_type = YAGL::Node<key_type, data_type>;
    
    for(auto i = 0; i < 4; i++)
        graph.addNode({i, 0.0});
    
    //creates a path graph and then loops it
    for(auto i = 0; i < 3; i++)
        graph.addEdge(i, i+1);
    graph.addEdge(3, 0);
    
    //add the diagonals to make it a complete graph K4
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    
    std::cout << graph;
    
    //run a dfs for all keys an assert that all nodes are found in this connected graph
    for(auto i = 0; i < 4; i++)
    {
        auto visited = YAGL::recursive_dfs(graph, i);
        REQUIRE(visited.size() == graph.numNodes());
    }

    //add a disconnected component
    graph.addNode({4, 0.0}); graph.addNode({5, 0.0});
    graph.addEdge(4, 5);
    
    { //Test to see that the disconnected component is not found
        auto visited = YAGL::recursive_dfs(graph, 0);
        REQUIRE(visited.size() == graph.numNodes() - 2);
    }

    { //Test to see that only the disconnected component is found
        auto visited = YAGL::recursive_dfs(graph, 4);
        REQUIRE(visited.size() == 2);
    }

    //Connect the disconnected component and check that the whole 
    //graph is now reachable from every node
    graph.addEdge(3, 4);
   
    for(auto i = 0; i < 6; i++)
    {
        auto visited = YAGL::recursive_dfs(graph, i);
        REQUIRE(visited.size() == graph.numNodes());
    }
}

