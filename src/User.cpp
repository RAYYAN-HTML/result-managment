#include "User.h"
#include "Utils.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cstdlib>

// ==================== USER CLASS ====================

User::User()
    : username(""), passwordHash(""), role(UserRole::GUEST), isActive(false)
{
    createdDate = "";
    lastLogin = "";
}

User::User(const std::string& username, const std::string& password, UserRole role)
    : username(username), role(role), isActive(true)
{
    setPassword(password);
    
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    createdDate = std::string(buffer);
    lastLogin = createdDate;
}

// ==================== PASSWORD OPERATIONS ====================

bool User::verifyPassword(const std::string& password) const
{
    // Simple string comparison (TODO: implement proper hashing)
    return passwordHash == password;
}

bool User::changePassword(const std::string& oldPassword, const std::string& newPassword)
{
    if (!verifyPassword(oldPassword)) {
        return false;
    }
    setPassword(newPassword);
    return true;
}

void User::setPassword(const std::string& password)
{
    // TODO: Implement proper password hashing (bcrypt, SHA-256, etc.)
    passwordHash = password;
}

// ==================== ROLE-BASED PERMISSIONS ====================

bool User::canAddStudent() const
{
    return role == UserRole::ADMIN || role == UserRole::TEACHER;
}

bool User::canEditStudent() const
{
    return role == UserRole::ADMIN || role == UserRole::TEACHER;
}

bool User::canDeleteStudent() const
{
    return role == UserRole::ADMIN;
}

bool User::canViewAllResults() const
{
    return role == UserRole::ADMIN || role == UserRole::TEACHER;
}

bool User::canEnterMarks() const
{
    return role == UserRole::ADMIN || role == UserRole::TEACHER;
}

bool User::canModifyResults() const
{
    return role == UserRole::ADMIN;
}

bool User::canViewOwnResult() const
{
    return role == UserRole::STUDENT || role == UserRole::ADMIN || role == UserRole::TEACHER;
}

bool User::canManageUsers() const
{
    return role == UserRole::ADMIN;
}

bool User::canAccessReports() const
{
    return role == UserRole::ADMIN || role == UserRole::TEACHER;
}

bool User::canCreateBackup() const
{
    return role == UserRole::ADMIN;
}

// ==================== UTILITY ====================

std::string User::getRoleString() const
{
    return getRoleString(role);
}

std::string User::getRoleString(UserRole role)
{
    switch (role) {
        case UserRole::ADMIN:
            return "Admin";
        case UserRole::TEACHER:
            return "Teacher";
        case UserRole::STUDENT:
            return "Student";
        case UserRole::GUEST:
            return "Guest";
        default:
            return "Unknown";
    }
}

void User::updateLastLogin()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    lastLogin = std::string(buffer);
}

// ==================== FILE OPERATIONS ====================

std::string User::toFileString() const
{
    std::stringstream ss;
    ss << username << "|" << passwordHash << "|" 
       << static_cast<int>(role) << "|"
       << (isActive ? "1" : "0") << "|"
       << createdDate << "|" << lastLogin;
    return ss.str();
}

User User::fromFileString(const std::string& data)
{
    User u;
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(data);

    while (std::getline(stream, token, '|')) {
        tokens.push_back(token);
    }

    if (tokens.size() >= 6) {
        u.username = tokens[0];
        u.passwordHash = tokens[1];
        u.role = static_cast<UserRole>(atoi(tokens[2].c_str()));
        u.isActive = (tokens[3] == "1");
        u.createdDate = tokens[4];
        u.lastLogin = tokens[5];
    }

    return u;
}

// ==================== AUTHENTICATION MANAGER ====================

AuthenticationManager::AuthenticationManager(const std::string& credFile)
    : currentUser(nullptr), credentialsFile(credFile)
{
    loadCredentials();
}

AuthenticationManager::~AuthenticationManager()
{
    saveCredentials();
    currentUser = nullptr;
}

// ==================== AUTHENTICATION ====================

bool AuthenticationManager::login(const std::string& username, const std::string& password)
{
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].getUsername() == username && users[i].verifyPassword(password)) {
            if (!users[i].getIsActive()) {
                return false;
            }
            users[i].updateLastLogin();
            currentUser = &users[i];
            return true;
        }
    }
    return false;
}

void AuthenticationManager::logout()
{
    currentUser = nullptr;
}

// ==================== USER MANAGEMENT ====================

bool AuthenticationManager::addUser(const std::string& username, const std::string& password, UserRole role)
{
    if (userExists(username)) {
        return false;
    }
    
    users.push_back(User(username, password, role));
    return saveCredentials();
}

bool AuthenticationManager::removeUser(const std::string& username)
{
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].getUsername() == username) {
            users.erase(users.begin() + i);
            return saveCredentials();
        }
    }
    return false;
}

bool AuthenticationManager::updateUserRole(const std::string& username, UserRole newRole)
{
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].getUsername() == username) {
            users[i].setRole(newRole);
            return saveCredentials();
        }
    }
    return false;
}

bool AuthenticationManager::changePassword(const std::string& username, const std::string& oldPassword,
                                          const std::string& newPassword)
{
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].getUsername() == username) {
            return users[i].changePassword(oldPassword, newPassword) && saveCredentials();
        }
    }
    return false;
}

// ==================== GETTERS ====================

User* AuthenticationManager::getUser(const std::string& username)
{
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].getUsername() == username) {
            return &users[i];
        }
    }
    return nullptr;
}

const User* AuthenticationManager::getUser(const std::string& username) const
{
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].getUsername() == username) {
            return &users[i];
        }
    }
    return nullptr;
}

// ==================== VALIDATION ====================

bool AuthenticationManager::userExists(const std::string& username) const
{
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].getUsername() == username) {
            return true;
        }
    }
    return false;
}

bool AuthenticationManager::isValidUsername(const std::string& username) const
{
    if (username.empty() || username.length() > 50) return false;
    for (size_t i = 0; i < username.length(); i++) {
        char c = username[i];
        if (!isalnum(c) && c != '_' && c != '.') return false;
    }
    return true;
}

bool AuthenticationManager::isValidPassword(const std::string& password) const
{
    return password.length() >= 8;
}

// ==================== PERSISTENCE ====================

bool AuthenticationManager::loadCredentials()
{
    std::ifstream file(credentialsFile.c_str());
    if (!file.is_open()) {
        // Create default admin account
        users.push_back(User("admin", "admin123", UserRole::ADMIN));
        return saveCredentials();
    }

    users.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            users.push_back(User::fromFileString(line));
        }
    }
    file.close();
    return true;
}

bool AuthenticationManager::saveCredentials()
{
    std::ofstream file(credentialsFile.c_str());
    if (!file.is_open()) {
        return false;
    }

    for (size_t i = 0; i < users.size(); i++) {
        file << users[i].toFileString() << "\n";
    }
    file.close();
    return true;
}
