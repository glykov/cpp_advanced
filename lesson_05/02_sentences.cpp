/*
 * Используя ассоциативный контейнер, напишите программу, 
 * которая будет считывать данные введенные пользователем из стандартного потока ввода 
 * и разбивать их на предложения. 
 * Далее программа должна вывести пользователю все предложения, 
 * а также количество слов в них, отсортировав предложения по количеству слов.
*/
#include <iostream>
#include <map>
#include <string>

int main()
{
    std::multimap <int, std::string> sentencies;
	std::string sentence;
	std::string word;
	int word_count = 0;

	while (std::cin >> word) {
		++word_count;
		if (sentence.empty()) {
			sentence += word;
		}
		else {
			sentence += " " + word;
		}
		if (word.find('.') != std::string::npos) {
			sentencies.insert({ word_count, sentence });
			word_count = 0;
			sentence.clear();
		}
	}


	for (const auto& word : sentencies) {
		std::cout << word.second << " contains " << word.first
			<< (word.first == 1 ? " word." : " words.") << std::endl;
	}
    
    return 0;
}