#pragma once
#include <algorithm>
#include <fstream>
#include "02_student.h"
#include "interfaces.h"

namespace students_group
{
    class StudentsGroup : public IRepository, IMethods
    {
    public:
        StudentsGroup() : group(std::vector<Student>()) {}

        void AddStudent(Student student) {
             group.push_back(student);
        }

        double GetAverageScore(const FullName& name) override {
            for (auto it = group.begin(); it != group.end(); ++it) {
                if (it->get_name() == name.get_full_name()) {
                    return it->get_average();
                }
            }
            return -1.0;
        }

        std::string GetAllInfo(const FullName& name) override {
            for (auto it = group.begin(); it != group.end(); ++it) {
                if (it->get_name() == name.get_full_name()) {
                    std::string res = "";
                    res += it->get_name();
                    res += ", average mark: ";
                    res += std::to_string(it->get_average());
                    return res;
                }
            }
            
            return std::string("No such student");
        }

        std::string GetAllInfo() override {
            std::string res = "";
            for (auto it = group.begin(); it != group.end(); ++it) {
                res += it->get_name();
                res += ", average mark: ";
                res += std::to_string(it->get_average());
                res += "\n";
                
            }
            return res;
        }

        void Open() override {
            std::ifstream fin("students.bin", std::ios::binary);
            if (!fin) {
                std::cout << "Error reading file students.bin\n";
                return;
            } 
            size_t len = 0;
            fin.read(reinterpret_cast<char*>(&len), sizeof(len));
            std::cout << len << std::endl;
            group.resize(len);
            fin.read(reinterpret_cast<char*>(group.data()), len * sizeof(Student));
            fin.close();
        } 
        void Save() override {
            std::ofstream fout("students.bin", std::ios::binary);
            size_t len = group.size();
            fout.write(reinterpret_cast<char*>(&len), sizeof(len));
            fout.write(reinterpret_cast<char*>(&group), len * sizeof(Student));
            fout.close();
        } 
    private:
        std::vector<Student> group;
    };
}