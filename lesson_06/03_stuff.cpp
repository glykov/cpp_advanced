/*
 * Промоделировать следующую ситуацию. Есть два человека (2 потока): хозяин и вор. 
 * Хозяин приносит домой вещи (функция добавляющая случайное число в вектор с периодичностью 1 раз в секунду). 
 * При этом у каждой вещи есть своя ценность. 
 * Вор забирает вещи (функция, которая находит наибольшее число и удаляет из вектора с периодичностью 1 раз в 0.5 секунд), 
 * каждый раз забирает вещь с наибольшей ценностью.
*/

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib>

std::vector<int> stuff;
std::mutex mtx;

void host_function()
{
    int thing;
    while (true) {
        thing = 1 + rand() % 100;
        mtx.lock();
        stuff.push_back(thing);
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void theif_function()
{
    int index;
    while (true) {
        index = 0;
        for (int i = 0; i < stuff.size(); ++i) {
            if (stuff[i] > stuff[index]) {
                index = i;
            }
        }
        mtx.lock();
        stuff.erase(stuff.begin() + index);
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

template <typename T>
void print_vec(std::vector<T> vec)
{
    for (int i = 0; i < vec.size(); ++i) {
        if (i != 0) {
            std::cout << ", ";
        }
        std::cout << vec[i];
    }
    std::cout << std::endl;
}

int main()
{
    std::thread host(host_function);
    std::thread thief(theif_function);

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        print_vec(stuff);
    }

    host.join();
    thief.join();

    return 0;
}