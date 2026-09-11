#include "ResultManager.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>

// ==================== RESULT MANAGER ====================

ResultManager::ResultManager()
    : dbManager("students.dat", "students_backup.dat", "system_config.dat")
{
    load();
    initializeRollNumberCounters();
}

ResultManager::~ResultManager()
{
    save();
}

// ==================== INITIALIZATION ====================

void ResultManager::initializeRollNumberCounters()
{
    rollNumberCounters["PM"] = 0;
    rollNumberCounters["PE"] = 0;
    rollNumberCounters["CS"] = 0;

    for (size_t i = 0; i < students.size(); i++) {
        std::string roll = students[i].getRoll();
        if (InputValidator::isValidRollNumber(roll)) {
            std::string prefix = roll.substr(0, 2);
            std::string numberStr = roll.substr(2);
            int number = atoi(numberStr.c_str());
            
            if (rollNumberCounters.find(prefix) != rollNumberCounters.end()) {
                if (number > rollNumberCounters[prefix]) {
                    rollNumberCounters[prefix] = number;
                }
            }
        }
    }
}

// ==================== STUDENT MANAGEMENT ====================

bool ResultManager::addStudent(const std::string& name, const std::string& group,
                               double mark1, double mark2, double mark3,
                               const std::string& email, const std::string& phone)
{
    // Validate inputs
    if (!InputValidator::isValidName(name)) return false;
    if (!InputValidator::isValidMark(mark1) || !InputValidator::isValidMark(mark2) 
        || !InputValidator::isValidMark(mark3)) return false;
    
    // Generate roll number
    std::string rollNumber = generateRollNumber(group);
    
    // Create student
    Student s(name, rollNumber, group, mark1, mark2, mark3, email, phone);
    students.push_back(s);
    
    return save();
}

Student* ResultManager::getStudentByRoll(const std::string& roll)
{
    int index = findStudentByRoll(roll);
    if (index != -1) return &students[index];
    return nullptr;
}

const Student* ResultManager::getStudentByRoll(const std::string& roll) const
{
    std::string rollUpper = InputValidator::toUppercase(roll);
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getRoll() == rollUpper) {
            return &students[i];
        }
    }
    return nullptr;
}

// ==================== UPDATE OPERATIONS ====================

bool ResultManager::updateStudentName(const std::string& roll, const std::string& newName)
{
    Student* s = getStudentByRoll(roll);
    if (!s) return false;
    return s->setName(newName) && save();
}

bool ResultManager::updateStudentMarks(const std::string& roll, double m1, double m2, double m3)
{
    Student* s = getStudentByRoll(roll);
    if (!s) return false;
    
    if (!s->setMark(0, m1) || !s->setMark(1, m2) || !s->setMark(2, m3)) {
        return false;
    }
    return save();
}

bool ResultManager::updateStudentEmail(const std::string& roll, const std::string& email)
{
    Student* s = getStudentByRoll(roll);
    if (!s) return false;
    return s->setEmail(email) && save();
}

bool ResultManager::updateStudentPhone(const std::string& roll, const std::string& phone)
{
    Student* s = getStudentByRoll(roll);
    if (!s) return false;
    return s->setPhone(phone) && save();
}

bool ResultManager::updateStudentStatus(const std::string& roll, bool active)
{
    Student* s = getStudentByRoll(roll);
    if (!s) return false;
    s->setActive(active);
    return save();
}

bool ResultManager::deleteStudent(const std::string& roll)
{
    int index = findStudentByRoll(roll);
    if (index == -1) return false;
    
    students.erase(students.begin() + index);
    initializeRollNumberCounters();
    return save();
}

// ==================== SEARCH & FILTER ====================

std::vector<Student> ResultManager::searchByRoll(const std::string& roll) const
{
    std::vector<Student> results;
    std::string rollUpper = InputValidator::toUppercase(roll);
    
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getRoll() == rollUpper) {
            results.push_back(students[i]);
            break;
        }
    }
    return results;
}

std::vector<Student> ResultManager::searchByName(const std::string& name) const
{
    std::vector<Student> results;
    std::string nameLower = InputValidator::toLowercase(name);
    
    for (size_t i = 0; i < students.size(); i++) {
        std::string studentNameLower = InputValidator::toLowercase(students[i].getName());
        if (studentNameLower.find(nameLower) != std::string::npos) {
            results.push_back(students[i]);
        }
    }
    return results;
}

std::vector<Student> ResultManager::searchByGroup(const std::string& group) const
{
    std::vector<Student> results;
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getGroup() == group) {
            results.push_back(students[i]);
        }
    }
    return results;
}

std::vector<Student> ResultManager::searchByGrade(char grade) const
{
    std::vector<Student> results;
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getGrade() == grade) {
            results.push_back(students[i]);
        }
    }
    return results;
}

std::vector<Student> ResultManager::searchByStatus(bool active) const
{
    std::vector<Student> results;
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getIsActive() == active) {
            results.push_back(students[i]);
        }
    }
    return results;
}

std::vector<Student> ResultManager::getAllStudents() const
{
    return students;
}

// ==================== SORTING ====================

