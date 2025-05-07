#include <iostream>
#include <string>
using namespace std;


class Person {
protected:
    string name, id;
    int age;
public:
    Person(string n, int a, string i) : name(n), age(a), id(i) {}
    virtual void display() {
        cout << "Name: " << name << ", ID: " << id << endl;
    }
    virtual double calculatePayment() { return 0; }
};


class Professor : public Person {
public:
    Professor(string n, int a, string i) : Person(n, a, i) {}
    void display() override {
        cout << "Professor: " << name << endl;
    }
    double calculatePayment() override {
        return 80000;
    }
};


class Student : public Person {
protected:
    double gpa;
public:
    Student(string n, int a, string i, double g) : Person(n, a, i), gpa(g) {}
    void display() override {
        cout << "Student: " << name << ", GPA: " << gpa << endl;
    }
    double calculatePayment() override {
        return 1000;
    }
};

// GraduateStudent inherits Student
class GraduateStudent : public Student {
    Professor* advisor;
    bool isTA;
public:
    GraduateStudent(string n, int a, string i, double g, Professor* adv, bool ta)
        : Student(n, a, i, g), advisor(adv), isTA(ta) {}

    void display() override {
        cout << "Graduate Student: " << name << ", GPA: " << gpa << endl;
        if (advisor) {
            cout << "Advisor: " << advisor->name << endl;
        }
        cout << (isTA ? "Role: TA" : "Role: None") << endl;
    }

    double calculatePayment() override {
        return isTA ? 2000 : 1000;
    }
};

int main() {
    Professor prof("Dr. Smith", 50, "P01");
    GraduateStudent grad("Ali", 24, "S01", 3.7, &prof, true);

    prof.display();
    cout << "Professor Salary: " << prof.calculatePayment() << endl;

    grad.display();
    cout << "Graduate Student Payment: " << grad.calculatePayment() << endl;

    return 0;
}
