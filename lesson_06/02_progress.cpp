/*
 * Реализовать функцию, возвращающую i-ое простое число (например, миллионное простое число равно 15485863). 
 * Вычисления реализовать во вторичном потоке. В консоли отображать прогресс вычисления (в основном потоке)
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstdint>
#include <climits>

std::mutex mtx;
std::condition_variable sync_cond;
bool run = false;
bool finish = false;

uint64_t find_prime(uint64_t number)
{
    uint64_t counter = 0;
    uint64_t progress = number / 10;
    uint64_t i, j;
    bool found;
    for (i = 2; i < ULLONG_MAX; ++i) {
        found = true;
        for (j = 2; j * j <= i; ++j) {
            if (i % j == 0) {
                found = false;
                break;
            }
        }
        if (found) {
            ++counter;
            if (counter % progress == 0) {
                std::unique_lock<std::mutex> lk(mtx);
                sync_cond.wait(lk, [] { return !run; });
                run = true;
                sync_cond.notify_one();
            }
        }
        if (counter == number) {
            break;
        }
    }
    finish = true;
    return i;
}

int main()
{
    uint64_t prime = 0;
    std::thread t([&prime]() { prime = find_prime(1'000'000); });

    int i = 1;
    while (!finish)
    {
        std::unique_lock<std::mutex> lk(mtx);
        sync_cond.wait(lk, [] { return run; });
        std::cout << "running " << (i * 10) << "% of calculations..." << std::endl;
        ++i;
        run = false;
        sync_cond.notify_one();
    }

    t.join();
    std::cout << "found prime number is " << prime << std::endl;

    return 0;
}