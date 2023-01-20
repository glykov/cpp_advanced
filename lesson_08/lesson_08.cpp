#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <optional>
#include <tuple>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <gtest/gtest.h>


struct Person
{
    std::string first_name;
    std::optional<std::string> middle_name;
    std::string last_name;

    Person(std::string fname, std::string lname)
        : first_name(fname), last_name(lname) {}

    Person(std::string fname, std::string mname, std::string lname)
        : Person(fname, lname) {
        middle_name = mname;
    }

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
        : PhoneNumber(country, city, num) {
        extension = ext;
    }

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

class PhoneBook
{
public:
    PhoneBook(std::istream& fin);
    void sort_by_name();
    void sort_by_phone();
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
    }
    else {
        num = number;
    }

    if (ext >= 0) {
        return PhoneNumber(country, city, num, ext);
    }
    return PhoneNumber(country, city, num);
}

PhoneBook::PhoneBook(std::istream& fin)
{
    std::string record;

    while (std::getline(fin, record)) {
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

void PhoneBook::sort_by_phone()
{
    std::sort(phone_book.begin(), phone_book.end(),
        [](const std::pair<Person, PhoneNumber>& a, const std::pair<Person, PhoneNumber>& b)
        { return a.second < b.second; });
}

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
            }
            else {
                number_found++;
            }
        }
    }

    if (number_found == 0) {
        result = std::make_tuple("not found", pn);
    }
    else if (number_found > 1) {
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
// ----- PERSON TESTS ---------

TEST(person, get_name_test) 
{
    Person p{ "Abc", "Xyz" };
    std::stringstream ss;
    ss << p;
    std::string s = ss.str();
    ASSERT_STREQ("Abc  Xyz", s.c_str());
}

TEST(person, get_name_test_2)
{
    Person p{ "Abc", "Qrs", "Xyz" };
    std::stringstream ss;
    ss << p;
    std::string s = ss.str();
    ASSERT_STREQ("Abc Qrs Xyz", s.c_str());
}

TEST(person, lt_test)
{
    Person p1{ "Abc", "Xyz" };
    Person p2{ "Xyz", "Abc" };
    ASSERT_LT(p1, p2);
}

TEST(person, gt_test)
{
    Person p1{ "Abc", "Xyz" };
    Person p2{ "Xyz", "Abc" };
    ASSERT_GT(p2, p1);
}

TEST(person, eq_test)
{
    Person p1{ "Abc", "Qrs", "Xyz" };
    Person p2{ "Abc", "Qrs", "Xyz" };
    ASSERT_EQ(p1, p2);
}

// ----- PHONE NUMBER TESTS --------- 

TEST(phone_number, output_test)
{
    PhoneNumber pn{ 11, 222, "333" };
    std::stringstream ss;
    ss << pn;
    std::string s = ss.str();
    ASSERT_STREQ("+11(222)333", s.c_str());
}

TEST(phone_number, lt_test)
{
    PhoneNumber pn1{ 11, 222, "333" };
    PhoneNumber pn2{ 11, 222, "444" };
    ASSERT_LT(pn1, pn2);
}

TEST(phone_number, gt_test)
{
    PhoneNumber pn1{ 11, 222, "333" };
    PhoneNumber pn2{ 11, 222, "444" };
    ASSERT_GT(pn2, pn1);
}

TEST(phone_number, eq_test)
{
    PhoneNumber pn1{ 11, 222, "333" };
    PhoneNumber pn2{ 11, 222, "333" };
    ASSERT_EQ(pn1, pn2);
}

// ----- PHONE BOOK TESTS --------- 

TEST(phone_book, ctr_test)
{
    std::stringstream sin;
    sin << "Harry Potter +44(120)73238181";
    PhoneBook pb(sin);
    std::stringstream sout;
    sout << pb;
    std::string s = sout.str();
    ASSERT_STREQ("Harry  Potter +44(120)73238181\n", s.c_str());
}

TEST(phone_book, change_phone)
{
    std::stringstream sin;
    sin << "Harry Potter +44(020)73238181";
    PhoneBook pb(sin);
    Person p{ "Harry", "Potter" };
    PhoneNumber pn{ 11, 222, "333" };
    pb.change_phone_number(p, pn);
    std::stringstream sout;
    sout << pb;
    std::string s = sout.str();
    ASSERT_STREQ("Harry  Potter +11(222)333\n", s.c_str());
}

int main(int argc, const char** argv) {
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
