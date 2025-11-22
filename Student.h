#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <windows.h>

class Subject {
public:
    char* name;      // Название предмета
    int mark;        // Оценка (2-5)

    Subject();
    Subject(const char* n, int m);
    Subject(const Subject& other);
    ~Subject();
    Subject& operator=(const Subject& other);
};

class Student {
private:
    char* fio;
    char* group;
    Subject* subjects;
    int subjectCount;
    double avgMark;

    void calcAvg();

public:
    Student();
    Student(const char* f, const char* g, Subject* subs, int count);
    Student(const Student& other);
    ~Student();

    Student& operator=(const Student& other);

    // Геттеры
    const char* getFio() const;
    const char* getGroup() const;
    double getAvgMark() const;
    bool hasTwo() const;

    // Перегрузка ввода-вывода
    friend std::ostream& operator<<(std::ostream& os, const Student& s);
    friend std::istream& operator>>(std::istream& is, Student& s);
};

// Исключения
class BadInputException {
public:
    const char* msg;
    BadInputException(const char* m) : msg(m) {}
};

class FileErrorException {
public:
    const char* msg;
    FileErrorException(const char* m) : msg(m) {}
};

#endif