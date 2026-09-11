#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

enum class UserRole
{
    ADMIN,
    TEACHER,
    STUDENT,
    GUEST
};

class User
{
private:
    std::string username;
    std::string passwordHash;  // Will store hashed password in future
    UserRole role;
    bool isActive;
    std::string createdDate;
    std::string lastLogin;

public:
    // Constructor
    User();
    User(const std::string& username, const std::string& password, UserRole role);

    // Getters
    std::string getUsername() const { return username; }
    UserRole getRole() const { return role; }
    bool getIsActive() const { return isActive; }
    std::string getCreatedDate() const { return createdDate; }
    std::string getLastLogin() const { return lastLogin; }
    
    // Setters
    void setRole(UserRole newRole) { role = newRole; }
    void setActive(bool active) { isActive = active; }
    void updateLastLogin();
    
    // Password operations
    bool verifyPassword(const std::string& password) const;
    bool changePassword(const std::string& oldPassword, const std::string& newPassword);
    void setPassword(const std::string& password);
    
    // Role-based permissions
    bool canAddStudent() const;
    bool canEditStudent() const;
    bool canDeleteStudent() const;
    bool canViewAllResults() const;
    bool canEnterMarks() const;
    bool canModifyResults() const;
    bool canViewOwnResult() const;
    bool canManageUsers() const;
    bool canAccessReports() const;
    bool canCreateBackup() const;
    
    // Utility
    std::string getRoleString() const;
    static std::string getRoleString(UserRole role);
    
    // File operations
    std::string toFileString() const;
    static User fromFileString(const std::string& data);
};

class AuthenticationManager
{
private:
    std::vector<User> users;
    User* currentUser;
    std::string credentialsFile;

public:
    AuthenticationManager(const std::string& credFile = "system_config.dat");
    ~AuthenticationManager();

    // Authentication
    bool login(const std::string& username, const std::string& password);
    void logout();
    bool isLoggedIn() const { return currentUser != nullptr; }
    
    // User management (admin only)
    bool addUser(const std::string& username, const std::string& password, UserRole role);
    bool removeUser(const std::string& username);
    bool updateUserRole(const std::string& username, UserRole newRole);
    bool changePassword(const std::string& username, const std::string& oldPassword, 
                       const std::string& newPassword);
    
    // Getters
    User* getCurrentUser() { return currentUser; }
    const User* getCurrentUser() const { return currentUser; }
    
    User* getUser(const std::string& username);
    const User* getUser(const std::string& username) const;
    
    std::vector<User> getAllUsers() const { return users; }
    
    // Validation
    bool userExists(const std::string& username) const;
    bool isValidUsername(const std::string& username) const;
    bool isValidPassword(const std::string& password) const;
    
    // Persistence
    bool loadCredentials();
    bool saveCredentials();
};

#endif // USER_H
