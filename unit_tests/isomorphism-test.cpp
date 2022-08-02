#include <iostream>

#include "catch.hpp"
#include "YAGL_Graph.hpp"
#include "YAGL_Algorithms.hpp"

#include <vector>
#include <type_traits>
#include <string> 
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

void create_generic_graph1(YAGL::Graph<std::string, double>& graph)
{
    std::string tag = "v";
    for(auto i = 1; i <= 5; i++)
        graph.addNode({tag+std::to_string(i), 0.0});
    
    auto t1 = tag+"1";
    auto t2 = tag+"2";
    auto t3 = tag+"3";
    auto t4 = tag+"4";
    auto t5 = tag+"5";

    graph.addEdge(t1, t2);
    graph.addEdge(t1, t3);
    graph.addEdge(t1, t4);
    
    graph.addEdge(t2, t1);
    graph.addEdge(t2, t5);
    graph.addEdge(t2, t3);
    
    graph.addEdge(t4, t5);
    graph.addEdge(t4, t1);
    graph.addEdge(t4, t3);
    
    graph.addEdge(t5, t4);
    graph.addEdge(t5, t3);
    graph.addEdge(t5, t2);
    
    graph.addEdge(t3, t1);
    graph.addEdge(t3, t2);
    graph.addEdge(t3, t4);
    graph.addEdge(t3, t5);
}

void create_generic_graph2(YAGL::Graph<std::string, double>& graph)
{
    std::string tag = "w";
    for(auto i = 1; i <= 5; i++)
        graph.addNode({tag+std::to_string(i), 0.0});
    
    auto t1 = tag+"1";
    auto t2 = tag+"2";
    auto t3 = tag+"3";
    auto t4 = tag+"4";
    auto t5 = tag+"5";

    graph.addEdge(t3, t2);
    graph.addEdge(t3, t1);
    graph.addEdge(t3, t4);
    
    graph.addEdge(t2, t1);
    graph.addEdge(t2, t5);
    graph.addEdge(t2, t3);
    
    graph.addEdge(t4, t5);
    graph.addEdge(t4, t1);
    graph.addEdge(t4, t3);
    
    graph.addEdge(t5, t4);
    graph.addEdge(t5, t1);
    graph.addEdge(t5, t2);
    
    graph.addEdge(t1, t3);
    graph.addEdge(t1, t2);
    graph.addEdge(t1, t4);
    graph.addEdge(t1, t5);
}


TEST_CASE("isomorphism test k4", "[dfs_test]")
{    
    // Define the graph types
    using key_type = int; using data_type = double;
    using graph_type = YAGL::Graph<key_type, data_type>;

    graph_type g1, g2;
    
    create_complete_k4_graph(g1);
    create_complete_k4_graph(g2); 
    
    std::cout << g1 << g2;

    auto results = graph_isomorphism(g1, g2);
    
    // The complete graph K4 has has 24 automorphisms to itself
    REQUIRE(results.size() == 24);

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

TEST_CASE("isomorphism test generic", "[dfs_test]")
{    
    // Define the graph types
    using key_type = std::string; using data_type = double;
    using graph_type = YAGL::Graph<key_type, data_type>;

    graph_type g1, g2;
    
    create_generic_graph1(g1);
    create_generic_graph2(g2);

    std::cout << g1 << g2;

    auto results = graph_isomorphism(g1, g2);
    
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

