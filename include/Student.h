#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Student
{
private:
    std::string name;
    std::string roll;
    std::string group;
    double marks[3];
    float percentage;
    char grade;
    std::string admissionDate;
    std::string email;
    std::string phone;
    bool isActive;
    std::string lastModified;

    // Helper methods
    std::string getCurrentDate();
    void updateLastModified();
    std::vector<std::string> getSubjects() const;

public:
    // Constructor
    Student();
    Student(std::string n, std::string r, std::string g, 
            double m1, double m2, double m3,
            std::string email = "", std::string phone = "");

    // Getters
    std::string getName() const { return name; }
    std::string getRoll() const { return roll; }
    std::string getGroup() const { return group; }
    float getPercentage() const { return percentage; }
    char getGrade() const { return grade; }
    std::string getEmail() const { return email; }
    std::string getPhone() const { return phone; }
    std::string getAdmissionDate() const { return admissionDate; }
    std::string getLastModified() const { return lastModified; }
    bool getIsActive() const { return isActive; }
    
    double getMark(int index) const;
    double getTotalMarks() const;

    // Setters with validation
    bool setName(const std::string &n);
    void setRoll(const std::string &r);
    void setGroup(const std::string &g);
    bool setMark(int index, double value);
    bool setEmail(const std::string &e);
    bool setPhone(const std::string &p);
    void setActive(bool active);

    // Result calculation
    void calculateResult();

    // Display methods
    void displayDetailed() const;
    void displaySummary() const;

    // File operations
    std::string toFileString() const;
    static Student fromFileString(const std::string &data);
};

#endif // STUDENT_H
