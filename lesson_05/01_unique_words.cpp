/*
 * Создать шаблонную функцию, которая принимает итераторы на начало и конец последовательности слов, 
 * и выводящую в консоль список уникальных слов (если слово повторяется больше 1 раза, то вывести его надо один раз).
 * Продемонстрировать работу функции, передав итераторы различных типов.
*/
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <list>

template<typename Iterator>
void show_unique_words(Iterator first, Iterator last)
{
    std::set<std::string> words(first, last);
    for (auto word : words) {
        std::cout << word << std::endl;
    }
}

int main()
{
    std::vector<std::string> str_vec{ "the", "world", "is", "not", "enough", "the", "is" };
	show_unique_words(str_vec.begin(), str_vec.end());

	std::string str_arr[]{"the", "world", "is", "not", "enough", "the", "is"};
	show_unique_words(std::begin(str_arr), std::end(str_arr));

	show_unique_words(str_arr, str_arr + 7);

    std::list<std::string> str_lst(str_vec.begin(), str_vec.end());
    show_unique_words(str_lst.begin(), str_lst.end());
    
    return 0;
}