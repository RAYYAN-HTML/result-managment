#include "Student.h"
#include "Utils.h"
#include "ResultCalculator.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <cstdlib>

// ==================== STUDENT CLASS ====================

Student::Student() 
    : percentage(0), grade('F'), isActive(true)
{
    for (int i = 0; i < 3; i++)
        marks[i] = 0;
    admissionDate = getCurrentDate();
    lastModified = admissionDate;
}

Student::Student(std::string n, std::string r, std::string g, 
                 double m1, double m2, double m3,
                 std::string email, std::string phone)
    : name(InputValidator::capitalizeName(n)), roll(r), group(g), 
      email(email), phone(phone), isActive(true)
{
    marks[0] = m1;
    marks[1] = m2;
    marks[2] = m3;
    calculateResult();
    admissionDate = getCurrentDate();
    lastModified = admissionDate;
}

// ==================== GETTERS ====================

double Student::getMark(int index) const
{
    if (index >= 0 && index < 3)
        return marks[index];
    return 0;
}

double Student::getTotalMarks() const
{
    return marks[0] + marks[1] + marks[2];
}

// ==================== SETTERS ====================

bool Student::setName(const std::string &n)
{
    if (InputValidator::isValidName(n)) {
        name = InputValidator::capitalizeName(n);
        updateLastModified();
        return true;
    }
    return false;
}

void Student::setRoll(const std::string &r)
{
    roll = r;
    updateLastModified();
}

void Student::setGroup(const std::string &g)
{
    group = g;
    calculateResult();
    updateLastModified();
}

bool Student::setMark(int index, double value)
{
    if (index >= 0 && index < 3 && InputValidator::isValidMark(value)) {
        marks[index] = value;
        calculateResult();
        updateLastModified();
        return true;
    }
    return false;
}

bool Student::setEmail(const std::string &e)
{
    if (InputValidator::isValidEmail(e)) {
        email = e;
        updateLastModified();
        return true;
    }
    return false;
}

bool Student::setPhone(const std::string &p)
{
    if (InputValidator::isValidPhone(p)) {
        phone = p;
        updateLastModified();
        return true;
    }
    return false;
}

void Student::setActive(bool active)
{
    isActive = active;
    updateLastModified();
}

// ==================== CALCULATIONS ====================

void Student::calculateResult()
{
    percentage = ResultCalculator::calculatePercentage(marks);
    grade = ResultCalculator::calculateGrade(percentage);
}

// ==================== DISPLAY METHODS ====================

void Student::displayDetailed() const
{
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "                   STUDENT DETAILS\n";
    std::cout << std::string(60, '=') << "\n";
    std::cout << std::left << std::setw(20) << "Name:" << name << "\n";
    std::cout << std::setw(20) << "Roll Number:" << roll << "\n";
    std::cout << std::setw(20) << "Group:" << group << "\n";
    std::cout << std::setw(20) << "Admission Date:" << admissionDate << "\n";
    std::cout << std::setw(20) << "Last Modified:" << lastModified << "\n";
    std::cout << std::setw(20) << "Status:" << (isActive ? "Active" : "Inactive") << "\n";
    std::cout << std::setw(20) << "Email:" << (email.empty() ? "N/A" : email) << "\n";
    std::cout << std::setw(20) << "Phone:" << (phone.empty() ? "N/A" : phone) << "\n";

    std::cout << "\n" << std::string(60, '-') << "\n";
    std::cout << "                    MARKS DETAIL\n";
    std::cout << std::string(60, '-') << "\n";

    std::vector<std::string> subjects = getSubjects();
    for (int i = 0; i < 3; i++) {
        std::cout << std::left << std::setw(20) << subjects[i] + ":" << marks[i] << "/100\n";
    }

    std::cout << "\n" << std::string(60, '-') << "\n";
    std::cout << std::setw(20) << "Total Marks:" << getTotalMarks() << "/300\n";
    std::cout << std::setw(20) << "Percentage:" << std::fixed << std::setprecision(2) << percentage << "%\n";
    std::cout << std::setw(20) << "Grade:" << grade << "\n";
    std::cout << std::string(60, '=') << "\n";
}

void Student::displaySummary() const
{
    std::string status = isActive ? "A" : "I";
    std::cout << std::left << std::setw(25) << name
         << std::setw(15) << roll
         << std::setw(20) << group
         << std::setw(12) << std::fixed << std::setprecision(2) << percentage << "%"
         << std::setw(8) << grade
         << std::setw(10) << status
         << std::setw(15) << admissionDate << "\n";
}

// ==================== FILE OPERATIONS ====================

std::string Student::toFileString() const
{
    std::stringstream ss;
    ss << name << "|" << roll << "|" << group << "|"
       << marks[0] << "|" << marks[1] << "|" << marks[2] << "|"
       << percentage << "|" << grade << "|" << admissionDate << "|"
       << email << "|" << phone << "|"
       << (isActive ? "1" : "0") << "|" << lastModified;
    return ss.str();
}

Student Student::fromFileString(const std::string &data)
{
    Student s;
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(data);

    while (std::getline(stream, token, '|')) {
        tokens.push_back(token);
    }

    if (tokens.size() >= 13) {
        s.name = tokens[0];
        s.roll = tokens[1];
        s.group = tokens[2];
        s.marks[0] = atof(tokens[3].c_str());
        s.marks[1] = atof(tokens[4].c_str());
        s.marks[2] = atof(tokens[5].c_str());
        s.percentage = atof(tokens[6].c_str());
        s.grade = tokens[7][0];
        s.admissionDate = tokens[8];
        s.email = tokens[9];
        s.phone = tokens[10];
        s.isActive = (tokens[11] == "1");
        s.lastModified = tokens[12];
    }

    return s;
}

// ==================== PRIVATE HELPER METHODS ====================

std::vector<std::string> Student::getSubjects() const
{
    std::vector<std::string> subjects;
    if (group == "Pre-Medical") {
        subjects.push_back("Biology");
        subjects.push_back("Chemistry");
        subjects.push_back("Physics");
    }
    else if (group == "Pre-Engineering") {
        subjects.push_back("Mathematics");
        subjects.push_back("Chemistry");
        subjects.push_back("Physics");
    }
    else {
        subjects.push_back("Computer");
        subjects.push_back("Mathematics");
        subjects.push_back("Physics");
    }
    return subjects;
}

void Student::updateLastModified()
{
    lastModified = getCurrentDate();
}

std::string Student::getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return std::string(buffer);
}
