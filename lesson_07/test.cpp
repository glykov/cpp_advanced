#include <iostream>
#include "03_students_group.h"

namespace sg = students_group;

int main()
{
    sg::StudentsGroup students;
    students.AddStudent(sg::Student(sg::FullName("Ivan", "Ivanov"), {5, 4, 3, 4, 5}));
    students.AddStudent(sg::Student(sg::FullName("Petr", "Petrovich", "Petrov"), {5, 4, 5, 4, 5}));
    std::cout << students.GetAllInfo() << std::endl;
    students.Save();

    sg::StudentsGroup students1;
    students1.Open();
    std::cout << students1.GetAllInfo() << std::endl;

    return 0;
}