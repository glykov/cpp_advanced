/**
 * Реализуйте шаблонную функцию SortPointers, которая принимает вектор указателей
 * и сортирует указатели по значениям, на которые они указывают.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

template<typename T>
void sort_ptr(std::vector<T*>& v)
{
	std::sort(v.begin(), v.end(), [](T* a, T* b) -> bool { return *a < *b; });
}

int main()
{
	std::vector<int*> vec;

	for (int i = 0; i < 10; ++i) {
		int* a = new int(rand() % 23);
		vec.push_back(a);
	}

	for (auto e : vec) {
		std::cout << *e << " ";
	}
	std::cout << std::endl;

	sort_ptr(vec);

	for (auto e : vec) {
		std::cout << *e << " ";
	}
	std::cout << std::endl;

}