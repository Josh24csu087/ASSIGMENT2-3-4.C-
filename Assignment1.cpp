// Assignment 2 - Classes, Encapsulation, and Polymorphism
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

class Person {
protected:
    string name, id, contact;
    int age;
public:
    Person(string n, int a, string i, string c) : name(n), age(a), id(i), contact(c) {
        if (n.empty()) name = "NoName";
        if (a <= 0 || a > 120) age = 18;
    }
    virtual void displayDetails() { cout << "Name: " << name << ", ID: " << id << endl; }
    virtual double calculatePayment() { return 0; }
    virtual ~Person() {}
};

class Student : public Person {
    string enrollmentDate, program;
    double gpa;
public:
    Student(string n, int a, string i, string c, string e, string p, double g)
        : Person(n, a, i, c), enrollmentDate(e), program(p), gpa(g) {
        if (g < 0.0 || g > 4.0) gpa = 0.0;
    }
    void displayDetails() override {
        cout << "Student: " << name << ", Program: " << program << ", GPA: " << gpa << endl;
    }
    double calculatePayment() override { return 1000; }
};

class Professor : public Person {
    string department, specialization, hireDate;
public:
    Professor(string n, int a, string i, string c, string d, string s, string h)
        : Person(n, a, i, c), department(d), specialization(s), hireDate(h) {}
    void displayDetails() override {
        cout << "Professor: " << name << ", Specialization: " << specialization << ", Department: " << department << endl;
    }
    double calculatePayment() override { return 5000; }
};

class Course {
    string code, title, description;
    int credits;
public:
    Course(string co, string t, int cr, string d="") : code(co), title(t), credits(cr), description(d) {
        if (credits <= 0) credits = 1;
    }
};

class Department {
    string name, location;
    double budget;
public:
    Department(string n, string l, double b) : name(n), location(l), budget(b) {}
};

class GradeBook {
    map<string, double> grades;
public:
    void addGrade(string sid, double g) { grades[sid] = g; }
    double average() {
        double sum = 0;
        for (auto &g : grades) sum += g.second;
        return grades.empty() ? 0 : sum / grades.size();
    }
    double highest() {
        double high = 0;
        for (auto &g : grades) if (g.second > high) high = g.second;
        return high;
    }
    vector<string> failing() {
        vector<string> fail;
        for (auto &g : grades) if (g.second < 50) fail.push_back(g.first);
        return fail;
    }
};

class EnrollmentManager {
    map<string, vector<string>> enrollments;
public:
    void enroll(string sid, string cid) { enrollments[cid].push_back(sid); }
    void drop(string sid, string cid) {
        auto &v = enrollments[cid];
        v.erase(remove(v.begin(), v.end(), sid), v.end());
    }
    int count(string cid) { return enrollments[cid].size(); }
};

int main() {
    Student s("Ali", 20, "S01", "ali@uni.com", "2023", "CS", 3.5);
    Professor p("Dr. Zed", 50, "P01", "zed@uni.com", "CS", "AI", "2010");

    s.displayDetails();
    p.displayDetails();

    cout << "Student payment: " << s.calculatePayment() << endl;
    cout << "Professor payment: " << p.calculatePayment() << endl;

    GradeBook gb;
    gb.addGrade("S01", 85);
    gb.addGrade("S02", 60);
    gb.addGrade("S03", 45);
    cout << "Average: " << gb.average() << ", Highest: " << gb.highest() << endl;

    vector<string> fails = gb.failing();
    for (string id : fails) cout << "Failing student ID: " << id << endl;

    EnrollmentManager em;
    em.enroll("S01", "CS101");
    cout << "Enrolled count in CS101: " << em.count("CS101") << endl;

    return 0;
}
