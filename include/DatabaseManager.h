#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <string>
#include <vector>
#include "Student.h"

class DatabaseManager
{
private:
    std::string dataFile;
    std::string backupFile;
    std::string configFile;

public:
    DatabaseManager(const std::string& dataFileName = "students.dat",
                    const std::string& backupFileName = "students_backup.dat",
                    const std::string& configFileName = "system_config.dat");

    // Student data operations
    bool loadStudents(std::vector<Student>& students);
    bool saveStudents(const std::vector<Student>& students);
    
    // Backup operations
    bool createBackup(const std::vector<Student>& students);
    bool restoreFromBackup(std::vector<Student>& students);
    bool hasBackup() const;
    
    // File info
    long getFileSize(const std::string& filename) const;
    std::string getBackupInfo() const;
    
    // Admin credentials (file-based, for now)
    bool loadAdminCredentials(std::map<std::string, std::string>& credentials);
    bool saveAdminCredentials(const std::map<std::string, std::string>& credentials);
    
    // Utility
    std::string getCurrentTimestamp() const;
    bool fileExists(const std::string& filename) const;
    bool deleteFile(const std::string& filename);
};

#endif // DATABASE_MANAGER_H
