#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include "../common/common.h"

class Student : public NoCopyAble {
public:
    Student(std::string name, int age);
    virtual ~Student();

    void setName(std::string name);
    std::string getName() const;

    void setAge(int age);
    int getAge() const;

    bool operator<(const Student &student);

    friend std::ostream& operator<<(std::ostream& os, const Student& student);

private:
    std::string m_name;
    int m_age;
};


#endif