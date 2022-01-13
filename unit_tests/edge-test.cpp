#include <iostream>

#include "catch.hpp"
#include "YAGL_Node.hpp"
#include "YAGL_Edge.hpp"

TEST_CASE("Running Edge Test", "[edge test]")
{    
    using key_type = std::size_t;
    using data_type = double;
    
    using node_type = YAGL::Node<key_type, data_type>;
    using edge_type = YAGL::Edge<key_type, data_type>;

    node_type node_a(11, 2.6);
    node_type node_b(13, 3.1);

    edge_type edge_ab(node_a.getKey(), node_a, node_b);
    
    REQUIRE(edge_ab.getKey() == node_a.getKey());

    std::cout << node_a << node_b << edge_ab;
}
