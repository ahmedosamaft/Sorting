#include <fstream>
#include <iostream>
#include <string>
#include <functional>
#include <chrono>
#include "Student.h"
#include "Sorting.h"

const std::string STUDENTS_FILE_PATH = R"(G:\Assignments\DataStructures\students.txt)";

int total_students = 0;
Faculty::Student *students;

void readStudentsData();

void printStudents(std::ostream &fout = std::cout);

void runAlgorithm(std::string algorithmName,
                  std::function<void()> action,
                  std::ostream &fout = std::cout);

template<typename T>
void runAllSortingAlgorithm(std::function<bool(T &, T &)> cmp, std::string fileDir);

int main() {
    readStudentsData();
    runAllSortingAlgorithm<Faculty::Student>([](auto &student_a, auto &student_b) -> bool {
        return student_a.getGpa() < student_b.getGpa();
    }, "SortedByGPA.txt");
    runAllSortingAlgorithm<Faculty::Student>(
            [](auto &student_a, auto &student_b) -> bool { return student_a < student_b; }, "SortedByName.txt");
    delete[] students;
}

void readStudentsData() {
    std::ifstream fin(STUDENTS_FILE_PATH);
    if (fin.bad() || fin.fail() || !fin.is_open()) {
        std::cerr << "Fail to open students file\n";
        exit(1);
    }
    fin >> total_students;
    students = new Faculty::Student[total_students];
    fin.ignore(); // To skip the new line character
    for (int i = 0; i < total_students; ++i) {
        std::string student_name;
        std::string student_id;
        std::string student_gpa; // Declared as string to use getline()
        std::getline(fin, student_name);
        std::getline(fin, student_id);
        std::getline(fin, student_gpa);
        students[i] = Faculty::Student(student_id, student_name, std::stod(student_gpa));
    }
    fin.close();
}

void printStudents(std::ostream &fout) {
    for (int i = 0; i < total_students; ++i) {
        fout << students[i].toString() << std::endl;
    }
    std::cout << "\n";
}

void runAlgorithm(std::string algorithmName,
                  std::function<void()> action,
                  std::ostream &fout) {
    fout << "Algorithm: " << algorithmName << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    action();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    fout << "Running Time: " << duration.count() << " microseconds\n";
    printStudents(fout);
}

template<typename T>
void runAllSortingAlgorithm(std::function<bool(T &, T &)> cmp, std::string fileDir) {
    Algorithms::Sorting<T> sorter;
    std::ofstream fout(fileDir);
    std::function<void()> fn = [&]() { sorter.InsertionSort(students, total_students, cmp); };
    runAlgorithm("Insertion Sort", fn, fout);
    fn = [&]() { sorter.SelectionSort(students, total_students, cmp); };
    runAlgorithm("Selection Sort", fn, fout);
    fn = [&]() { sorter.BubbleSort(students, total_students, cmp); };
    runAlgorithm("Bubble Sort", fn, fout);
    fn = [&]() { sorter.MergeSort(students, total_students, cmp); };
    runAlgorithm("Merge Sort", fn, fout);
    fn = [&]() { sorter.QuickSort(students, total_students, cmp); };
    runAlgorithm("Quick Sort", fn, fout);
    fn = [&]() { sorter.ShellSort(students, total_students, cmp); };
    runAlgorithm("Shell Sort", fn, fout);
    fout.close();
}
