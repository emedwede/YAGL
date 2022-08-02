#include <iostream>

#include "catch.hpp"
#include "YAGL_Graph.hpp"
#include "YAGL_Algorithms.hpp"

#include <vector>
#include <type_traits>

void create_complete_k4_graph(YAGL::Graph<int, double>& graph)
{
    for(auto i = 0; i < 4; i++)
        graph.addNode({i, 0.0});
    
    //creates a path graph and then loops it
    for(auto i = 0; i < 3; i++)
        graph.addEdge(i, i+1);
    graph.addEdge(3, 0);
    
    //add the diagonals to make it a complete graph K4
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
}

TEST_CASE("isomorphism test", "[dfs_test]")
{    
    // Define the graph types
    using key_type = int; using data_type = double;
    using graph_type = YAGL::Graph<key_type, data_type>;

    graph_type g1, g2;
    
    create_complete_k4_graph(g1);
    create_complete_k4_graph(g2); 
    
    std::cout << g1 << g2;

    auto results = graph_isomorphism(g1, g2);
    
    // The complete graph K4 has has 8 automorphisms to itself
    REQUIRE(results.size() == 8);

    auto print_key_value = [](const auto& key, const auto& value) {
        std::cout << "[ "<< key << " -> " << value << " ]";
    };                                                                                                   
    for(const auto& isomorphism : results)
    {
        std::cout << "Isomorphism: { ";
        for( const auto& [key, value] : isomorphism ) { 
            print_key_value(key, value); 
        } std::cout << " }\n"; 
    }
}
