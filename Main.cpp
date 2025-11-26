#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include "Student.h"

using namespace std;

// Динамический список студентов
struct StudentList {
    Student** arr;
    int size, capacity;

    StudentList() : size(0), capacity(10) {
        arr = new Student * [capacity];
    }
    ~StudentList() {
        for (int i = 0; i < size; i++) delete arr[i];
        delete[] arr;
    }

    void add(Student* s, int pos = -1) {
        if (size == capacity) {
            capacity *= 2;
            Student** temp = new Student * [capacity];
            for (int i = 0; i < size; i++) temp[i] = arr[i];
            delete[] arr; arr = temp;
        }
        if (pos == -1 || pos >= size) {
            arr[size++] = s;
        }
        else {
            for (int i = size; i > pos; i--) arr[i] = arr[i - 1];
            arr[pos] = s;
            size++;
        }
    }

    void remove(int idx) {
        if (idx < 0 || idx >= size) throw "Неверный индекс";
        delete arr[idx];
        for (int i = idx; i < size - 1; i++) arr[i] = arr[i + 1];
        size--;
    }

    void sortByAvg() {
        for (int i = 0; i < size - 1; i++)
            for (int j = i + 1; j < size; j++)
                if (arr[i]->getAvgMark() > arr[j]->getAvgMark())
                    swap(arr[i], arr[j]);
    }

    void printAll() const {
        if (size == 0) { cout << "Список пуст.\n"; return; }
        for (int i = 0; i < size; i++) {
            cout << "\n=== Студент " << (i + 1) << " ===\n";
            cout << *arr[i] << "\n";
        }
    }

    void printWithTwo() const {
        cout << "\nСтуденты с хотя бы одной двойкой:\n";
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (arr[i]->hasTwo()) {
                cout << arr[i]->getFio() << " (группа " << arr[i]->getGroup() << ")\n";
                found = true;
            }
        }
        if (!found) cout << "Таких студентов нет.\n";
    }
};

// ЧАСТЬ 2 — строки с двузначными числами (без assert!)
void part2() {
    cout << "\n=== Часть 2: строки с двузначными числами ===\n";
    ifstream f("input.txt");
    if (!f) {
        cout << "Файл input.txt не найден! Положи его в папку с .exe\n";
        return;
    }

    char line[2048];
    bool foundAny = false;

    while (f.getline(line, sizeof(line))) {
        bool hasTwoDigit = false;
        for (const char* p = line; *p; ++p) {
            unsigned char ch = static_cast<unsigned char>(*p);
            if (ch >= '0' && ch <= '9' && *(p + 1) != '\0') {
                unsigned char next = static_cast<unsigned char>(*(p + 1));
                if (next >= '0' && next <= '9') {
                    int num = (ch - '0') * 10 + (next - '0');
                    if (num >= 10 && num <= 99) {
                        char prev = (p == line) ? ' ' : *(p - 1);
                        unsigned char uprev = static_cast<unsigned char>(prev);
                        unsigned char unext = static_cast<unsigned char>(*(p + 2));
                        if ((uprev < '0' || uprev > '9') &&
                            (*(p + 2) == '\0' || unext < '0' || unext > '9')) {
                            hasTwoDigit = true;
                            break;
                        }
                    }
                }
            }
        }
        if (hasTwoDigit) {
            cout << line << "\n";
            foundAny = true;
        }
    }
    f.close();
    if (!foundAny) cout << "Двузначные числа не найдены.\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    StudentList list;
    int choice = -1, pos;

    cout << "Лабораторная работа №2 — Вариант 3\n\n";

    while (choice != 0) {
        system("cls");
        cout << "=============================\n";
        cout << "            МЕНЮ            \n";
        cout << "=============================\n";
        cout << "1. Добавить студента\n";
        cout << "2. Вставить на позицию\n";
        cout << "3. Удалить студента\n";
        cout << "4. Редактировать студента\n";
        cout << "5. Показать всех\n";
        cout << "6. Студенты с двойкой\n";
        cout << "7. Отсортировать по среднему баллу\n";
        cout << "8. ЧАСТЬ 2 — строки с двузначными числами\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";
        cin >> choice;
        cin.ignore();

        try {
            switch (choice) {
            case 1: {
                Student* s = new Student();
                cin >> *s;
                list.add(s);
                cout << "Студент добавлен!\n";
                break;
            }
            case 2: {
                Student* s = new Student();
                cin >> *s;
                cout << "Позиция (0 — в начало): ";
                cin >> pos;
                list.add(s, pos);
                break;
            }
            case 3: {
                list.printAll();
                cout << "Номер для удаления (1-" << list.size << "): ";
                cin >> pos;
                list.remove(pos - 1);
                cout << "Удалено!\n";
                break;
            }
            case 4: {
                list.printAll();
                cout << "Номер для редактирования (1-" << list.size << "): ";
                cin >> pos;
                cin >> *list.arr[pos - 1];
                cout << "Обновлено!\n";
                break;
            }
            case 5: list.printAll(); break;
            case 6: list.printWithTwo(); break;
            case 7: list.sortByAvg(); cout << "Отсортировано!\n"; list.printAll(); break;
            case 8: part2(); break;
            case 0: cout << "До свидания!\n"; break;
            default: cout << "Неверный пункт!\n"; break;
            }
        }
        catch (...) {
            cout << "Произошла ошибка!\n";
        }

        if (choice != 0) {
            cout << "\nНажмите любую клавишу...";
            _getch();
        }
    }

    return 0;
}