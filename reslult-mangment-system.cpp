#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

struct Student
{
    string name;
    string roll;
    string group;
    double marks[3];
    float percentage;
    char grade;
};

void mainMenu();
void adminMenu();
void addStudents();
void viewStudent();
void viewAllStudents();
void showHighest();
void deleteStudent();
void calculateResult(Student &s, string group);
void saveToFile(Student s);
void readFromFile();
int findStudent(string roll);
void updateFiles();
bool checkPassword();
string toLowercase(string str);

Student students[100];
int studentCount = 0;
string password = "123";

string toLowercase(string str)
{
    string result = str;
    for (int i = 0; i < result.length(); i++)
    {
        result[i] = tolower(result[i]);
    }
    return result;
}

int main()
{
    readFromFile();
    int choice;
    
    while (true)
    {
        mainMenu();
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        if (choice == 1)
        {
            if (checkPassword())
            {
                adminMenu();
            }
            else
            {
                cout << "\nWrong password! Access denied.\n";
            }
        }
        else if (choice == 2)
        {
            viewStudent();
        }
        else if (choice == 3)
        {
            cout << "\nThank you for using Student Result System!\n";
            cout << "Goodbye!\n";
            break;
        }
        else
        {
            cout << "\nInvalid choice! Please try again.\n";
        }
    }
    return 0;
}

void mainMenu()
{
    cout << "\n";
    cout << "========================================\n";
    cout << "      STUDENT RESULT SYSTEM            \n";
    cout << "========================================\n";
    cout << "  1. Admin Login                       \n";
    cout << "  2. View Student Result               \n";
    cout << "  3. Exit                              \n";
    cout << "========================================\n";
}

void adminMenu()
{
    int choice;
    
    while (true)
    {
        cout << "\n";
        cout << "========================================\n";
        cout << "          ADMIN MENU                   \n";
        cout << "========================================\n";
        cout << "  1. Add New Students                  \n";
        cout << "  2. View All Students                 \n";
        cout << "  3. Show Topper Student               \n";
        cout << "  4. Delete Student Record             \n";
        cout << "  5. Back to Main Menu                 \n";
        cout << "========================================\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        if (choice == 1)
        {
            addStudents();
        }
        else if (choice == 2)
        {
            viewAllStudents();
        }
        else if (choice == 3)
        {
            showHighest();
        }
        else if (choice == 4)
        {
            deleteStudent();
        }
        else if (choice == 5)
        {
            break;
        }
        else
        {
            cout << "\nInvalid choice! Please try again.\n";
        }
    }
}

void addStudents()
{
    int num;
    int groupChoice;
    string group;
    
    cout << "\n";
    cout << "========================================\n";
    cout << "         ADD STUDENTS                   \n";
    cout << "========================================\n";
    
    cout << "\nSelect Group:\n";
    cout << "  1. Pre-Medical\n";
    cout << "  2. Pre-Engineering\n";
    cout << "  3. Computer Science\n";
    cout << "\nEnter group choice (1-3): ";
    cin >> groupChoice;
    
    if (groupChoice == 1)
        group = "Pre-Medical";
    else if (groupChoice == 2)
        group = "Pre-Engineering";
    else if (groupChoice == 3)
        group = "Computer Science";
    else
    {
        cout << "\nInvalid group choice!\n";
        return;
    }
    
    cout << "\nHow many students to add? ";
    cin >> num;
    
    if (studentCount + num > 100)
    {
        cout << "\nNot enough space! Only " << 100 - studentCount << " slots left.\n";
        return;
    }
    
    cin.ignore();
    
    for (int i = 0; i < num; i++)
    {
        cout << "\n----------------------------------------\n";
        cout << "    Student " << i + 1 << " of " << num << "\n";
        cout << "----------------------------------------\n";
        
        Student s;
        s.group = group;
        
        cout << "Enter name    : ";
        getline(cin, s.name);
        
        if (group == "Pre-Medical")
            s.roll = "PM" + to_string(studentCount + 1 + i);
        else if (group == "Pre-Engineering")
            s.roll = "PE" + to_string(studentCount + 1 + i);
        else
            s.roll = "CS" + to_string(studentCount + 1 + i);
            
        cout << "Roll number  : " << s.roll << "\n";
        cout << "Group        : " << s.group << "\n\n";
        
        cout << "Enter marks (0-100, decimals allowed):\n";
        if (group == "Pre-Medical")
        {
            cout << "  Biology    : ";
            cin >> s.marks[0];
            cout << "  Chemistry  : ";
            cin >> s.marks[1];
            cout << "  Physics    : ";
            cin >> s.marks[2];
        }
        else if (group == "Pre-Engineering")
        {
            cout << "  Math       : ";
            cin >> s.marks[0];
            cout << "  Chemistry  : ";
            cin >> s.marks[1];
            cout << "  Physics    : ";
            cin >> s.marks[2];
        }
        else 
        {
            cout << "  Computer   : ";
            cin >> s.marks[0];
            cout << "  Math       : ";
            cin >> s.marks[1];
            cout << "  Physics    : ";
            cin >> s.marks[2];
        }
        
        for (int j = 0; j < 3; j++)
        {
            while (s.marks[j] < 0 || s.marks[j] > 100)
            {
                cout << "Invalid! Enter 0-100 for mark " << j + 1 << ": ";
                cin >> s.marks[j];
            }
        }
        
        calculateResult(s, group);
        students[studentCount + i] = s;
        saveToFile(s);
        cin.ignore();
        
        cout << "\nStudent added successfully!\n";
    }
    
    studentCount += num;
    cout << "\n" << num << " students added to " << group << " group!\n";
}

