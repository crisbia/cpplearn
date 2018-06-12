#include <iostream>
#include <memory>
#include <tuple>
#include <type_traits>

//template <typename T, typename ... Args>
//struct are_all_ints
//{
//    constexpr static bool value = std::is_integral<T>::value && are_all_ints<Args...>::value;
//};

//template <> struct are_all_ints<int>
//{
//    constexpr static bool value = true;
//};


template <typename T>
void printPairs(T value)
{
    std::cout << "[" << value.first << "," << value.second << "]\n";
}

template <typename T, typename ... Args>
void printPairs(T value, Args... args)
{
    printPairs(value);
    printPairs(args...);
}

template <typename>
struct is_pair : std::false_type
{ };

template <typename V, typename U>
struct is_pair<std::pair<V, U>> : std::true_type
{ };

template <typename S, typename ... P>
struct are_all_pairs
{
    constexpr static bool value = is_pair<S>::value && are_all_pairs<P...>::value;
};

template <typename P, typename Q> struct are_all_pairs<std::pair<P,Q>>
{
    constexpr static bool value = true;
};

template <typename T, typename ... Args>
class Tuple
{
public:
    template <typename = std::enable_if<are_all_pairs<T, Args...>::value, T>, typename = std::enable_if<are_all_pairs<T, Args...>::value, Args...>>
    Tuple(T value, Args... args)
    {
        std::cout << 1 + sizeof...(args) << "\n";
        printPairs(value, args...);
        args_ = std::tuple<T, Args...>(value, args...);
    }

//    template <const size_t N>
//    typename std::tuple_element<N, std::tuple<Args...>>::type get() const
//    {
//        return std::get<N>(args_);
//    };

public:
    std::tuple<T, Args...> args_;
};

int main()
{

//    std::cout << t.get<0>() << "\n";
//    std::cout << t.get<1>() << "\n";
//    std::cout << t.get<2>() << "\n";

    Tuple<std::pair<const char*, double>, std::pair<const char*, int>> t(std::make_pair("dio", 789.0), std::make_pair("cane", 789));
//    Tuple<std::pair<const char*, int>, std::pair<const char*, int>> t(std::make_pair("dio", 789), std::make_pair("cane", 789));
//    Tuple<std::pair<const char*, double>> t(std::make_pair("dio", 789.0));

    return 0;
}
