#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cctype>

class InputValidator
{
public:
    // Name validation
    static bool isValidName(const std::string& name);
    
    // Mark validation (0-100)
    static bool isValidMark(double mark);
    
    // Roll number validation (format: PM/PE/CS + 3 digits)
    static bool isValidRollNumber(const std::string& roll);
    
    // Email validation (basic)
    static bool isValidEmail(const std::string& email);
    
    // Phone validation
    static bool isValidPhone(const std::string& phone);
    
    // String utilities
    static std::string capitalizeName(const std::string& name);
    static std::string toLowercase(const std::string& str);
    static std::string toUppercase(const std::string& str);
};

// Cross-platform utilities
class SystemUtils
{
public:
    // Screen clearing (cross-platform)
    static void clearScreen();
    
    // Pause screen
    static void pauseScreen();
    
    // Get password without echo (simple version)
    static std::string getPassword(const std::string& prompt = "Password: ");
};

#endif // UTILS_H
