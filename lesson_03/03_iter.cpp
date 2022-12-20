/*
 * Реализовать собственный класс итератора, с помощью которого можно будет проитерироваться по диапазону целых чисел в цикле for-range-based
*/
#include <iostream>

class Iterator
{
public:
    Iterator(int* first) : curr(first) 
    {}

    int& operator+(int n) { return *(curr + n); }
    int& operator-(int n) { return *(curr - n); }

    int& operator++(int) { return *curr++; }
    int& operator--(int) { return *curr--; }
    int& operator++() { return *(++curr); }
    int& operator--() { return *(--curr); }

    bool operator!=(const Iterator& other) { return curr != other.curr; }
    bool operator==(const Iterator& other) { return curr == other.curr; }

    int& operator*() { return *curr; }
private:
    int* curr;
};

class Range
{
public:
    Range(int start, int stop, int step=1) 
    {
        m_size = (stop - start) / step;
        data = new int[m_size];
        for (int i = start, j = 0; i < stop; i += step, j++) {
            data[j] = i;
        }
    }

    int& operator[](int index)
    {
        return data[index];
    }

    Iterator begin() { return data; }
    Iterator end() { return data + m_size; }
private:
    int* data;
    int m_size;
};

int main()
{
    for (auto x : Range(1, 10)) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}