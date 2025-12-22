#include <iostream>
#include <fstream>
#include <string>
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

Student students[100];
int studentCount = 0;
string password = "123";

int main()
{
    readFromFile();

    int choice;

    while (true)
    {
        mainMenu();
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            if (checkPassword())
            {
                adminMenu();
            }
            else
            {
                cout << "Wrong password!\n";
            }
        }
        else if (choice == 2)
        {
            viewStudent();
        }
        else if (choice == 3)
        {
            cout << "Goodbye!\n";
            break;
        }
        else
        {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}

void mainMenu()
{
    cout << "\n====== Student Result System ======\n";
    cout << "1. Admin Login\n";
    cout << "2. View Result\n";
    cout << "3. Exit\n";
    cout << "===================================\n";
}

void adminMenu()
{
    int choice;

    while (true)
    {
        cout << "\n===== Admin Menu =====\n";
        cout << "1. Add Students\n";
        cout << "2. View All Students\n";
        cout << "3. Show Topper Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter choice: ";
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
            cout << "Invalid choice!\n";
        }
    }
}

void addStudents()
{
    int num;
    int groupChoice;
    string group;

    cout << "\n=== Add Students ===\n";

    cout << "Select Group:\n";
    cout << "1. Pre-Medical\n";
    cout << "2. Pre-Engineering\n";
    cout << "3. Computer Science\n";
    cout << "Enter choice (1-3): ";
    cin >> groupChoice;
    
    if (groupChoice == 1)
        group = "Pre-Medical";
    else if (groupChoice == 2)
        group = "Pre-Engineering";
    else if (groupChoice == 3)
        group = "Computer Science";
    else
    {
        cout << "Invalid group choice!\n";
        return;
    }
    
    cout << "How many students to add? ";
    cin >> num;

    if (studentCount + num > 100)
    {
        cout << "Not enough space! Only " << 100 - studentCount << " left.\n";
        return;
    }

    cin.ignore();

    for (int i = 0; i < num; i++)
    {
        cout << "\n--- Student " << i + 1 << " of " << num << " ---\n";

        Student s;
        s.group = group;

        cout << "Enter name: ";
        getline(cin, s.name);

        if (group == "Pre-Medical")
            s.roll = "PM" + to_string(studentCount + 1 + i);
        else if (group == "Pre-Engineering")
            s.roll = "PE" + to_string(studentCount + 1 + i);
        else
            s.roll = "CS" + to_string(studentCount + 1 + i);
            
        cout << "Roll number: " << s.roll << endl;
        cout << "Group: " << s.group << endl;

        cout << "Enter marks (0-100, can use decimals):\n";
        if (group == "Pre-Medical")
        {
            cout << "Biology: ";
            cin >> s.marks[0];
            cout << "Chemistry: ";
            cin >> s.marks[1];
            cout << "Physics: ";
            cin >> s.marks[2];
        }
        else if (group == "Pre-Engineering")
        {
            cout << "Math: ";
            cin >> s.marks[0];
            cout << "Chemistry: ";
            cin >> s.marks[1];
            cout << "Physics: ";
            cin >> s.marks[2];
        }
        else 
        {
            cout << "Computer: ";
            cin >> s.marks[0];
            cout << "Math: ";
            cin >> s.marks[1];
            cout << "Physics: ";
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

        cout << "Student added!\n";
    }

    studentCount += num;

    cout << "\n" << num << " students added!\n";
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

    cout << "\n=== View Result ===\n";
    cout << "Enter roll number: ";
    cin >> roll;

    int index = findStudent(roll);

    if (index == -1)
    {
        cout << "Student not found!\n";
        return;
    }

    cout << "\n======= RESULT =======\n";
    cout << "Name: " << students[index].name << endl;
    cout << "Roll: " << students[index].roll << endl;
    cout << "Group: " << students[index].group << endl;

    cout << fixed;
    cout.precision(2);
    cout << "Marks: ";
    if (students[index].group == "Pre-Medical")
    {
        cout << "Bio=" << students[index].marks[0] << " ";
        cout << "Chem=" << students[index].marks[1] << " ";
        cout << "Phy=" << students[index].marks[2];
    }
    else if (students[index].group == "Pre-Engineering")
    {
        cout << "Math=" << students[index].marks[0] << " ";
        cout << "Chem=" << students[index].marks[1] << " ";
        cout << "Phy=" << students[index].marks[2];
    }
    else
    {
        cout << "Comp=" << students[index].marks[0] << " ";
        cout << "Math=" << students[index].marks[1] << " ";
        cout << "Phy=" << students[index].marks[2];
    }
    
    cout << endl;
    cout << "Percentage: " << students[index].percentage << "%" << endl;
    cout << "Grade: " << students[index].grade << endl;
    cout << "=====================\n";
}

void viewAllStudents()
{
    if (studentCount == 0)
    {
        cout << "No students found!\n";
        return;
    }

    cout << "\n===== All Students =====\n";
    cout << fixed;
    cout.precision(2);
    for (int i = 0; i < studentCount; i++)
    {
        cout << i + 1 << ". " << students[i].name;
        cout << " (" << students[i].roll << ") ";
        cout << "[" << students[i].group << "] ";
        cout << students[i].percentage << "% ";
        cout << students[i].grade << endl;
    }
}

void showHighest()
{
    if (studentCount == 0)
    {
        cout << "No students found!\n";
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

    cout << "\n===== Topper Student =====\n";
    cout << "Name: " << students[highestIndex].name << endl;
    cout << "Roll: " << students[highestIndex].roll << endl;
    cout << "Group: " << students[highestIndex].group << endl;
    cout << "Percentage: " << students[highestIndex].percentage << "%\n";
    cout << "Grade: " << students[highestIndex].grade << endl;
    cout << "=========================\n";
}

void deleteStudent()
{
    string roll;

    cout << "\n=== Delete Student ===\n";
    cout << "Enter roll number: ";
    cin >> roll;

    int index = findStudent(roll);

    if (index == -1)
    {
        cout << "Student not found!\n";
        return;
    }

    for (int i = index; i < studentCount - 1; i++)
    {
        students[i] = students[i + 1];
    }

    studentCount--;
    updateFiles();

    cout << "Student deleted!\n";
}

int findStudent(string roll)
{
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].roll == roll)
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
    cout << "Enter password: ";
    cin >> input;

    return input == password;
}