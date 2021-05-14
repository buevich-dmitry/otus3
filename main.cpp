#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <string>
#include <cstddef>

template <class T, typename = std::enable_if_t<std::is_integral_v<T>>>
void PrintIp(T value, std::ostream& out = std::cout) {
    constexpr size_t size = sizeof(T);
    for (size_t i = 0; i < size; ++i) {
        if (i != 0) {
            out << '.';
        }
        const auto byte = static_cast<std::byte>(value >> ((size - 1 - i) * 8));
        out << std::to_integer<unsigned short>(byte);
    }
    out << '\n';
}

template<class T, typename = std::enable_if_t<std::is_same_v<std::string, T>>>
void PrintIp(const T& value, std::ostream& out = std::cout) {
    out << value << '\n';
}

template <class T,
        typename = std::enable_if_t<std::is_same_v<decltype(std::declval<T>().begin()), typename T::iterator>>,
        typename = std::enable_if_t<std::is_same_v<decltype(std::declval<T>().end()), typename T::iterator>>,
        typename = std::enable_if_t<std::is_integral_v<typename T::value_type>>,
        typename = std::enable_if_t<!std::is_same_v<T, std::string>>
>
void PrintIp(const T& value, std::ostream& out = std::cout) {
    bool first = true;
    for (const auto& element : value) {
        if (!first) {
            out << '.';
        }
        first = false;
        out << element;
    }
    out << '\n';
}

template <size_t I = 0, class... Args>
std::enable_if_t<I == sizeof...(Args)> PrintTupleElements(const std::tuple<Args...>&, std::ostream& out) {
    out << '\n';
}

template <size_t I = 0, class... Args>
std::enable_if_t<I < sizeof...(Args)> PrintTupleElements(const std::tuple<Args...>& value, std::ostream& out) {
    if constexpr (I != 0) {
        out << '.';
    }
    out << std::get<I>(value);
    PrintTupleElements<I + 1>(value, out);
}

template <class Arg, class... Args, typename = std::enable_if_t<std::disjunction_v<std::is_same<Arg, Args>...>>>
void PrintIp(const std::tuple<Arg, Args...>& value, std::ostream& out = std::cout) {
    PrintTupleElements(value, out);
}

int main() {
    PrintIp( char{-1} ); // 255
    PrintIp( short{0} ); // 0.0
    PrintIp( int{2130706433} ); // 127.0.0.1
    PrintIp( long{8875824491850138409} ); // 123.45.67.89.101.112.131.41
    PrintIp( std::string{"Hello, World!"} ); // Hello, World!
    PrintIp( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    PrintIp( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
    PrintIp( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
    return 0;
}
