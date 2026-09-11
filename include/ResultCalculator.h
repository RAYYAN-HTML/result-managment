#ifndef RESULT_CALCULATOR_H
#define RESULT_CALCULATOR_H

class ResultCalculator
{
public:
    // Calculate percentage from marks
    // marks: array of 3 marks (0-100 each)
    static float calculatePercentage(const double marks[3]);
    
    // Calculate grade based on percentage
    static char calculateGrade(float percentage);
    
    // Calculate GPA (if needed for future enhancement)
    static float calculateGPA(float percentage);
    
    // Check if student passed (grade != 'F')
    static bool isPassed(char grade);
    
    // Validate marks
    static bool isValidMarks(double marks[3]);
    
    // Get grade description
    static const char* getGradeDescription(char grade);
    
    // Grading scale information
    static void displayGradingScale();
};

#endif // RESULT_CALCULATOR_H
