/*
 * Сгенерируйте вектор a, состоящий из 100 вещественный чисел, 
 * представляющий собой значения аналогового сигнала. 
 * На основе этого массива чисел создайте другой вектор целых чисел b, 
 * представляющий цифровой сигнал, в котором будут откинуты дробные части чисел. 
 * Выведите получившиеся массивы чисел. 
 * Посчитайте ошибку, которой обладает цифровой сигнал по сравнению с аналоговым по формуле
*/
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <functional>

int main()
{
    const int SIZE = 100;
    std::vector<double> analog;
    std::default_random_engine engine;
    std::uniform_real_distribution<double> dist(1, 10);

    for (int i = 0; i < SIZE; ++i) {
        analog.push_back(dist(engine));
    }

    std::vector<int> digital(SIZE);
    std::transform(analog.begin(), analog.end(), digital.begin(), [](double x) { return static_cast<int>(x); });

    for (auto el : analog) {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    for (auto el : digital) {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    // не удалось заставить правильно работать, посчитал вручную
    // double result = std::inner_product(analog.begin(), analog.end(), digital.begin(), 0,
    //         std::plus<double>(), [](double x, int y) { return std::pow((x - y), 2);});
    auto it1 = analog.begin();
    auto it2 = digital.begin();
    double error = 0.0;
    while (it1 != analog.end()) {
        error += std::pow((*it1 - *it2), 2);
        ++it1;
        ++it2;
    }
    std::cout << "The error = " << error << std::endl;

    куегкт 0ж
}