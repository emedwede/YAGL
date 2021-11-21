#include <iostream>

#include "catch.hpp"
#include "YAGL_Node.hpp"

#include <type_traits>

TEST_CASE("Running Node Test", "[node test]")
{    
    using key_type = std::size_t;
    using data_type = double;
    
    using node_type = YAGL::Node<key_type, data_type>;

    key_type key = 101;
    data_type data = 2.6;

    node_type node(key, data);

    //check that our types are correct
    REQUIRE(std::is_same<typename node_type::key_type, key_type>::value == true);
    REQUIRE(std::is_same<typename node_type::data_type, data_type>::value == true);

    REQUIRE(node.getKey() == key);

    REQUIRE(node.getData() == data);
}
