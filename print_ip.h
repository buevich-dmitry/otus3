#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <string>
#include <cstddef>

namespace {

template<size_t I = 0, class... Args>
std::enable_if_t<I == sizeof...(Args)> PrintTupleElements(const std::tuple<Args...>&, std::ostream& out) {
    out << '\n';
}

template<size_t I = 0, class... Args>
std::enable_if_t<I < sizeof...(Args)> PrintTupleElements(const std::tuple<Args...>& value, std::ostream& out) {
    if constexpr (I != 0) {
        out << '.';
    }
    out << std::get<I>(value);
    PrintTupleElements<I + 1>(value, out);
}

}  // anonymous namespace

template <class T, typename = std::enable_if_t<std::is_integral_v<T>>>
void PrintIp(T integral_value, std::ostream& out = std::cout) {
    constexpr size_t size = sizeof(T);
    for (size_t i = 0; i < size; ++i) {
        if (i != 0) {
            out << '.';
        }
        const auto byte = static_cast<std::byte>(integral_value >> ((size - 1 - i) * 8));
        out << std::to_integer<unsigned short>(byte);
    }
    out << '\n';
}

template<class T, typename = std::enable_if_t<std::is_same_v<std::string, T>>>
void PrintIp(const T& string_value, std::ostream& out = std::cout) {
    out << string_value << '\n';
}

template <class T,
        typename = std::enable_if_t<std::is_same_v<decltype(std::declval<T>().begin()), typename T::iterator>>,
        typename = std::enable_if_t<std::is_same_v<decltype(std::declval<T>().end()), typename T::iterator>>,
        typename = std::enable_if_t<std::is_integral_v<typename T::value_type>>,
        typename = std::enable_if_t<!std::is_same_v<T, std::string>>
>
void PrintIp(const T& container_value, std::ostream& out = std::cout) {
    bool first = true;
    for (const auto& element : container_value) {
        if (!first) {
            out << '.';
        }
        first = false;
        out << element;
    }
    out << '\n';
}

template <class Arg, class... Args, typename = std::enable_if_t<std::conjunction_v<std::is_same<Arg, Args>...>>>
void PrintIp(const std::tuple<Arg, Args...>& tuple_value, std::ostream& out = std::cout) {
    PrintTupleElements(tuple_value, out);
}
