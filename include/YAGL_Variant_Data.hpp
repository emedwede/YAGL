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
    class VariantData;

    template <typename ... Ts>
    class VariantData
    {
    public:
        VariantData() {
            static_assert(are_types_unique<Ts ...>(), "Types aren't unique");
        }

        template <typename T>
        VariantData(T&& item) : data(item) {
            type = data.index();
            static_assert(are_types_unique<Ts ...>(), "Types aren't unique");
        }

        using node_variant_t = std::variant<Ts ...>;

        constexpr auto get_size() { return std::variant_size_v<node_variant_t>;}

        template<typename T>
        void setData(T&&);

        template<typename T>
        T& getData();

        auto getTypeIndex() const;

    //private:

        constexpr std::size_t TypeIndex() const;
        std::size_t typeIndex, type;
        node_variant_t data;
    };

    // Public Functions
    template <typename ... Ts>
    template <typename T>
    void VariantData<Ts ...>::setData(T&& value)
    {
        data = value;
        type = data.index();
        typeIndex = data.index();
    }

    template <typename ... Ts>
    template <typename T>
    T& VariantData<Ts ...>::getData()
    {
        return std::get<T>(data);
    }

    template <typename ... Ts>
    auto VariantData<Ts ...>::getTypeIndex() const
    {
        return typeIndex;
    }

    // Private Functions
    template <typename ... Ts>
    constexpr std::size_t VariantData<Ts ...>::TypeIndex() const
    {
        return data.index();
    }
}
#endif //YAGL_VARIANT_NODE_HPP