std::vector<Student> ResultManager::sortByPercentage(bool descending) const
{
    std::vector<Student> sorted = students;
    std::sort(sorted.begin(), sorted.end(),
        [descending](const Student& a, const Student& b) {
            if (descending)
                return a.getPercentage() > b.getPercentage();
            else
                return a.getPercentage() < b.getPercentage();
        });
    return sorted;
}

std::vector<Student> ResultManager::sortByName(bool ascending) const
{
    std::vector<Student> sorted = students;
    std::sort(sorted.begin(), sorted.end(),
        [ascending](const Student& a, const Student& b) {
            if (ascending)
                return a.getName() < b.getName();
            else
                return a.getName() > b.getName();
        });
    return sorted;
}

std::vector<Student> ResultManager::sortByRoll(bool ascending) const
{
    std::vector<Student> sorted = students;
    std::sort(sorted.begin(), sorted.end(),
        [ascending](const Student& a, const Student& b) {
            if (ascending)
                return a.getRoll() < b.getRoll();
            else
                return a.getRoll() > b.getRoll();
        });
    return sorted;
}

std::vector<Student> ResultManager::sortByGrade(bool descending) const
{
    std::vector<Student> sorted = students;
    std::sort(sorted.begin(), sorted.end(),
        [descending](const Student& a, const Student& b) {
            if (descending)
                return a.getGrade() > b.getGrade();
            else
                return a.getGrade() < b.getGrade();
        });
    return sorted;
}

// ==================== STATISTICS ====================

ResultManager::Statistics ResultManager::getStatistics() const
{
    Statistics stats = {0, 0, 0, 0, 0, 0.0f, 0.0f, 100.0f, nullptr};
    
    if (students.empty()) return stats;
    
    double totalPercentage = 0;
    stats.topStudent = (Student*)&students[0];
    
    for (size_t i = 0; i < students.size(); i++) {
        stats.totalStudents++;
        totalPercentage += students[i].getPercentage();
        
        if (students[i].getIsActive()) {
            stats.activeStudents++;
        } else {
            stats.inactiveStudents++;
        }
        
        if (students[i].getGrade() != 'F') {
            stats.passedStudents++;
        } else {
            stats.failedStudents++;
        }
        
        stats.gradeDistribution[students[i].getGrade()]++;
        
        if (students[i].getPercentage() > stats.topStudent->getPercentage()) {
            stats.topStudent = (Student*)&students[i];
        }
        
        if (students[i].getPercentage() > stats.highestPercentage) {
            stats.highestPercentage = students[i].getPercentage();
        }
        
        if (students[i].getPercentage() < stats.lowestPercentage) {
            stats.lowestPercentage = students[i].getPercentage();
        }
    }
    
    stats.averagePercentage = totalPercentage / stats.totalStudents;
    return stats;
}

std::map<std::string, ResultManager::Statistics> ResultManager::getGroupStatistics() const
{
    std::map<std::string, Statistics> groupStats;
    
    for (size_t i = 0; i < students.size(); i++) {
        std::string group = students[i].getGroup();
        
        if (groupStats.find(group) == groupStats.end()) {
            groupStats[group] = Statistics{0, 0, 0, 0, 0, 0.0f, 0.0f, 100.0f, nullptr};
        }
        
        Statistics& stats = groupStats[group];
        stats.totalStudents++;
        
        if (students[i].getIsActive()) {
            stats.activeStudents++;
        }
        
        if (students[i].getGrade() != 'F') {
            stats.passedStudents++;
        } else {
            stats.failedStudents++;
        }
    }
    
    return groupStats;
}

// ==================== ROLL NUMBER GENERATION ====================

std::string ResultManager::generateRollNumber(const std::string& group)
{
    std::string prefix;
    
    if (group == "Pre-Medical") {
        prefix = "PM";
    } else if (group == "Pre-Engineering") {
        prefix = "PE";
    } else {
        prefix = "CS";
    }
    
    int nextNumber = 1;
    while (true) {
        std::stringstream ss;
        ss << prefix << std::setw(3) << std::setfill('0') << nextNumber;
        std::string candidateRoll = ss.str();
        
        if (!isRollNumberExists(candidateRoll)) {
            rollNumberCounters[prefix] = nextNumber;
            return candidateRoll;
        }
        nextNumber++;
    }
}

bool ResultManager::isRollNumberExists(const std::string& roll) const
{
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getRoll() == roll && students[i].getIsActive()) {
            return true;
        }
    }
    return false;
}

// ==================== DATA PERSISTENCE ====================

bool ResultManager::save()
{
    return dbManager.saveStudents(students);
}

bool ResultManager::load()
{
    return dbManager.loadStudents(students);
}

bool ResultManager::createBackup()
{
    return dbManager.createBackup(students);
}

bool ResultManager::restoreFromBackup()
{
    return dbManager.restoreFromBackup(students);
}

// ==================== UTILITY ====================

int ResultManager::getActiveStudentCount() const
{
    int count = 0;
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getIsActive()) count++;
    }
    return count;
}

// ==================== PRIVATE HELPERS ====================

int ResultManager::findStudentByRoll(const std::string& roll)
{
    std::string rollUpper = InputValidator::toUppercase(roll);
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getRoll() == rollUpper) {
            return i;
        }
    }
    return -1;
}