void calculateResult(Student &s, string group)
{
    double total = 0;
    for (int i = 0; i < 3; i++)
    {
        total += s.marks[i];
    }
    
    s.percentage = (total / 300.0) * 100;
    
    if (s.percentage >= 80)
        s.grade = 'A';
    else if (s.percentage >= 70)
        s.grade = 'B';
    else if (s.percentage >= 60)
        s.grade = 'C';
    else if (s.percentage >= 50)
        s.grade = 'D';
    else
        s.grade = 'F';
}

void viewStudent()
{
    string roll;
    
    cout << "\n";
    cout << "========================================\n";
    cout << "         VIEW STUDENT RESULT           \n";
    cout << "========================================\n";
    cout << "\nEnter roll number: ";
    cin >> roll;
    
    int index = findStudent(roll);
    
    if (index == -1)
    {
        cout << "\nStudent not found!\n";
        return;
    }
    
    cout << "\n";
    cout << "========================================\n";
    cout << "           OFFICIAL RESULT              \n";
    cout << "========================================\n";
    cout << "  Name       : " << students[index].name << "\n";
    cout << "  Roll No    : " << students[index].roll << "\n";
    cout << "  Group      : " << students[index].group << "\n";
    cout << "  --------------------------------------\n";
    
    if (students[index].group == "Pre-Medical")
    {
        cout << "  Biology    : " << students[index].marks[0] << "\n";
        cout << "  Chemistry  : " << students[index].marks[1] << "\n";
        cout << "  Physics    : " << students[index].marks[2] << "\n";
    }
    else if (students[index].group == "Pre-Engineering")
    {
        cout << "  Math       : " << students[index].marks[0] << "\n";
        cout << "  Chemistry  : " << students[index].marks[1] << "\n";
        cout << "  Physics    : " << students[index].marks[2] << "\n";
    }
    else
    {
        cout << "  Computer   : " << students[index].marks[0] << "\n";
        cout << "  Math       : " << students[index].marks[1] << "\n";
        cout << "  Physics    : " << students[index].marks[2] << "\n";
    }
    
    cout << "  --------------------------------------\n";
    cout << "  Percentage : " << students[index].percentage << "%\n";
    cout << "  Grade      : " << students[index].grade << "\n";
    cout << "========================================\n";
}

void viewAllStudents()
{
    if (studentCount == 0)
    {
        cout << "\nNo students found in the system!\n";
        return;
    }
    
    cout << "\n";
    cout << "================================================================================\n";
    cout << "                              ALL STUDENTS LIST                                 \n";
    cout << "================================================================================\n";
    cout << "No.  Name                      Roll No    Group               Percentage  Grade\n";
    cout << "--------------------------------------------------------------------------------\n";
    
    for (int i = 0; i < studentCount; i++)
    {
        cout << i + 1 << "    ";
        cout << students[i].name;
        
        // Add spaces for alignment
        if (students[i].name.length() < 24)
            cout << string(24 - students[i].name.length(), ' ');
        else
            cout << " ";
            
        cout << students[i].roll << "      ";
        cout << students[i].group;
        
        // Add spaces for alignment
        if (students[i].group.length() < 18)
            cout << string(18 - students[i].group.length(), ' ');
            
        cout << students[i].percentage << "%      ";
        cout << students[i].grade << "\n";
    }
    
    cout << "================================================================================\n";
    cout << "Total Students: " << studentCount << "\n";
}

