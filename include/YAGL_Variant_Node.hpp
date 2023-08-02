#ifndef YAGL_VARIANT_NODE_HPP
#define YAGL_VARIANT_NODE_HPP

#include <iostream>
#include <variant>
#include <type_traits>

namespace YAGL
{
#include <type_traits>

    // Empty type set (base case)
    template<typename... Types>
    struct TypeSet {
        static constexpr bool is_unique = true;
    };

    // Type set with at least one type
    template<typename T, typename... Rest>
    struct TypeSet<T, Rest...> {
        static constexpr bool is_unique =
                (!std::disjunction_v<std::is_same<T, Rest>...>)
                && TypeSet<Rest...>::is_unique;
    };

    // Helper function to check uniqueness of types
    template<typename... Types>
    constexpr bool are_types_unique() {
        return TypeSet<Types...>::is_unique;
    }
    template <typename ... Ts>
    class VariantNode;

    template <typename ... Ts>
    class VariantNode
    {
    public:
        VariantNode() {
            static_assert(are_types_unique<Ts ...>(), "Types aren't unique");
        }

        using node_variant_t = std::variant<Ts ...>;

        constexpr auto get_size() { return std::variant_size_v<node_variant_t>;}

        template<typename T>
        void setData(const T&);

        auto getTypeIndex() const;

    private:
        std::size_t typeIndex;
        node_variant_t data;
    };

    template <typename ... Ts>
    template <typename T>
    void VariantNode<Ts ...>::setData(const T& value)
    {
        data = value;
        typeIndex = data.index();
    }

    template <typename ... Ts>
    auto VariantNode<Ts ...>::getTypeIndex() const
    {
        return typeIndex;
    }
}
#endif //YAGL_VARIANT_NODE_HPP
