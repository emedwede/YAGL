#include <iostream>

#include "catch.hpp"
#include "YAGL_Graph.hpp"

#include <type_traits>

TEST_CASE("Running Graph Test", "[graph test]")
{    
    using key_type = int;
    using data_type = double;

    using graph_type = YAGL::Graph<key_type, data_type>;

    graph_type graph;

    std::cout << graph;

    REQUIRE(graph.numNodes() == 0);
    
    //create a node
    using node_type = YAGL::Node<key_type, data_type>;
    
    key_type key_a = 101;
    data_type data_a = 2.6;
    node_type node_a(key_a, data_a);

    key_type key_b = 101;
    data_type data_b = 3.6;
    node_type node_b(key_b, data_b);

    key_type key_c = 2;
    data_type data_c = 2.6;
    node_type node_c(key_c, data_c);

    graph.addNode(node_a);
    graph.addNode(node_b);
    graph.addNode(node_c);

    REQUIRE(graph.numNodes() == 2);

    graph.removeNode(node_c);

    REQUIRE(graph.numNodes() == 1);
   
    //TODO: add graph.clear()
    
    graph_type graph_perf;

    //TODO: add this to a performance test
    std::size_t num_adds = 10'000;
    for(auto i = 0; i < num_adds; i++) {
        node_type n(i, i*1.1);
        graph_perf.addNode(n);
    }
    
    REQUIRE(graph_perf.numNodes() == num_adds);
    
    REQUIRE( graph_perf.findNode(100'000) == graph_perf.node_list_end() );
    
    auto search = graph_perf.findNode(101);
    auto node_d = search->second;
    
    REQUIRE(search != graph_perf.node_list_end());
    REQUIRE( node_d.getData() == node_d.getKey()*1.1 );
    
    auto nbr_list = graph_perf.out_neighbors(node_d);
    REQUIRE(nbr_list.size() == 0);
}
