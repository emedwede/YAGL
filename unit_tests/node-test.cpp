#include <iostream>

#include "catch.hpp"
#include "YAGL_Node.hpp"

#include <type_traits>

TEST_CASE("Type Node Test", "[node test]")
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

    std::cout << node;
}

struct PhysicsData
{
    double position[3];
    double energy;
};

//node data needs it's own print function
std::ostream &operator<<(std::ostream& os, const PhysicsData& data)
{
    os << "{"
       << " { Position: { " 
       << data.position[0] << ", "
       << data.position[1] << ", "
       << data.position[2] << " }, "
       << "{ Energy: { "
       << data.energy << " } }\n";
    return os;
}

TEST_CASE("Node Copy Constructor Test", "[node test]")
{
    using key_type = std::size_t;
    using data_type = PhysicsData;//int[3];

    using node_type = YAGL::Node<key_type, data_type>;

    key_type key = 101;
    data_type data = {{0.0, 1.1, 2.2}, 10.6};
    
    node_type node(key, {{0.0, 1.1, 2.2}, 10.6});
    
    std::cout << node;

    //check that it was set correct by copy constructor
    REQUIRE(node.getData().position[2] == 2.2);
    data.position[2] = 6.6;
    //check that changing the original data does not affect the node data
    REQUIRE(data.position[2] == 6.6);
    REQUIRE(node.getData().position[2] == 2.2);
    
    std::cout << node;
}
