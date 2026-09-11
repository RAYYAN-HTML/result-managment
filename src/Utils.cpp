#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

// ==================== INPUT VALIDATOR ====================

bool InputValidator::isValidName(const std::string& name)
{
    if (name.empty() || name.length() > 50) return false;
    for (size_t i = 0; i < name.length(); i++) {
        char c = name[i];
        if (!isalpha(c) && !isspace(c) && c != '.' && c != '\'' && c != '-') {
            return false;
        }
    }
    return true;
}

bool InputValidator::isValidMark(double mark)
{
    return mark >= 0 && mark <= 100;
}

bool InputValidator::isValidRollNumber(const std::string& roll)
{
    if (roll.length() != 5) return false;
    std::string prefix = roll.substr(0, 2);
    std::string number = roll.substr(2);
    
    if (prefix != "PM" && prefix != "PE" && prefix != "CS") return false;
    
    for (size_t i = 0; i < number.length(); i++) {
        if (!isdigit(number[i])) return false;
    }
    
    return true;
}

bool InputValidator::isValidEmail(const std::string& email)
{
    if (email.empty()) return true;
    size_t at_pos = email.find('@');
    size_t dot_pos = email.rfind('.');
    return (at_pos != std::string::npos && 
            dot_pos != std::string::npos && 
            dot_pos > at_pos + 1 && 
            dot_pos < email.length() - 1);
}

bool InputValidator::isValidPhone(const std::string& phone)
{
    if (phone.empty()) return true;
    if (phone[0] == '+') {
        for (size_t i = 1; i < phone.length(); i++) {
            if (!isdigit(phone[i])) return false;
        }
        return phone.length() >= 10 && phone.length() <= 15;
    } else {
        for (size_t i = 0; i < phone.length(); i++) {
            if (!isdigit(phone[i])) return false;
        }
        return phone.length() >= 10 && phone.length() <= 15;
    }
}

std::string InputValidator::capitalizeName(const std::string& name)
{
    std::string result = name;
    bool newWord = true;
    
    for (size_t i = 0; i < result.length(); i++) {
        if (newWord && isalpha(result[i])) {
            result[i] = toupper(result[i]);
            newWord = false;
        } else if (isspace(result[i])) {
            newWord = true;
        } else {
            result[i] = tolower(result[i]);
        }
    }
    return result;
}

std::string InputValidator::toLowercase(const std::string& str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string InputValidator::toUppercase(const std::string& str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// ==================== SYSTEM UTILS ====================

void SystemUtils::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void SystemUtils::pauseScreen()
{
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

std::string SystemUtils::getPassword(const std::string& prompt)
{
    std::cout << prompt;
    std::string password;
    std::getline(std::cin, password);
    return password;
}
