#define _CRT_SECURE_NO_WARNINGS
#include "Student.h"
#include <cstring>
#include <iomanip>

using namespace std;

// === Subject ===
Subject::Subject() {
    cout << "Subject: конструктор по умолчанию\n";
    name = new char[1]; name[0] = '\0';
    mark = 0;
}

Subject::Subject(const char* n, int m) {
    cout << "Subject: конструктор с параметрами\n";
    name = new char[strlen(n) + 1];
    strcpy(name, n);
    mark = m;
}

Subject::Subject(const Subject& other) {
    cout << "Subject: конструктор копирования\n";
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    mark = other.mark;
}

Subject::~Subject() {
    cout << "Subject: деструктор для " << (name ? name : "пустой") << endl;
    delete[] name;
}

Subject& Subject::operator=(const Subject& other) {
    if (this != &other) {
        delete[] name;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        mark = other.mark;
    }
    return *this;
}

// === Student ===
void Student::calcAvg() {
    if (subjectCount == 0) { avgMark = 0; return; }
    int sum = 0;
    for (int i = 0; i < subjectCount; i++) sum += subjects[i].mark;
    avgMark = (double)sum / subjectCount;
}

Student::Student() {
    cout << "Student: конструктор по умолчанию\n";
    fio = new char[1]; fio[0] = '\0';
    group = new char[1]; group[0] = '\0';
    subjects = nullptr;
    subjectCount = 0;
    avgMark = 0;
}

Student::Student(const char* f, const char* g, Subject* subs, int count) {
    cout << "Student: конструктор с параметрами\n";
    fio = new char[strlen(f) + 1]; strcpy(fio, f);
    group = new char[strlen(g) + 1]; strcpy(group, g);
    subjectCount = count;
    subjects = new Subject[count];
    for (int i = 0; i < count; i++) {
        subjects[i] = subs[i];
    }
    calcAvg();
}

Student::Student(const Student& other) {
    cout << "Student: конструктор копирования\n";
    fio = new char[strlen(other.fio) + 1]; strcpy(fio, other.fio);
    group = new char[strlen(other.group) + 1]; strcpy(group, other.group);
    subjectCount = other.subjectCount;
    subjects = new Subject[subjectCount];
    for (int i = 0; i < subjectCount; i++) {
        subjects[i] = other.subjects[i];
    }
    avgMark = other.avgMark;
}

Student::~Student() {
    cout << "Student: деструктор для " << (fio ? fio : "пустой") << endl;
    delete[] fio;
    delete[] group;
    delete[] subjects;
}

const char* Student::getFio() const { return fio; }
const char* Student::getGroup() const { return group; }
double Student::getAvgMark() const { return avgMark; }

bool Student::hasTwo() const {
    for (int i = 0; i < subjectCount; i++) {
        if (subjects[i].mark == 2) return true;
    }
    return false;
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        delete[] fio; delete[] group; delete[] subjects;
        fio = new char[strlen(other.fio) + 1]; strcpy(fio, other.fio);
        group = new char[strlen(other.group) + 1]; strcpy(group, other.group);
        subjectCount = other.subjectCount;
        subjects = new Subject[subjectCount];
        for (int i = 0; i < subjectCount; i++) subjects[i] = other.subjects[i];
        avgMark = other.avgMark;
    }
    return *this;
}

ostream& operator<<(ostream& os, const Student& s) {
    os << "ФИО: " << s.fio << "\nГруппа: " << s.group << "\nПредметы и оценки:\n";
    for (int i = 0; i < s.subjectCount; i++) {
        os << "  " << s.subjects[i].name << " — " << s.subjects[i].mark << "\n";
    }
    os << fixed << setprecision(2) << "Средний балл: " << s.avgMark << "\n";
    return os;
}

istream& operator>>(istream& is, Student& s) {
    char buffer[256];

    cout << "ФИО: "; is.getline(buffer, 256);
    delete[] s.fio; s.fio = new char[strlen(buffer) + 1]; strcpy(s.fio, buffer);

    cout << "Номер группы: "; is.getline(buffer, 256);
    delete[] s.group; s.group = new char[strlen(buffer) + 1]; strcpy(s.group, buffer);

    cout << "Количество предметов: ";
    int n; is >> n; is.ignore();
    if (n <= 0) throw BadInputException("Количество предметов должно быть > 0");

    delete[] s.subjects;
    s.subjects = new Subject[n];
    s.subjectCount = n;

    cout << "Ввод предметов и оценок:\n";
    for (int i = 0; i < n; i++) {
        cout << "  Предмет " << (i + 1) << ": ";
        is.getline(buffer, 256);
        cout << "  Оценка (2-5): ";
        int mark; is >> mark; is.ignore();
        if (mark < 2 || mark > 5) throw BadInputException("Оценка должна быть от 2 до 5");
        s.subjects[i] = Subject(buffer, mark);
    }

    s.calcAvg();
    return is;
}