#include "Student.h"

Student::Student(std::string name, int age) : m_name(name), m_age(age) {}

Student::~Student(){}

void Student::setName(std::string name) {
    m_name = name;
}

std::string Student::getName() const {
    return m_name;
}

void Student::setAge(int age) {
    if (age >= 0) {
        m_age = age;
    } else {
        std::cerr << "Invalid age. Age must be non-negative." << std::endl;
    }
}

int Student::getAge() const {
    return m_age;
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << "Name: " << student.m_name << ", Age: " << student.m_age;
    return os;
}

bool Student::operator<(const Student& student) {
    return m_age < student.m_age;
}

