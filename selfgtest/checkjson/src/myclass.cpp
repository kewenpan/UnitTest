//
// Created by blithepan on 2020/8/13.
//

#pragma once

#include <string>

class my_class
{
public:
    my_class(const std::string& name, int age)
    {
        m_age = age;
        m_name = name;
    }

public:
    int get_age() { return m_age; }
    std::string get_name() { return m_name; }

private:
    int m_age;
    std::string m_name;
};