#include "DatabaseManager.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <map>
#include <sstream>
#include <cstdlib>

// ==================== DATABASE MANAGER ====================

DatabaseManager::DatabaseManager(const std::string& dataFileName,
                                 const std::string& backupFileName,
                                 const std::string& configFileName)
    : dataFile(dataFileName), backupFile(backupFileName), configFile(configFileName)
{
}

// ==================== STUDENT DATA OPERATIONS ====================

bool DatabaseManager::loadStudents(std::vector<Student>& students)
{
    std::ifstream file(dataFile.c_str());
    if (!file.is_open()) {
        return false;
    }

    students.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            try {
                students.push_back(Student::fromFileString(line));
            } catch (...) {
                // Skip invalid lines
            }
        }
    }
    file.close();
    return true;
}

bool DatabaseManager::saveStudents(const std::vector<Student>& students)
{
    std::ofstream file(dataFile.c_str());
    if (!file.is_open()) {
        std::cout << "Error saving data!\n";
        return false;
    }

    for (size_t i = 0; i < students.size(); i++) {
        file << students[i].toFileString() << "\n";
    }
    file.close();
    return true;
}

// ==================== BACKUP OPERATIONS ====================

bool DatabaseManager::createBackup(const std::vector<Student>& students)
{
    std::string timestamp = getCurrentTimestamp();
    std::string backupName = "backup_" + timestamp + ".dat";
    
    std::ofstream backup(backupName.c_str());
    if (!backup.is_open()) {
        return false;
    }

    for (size_t i = 0; i < students.size(); i++) {
        backup << students[i].toFileString() << "\n";
    }
    backup.close();
    return true;
}

bool DatabaseManager::restoreFromBackup(std::vector<Student>& students)
{
    std::ifstream backup(backupFile.c_str());
    if (!backup.is_open()) {
        return false;
    }

    std::vector<Student> newStudents;
    std::string line;
    while (std::getline(backup, line)) {
        if (!line.empty()) {
            newStudents.push_back(Student::fromFileString(line));
        }
    }
    backup.close();
    
    students = newStudents;
    return saveStudents(students);
}

bool DatabaseManager::hasBackup() const
{
    return fileExists(backupFile);
}

// ==================== FILE INFO ====================

long DatabaseManager::getFileSize(const std::string& filename) const
{
    std::ifstream file(filename.c_str(), std::ios::binary | std::ios::ate);
    if (file.is_open()) {
        long size = file.tellg();
        file.close();
        return size;
    }
    return 0;
}

std::string DatabaseManager::getBackupInfo() const
{
    std::stringstream ss;
    ss << "Main data file: " << getFileSize(dataFile) << " bytes\n";
    ss << "Backup file: " << getFileSize(backupFile) << " bytes\n";
    return ss.str();
}

// ==================== ADMIN CREDENTIALS ====================

bool DatabaseManager::loadAdminCredentials(std::map<std::string, std::string>& credentials)
{
    std::ifstream file(configFile.c_str());
    if (!file.is_open()) {
        // Create default admin account
        credentials["admin"] = "admin123";
        return saveAdminCredentials(credentials);
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string username = line.substr(0, pos);
            std::string password = line.substr(pos + 1);
            credentials[username] = password;
        }
    }
    file.close();
    return true;
}

bool DatabaseManager::saveAdminCredentials(const std::map<std::string, std::string>& credentials)
{
    std::ofstream file(configFile.c_str());
    if (!file.is_open()) {
        return false;
    }

    for (std::map<std::string, std::string>::const_iterator it = credentials.begin();
         it != credentials.end(); ++it) {
        file << it->first << ":" << it->second << "\n";
    }
    file.close();
    return true;
}

// ==================== UTILITY ====================

std::string DatabaseManager::getCurrentTimestamp() const
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", ltm);
    return std::string(buffer);
}

bool DatabaseManager::fileExists(const std::string& filename) const
{
    std::ifstream file(filename.c_str());
    bool exists = file.is_open();
    if (exists) file.close();
    return exists;
}

bool DatabaseManager::deleteFile(const std::string& filename)
{
    return std::remove(filename.c_str()) == 0;
}
