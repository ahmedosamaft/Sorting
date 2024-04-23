#ifndef DATASTRUCTURES_STUDENT_H
#define DATASTRUCTURES_STUDENT_H

#include <string>

namespace Faculty {

    class Student {
        std::string id;
        std::string name;
        double gpa;
    public:
        Student();

        Student(std::string id, std::string name, double gpa);

        const std::string &getId() const;

        void setId(const std::string &id);

        const std::string &getName() const;

        void setName(const std::string &name);

        double getGpa() const;

        void setGpa(double gpa);

        bool operator<(const Student &) const;

        std::string toString() const;
    };

}

#endif
