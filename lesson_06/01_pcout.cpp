/**
 * Создайте потокобезопасную оболочку для объекта cout. Назовите ее pcout. 
 * Необходимо, чтобы несколько потоков могли обращаться к pcout и информация выводилась в консоль. 
 * Продемонстрируйте работу pcout.
 * 
 * Вывод при работе тестовой функции 2 с объектом std::cout
 * test test 2: three
 * 2: one
 * test 2: four
 * test 2: two
 * 
 * Вывод при работе тестовой функции 1 с объектом pcout
 * test 1: one
 * test 1: two
 * test 1: three
 * test 1: four
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

class myostream
{
public:
    myostream() {
        myostream::_mtx.lock();
    }
    ~myostream() {
        myostream::_mtx.unlock();
    }
    myostream& operator<<(int x) {
        std::cout << x;
        return *this;
    }
    myostream& operator<<(double x) {
        std::cout << x;
        return *this;
    }
    myostream& operator<<(const char* str) {
        std::cout << str;
        return *this;
    }
private:
    static std::mutex _mtx;
};

std::mutex myostream::_mtx = std::mutex();

void test_function_1(const char* str1, const char* str2) {
    myostream pcout;
    pcout << "test " << 1 << ": " << str1;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    pcout << "test " << 1 << ": " << str2;
}

void test_function_2(const char* str1, const char* str2) {
    std::cout << "test " << 2 << ": " << str1;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "test " << 2 << ": " << str2;
}


int main()
{
    std::thread t1(test_function_1, "one\n", "two\n");
    std::thread t2(test_function_1, "three\n", "four\n");
    // std::thread t3(test_function_2, "one\n", "two\n");
    // std::thread t4(test_function_2, "three\n", "four\n");
    
    t1.join();
    t2.join();
    // t3.join();
    // t4.join();
    
    return 0;
}