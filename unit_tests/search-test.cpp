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

//TODO: move to a separate test 
TEST_CASE("induced_subgraph", "[induced_subgraph test]")
{
    using key_type = int; using data_type = double;
    using graph_type = YAGL::Graph<key_type, data_type>;
    
    graph_type graph;
    create_complete_k4_graph(graph);

    std::vector<key_type> inducing_set{0, 1, 3};
    auto subgraph = YAGL::induced_subgraph(graph, inducing_set);
    
    //any 3 noded induced subgraph of K4 is a K3 graph 
    REQUIRE(subgraph.numNodes() == 3);
    REQUIRE(subgraph.numEdges() == 3);
    REQUIRE(subgraph.min_degree() == 2);
    REQUIRE(subgraph.max_degree() == 2);

}
TEST_CASE("recursive depth first search", "[dfs_test]")
{    
    // Define the graph types
    using key_type = int; using data_type = double;
    using graph_type = YAGL::Graph<key_type, data_type>;

    graph_type graph;
    
    create_complete_k4_graph(graph);
    
    std::cout << graph;
    
    //run a dfs for all keys an assert that all nodes are found in this connected graph
    for(auto i = 0; i < 4; i++)
    {
        auto visited = YAGL::recursive_dfs(graph, i);
        REQUIRE(visited.size() == graph.numNodes());
    }
    
    //run dfs with a modifed depth level 
    {
        auto visited = YAGL::recursive_dfs(graph, 0, 0);
        REQUIRE(visited.size() == graph.numNodes());
    }
    {
        auto visited = YAGL::recursive_dfs(graph, 0, 1);
        REQUIRE(visited.size() == 1);
    }
    {
        auto visited = YAGL::recursive_dfs(graph, 0, 2);
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

TEST_CASE("iterative depth first search", "[dfs_test]")
{    
    // Define the graph types
    using key_type = int; using data_type = double;
    using graph_type = YAGL::Graph<key_type, data_type>;

    graph_type graph;
    
    create_complete_k4_graph(graph);
    
    std::cout << graph;
    
    //run a dfs for all keys an assert that all nodes are found in this connected graph
    for(auto i = 0; i < 4; i++)
    {
        auto visited = YAGL::iterative_dfs(graph, i);
        REQUIRE(visited.size() == graph.numNodes());
    }

    //add a disconnected component
    graph.addNode({4, 0.0}); graph.addNode({5, 0.0});
    graph.addEdge(4, 5);
    
    { //Test to see that the disconnected component is not found
        auto visited = YAGL::iterative_dfs(graph, 0);
        REQUIRE(visited.size() == graph.numNodes() - 2);
    }

    { //Test to see that only the disconnected component is found
        auto visited = YAGL::iterative_dfs(graph, 4);
        REQUIRE(visited.size() == 2);
    }

    //Connect the disconnected component and check that the whole 
    //graph is now reachable from every node
    graph.addEdge(3, 4);
   
    for(auto i = 0; i < 6; i++)
    {
        auto visited = YAGL::iterative_dfs(graph, i);
        REQUIRE(visited.size() == graph.numNodes());
    } 
}

TEST_CASE("iterative breadth first search", "[bfs_test]")
{    
    // Define the graph types
    using key_type = int; using data_type = double;
    using graph_type = YAGL::Graph<key_type, data_type>;

    graph_type graph;
    
    create_complete_k4_graph(graph);
    
    std::cout << graph;
    
    //run a bfs for all keys an assert that all nodes are found in this connected graph
    for(auto i = 0; i < 4; i++)
    {
        auto visited = YAGL::iterative_bfs(graph, i);
        REQUIRE(visited.size() == graph.numNodes());
    }

    //add a disconnected component
    graph.addNode({4, 0.0}); graph.addNode({5, 0.0});
    graph.addEdge(4, 5);
    
    { //Test to see that the disconnected component is not found
        auto visited = YAGL::iterative_bfs(graph, 0);
        REQUIRE(visited.size() == graph.numNodes() - 2);
    }

    { //Test to see that only the disconnected component is found
        auto visited = YAGL::iterative_bfs(graph, 4);
        REQUIRE(visited.size() == 2);
    }

    //Connect the disconnected component and check that the whole 
    //graph is now reachable from every node
    graph.addEdge(3, 4);
   
    for(auto i = 0; i < 6; i++)
    {
        auto visited = YAGL::iterative_bfs(graph, i);
        REQUIRE(visited.size() == graph.numNodes());
    }
}

TEST_CASE("connected component search test", "[connected_component_test]")
{    
    // Define the graph types
    using key_type = int; using data_type = double;
    using graph_type = YAGL::Graph<key_type, data_type>;

    graph_type graph;
    
    create_complete_k4_graph(graph);
    
    std::cout << graph;
    
    //search for connected components 
    {
        auto component_count = YAGL::connected_components(graph);
        REQUIRE(component_count == 1);
    }
    //add a disconnected component
    graph.addNode({4, 0.0}); graph.addNode({5, 0.0});
    graph.addEdge(4, 5);
    
    std::cout << graph;
    
    //search for connected components 
    {
        auto component_count = YAGL::connected_components(graph);
        REQUIRE(component_count == 2);
    }
    
    //remove some edges to disconnect it 
    graph.removeEdge(0, 3);
    graph.removeEdge(0, 2);
    graph.removeEdge(1, 3);
    graph.removeEdge(1, 2);
    
    std::cout << graph;
    
    //search for connected components 
    {
        auto component_count = YAGL::connected_components(graph);
        REQUIRE(component_count == 3);
    }
}


