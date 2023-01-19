#pragma once
#include <string>
#include "01_full_name.h"

namespace sg = students_group; 


class IRepository 
{
public:
    virtual void Open() = 0; // бинарная десериализация в файл 
    virtual void Save() = 0; // бинарная сериализация в файл
};

class IMethods 
{
public:
    virtual double GetAverageScore(const sg::FullName& name) = 0;
    virtual std::string GetAllInfo(const sg::FullName& name) = 0;
    virtual std::string GetAllInfo() = 0;
};