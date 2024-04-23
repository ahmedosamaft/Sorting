#include "Student.h"

namespace Faculty {
    Student::Student(std::string id, std::string name, double gpa) : id(std::move(id)), name(std::move(name)),
                                                                     gpa(gpa) {}

    Student::Student() {}

    bool Student::operator<(const Student &rhs) const {
        return name < rhs.name;
    }

    const std::string &Student::getId() const {
        return id;
    }

    void Student::setId(const std::string &id) {
        Student::id = id;
    }

    const std::string &Student::getName() const {
        return name;
    }

    void Student::setName(const std::string &name) {
        Student::name = name;
    }

    double Student::getGpa() const {
        return gpa;
    }

    void Student::setGpa(double gpa) {
        Student::gpa = gpa;
    }

    std::string Student::toString() const {
        return "Id=" + id + ", Name=" + name + ", Gpa=" + std::to_string(gpa);
    }

}