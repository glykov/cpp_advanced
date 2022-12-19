/**
 * Реализуйте шаблонную функцию Swap, которая принимает два указателя и обменивает местами значения, 
 * на которые указывают эти указатели (нужно обменивать именно сами указатели, 
 * переменные должны оставаться в тех же адресах памяти
 */
#include <iostream>

template<typename T>
void swap_ptr(T* p1, T* p2)
{
	T* tmp = p1;
	p1 = p2;
	p2 = tmp;
}

int main()
{
	int a = 5;
	int b = 7;

	int* a_ptr = &a;
	int* b_ptr = &b;

	std::cout << "a = " << a << ", address = " << &a << std::endl;
	std::cout << "b = " << b << ", address = " << &b << std::endl;

	std::cout << "a_ptr = " << a_ptr << ", *a_ptr = " << *a_ptr << std::endl;
	std::cout << "b_ptr = " << b_ptr << ", *b_ptr = " << *b_ptr << std::endl;

	int* tmp = a_ptr;
	a_ptr = b_ptr;
	b_ptr = tmp;

	std::cout << "==============================\n";

	std::cout << "a = " << a << ", address = " << &a << std::endl;
	std::cout << "b = " << b << ", address = " << &b << std::endl;

	std::cout << "a_ptr = " << a_ptr << ", *a_ptr = " << *a_ptr << std::endl;
	std::cout << "b_ptr = " << b_ptr << ", *b_ptr = " << *b_ptr << std::endl;

	std::cout << "==============================\n";

	swap_ptr(a_ptr, b_ptr);

	std::cout << "a = " << a << ", address = " << &a << std::endl;
	std::cout << "b = " << b << ", address = " << &b << std::endl;

	std::cout << "a_ptr = " << a_ptr << ", *a_ptr = " << *a_ptr << std::endl;
	std::cout << "b_ptr = " << b_ptr << ", *b_ptr = " << *b_ptr << std::endl;

	return 0;
}