/*
 * Написать функцию, добавляющую в конец списка вещественных чисел элемент,
 * значение которого равно среднему арифметическому всех его элементов
*/
#include <iostream>
#include <vector>
#include <cstdlib>

void add_average(std::vector<double>& v)
{
    double sum = 0;
    for (auto el : v) {
        sum += el;
    }
    v.push_back(sum / v.size());
}

void print_vec(const std::vector<double>& v) {
    for (auto el : v) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<double> vec;
    for (int i = 0; i < 10; i++) {
        double d = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        vec.push_back(d);
    }
    print_vec(vec);

    add_average(vec);
    print_vec(vec);

    return 0;
}