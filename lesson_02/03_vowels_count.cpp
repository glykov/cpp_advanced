/**
 * Подсчитайте количество гласных букв в книге “Война и мир”
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "time.h"

std::vector<char> vowels = {'a', 'e', 'i', 'o', 'u'};

// 1. count_if и find
int count_vowels_01(const std::string& text)
{
    int result = 0;
    Timer t("1. count_if and find");
    result = count_if(text.begin(), text.end(), [](char c) { return std::find(vowels.begin(), vowels.end(), c) != vowels.end(); });
    t.print();
    return result;
}

// 2.  count_if и цикл for
int count_vowels_02(const std::string& text)
{
    int result = 0;
    Timer t("2. count_if and for");
    for(char c : vowels) {
        result += count_if(text.begin(), text.end(), [&c](char current) { return current == c; });
    }
    t.print();
    return result;
}

// 3. цикл for и find
int count_vowels_03(const std::string& text)
{
    int result = 0;
    Timer t("3. for and find");
    for (char c : text) {
        result += (std::find(vowels.begin(), vowels.end(), c) != vowels.end());
    }
    t.print();
    return result;
}

// 4. 2 цикла for
int count_vowels_04(const std::string& text)
{
    int result = 0;
    Timer t("4. two for cycles");
    for (char c1 : text) {
        for (char c2 : vowels) {
            if (c1 == c2) {
                result++;
                break;
            }
        }
    }
    t.print();
    return result;
}

std::string get_file_contents(const char* file_name)
{
    std::ifstream fin(file_name, std::ios::in | std::ios::binary);
    std::string contents;

    if (fin) {
        fin.seekg(0, std::ios::end);
        contents.resize(fin.tellg());
        fin.seekg(0, std::ios::beg);
        fin.read(&contents[0], contents.size());
        fin.close();
    }

    return contents;
}

int main()
{
    std::string text = get_file_contents("war_and_peace.txt");

    if (text.size() == 0) {
        std::cout << "cannot get file contents\n";
    } else {
        count_vowels_01(text); // 1. count_if and find:   193.767 ms
        count_vowels_02(text); // 2. count_if and for:    299.115 ms
        count_vowels_03(text); // 3. for and find:        201.128 ms
        count_vowels_04(text); // 4. two for cycles:      185.038 ms
    }

    return 0;
}