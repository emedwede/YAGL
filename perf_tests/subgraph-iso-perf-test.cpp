#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip> 
#include <fstream> 

#include "catch.hpp"
#include "YAGL_Graph.hpp"
#include "YAGL_Algorithms.hpp"

using data_type = struct DataType {std::size_t type;};
using key_type = std::size_t;

using graph_type = YAGL::Graph<key_type, data_type>;

void scatter_3_segments(graph_type& graph, std::size_t n)
{
    for(std::size_t i = 0; i < n*3; i += 3)
    {
        graph.addNode({i, {0}});
        graph.addNode({i+1, {1}});
        graph.addNode({i+2, {2}});
        graph.addEdge(i, i+1);
        graph.addEdge(i+1, i+2);
    }
}

//simple template for writing a python file
void write_results_matplotlib(std::vector<double>& runtimes, std::vector<std::size_t>& match_counts)
{
    std::fstream myfile;
    myfile.open("sub_iso_res.py", std::ios::out);
    if(!myfile)
        std::cout << "Error file not created\n";
    else
    {
        myfile << "#!/bin/python\n" 
            << "import numpy as np\n"
            << "import matplotlib.pyplot as plt"
            << "\n";
        
        myfile << "runtimes = np.asarray([";
        for(int i = 0; i < runtimes.size(); i++)
        {
            if(i != runtimes.size() - 1)
                myfile << runtimes[i] << ", ";
            else 
                myfile << runtimes[i];
        }
        myfile << "]);\n";
        
        myfile << "counts = np.asarray([";
        for(int i = 0; i < match_counts.size(); i++)
        {
            if(i != match_counts.size() - 1)
                myfile << match_counts[i] << ", ";
            else 
                myfile << match_counts[i];
        }
        myfile << "]);\n";
        myfile << "plt.xlabel(\'Matches Found\')\n";
        myfile << "plt.ylabel(\'Runtime in ms\')\n";
        myfile << "plt.title(\'Performance Analysis for MT-Like Graph\')\n";
        myfile << "plt.plot(counts, runtimes, \'--o\')\n";

        myfile << "plt.show()\n";
        myfile.close();
    }
}

TEST_CASE("subgraph iso performance test", "[subgraph_iso_performance_test]")
{
    
    std::size_t m = 8;
    std::vector<double> runtimes;
    std::vector<std::size_t> match_counts;
    std::size_t n = 1;
    for(auto i = 0; i < m; i++)
    {
    graph_type g1, g2;
    
    //g1 is a single pattern 
    scatter_3_segments(g1, 1);

    n *= 2;
    //g2 is the large graph with n compentents to match 
    scatter_3_segments(g2, n);
    
    //std::cout << g1 << g2; 
    std::cout << "Running test for n == " << n << "\n";
    const auto start = std::chrono::high_resolution_clock::now();
    auto results = YAGL::subgraph_isomorphism(g1, g2);
    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> ms = end - start;
    std::cout << "SubGraphIso: " << std::fixed << std::setprecision(1)
        << results.size() << " matches in " << ms.count() << "ms\n"; 
    REQUIRE(results.size() == n);
    runtimes.push_back(ms.count());
    match_counts.push_back(results.size());
    }
    write_results_matplotlib(runtimes, match_counts); 
}

