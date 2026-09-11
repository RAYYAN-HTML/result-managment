#ifndef RESULT_MANAGER_H
#define RESULT_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include "Student.h"
#include "DatabaseManager.h"
#include "ResultCalculator.h"

class ResultManager
{
private:
    std::vector<Student> students;
    DatabaseManager dbManager;
    std::map<std::string, int> rollNumberCounters; // PM/PE/CS -> next number

    // Private helper methods
    int findStudentByRoll(const std::string& roll);
    void initializeRollNumberCounters();
    void updateLastModified();

public:
    ResultManager();
    ~ResultManager();

    // ===== STUDENT MANAGEMENT =====
    
    // Add new student
    bool addStudent(const std::string& name, const std::string& group,
                    double mark1, double mark2, double mark3,
                    const std::string& email = "", const std::string& phone = "");
    
    // Get student by roll number
    Student* getStudentByRoll(const std::string& roll);
    const Student* getStudentByRoll(const std::string& roll) const;
    
    // Update student information
    bool updateStudentName(const std::string& roll, const std::string& newName);
    bool updateStudentMarks(const std::string& roll, double m1, double m2, double m3);
    bool updateStudentEmail(const std::string& roll, const std::string& email);
    bool updateStudentPhone(const std::string& roll, const std::string& phone);
    bool updateStudentStatus(const std::string& roll, bool active);
    
    // Delete student
    bool deleteStudent(const std::string& roll);
    
    // ===== SEARCH & FILTER =====
    
    std::vector<Student> searchByRoll(const std::string& roll) const;
    std::vector<Student> searchByName(const std::string& name) const;
    std::vector<Student> searchByGroup(const std::string& group) const;
    std::vector<Student> searchByGrade(char grade) const;
    std::vector<Student> searchByStatus(bool active) const;
    std::vector<Student> getAllStudents() const;
    
    // ===== SORTING =====
    
    std::vector<Student> sortByPercentage(bool descending = true) const;
    std::vector<Student> sortByName(bool ascending = true) const;
    std::vector<Student> sortByRoll(bool ascending = true) const;
    std::vector<Student> sortByGrade(bool descending = true) const;
    
    // ===== STATISTICS =====
    
    struct Statistics {
        int totalStudents;
        int activeStudents;
        int inactiveStudents;
        int passedStudents;
        int failedStudents;
        float averagePercentage;
        float highestPercentage;
        float lowestPercentage;
        Student* topStudent;
        std::map<char, int> gradeDistribution;
    };
    
    Statistics getStatistics() const;
    std::map<std::string, Statistics> getGroupStatistics() const;
    
    // ===== ROLL NUMBER GENERATION =====
    
    std::string generateRollNumber(const std::string& group);
    bool isRollNumberExists(const std::string& roll) const;
    
    // ===== DATA PERSISTENCE =====
    
    bool save();
    bool load();
    bool createBackup();
    bool restoreFromBackup();
    
    // ===== UTILITY =====
    
    int getStudentCount() const { return students.size(); }
    int getActiveStudentCount() const;
    bool isEmpty() const { return students.empty(); }
};

#endif // RESULT_MANAGER_H
