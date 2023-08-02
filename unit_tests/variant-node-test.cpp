#include <iostream>

#include "catch.hpp"
#include "YAGL_Variant_Node.hpp"


TEST_CASE("Variant Type Node Test", "[variant node test]")
{    
    YAGL::VariantNode<int, double, char> node1;
    REQUIRE(node1.get_size() == 3);

    node1.setData(2.2);
    std::cout << node1.getTypeIndex() << "\n";
}
