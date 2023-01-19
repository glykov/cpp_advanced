#pragma once
#include <vector>
#include "01_full_name.h"

namespace students_group
{
    class Student
    {
    public:
        Student() = default;
        Student(FullName full_name) : name(full_name), marks(std::vector<int>()) {}
        Student(FullName full_name, std::vector<int> the_marks)
        : name(full_name), marks(the_marks) {
            calc_average();
        }

        std::string get_name() const {
            return name.get_full_name();
        }
        std::vector<int> get_marks() const {
            return marks;
        }
        double get_average() const {
            return average_mark;
        }

        void add_mark(int mark) {
            marks.push_back(mark);
            calc_average();
        }
        void add_marks(int* additional_marks, int size) {
            marks.insert(marks.end(), additional_marks, additional_marks + size);
            calc_average();
        }
        void set_name(FullName full_name) {
            name = full_name;
        }
    private:
        void calc_average() {
            int sum = 0;
            for (auto it = marks.begin(); it != marks.end(); ++it) {
                sum += *it;
            }
            average_mark = static_cast<double>(sum) / marks.size();
        }
        FullName name;
        std::vector<int> marks;
        double average_mark;
    };
}