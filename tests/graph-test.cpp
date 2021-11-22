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
}
