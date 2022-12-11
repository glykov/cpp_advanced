#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <tuple>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
/**
 * 1. Создайте структуру Person с 3 полями: фамилия, имя, отчество. 
 * Поле отчество должно быть опционального типа, т.к. не у всех людей есть отчество. 
 * Перегрузите оператор вывода данных для этой структуры. 
 * Также перегрузите операторы < и == (используйте tie).
 */

struct Person
{
    std::string first_name;
    std::optional<std::string> middle_name;
    std::string last_name;

    Person(std::string fname, std::string lname)
    : first_name(fname), last_name(lname) {}

    Person(std::string fname, std::string mname, std::string lname)
    : Person(fname, lname) { middle_name = mname; }

    friend std::ostream& operator<<(std::ostream& os, const Person& p);
    friend bool operator<(const Person& p1, const Person& p2);
    friend bool operator==(const Person& p1, const Person& p2);
    friend bool operator>(const Person& p1, const Person& p2); 
};

std::ostream& operator<<(std::ostream& os, const Person& p)
{
    os << p.first_name << " " << p.middle_name.value_or("") << " " << p.last_name;
    return os;
}

bool operator<(const Person& p1, const Person& p2)
{
    return std::tie(p1.first_name, p1.middle_name, p1.last_name) < 
            std::tie(p2.first_name, p2.middle_name, p2.last_name);
}

bool operator==(const Person& p1, const Person& p2)
{
    return std::tie(p1.first_name, p1.middle_name, p1.last_name) == 
            std::tie(p2.first_name, p2.middle_name, p2.last_name);
}

bool operator>(const Person& p1, const Person& p2)
{
    return !(p1 < p2) && !(p1 == p2);
}

/**
 * Создайте структуру PhoneNumber с 4 полями:
 * · код страны (целое число)
 * · код города (целое число)
 * · номер (строка)
 * · добавочный номер (целое число, опциональный тип)
 * Для этой структуры перегрузите оператор вывода. 
 * Необходимо, чтобы номер телефона выводился в формате: +7(911)1234567 12, 
 * где 7 – это номер страны, 911 – номер города, 1234567 – номер, 12 – добавочный номер.
 *  Если добавочного номера нет, то его выводить не надо. 
 * Также перегрузите операторы < и == (используйте tie)
 */
struct PhoneNumber
{
    int country_code;
    int city_code;
    std::string number;
    std::optional<int> extension;

    PhoneNumber()
    : country_code(0), city_code(0), number("") {}

    PhoneNumber(int country, int city, std::string num)
    : country_code(country), city_code(city), number(num) {}

    PhoneNumber(int country, int city, std::string num, int ext)
    : PhoneNumber(country, city, num) { extension = ext; }

    friend std::ostream& operator<<(std::ostream& os, const PhoneNumber& pn);
    friend bool operator<(const PhoneNumber& pn1, const PhoneNumber& pn2);
    friend bool operator>(const PhoneNumber& pn1, const PhoneNumber& pn2);
    friend bool operator==(const PhoneNumber& pn1, const PhoneNumber& pn2);
};

std::ostream& operator<<(std::ostream& os, const PhoneNumber& pn)
{
    os << "+" << pn.country_code << "(" << pn.city_code << ")" << pn.number;
    if (pn.extension.has_value()) os << " " << pn.extension.value();
    return os;
}

bool operator<(const PhoneNumber& pn1, const PhoneNumber& pn2)
{
    return std::tie(pn1.country_code, pn1.city_code, pn1.number, pn1.extension) <
            std::tie(pn2.country_code, pn2.city_code, pn2.number, pn2.extension);
}

bool operator==(const PhoneNumber& pn1, const PhoneNumber& pn2)
{
    return std::tie(pn1.country_code, pn1.city_code, pn1.number, pn1.extension) ==
            std::tie(pn2.country_code, pn2.city_code, pn2.number, pn2.extension);
}

bool operator>(const PhoneNumber& pn1, const PhoneNumber& pn2)
{
    return !(pn1 < pn2) && !(pn1 == pn2);
}

/**
 * 3. Создайте класс PhoneBook, который будет в контейнере хранить пары: Человек – Номер телефона. 
 * Конструктор этого класса должен принимать параметр типа ifstream – поток данных, полученных из файла. 
 * В теле конструктора происходит считывание данных из файла и заполнение контейнера. 
 * Класс PhoneBook должен содержать перегруженный оператор вывода, для вывода всех данных из контейнера в консоль. 
 * В классе PhoneBook реализуйте метод SortByName, который должен сортировать элементы контейнера по фамилии людей в алфавитном порядке. 
 * Используйте алгоритмическую функцию sort.
 * Реализуйте метод GetPhoneNumber, который принимает фамилию человека, а возвращает кортеж из строки и PhoneNumber. 
 * Строка должна быть пустой, если найден ровно один человек с заданном фамилией в списке. 
 * Если не найден ни один человек с заданной фамилией, то в строке должна быть запись «not found», 
 * если было найдено больше одного человека, то в строке должно быть «found more than 1».
 * Реализуйте метод ChangePhoneNumber, который принимает человека и новый номер телефона и, 
 * если находит заданного человека в контейнере, то меняет его номер телефона на новый, иначе ничего не делает.
 */