void showHighest()
{
    if (studentCount == 0)
    {
        cout << "\nNo students found in the system!\n";
        return;
    }
    
    int highestIndex = 0;
    for (int i = 1; i < studentCount; i++)
    {
        if (students[i].percentage > students[highestIndex].percentage)
        {
            highestIndex = i;
        }
    }
    
    cout << "\n";
    cout << "========================================\n";
    cout << "         TOPPER STUDENT                 \n";
    cout << "========================================\n";
    cout << "  Name       : " << students[highestIndex].name << "\n";
    cout << "  Roll No    : " << students[highestIndex].roll << "\n";
    cout << "  Group      : " << students[highestIndex].group << "\n";
    cout << "  Percentage : " << students[highestIndex].percentage << "%\n";
    cout << "  Grade      : " << students[highestIndex].grade << "\n";
    cout << "========================================\n";
}

void deleteStudent()
{
    string roll;
    
    cout << "\n";
    cout << "========================================\n";
    cout << "         DELETE STUDENT RECORD         \n";
    cout << "========================================\n";
    cout << "\nEnter roll number to delete: ";
    cin >> roll;
    
    int index = findStudent(roll);
    
    if (index == -1)
    {
        cout << "\nStudent not found!\n";
        return;
    }
    
    cout << "\nAre you sure you want to delete?\n";
    cout << "Name: " << students[index].name << "\n";
    cout << "Roll: " << students[index].roll << "\n";
    cout << "\nEnter 'yes' to confirm: ";
    
    string confirm;
    cin >> confirm;
    
    if (confirm == "yes" || confirm == "YES" || confirm == "Yes")
    {
        for (int i = index; i < studentCount - 1; i++)
        {
            students[i] = students[i + 1];
        }
        
        studentCount--;
        updateFiles();
        cout << "\nStudent record deleted successfully!\n";
    }
    else
    {
        cout << "\nDeletion cancelled.\n";
    }
}

int findStudent(string roll)
{
    string rollLower = toLowercase(roll);
    
    for (int i = 0; i < studentCount; i++)
    {
        string storedRollLower = toLowercase(students[i].roll);
        
        if (storedRollLower == rollLower)
        {
            return i;
        }
    }
    return -1;
}

void saveToFile(Student s)
{
    ofstream file;
    file.open("students.txt", ios::app);
    
    if (file.is_open())
    {
        file << s.name << " ";
        file << s.roll << " ";
        file << s.group << " ";
        file << s.marks[0] << " ";
        file << s.marks[1] << " ";
        file << s.marks[2] << " ";
        file << s.percentage << " ";
        file << s.grade << endl;
        
        file.close();
    }
    else
    {
        cout << "File error!\n";
    }
}

void readFromFile()
{
    ifstream file;
    file.open("students.txt");
    
    if (!file.is_open())
    {
        return;
    }
    
    studentCount = 0;
    
    while (file >> students[studentCount].name 
                >> students[studentCount].roll 
                >> students[studentCount].group
                >> students[studentCount].marks[0] 
                >> students[studentCount].marks[1] 
                >> students[studentCount].marks[2] 
                >> students[studentCount].percentage 
                >> students[studentCount].grade)
    {
        studentCount++;
        
        if (studentCount >= 100)
            break;
    }
    
    file.close();
}

void updateFiles()
{
    ofstream file;
    file.open("students.txt");
    
    if (!file.is_open())
    {
        cout << "File error!\n";
        return;
    }
    
    for (int i = 0; i < studentCount; i++)
    {
        file << students[i].name << " ";
        file << students[i].roll << " ";
        file << students[i].group << " ";
        file << students[i].marks[0] << " ";
        file << students[i].marks[1] << " ";
        file << students[i].marks[2] << " ";
        file << students[i].percentage << " ";
        file << students[i].grade << endl;
    }
    
    file.close();
}

bool checkPassword()
{
    string input;
    cout << "\nEnter password: ";
    cin >> input;
    return input == password;
}