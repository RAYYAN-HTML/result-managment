#include "ResultCalculator.h"
#include <iostream>
#include <iomanip>

// ==================== RESULT CALCULATOR ====================

float ResultCalculator::calculatePercentage(const double marks[3])
{
    double total = marks[0] + marks[1] + marks[2];
    return (total / 300.0f) * 100.0f;
}

char ResultCalculator::calculateGrade(float percentage)
{
    if (percentage >= 85)
        return 'A';
    else if (percentage >= 75)
        return 'B';
    else if (percentage >= 65)
        return 'C';
    else if (percentage >= 55)
        return 'D';
    else if (percentage >= 45)
        return 'E';
    else
        return 'F';
}

float ResultCalculator::calculateGPA(float percentage)
{
    // Standard GPA calculation: 4.0 scale
    // 90-100 = 4.0, 80-89 = 3.0, 70-79 = 2.0, 60-69 = 1.0, <60 = 0.0
    if (percentage >= 90)
        return 4.0f;
    else if (percentage >= 80)
        return 3.0f;
    else if (percentage >= 70)
        return 2.0f;
    else if (percentage >= 60)
        return 1.0f;
    else
        return 0.0f;
}

bool ResultCalculator::isPassed(char grade)
{
    return grade != 'F';
}

bool ResultCalculator::isValidMarks(double marks[3])
{
    for (int i = 0; i < 3; i++) {
        if (marks[i] < 0 || marks[i] > 100)
            return false;
    }
    return true;
}

const char* ResultCalculator::getGradeDescription(char grade)
{
    switch (grade) {
        case 'A': return "Excellent";
        case 'B': return "Very Good";
        case 'C': return "Good";
        case 'D': return "Satisfactory";
        case 'E': return "Pass";
        case 'F': return "Fail";
        default: return "Unknown";
    }
}

void ResultCalculator::displayGradingScale()
{
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "                  GRADING SCALE\n";
    std::cout << std::string(60, '=') << "\n\n";
    std::cout << "Grade    Percentage Range    Description\n";
    std::cout << std::string(60, '-') << "\n";
    std::cout << "  A      85 - 100            Excellent\n";
    std::cout << "  B      75 - 84             Very Good\n";
    std::cout << "  C      65 - 74             Good\n";
    std::cout << "  D      55 - 64             Satisfactory\n";
    std::cout << "  E      45 - 54             Pass\n";
    std::cout << "  F      0  - 44             Fail\n";
    std::cout << std::string(60, '=') << "\n";
}
