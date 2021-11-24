#include <iostream>

#include "catch.hpp"
#include "YAGL_Graph.hpp"
#include <vector>
#include <type_traits>

TEST_CASE("graphs can add or remove nodes and duplicate check", "[graph_test]")
{
    // Define the graph types
    using key_type = int; using data_type = double;
    using graph_type = YAGL::Graph<key_type, data_type>;

    graph_type graph;

    //Graph starts out empty
    REQUIRE(graph.numNodes() == 0);
    REQUIRE(graph.numEdges() == 0);
   
    // Define the node type
    using node_type = YAGL::Node<key_type, data_type>;
        
    SECTION("adding nodes increases the number of nodes") {

        //create a node
        using node_type = YAGL::Node<key_type, data_type>;
        
        auto num_nodes = 4;
        auto num_edges = 0;

        node_type node_a(1, 2.6);
        node_type node_b(2, 2.6);
        node_type node_c(4, 2.6);
        node_type node_d(606, 2.6);

        graph.addNode(node_a);
        graph.addNode(node_b);
        graph.addNode(node_c);
        graph.addNode(node_d);
            
        REQUIRE(graph.numNodes() == num_nodes);
        REQUIRE(graph.numEdges() == num_edges); 
    }

    SECTION("adding duplicate nodes does not work") {

        //create a node
        using node_type = YAGL::Node<key_type, data_type>;
        
        auto num_unique_keys = 3;
        auto num_edges = 0;

        node_type node_a(1, 2.6);
        node_type node_b(2, 2.6);
        node_type node_c(3, 2.6);
        node_type node_d(2, 2.6);

        graph.addNode(node_a);
        graph.addNode(node_b);
        graph.addNode(node_c);
        graph.addNode(node_d);
            
        REQUIRE(graph.numNodes() == num_unique_keys);
        REQUIRE(graph.numEdges() == num_edges); 
    }
    
    SECTION("deleting a node decreases the number of nodes") {

        //create a node
        using node_type = YAGL::Node<key_type, data_type>;
        
        auto num_nodes = 2;
        auto num_edges = 0;

        node_type node_a(1, 2.6);
        node_type node_b(2, 2.6);
        node_type node_c(4, 2.6);
        node_type node_d(606, 2.6);

        graph.addNode(node_a);
        graph.addNode(node_b);
        graph.addNode(node_c);
        graph.addNode(node_d);
        
        graph.removeNode(node_b);
        graph.removeNode(node_d);

        REQUIRE(graph.numNodes() == num_nodes);
        REQUIRE(graph.numEdges() == num_edges); 
    }

}

TEST_CASE("graphs can and or remove edges and degree can be checked", "[graph_test]")
{    
    // Define the graph types
    using key_type = int; using data_type = double;
    using graph_type = YAGL::Graph<key_type, data_type>;

    graph_type graph;

    //Graph starts out empty
    REQUIRE(graph.numNodes() == 0);
    REQUIRE(graph.numEdges() == 0);
   
    // Define the node type
    using node_type = YAGL::Node<key_type, data_type>;
        
    SECTION("edges can be added and degrees checked") {

        //create a node
        using node_type = YAGL::Node<key_type, data_type>;
        
        auto num_nodes = 4;
        auto num_edges = 2;

        node_type node_a(1, 2.6);
        node_type node_b(2, 2.6);
        node_type node_c(4, 2.6);
        node_type node_d(606, 2.6);

        graph.addNode(node_a);
        graph.addNode(node_b);
        graph.addNode(node_c);
        graph.addNode(node_d);
            
        REQUIRE(graph.numNodes() == num_nodes);
        REQUIRE(graph.numEdges() == 0);

        graph.addEdge(node_a, node_c);
        REQUIRE( graph.in_degree(node_a) == 1 );
        REQUIRE( graph.out_degree(node_a) == 1 );
        REQUIRE( graph.in_degree(node_c) == 1 );
        REQUIRE( graph.out_degree(node_c) == 1 );
        
        REQUIRE( graph.numEdges() == 1 );

        graph.addEdge(node_a, node_d);
        REQUIRE( graph.in_degree(node_a) == 2 );
        REQUIRE( graph.out_degree(node_a) == 2 );
        REQUIRE( graph.in_degree(node_d) == 1 );
        REQUIRE( graph.out_degree(node_d) == 1 );

        REQUIRE(graph.numEdges() == num_edges);
    }
    
    SECTION("edges can be removed and degrees checked") {

        //create a node
        using node_type = YAGL::Node<key_type, data_type>;
        
        auto num_nodes = 4;
        auto num_edges = 6;

        node_type node_a(366, 2.6);
        node_type node_b(2, 2.6);
        node_type node_c(4, 2.6);
        node_type node_d(606, 2.6);

        graph.addNode(node_a);
        graph.addNode(node_b);
        graph.addNode(node_c);
        graph.addNode(node_d);
            
        REQUIRE(graph.numNodes() == num_nodes);
        REQUIRE(graph.numEdges() == 0);

        graph.addEdge(node_a, node_c);
        REQUIRE( graph.in_degree(node_a) == 1 );
        REQUIRE( graph.out_degree(node_a) == 1 );
        REQUIRE( graph.in_degree(node_c) == 1 );
        REQUIRE( graph.out_degree(node_c) == 1 );
        
        REQUIRE( graph.numEdges() == 1 );

        graph.addEdge(node_a, node_d);
        graph.addEdge(node_a, node_b);
        graph.addEdge(node_b, node_c);
        graph.addEdge(node_b, node_d);
        graph.addEdge(node_c, node_d);

        REQUIRE( graph.in_degree(node_a) == 3 );
        REQUIRE( graph.out_degree(node_a) == 3 );
        REQUIRE( graph.in_degree(node_d) == 3 );
        REQUIRE( graph.out_degree(node_d) == 3 );
        
        std::cout << graph;

        REQUIRE(graph.numEdges() == num_edges);
    
        graph.removeEdge(node_d, node_a);
    
        REQUIRE(graph.numEdges() == num_edges-1);

        graph.removeNode(node_c);

        REQUIRE(graph.numNodes() == 3);
        REQUIRE(graph.numEdges() == 2);
    }
}

TEST_CASE("graphs can be completely cleared", "[graph_test]")
{    
    // Define the graph types
    using key_type = int; using data_type = double;
    using graph_type = YAGL::Graph<key_type, data_type>;

    graph_type graph;

    // Define the node type
    using node_type = YAGL::Node<key_type, data_type>;
        

    auto num_nodes = 4;
    auto num_edges = 6;

    node_type node_a(366, 2.6);
    node_type node_b(2, 2.6);
    node_type node_c(4, 2.6);
    node_type node_d(606, 2.6);

    graph.addNode(node_a);
    graph.addNode(node_b);
    graph.addNode(node_c);
    graph.addNode(node_d);
        
    graph.addEdge(node_a, node_c);
    graph.addEdge(node_a, node_d);
    graph.addEdge(node_a, node_b);
    graph.addEdge(node_b, node_c);
    graph.addEdge(node_b, node_d);
    graph.addEdge(node_c, node_d);

    graph.clear();

    REQUIRE(graph.numNodes() == 0);
    REQUIRE(graph.numEdges() == 0);
    
    std::cout << graph;
}

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
