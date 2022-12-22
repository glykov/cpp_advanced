/*
 * Имеется отсортированный массив целых чисел. 
 * Необходимо разработать функцию insert_sorted, которая принимает вектор и новое число 
 * и вставляет новое число в определенную позицию в векторе, чтобы упорядоченность контейнера сохранялась. 
 * Реализуйте шаблонную функцию insert_sorted, которая сможет аналогично работать с любым контейнером, 
 * содержащим любой тип значения.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

template<typename T>
void insert_sorted(std::vector<T>& vec, T val)
{
    auto it = find_if(vec.begin(), vec.end(), [val](T x){ return x > val; });
    vec.insert(it, val);
}

int main()
{
    std::vector<int> v {1, 2, 3, 4, 6, 7, 8};
    std::ostream_iterator<int> os_it(std::cout, " ");
    std::copy(v.begin(), v.end(), os_it);
    std::cout << std::endl;

    insert_sorted(v, 0);
    std::copy(v.begin(), v.end(), os_it);
    std::cout << std::endl;

    insert_sorted(v, 5);
    std::copy(v.begin(), v.end(), os_it);
    std::cout << std::endl;

    insert_sorted(v, 10);
    std::copy(v.begin(), v.end(), os_it);
    std::cout << std::endl;

    return 0;
}