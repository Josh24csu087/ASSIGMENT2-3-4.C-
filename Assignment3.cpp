#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <map>


class UniversitySystemException : public std::exception {
public:
    UniversitySystemException(const std::string& message) : message_(message) {}
    const char* what() const noexcept override { return message_.c_str(); }
protected:
    std::string message_;
};

class EnrollmentException : public UniversitySystemException {
public:
    EnrollmentException(const std::string& message) : UniversitySystemException(message) {}
};


class Person {
public:
    Person(const std::string& name) : name_(name) {}
    std::string getName() const { return name_; }
private:
    std::string name_;
};

class Student : public Person {
public:
    Student(const std::string& name, double gpa) : Person(name), gpa_(gpa) {
        if (gpa < 0.0 || gpa > 4.0) {
            throw UniversitySystemException("Invalid GPA");
        }
    }
private:
    double gpa_;
};


class EnrollmentManager {
public:
    void enrollStudent(int studentId, int courseId) {
        if (isCourseFull(courseId)) {
            throw EnrollmentException("Course Full");
        }
        enrollments_[courseId].push_back(studentId);
        std::cout << "Enrolled " << studentId << " in " << courseId << std::endl;
    }

    bool isCourseFull(int courseId) { return enrollments_[courseId].size() >= 3; } // Simple check
private:
    std::map<int, std::vector<int>> enrollments_; // courseId -> studentIds
};


class UniversitySystem {
public:
    UniversitySystem() : enrollmentManager_() {}

    void enroll(int studentId, int courseId) {
        try {
            enrollmentManager_.enrollStudent(studentId, courseId);
        } catch (const EnrollmentException& e) {
            std::cerr << "Enrollment Error: " << e.what() << std::endl;
            logException(e.what());
        } catch (const std::exception& e) {
            std::cerr << "Std Error: " << e.what() << std::endl;
            logException(e.what());
        } catch (...) {
            std::cerr << "Unknown Error" << std::endl;
            logException("Unknown");
        }
    }

    void addStudent(const std::string& name, double gpa) {
        students_.push_back(Student(name, gpa));
    }

private:
    EnrollmentManager enrollmentManager_;
    std::vector<Student> students_;

    void logException(const std::string& message) {
        std::ofstream log("log.txt", std::ios::app);
        if (log.is_open()) {
            log << message << std::endl;
            log.close();
        }
    }
};

int main() {
    UniversitySystem uni;
    uni.addStudent("Alice", 3.5);
    uni.addStudent("Bob", 3.9);

    uni.enroll(1, 101);
    uni.enroll(2, 101);
    uni.enroll(3,101);
    uni.enroll(4,101); 

    return 0;
}