class PhoneBook
{
public:
    PhoneBook(std::ifstream& fin);
    void sort_by_name();
    std::tuple<std::string, PhoneNumber> get_phone_number(std::string name) const;
    void change_phone_number(Person& p, PhoneNumber& pn);

    friend std::ostream& operator<<(std::ostream& os, const PhoneBook& pb);
private:
    Person parse_name(std::string name);
    PhoneNumber parse_number(std::string number);
    std::vector<std::pair<Person, PhoneNumber>> phone_book;
};

Person PhoneBook::parse_name(std::string name)
{
    std::vector<std::string> full_name;
    size_t last = 0;
    size_t next = 0;

    while ((next = name.find(' ', last)) != std::string::npos) {
        full_name.push_back(name.substr(last, next - last));
        last = next + 1;
    }
    full_name.push_back(name.substr(last));
    if (full_name.size() == 3) {
        return Person(full_name[0], full_name[1], full_name[2]);
    }
    return Person(full_name[0], full_name[1]);
}

PhoneNumber PhoneBook::parse_number(std::string number)
{
    int country, city, ext = -1;
    std::string num;

    int pos = number.find('(');
    country = atoi(number.substr(0, pos).c_str());
    number.erase(0, pos + 1);
    pos = number.find(')');
    city = atoi(number.substr(0, pos).c_str());
    number.erase(0, pos + 1);
    pos = number.find(' ');
    if (pos != std::string::npos) {
        ext = atoi(number.substr(pos + 1).c_str());
        num = number.substr(0, pos);
    } else {
        num = number;
    }

    if (ext >= 0) {
        return PhoneNumber(country, city, num, ext);
    }
    return PhoneNumber(country, city, num);
}

PhoneBook::PhoneBook(std::ifstream& fin)
{
    std::string record;
    
    while(std::getline(fin, record)) {
        size_t pos = record.find('+');
        std::string full_name = record.substr(0, pos - 1);
        std::string full_number = record.substr(pos + 1);
        
        Person p = parse_name(full_name);
        PhoneNumber pn = parse_number(full_number);
        phone_book.push_back(std::pair<Person, PhoneNumber>(p, pn));
    }
}

std::ostream& operator<<(std::ostream& os, const PhoneBook& pb)
{
    for (auto record : pb.phone_book) {
        os << record.first << " " << record.second << std::endl;
    }
    return os;
}

void PhoneBook::sort_by_name()
{
    std::sort(phone_book.begin(), phone_book.end(),
            [](const std::pair<Person, PhoneNumber>& a, const std::pair<Person, PhoneNumber>& b) 
            { return a.first < b.first; });
}

// согласно заданию нужно возвращать кортеж, хотя можно и пару (тем более, что это специальный вид кортежа)
// также в условии не указано, при наличии нескольких совпадений фамилии нужно ли возвращать первый найденный номер
// или последний, поэтому в данном случае возвращается первый найденный номер
std::tuple<std::string, PhoneNumber> PhoneBook::get_phone_number(std::string name) const
{
    std::tuple<std::string, PhoneNumber> result;
    int number_found = 0;
    PhoneNumber pn;
    for (auto it = phone_book.begin(); it != phone_book.end(); ++it) {
        if (it->first.last_name == name) {
            if (number_found == 0) {
                result = std::make_tuple("", it->second);
                number_found++;
            } else {
                number_found++;
            }
        }
    }

    if (number_found == 0) {
        result = std::make_tuple("not found", pn);
    } else if (number_found > 1) {
        std::get<0>(result) = "found more than 1";
    }

    return result;
}

void PhoneBook::change_phone_number(Person& p, PhoneNumber& pn)
{
    for (auto it = phone_book.begin(); it != phone_book.end(); ++it) {
        if (it->first == p) {
            it->second = pn;
        }
    }
}

int main()
{
    std::ifstream fin;
    fin.open("phone_book.txt", std::ios_base::in);
    if (!fin.is_open()) {
        std::cout << "Error openning file\n";
        exit(1);
    }
    PhoneBook pb(fin);
    std::cout << pb << std::endl;

    pb.sort_by_name();
    std::cout << pb << std::endl;

    auto phone = pb.get_phone_number("Potter");
    if (std::get<0>(phone) == "not found") {
        std::cout << std::get<0>(phone) << std::endl;
    } else {
        std::cout << std::get<0>(phone) << " " << std::get<1>(phone) << std::endl;
    }

    phone = pb.get_phone_number("Malfoy");
    if (std::get<0>(phone) == "not found") {
        std::cout << std::get<0>(phone) << std::endl;
    } else {
        std::cout << std::get<0>(phone) << " " << std::get<1>(phone) << std::endl;
    }

    Person person("Harry", "Potter");
    PhoneNumber number(11, 22, "333");
    pb.change_phone_number(person, number);
    std::cout << "\n" << pb << std::endl;
    
    return 0;
}