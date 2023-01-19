#pragma once
#include <iostream>
#include <string>
#include <tuple>

namespace students_group {
    class FullName
    {
    public:
        FullName() = default;

        FullName(std::string fn, std::string mn, std::string ln)
        : first_name(fn), middle_name(mn), last_name(ln)
        {}

        FullName(std::string fn, std::string ln)
        : FullName(fn, "", ln)
        {}

        FullName(const FullName& full_name) {
            first_name = full_name.first_name;
            middle_name = full_name.middle_name;
            last_name = full_name.last_name;
        }

        bool operator==(const FullName& other) const {
            return std::tie(first_name, middle_name, last_name) == 
                    std::tie(other.first_name, other.middle_name, other.last_name);
        }

        bool operator!=(const FullName& other) const {
            return !(*this != other);
        }

        std::string get_first_name() const {
            return first_name;
        }

        std::string get_middle_name() const {
            return middle_name;
        }

        std::string get_last_name() const {
            return last_name;
        }

        std::string get_full_name() const {
            return first_name + " " + middle_name + " " + last_name;
        }

        void set_first_name(std::string fn) {
            first_name = fn;
        }

        void set_middle_name(std::string mn) {
            middle_name = mn;
        }

        void set_last_name(std::string ln) {
            last_name = ln;
        }
    private:
        std::string first_name;
        std::string middle_name;
        std::string last_name;
    };  
}
