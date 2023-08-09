#include <iostream>

#include "catch.hpp"
#include "YAGL_Graph.hpp"
#include "YAGL_Node.hpp"
#include "YAGL_Variant_Data.hpp"

#include <optional>
struct BaseType { double x1, x2; };

struct TypeA : BaseType { double energy; };
struct TypeB : BaseType { bool bind; };
struct TypeC : BaseType { double p1, p2; };

struct NodeBase
{
    std::size_t id;

    virtual std::string getName() const = 0;

};

struct NodeA : NodeBase
{
    std::string getName() const override
    {
        return "NodeA";
    }
};

struct NodeB : NodeBase
{
    std::string getName() const override
    {
        return "NodeB";
    }
};

struct NodeC : NodeBase
{
    std::string getName() const override
    {
        return "NodeC";
    }
};

template <typename ... Ts>
struct SpatialNode2D : YAGL::VariantData<Ts ...>
{
    double x1, x2;
};

TEST_CASE("Variant Type Node Test", "[variant node test]")
{    
    YAGL::VariantData<TypeA, TypeB, TypeC> node1;
    REQUIRE(node1.get_size() == 3);
    node1.setData(TypeB{1.2, 1.2, false});

    const auto& data = node1.getData<TypeB>();
    REQUIRE(((data.x1 == 1.2) && (data.x2 == 1.2) && (data.bind == false)));
    //node1.setData(TypeA{1.2, 1.2, 2.2});
    auto result =
            std::visit(
                    [](auto& data)-> std::optional<double> {
                        using T = std::decay_t<decltype(data)>;
                        if constexpr (std::is_same_v<T, TypeB>)
                            return data.x1+data.x2;
                        else return std::nullopt;
                        }, node1.data);
    if(result)
        std::cout << result.value()  << "\n";
    else std::cout << "nullopt\n";
    //REQUIRE(result == 2.4);
    std::cout << node1.getTypeIndex() << "\n";
    //std::variant<std::monostate> var;
    using Sp2D = SpatialNode2D<std::size_t, TypeA, TypeB, TypeC>;
    using GT = YAGL::Graph<std::size_t, SpatialNode2D<std::size_t, TypeA, TypeB, TypeC>>;
    GT g1, g2;
    YAGL::VariantData<TypeA, TypeB, TypeC> v = {TypeA{}};
    TypeA b = {1.1, 2.2, 0.03};
    SpatialNode2D<std::size_t, TypeA, TypeB, TypeC> spn = {TypeC{}};
    std::cout << "type: " << spn.TypeIndex() << "\n";
    std::size_t k = 1;
    YAGL::Node snode(k, SpatialNode2D<std::size_t, TypeA, TypeB, TypeC>{TypeA{1.1, 1.1, 0.03}, 1.2, 1.2});
    g1.addNode({std::size_t{1}, Sp2D{TypeA{1.1, 1.1, 0.04}, 1.2, 1.2}});
    auto& n = g1.findNode(1)->second.getData();
    std::cout << n.getData<TypeA>().energy << "\n";
    g2.addNode({1, Sp2D{TypeB{}}});
    g2.addNode({2, Sp2D{TypeA{}}});
    g2.addNode({3, Sp2D{TypeA{}}});
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.addEdge(3, 1);

    for(auto& item : g2.getNodeSet())
        std::cout << item.first << " " << item.second.getData().type << "\n";

    auto where = [](GT& rhs) -> void
    {
        auto& n1 = rhs[1];
        auto& n2 = rhs[2];
        auto& n3 = rhs[3];

        n1.x1 = 0.0;
        n1.x2 = 0.0;
        n1.getData<TypeB>().bind = false;

        n2.x1 = 1.2;
        n2.x2 = 1.2;
        n2.getData<TypeA>().energy = 3.4;

        n3.x1 = 2.0;
        n3.x2 = 2.0;
        n3.getData<TypeA>().energy = 2.6;
    };

    auto propensity = [](GT& lhs) -> double
    {
        auto& n2 = lhs[2];
        auto& n3 = lhs[3];

        return n2.getData<TypeA>().energy + n3.getData<TypeA>().energy;
    };

    where(g2);
    std::cout << "result: " << propensity(g2) << "\n";
    std::cout << g2[2].getData<TypeA>().energy;

}

TEST_CASE("other test", "[other]")
{

        std::vector<std::unique_ptr<NodeBase>> nodes;
        nodes.push_back(std::make_unique<NodeA>());
        nodes.push_back(std::make_unique<NodeC>());
        nodes.push_back(std::make_unique<NodeB>());
        nodes.push_back(std::make_unique<NodeB>());
        nodes.push_back(std::make_unique<NodeA>());

        for(auto& item : nodes) {
            std::cout << item->getName() << "\n";
        }
}