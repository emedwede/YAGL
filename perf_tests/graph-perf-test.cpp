#include <iostream>

#include "catch.hpp"
#include "YAGL_Graph.hpp"
#include <vector>
#include <type_traits>
#include <chrono>
#include <iostream>

#include <unordered_map>

using namespace std::chrono;

TEST_CASE("graph insertion and copy performance test", "[graph_performance_test]")
{
    // Define the graph types
    using key_type = int; using data_type = double;
    using node_type = YAGL::Node<key_type, data_type>;

    using graph_type = YAGL::Graph<key_type, data_type>;

    graph_type graph_perf;
    
    std::size_t num_adds = 5'000;
    std::cout << "\n--------------------------------------------------\n";
    std::cout << "Inserting " << num_adds << " nodes and " << num_adds/2 << " edges...\n";
    auto start = high_resolution_clock::now();
    for(auto i = 0; i < num_adds; i++) {
        node_type n(i, i*1.1);
        graph_perf.addNode(n);
    }
    
    for(auto i = 0; i < num_adds - 1; i++) {
        auto node_a = graph_perf.findNode(i)->second;
        auto node_b = graph_perf.findNode(i+1)->second;
        graph_perf.addEdge(node_a, node_b);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop-start);
    std::cout << "Time taken: " << duration.count() << " milliseconds\n";
    std::cout << "--------------------------------------------------\n";

    REQUIRE(graph_perf.numNodes() == num_adds);
    REQUIRE(graph_perf.numEdges() == num_adds - 1);

    REQUIRE( graph_perf.findNode(1'000'000) == graph_perf.node_list_end() );
    
    auto search = graph_perf.findNode(101);
    auto node_d = search->second;
    
    REQUIRE(search != graph_perf.node_list_end());
    REQUIRE( node_d.getData() == node_d.getKey()*1.1 );
    
    auto nbr_list = graph_perf.out_neighbors(node_d);
    REQUIRE(nbr_list.size() == 2);
    
    std::cout << "\n" << graph_perf;

    std::cout << "\n--------------------------------------------------\n";
    std::cout << "Copying " << num_adds << " nodes and " << num_adds/2 << " edges...\n";
    start = high_resolution_clock::now();
    graph_type graph_perf_copy = graph_perf; 
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop-start);
    std::cout << "Time taken: " << duration.count() << " milliseconds\n";
    std::cout << "--------------------------------------------------\n";
    
    num_adds = 500'000;
    std::unordered_map<std::size_t, double> map_arr;
    std::cout << "Map size: " << map_arr.size() << "\n";
    for(auto i = 0; i < num_adds; i++) map_arr.insert({i, i*1.1});
    std::cout << "Map size: " << map_arr.size() << "\n";
    std::cout << "\n--------------------------------------------------\n";
    std::cout << "Copying " << num_adds << " nodes\n";
    start = high_resolution_clock::now();
    auto map_arr_copy = map_arr;
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop-start);
    std::cout << "Time taken: " << duration.count() << " milliseconds\n";
    std::cout << "--------------------------------------------------\n";


}
