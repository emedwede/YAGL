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

    SECTION("alternative interface to add and remove edges") {
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

        graph.addEdge(366, 4);
        REQUIRE( graph.in_degree(node_a) == 1 );
        REQUIRE( graph.out_degree(node_a) == 1 );
        REQUIRE( graph.in_degree(node_c) == 1 );
        REQUIRE( graph.out_degree(node_c) == 1 );
        
        REQUIRE( graph.numEdges() == 1 );

        graph.addEdge(366, 606);
        graph.addEdge(366, 2);
        graph.addEdge(2, 4);
        graph.addEdge(2, 606);
        graph.addEdge(4, 606);

        REQUIRE( graph.in_degree(node_a) == 3 );
        REQUIRE( graph.out_degree(node_a) == 3 );
        REQUIRE( graph.in_degree(node_d) == 3 );
        REQUIRE( graph.out_degree(node_d) == 3 );
        
        std::cout << graph;

        REQUIRE(graph.numEdges() == num_edges);
    
        graph.removeEdge(606, 366);
    
        REQUIRE(graph.numEdges() == num_edges-1);

        graph.removeNode(node_c);

        REQUIRE(graph.numNodes() == 3);
        REQUIRE(graph.numEdges() == 2);

    }
}

TEST_CASE("graphs can be completely cleared and copied", "[graph_test]")
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

    graph_type copy_graph;
    copy_graph = graph;

    graph.clear();

    REQUIRE(graph.numNodes() == 0);
    REQUIRE(graph.numEdges() == 0);
    REQUIRE(copy_graph.numNodes() == 4);
    REQUIRE(copy_graph.numEdges() == 6);
    
    auto& node_data = copy_graph.findNode(4)->second.getData();
    REQUIRE(node_data == 2.6);

    std::cout << graph;
}
