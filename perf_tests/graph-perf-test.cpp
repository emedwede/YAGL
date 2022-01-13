#include <iostream>

#include "catch.hpp"
#include "YAGL_Graph.hpp"
#include <vector>
#include <type_traits>

TEST_CASE("graph insertion performance test", "[graph_performance_test]")
{
    // Define the graph types
    using key_type = int; using data_type = double;
    using node_type = YAGL::Node<key_type, data_type>;

    using graph_type = YAGL::Graph<key_type, data_type>;

    graph_type graph_perf;

    //TODO: add this to a performance test
    std::size_t num_adds = 10'000;
    for(auto i = 0; i < num_adds; i++) {
        node_type n(i, i*1.1);
        graph_perf.addNode(n);
    }
    
    for(auto i = 0; i < num_adds/2; i++) {
        auto node_a = graph_perf.findNode(i)->second;
        auto node_b = graph_perf.findNode(i+1)->second;
        graph_perf.addEdge(node_a, node_b);
    }
    REQUIRE(graph_perf.numNodes() == num_adds);
    REQUIRE(graph_perf.numEdges() == num_adds/2);

    REQUIRE( graph_perf.findNode(100'000) == graph_perf.node_list_end() );
    
    auto search = graph_perf.findNode(101);
    auto node_d = search->second;
    
    REQUIRE(search != graph_perf.node_list_end());
    REQUIRE( node_d.getData() == node_d.getKey()*1.1 );
    
    auto nbr_list = graph_perf.out_neighbors(node_d);
    REQUIRE(nbr_list.size() == 2);

    std::cout << graph_perf;
}
