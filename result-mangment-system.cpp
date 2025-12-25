#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <map>
#include <sstream>
#include <cstring>

using namespace std;

// Cross-platform screen clearing
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Simple password input without masking (compatible with older compilers)
string getPassword(const string& prompt = "Password: ")
{
    cout << prompt;
    string password;
    getline(cin, password);
    return password;
}

// Pause screen function
void pauseScreen()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// ==================== ENHANCED CLASS DEFINITIONS ====================

class InputValidator {
public:
    static bool isValidName(const string& name) {
        if (name.empty() || name.length() > 50) return false;
        for (size_t i = 0; i < name.length(); i++) {
            char c = name[i];
            if (!isalpha(c) && !isspace(c) && c != '.' && c != '\'' && c != '-') {
                return false;
            }
        }
        return true;
    }
    
    static bool isValidMark(double mark) {
        return mark >= 0 && mark <= 100;
    }
    
    static bool isValidRollNumber(const string& roll) {
        if (roll.length() != 5) return false;
        string prefix = roll.substr(0, 2);
        string number = roll.substr(2);
        
        if (prefix != "PM" && prefix != "PE" && prefix != "CS") return false;
        
        for (size_t i = 0; i < number.length(); i++) {
            if (!isdigit(number[i])) return false;
        }
        
        return true;
    }
    
    static string capitalizeName(const string& name) {
        string result = name;
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
};

class Student
{
private:
    string name;
    string roll;
    string group;
    double marks[3];
    float percentage;
    char grade;
    string admissionDate;
    string email;
    string phone;
    bool isActive;
    string lastModified;

public:
    Student() : percentage(0), grade('F'), isActive(true)
    {
        for (int i = 0; i < 3; i++)
            marks[i] = 0;
        admissionDate = getCurrentDate();
        lastModified = admissionDate;
    }

    Student(string n, string r, string g, double m1, double m2, double m3,
            string email = "", string phone = "")
        : name(InputValidator::capitalizeName(n)), roll(r), group(g), 
          email(email), phone(phone), isActive(true)
    {
        marks[0] = m1;
        marks[1] = m2;
        marks[2] = m3;
        calculateResult();
        admissionDate = getCurrentDate();
        lastModified = admissionDate;
    }

    // Getters
    string getName() const { return name; }
    string getRoll() const { return roll; }
    string getGroup() const { return group; }
    float getPercentage() const { return percentage; }
    char getGrade() const { return grade; }
    string getEmail() const { return email; }
    string getPhone() const { return phone; }
    string getAdmissionDate() const { return admissionDate; }
    string getLastModified() const { return lastModified; }
    bool getIsActive() const { return isActive; }
    
    double getMark(int index) const
    {
        if (index >= 0 && index < 3)
            return marks[index];
        return 0;
    }
    
    double getTotalMarks() const {
        return marks[0] + marks[1] + marks[2];
    }

    // Setters with validation
    bool setName(const string &n) { 
        if (InputValidator::isValidName(n)) {
            name = InputValidator::capitalizeName(n);
            updateLastModified();
            return true;
        }
        return false;
    }
    
    void setRoll(const string &r) { 
        roll = r; 
        updateLastModified();
    }
    
    void setGroup(const string &g)
    {
        group = g;
        calculateResult();
        updateLastModified();
    }

    bool setMark(int index, double value)
    {
        if (index >= 0 && index < 3 && InputValidator::isValidMark(value))
        {
            marks[index] = value;
            calculateResult();
            updateLastModified();
            return true;
        }
        return false;
    }

    bool setEmail(const string &e)
    {
        if (validateEmail(e)) {
            email = e;
            updateLastModified();
            return true;
        }
        return false;
    }

    bool setPhone(const string &p)
    {
        if (validatePhone(p)) {
            phone = p;
            updateLastModified();
            return true;
        }
        return false;
    }
    
    void setActive(bool active) {
        isActive = active;
        updateLastModified();
    }

    // Result calculation
    void calculateResult()
    {
        double total = marks[0] + marks[1] + marks[2];
        percentage = (total / 300.0) * 100;

        if (percentage >= 85)
            grade = 'A';
        else if (percentage >= 75)
            grade = 'B';
        else if (percentage >= 65)
            grade = 'C';
        else if (percentage >= 55)
            grade = 'D';
        else if (percentage >= 45)
            grade = 'E';
        else
            grade = 'F';
    }

    // Validation methods
    static bool validateEmail(const string &email)
    {
        if (email.empty()) return true;
        // Simple email validation
        size_t at_pos = email.find('@');
        size_t dot_pos = email.rfind('.');
        return (at_pos != string::npos && 
                dot_pos != string::npos && 
                dot_pos > at_pos + 1 && 
                dot_pos < email.length() - 1);
    }

    static bool validatePhone(const string &phone)
    {
        if (phone.empty()) return true;
        // Check if all characters are digits or +
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

    // Display methods
    void displayDetailed() const
    {
        cout << "\n"
             << string(60, '=') << "\n";
        cout << "                   STUDENT DETAILS\n";
        cout << string(60, '=') << "\n";
        cout << left << setw(20) << "Name:" << name << "\n";
        cout << setw(20) << "Roll Number:" << roll << "\n";
        cout << setw(20) << "Group:" << group << "\n";
        cout << setw(20) << "Admission Date:" << admissionDate << "\n";
        cout << setw(20) << "Last Modified:" << lastModified << "\n";
        cout << setw(20) << "Status:" << (isActive ? "Active" : "Inactive") << "\n";
        cout << setw(20) << "Email:" << (email.empty() ? "N/A" : email) << "\n";
        cout << setw(20) << "Phone:" << (phone.empty() ? "N/A" : phone) << "\n";

        cout << "\n"
             << string(60, '-') << "\n";
        cout << "                    MARKS DETAIL\n";
        cout << string(60, '-') << "\n";

        vector<string> subjects = getSubjects();
        for (int i = 0; i < 3; i++)
        {
            cout << left << setw(20) << subjects[i] + ":" << marks[i] << "/100\n";
        }

        cout << "\n"
             << string(60, '-') << "\n";
        cout << setw(20) << "Total Marks:" << getTotalMarks() << "/300\n";
        cout << setw(20) << "Percentage:" << fixed << setprecision(2) << percentage << "%\n";
        cout << setw(20) << "Grade:" << grade << "\n";
        cout << string(60, '=') << "\n";
    }

    void displaySummary() const
    {
        string status = isActive ? "A" : "I";
        cout << left << setw(25) << name
             << setw(15) << roll
             << setw(20) << group
             << setw(12) << fixed << setprecision(2) << percentage << "%"
             << setw(8) << grade
             << setw(10) << status
             << setw(15) << admissionDate << "\n";
    }

    // File operations
    string toFileString() const
    {
        stringstream ss;
        ss << name << "|" << roll << "|" << group << "|"
           << marks[0] << "|" << marks[1] << "|" << marks[2] << "|"
           << percentage << "|" << grade << "|" << admissionDate << "|"
           << email << "|" << phone << "|"
           << (isActive ? "1" : "0") << "|" << lastModified;
        return ss.str();
    }

    static Student fromFileString(const string &data)
    {
        Student s;
        vector<string> tokens;
        string token;
        istringstream stream(data);

        while (getline(stream, token, '|'))
        {
            tokens.push_back(token);
        }

        if (tokens.size() >= 13)
        {
            s.name = tokens[0];
            s.roll = tokens[1];
            s.group = tokens[2];
            s.marks[0] = atof(tokens[3].c_str());
            s.marks[1] = atof(tokens[4].c_str());
            s.marks[2] = atof(tokens[5].c_str());
            s.percentage = atof(tokens[6].c_str());
            s.grade = tokens[7][0];
            s.admissionDate = tokens[8];
            s.email = tokens[9];
            s.phone = tokens[10];
            s.isActive = (tokens[11] == "1");
            s.lastModified = tokens[12];
        }

        return s;
    }

private:
    vector<string> getSubjects() const {
        vector<string> subjects;
        if (group == "Pre-Medical")
        {
            subjects.push_back("Biology");
            subjects.push_back("Chemistry");
            subjects.push_back("Physics");
        }
        else if (group == "Pre-Engineering")
        {
            subjects.push_back("Mathematics");
            subjects.push_back("Chemistry");
            subjects.push_back("Physics");
        }
        else
        {
            subjects.push_back("Computer");
            subjects.push_back("Mathematics");
            subjects.push_back("Physics");
        }
        return subjects;
    }
    
    void updateLastModified() {
        lastModified = getCurrentDate();
    }
    
    string getCurrentDate()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
        return string(buffer);
    }
};

// ==================== ENHANCED SYSTEM CLASS ====================

class StudentResultSystem
{
private:
    vector<Student> students;
    map<string, string> adminCredentials; // username -> password
    const string dataFile = "students.dat";
    const string backupFile = "students_backup.dat";
    const string configFile = "system_config.dat";
    
    // Roll number counters for each group
    map<string, int> rollNumberCounters;

public:
    StudentResultSystem()
    {
        loadAdminCredentials();
        loadFromFile();
        initializeRollNumberCounters();
    }

    ~StudentResultSystem()
    {
        saveToFile();
    }

    // Initialize roll number counters based on existing students
    void initializeRollNumberCounters()
    {
        rollNumberCounters["PM"] = 0;
        rollNumberCounters["PE"] = 0;
        rollNumberCounters["CS"] = 0;

        for (size_t i = 0; i < students.size(); i++)
        {
            string roll = students[i].getRoll();
            if (InputValidator::isValidRollNumber(roll))
            {
                string prefix = roll.substr(0, 2);
                string numberStr = roll.substr(2);

                int number = atoi(numberStr.c_str());
                if (rollNumberCounters.find(prefix) != rollNumberCounters.end())
                {
                    if (number > rollNumberCounters[prefix])
                    {
                        rollNumberCounters[prefix] = number;
                    }
                }
            }
        }
    }

    // Generate roll number based on group
    string generateRollNumber(const string &group)
    {
        string prefix;

        if (group == "Pre-Medical")
        {
            prefix = "PM";
        }
        else if (group == "Pre-Engineering")
        {
            prefix = "PE";
        }
        else
        {
            prefix = "CS";
        }

        // Find next available number
        int nextNumber = 1;
        while (true)
        {
            stringstream ss;
            ss << prefix << setw(3) << setfill('0') << nextNumber;
            string candidateRoll = ss.str();
            
            bool exists = false;
            for (size_t i = 0; i < students.size(); i++) {
                if (students[i].getRoll() == candidateRoll && students[i].getIsActive()) {
                    exists = true;
                    break;
                }
            }
            
            if (!exists) {
                rollNumberCounters[prefix] = nextNumber;
                return candidateRoll;
            }
            nextNumber++;
        }
    }

    // ==================== ENHANCED ADMIN FUNCTIONS ====================

    bool adminLogin()
    {
        clearScreen();
        cout << "\n"
             << string(50, '=') << "\n";
        cout << "               ADMIN LOGIN\n";
        cout << string(50, '=') << "\n\n";

        string username, password;
        cout << "Username: ";
        getline(cin, username);

        password = getPassword("Password: ");

        map<string, string>::iterator it = adminCredentials.find(username);
        if (it != adminCredentials.end() && it->second == password)
        {
            cout << "\n\nLogin successful!\n";
            cout << "\nPress Enter to continue...";
            cin.get();
            return true;
        }

        cout << "\n\nInvalid credentials!\n";
        
        // Simple delay
        for (int i = 0; i < 200000000; i++); // Simple busy wait
        
        cout << "\nPress Enter to continue...";
        cin.get();
        return false;
    }

    void changeAdminPassword()
    {
        clearScreen();
        cout << "\n"
             << string(50, '=') << "\n";
        cout << "          CHANGE ADMIN PASSWORD\n";
        cout << string(50, '=') << "\n\n";

        string username, oldPass, newPass;
        cout << "Username: ";
        getline(cin, username);

        oldPass = getPassword("Old Password: ");

        map<string, string>::iterator it = adminCredentials.find(username);
        if (it == adminCredentials.end())
        {
            cout << "\nInvalid username!\n";
            pauseScreen();
            return;
        }

        if (it->second != oldPass)
        {
            cout << "\nInvalid password!\n";
            pauseScreen();
            return;
        }

        newPass = getPassword("New Password (min 8 chars): ");

        if (newPass.length() < 8)
        {
            cout << "\nPassword must be at least 8 characters!\n";
            pauseScreen();
            return;
        }

        string confirmPass = getPassword("Confirm New Password: ");

        if (newPass != confirmPass)
        {
            cout << "\nPasswords don't match!\n";
            pauseScreen();
            return;
        }

        adminCredentials[username] = newPass;
        saveAdminCredentials();
        cout << "\nPassword changed successfully!\n";
        pauseScreen();
    }

    void addAdminAccount()
    {
        clearScreen();
        if (!adminLogin())
            return;

        cout << "\n"
             << string(50, '=') << "\n";
        cout << "          ADD ADMIN ACCOUNT\n";
        cout << string(50, '=') << "\n\n";

        string username, password;
        cout << "New Username: ";
        getline(cin, username);

        if (adminCredentials.find(username) != adminCredentials.end())
        {
            cout << "Username already exists!\n";
            pauseScreen();
            return;
        }

        password = getPassword("Password: ");

        if (password.length() < 8)
        {
            cout << "\nPassword must be at least 8 characters!\n";
            pauseScreen();
            return;
        }

        string confirmPass = getPassword("Confirm Password: ");

        if (password != confirmPass)
        {
            cout << "\nPasswords don't match!\n";
            pauseScreen();
            return;
        }

        adminCredentials[username] = password;
        saveAdminCredentials();
        cout << "\nAdmin account created successfully!\n";
        pauseScreen();
    }

    // ==================== ENHANCED STUDENT MANAGEMENT ====================

    void addStudent()
    {
        clearScreen();
        cout << "\n"
             << string(50, '=') << "\n";
        cout << "           ADD NEW STUDENT\n";
        cout << string(50, '=') << "\n\n";

        Student s;
        string input;

        // Get name with validation
        while (true)
        {
            cout << "Student Name: ";
            getline(cin, input);
            if (s.setName(input))
                break;
            cout << "Invalid name! Use only letters, spaces, and basic punctuation.\n";
        }

        // Get group
        cout << "\nSelect Group:\n";
        cout << "1. Pre-Medical\n";
        cout << "2. Pre-Engineering\n";
        cout << "3. Computer Science\n";
        cout << "\nEnter choice (1-3): ";

        int groupChoice;
        while (!(cin >> groupChoice) || groupChoice < 1 || groupChoice > 3)
        {
            cout << "Invalid choice! Enter 1-3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        string group;
        switch (groupChoice)
        {
        case 1:
            group = "Pre-Medical";
            break;
        case 2:
            group = "Pre-Engineering";
            break;
        case 3:
            group = "Computer Science";
            break;
        }

        s.setGroup(group);

        // Auto-generate roll number
        string rollNumber = generateRollNumber(group);
        s.setRoll(rollNumber);

        cout << "\nStudent Information:\n";
        cout << "  Name       : " << s.getName() << "\n";
        cout << "  Roll Number: " << s.getRoll() << " (Auto-generated)\n";
        cout << "  Group      : " << s.getGroup() << "\n";

        // Get marks with enhanced validation
        vector<string> subjects;
        if (group == "Pre-Medical")
        {
            subjects.push_back("Biology");
            subjects.push_back("Chemistry");
            subjects.push_back("Physics");
        }
        else if (group == "Pre-Engineering")
        {
            subjects.push_back("Mathematics");
            subjects.push_back("Chemistry");
            subjects.push_back("Physics");
        }
        else
        {
            subjects.push_back("Computer");
            subjects.push_back("Mathematics");
            subjects.push_back("Physics");
        }

        for (int i = 0; i < 3; i++)
        {
            while (true)
            {
                cout << subjects[i] << " Marks (0-100): ";
                double mark;
                if (cin >> mark && s.setMark(i, mark))
                {
                    cin.ignore();
                    break;
                }
                cout << "Invalid input! Enter between 0 and 100.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        // Additional information
        cout << "\nAdditional Information (optional):\n";

        while (true)
        {
            cout << "Email: ";
            getline(cin, input);
            if (input.empty() || s.setEmail(input))
                break;
            cout << "Invalid email format! Example: student@example.com\n";
        }

        while (true)
        {
            cout << "Phone (with country code, optional): ";
            getline(cin, input);
            if (input.empty() || s.setPhone(input))
                break;
            cout << "Invalid phone format! Example: +1234567890\n";
        }

        students.push_back(s);
        saveToFile();

        cout << "\nStudent added successfully!\n";
        cout << "  Roll Number: " << s.getRoll() << "\n";

        // Ask to view result
        cout << "\nDo you want to view the result? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore();
        
        if (tolower(choice) == 'y')
        {
            clearScreen();
            s.displayDetailed();
        }

        pauseScreen();
    }

    void editStudent()
    {
        clearScreen();
        cout << "\n"
             << string(50, '=') << "\n";
        cout << "           EDIT STUDENT\n";
        cout << string(50, '=') << "\n\n";

        string roll;
        cout << "Enter Roll Number: ";
        getline(cin, roll);

        int index = findStudentByRoll(roll);
        if (index == -1)
        {
            cout << "\nStudent not found!\n";
            pauseScreen();
            return;
        }

        Student &s = students[index];
        s.displayDetailed();

        cout << "\nWhat do you want to edit?\n";
        cout << "1. Name\n";
        cout << "2. Marks\n";
        cout << "3. Email\n";
        cout << "4. Phone\n";
        cout << "5. Toggle Active Status\n";
        cout << "6. Cancel\n";
        cout << "\nEnter choice: ";

        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 6)
        {
            cout << "Invalid choice! Enter 1-6: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            string name;
            while (true)
            {
                cout << "New Name: ";
                getline(cin, name);
                if (s.setName(name))
                    break;
                cout << "Invalid name!\n";
            }
            break;
        }
        case 2:
        {
            vector<string> subjects;
            if (s.getGroup() == "Pre-Medical")
            {
                subjects.push_back("Biology");
                subjects.push_back("Chemistry");
                subjects.push_back("Physics");
            }
            else if (s.getGroup() == "Pre-Engineering")
            {
                subjects.push_back("Mathematics");
                subjects.push_back("Chemistry");
                subjects.push_back("Physics");
            }
            else
            {
                subjects.push_back("Computer");
                subjects.push_back("Mathematics");
                subjects.push_back("Physics");
            }

            for (int i = 0; i < 3; i++)
            {
                while (true)
                {
                    cout << "New " << subjects[i] << " Marks: ";
                    double mark;
                    if (cin >> mark && s.setMark(i, mark))
                        break;
                    cout << "Invalid marks! Enter 0-100.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            cin.ignore();
            break;
        }
        case 3:
        {
            string email;
            while (true)
            {
                cout << "New Email: ";
                getline(cin, email);
                if (email.empty() || s.setEmail(email))
                    break;
                cout << "Invalid email format!\n";
            }
            break;
        }
        case 4:
        {
            string phone;
            while (true)
            {
                cout << "New Phone: ";
                getline(cin, phone);
                if (phone.empty() || s.setPhone(phone))
                    break;
                cout << "Invalid phone format!\n";
            }
            break;
        }
        case 5:
        {
            s.setActive(!s.getIsActive());
            cout << "\nStatus changed to: " 
                 << (s.getIsActive() ? "Active" : "Inactive") << "\n";
            break;
        }
        case 6:
            return;
        }

        saveToFile();
        cout << "\nStudent information updated successfully!\n";
        pauseScreen();
    }

    void deleteStudent()
    {
        clearScreen();
        cout << "\n"
             << string(50, '=') << "\n";
        cout << "           DELETE STUDENT\n";
        cout << string(50, '=') << "\n\n";

        string roll;
        cout << "Enter Roll Number: ";
        getline(cin, roll);

        int index = findStudentByRoll(roll);
        if (index == -1)
        {
            cout << "\nStudent not found!\n";
            pauseScreen();
            return;
        }

        Student s = students[index];
        s.displayDetailed();

        cout << "\nAre you sure you want to delete this student? (yes/no): ";
        string confirm;
        getline(cin, confirm);

        if (confirm == "yes" || confirm == "YES" || confirm == "Yes")
        {
            students.erase(students.begin() + index);
            saveToFile();

            // Update roll number counters
            initializeRollNumberCounters();

            // Create backup
            createBackup();

            cout << "\nStudent deleted successfully!\n";
        }
        else
        {
            cout << "\nDeletion cancelled.\n";
        }

        pauseScreen();
    }

    void searchStudent()
    {
        clearScreen();
        cout << "\n"
             << string(50, '=') << "\n";
        cout << "           SEARCH STUDENT\n";
        cout << string(50, '=') << "\n\n";

        cout << "Search by:\n";
        cout << "1. Roll Number\n";
        cout << "2. Name\n";
        cout << "3. Group\n";
        cout << "4. Grade\n";
        cout << "5. Status (Active/Inactive)\n";
        cout << "\nEnter choice: ";

        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 5)
        {
            cout << "Invalid choice! Enter 1-5: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        vector<Student> results;
        string searchTerm;

        switch (choice)
        {
        case 1:
        {
            cout << "Enter Roll Number: ";
            getline(cin, searchTerm);
            // Convert to uppercase
            for (size_t i = 0; i < searchTerm.length(); i++) 
                searchTerm[i] = toupper(searchTerm[i]);
            
            for (size_t i = 0; i < students.size(); i++)
            {
                if (students[i].getRoll() == searchTerm)
                {
                    results.push_back(students[i]);
                    break;
                }
            }
            break;
        }
        case 2:
        {
            cout << "Enter Name (or part of name): ";
            getline(cin, searchTerm);
            // Convert to lowercase for case-insensitive search
            for (size_t i = 0; i < searchTerm.length(); i++) 
                searchTerm[i] = tolower(searchTerm[i]);
            
            for (size_t i = 0; i < students.size(); i++)
            {
                string name = students[i].getName();
                for (size_t j = 0; j < name.length(); j++) 
                    name[j] = tolower(name[j]);
                
                if (name.find(searchTerm) != string::npos)
                {
                    results.push_back(students[i]);
                }
            }
            break;
        }
        case 3:
        {
            cout << "Enter Group: ";
            getline(cin, searchTerm);
            
            for (size_t i = 0; i < students.size(); i++)
            {
                if (students[i].getGroup() == searchTerm)
                {
                    results.push_back(students[i]);
                }
            }
            break;
        }
        case 4:
        {
            cout << "Enter Grade (A-F): ";
            getline(cin, searchTerm);
            if (!searchTerm.empty())
            {
                char grade = toupper(searchTerm[0]);
                for (size_t i = 0; i < students.size(); i++)
                {
                    if (students[i].getGrade() == grade)
                    {
                        results.push_back(students[i]);
                    }
                }
            }
            break;
        }
        case 5:
        {
            cout << "Enter Status (Active/Inactive): ";
            getline(cin, searchTerm);
            bool active = (searchTerm == "Active" || searchTerm == "active");
            
            for (size_t i = 0; i < students.size(); i++)
            {
                if (students[i].getIsActive() == active)
                {
                    results.push_back(students[i]);
                }
            }
            break;
        }
        }

        displaySearchResults(results);
        pauseScreen();
    }

    void displaySearchResults(const vector<Student>& results)
    {
        if (results.empty())
        {
            cout << "\nNo students found!\n";
            return;
        }

        clearScreen();
        cout << "\n"
             << string(110, '=') << "\n";
        cout << "                         SEARCH RESULTS\n";
        cout << string(110, '=') << "\n";
        cout << left << setw(25) << "NAME"
             << setw(15) << "ROLL"
             << setw(20) << "GROUP"
             << setw(12) << "PERCENTAGE"
             << setw(8) << "GRADE"
             << setw(10) << "STATUS"
             << setw(15) << "ADMISSION DATE" << "\n";
        cout << string(110, '-') << "\n";

        for (size_t i = 0; i < results.size(); i++)
        {
            results[i].displaySummary();
        }
        cout << string(110, '=') << "\n";
        cout << "Found: " << results.size() << " student(s)\n";

        if (results.size() == 1)
        {
            cout << "\nView detailed information? (y/n): ";
            char viewDetail;
            cin >> viewDetail;
            cin.ignore();
            if (tolower(viewDetail) == 'y')
            {
                clearScreen();
                results[0].displayDetailed();
            }
        }
    }

    void viewAllStudents()
    {
        clearScreen();
        if (students.empty())
        {
            cout << "\nNo students in the system!\n";
            pauseScreen();
            return;
        }

        // Sort by roll number
        vector<Student> sortedStudents = students;
        sort(sortedStudents.begin(), sortedStudents.end(),
             [](const Student &a, const Student &b)
             {
                 return a.getRoll() < b.getRoll();
             });

        cout << "\n"
             << string(110, '=') << "\n";
        cout << "                               ALL STUDENTS\n";
        cout << string(110, '=') << "\n";
        cout << left << setw(4) << "#"
             << setw(25) << "NAME"
             << setw(15) << "ROLL"
             << setw(20) << "GROUP"
             << setw(12) << "PERCENTAGE"
             << setw(8) << "GRADE"
             << setw(10) << "STATUS"
             << setw(15) << "ADMISSION DATE" << "\n";
        cout << string(110, '-') << "\n";

        int activeCount = 0;
        for (size_t i = 0; i < sortedStudents.size(); i++)
        {
            cout << setw(4) << i + 1;
            sortedStudents[i].displaySummary();
            if (sortedStudents[i].getIsActive()) activeCount++;
        }

        cout << string(110, '=') << "\n";
        cout << "Total Students: " << students.size() 
             << " (Active: " << activeCount << ", Inactive: " 
             << students.size() - activeCount << ")\n";

        displayStatistics();
        displayRollNumberStatistics();

        pauseScreen();
    }

    void generateReports()
    {
        clearScreen();
        cout << "\n"
             << string(50, '=') << "\n";
        cout << "           GENERATE REPORTS\n";
        cout << string(50, '=') << "\n\n";

        cout << "1. Class Toppers\n";
        cout << "2. Group-wise Report\n";
        cout << "3. Performance Statistics\n";
        cout << "4. Export to CSV\n";
        cout << "5. Roll Number Report\n";
        cout << "6. Grade Distribution\n";
        cout << "7. Attendance Report\n";
        cout << "8. Back\n";
        cout << "\nEnter choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            showToppers();
            break;
        case 2:
            showGroupReport();
            break;
        case 3:
            showStatistics();
            break;
        case 4:
            exportToCSV();
            break;
        case 5:
            showRollNumberReport();
            break;
        case 6:
            showGradeDistribution();
            break;
        case 7:
            showAttendanceReport();
            break;
        case 8:
            return;
        default:
            cout << "Invalid choice!\n";
            pauseScreen();
        }
    }

    void showToppers()
    {
        clearScreen();

        if (students.empty())
        {
            cout << "\nNo students in the system!\n";
            pauseScreen();
            return;
        }

        vector<Student> activeStudents;
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getIsActive()) {
                activeStudents.push_back(students[i]);
            }
        }

        if (activeStudents.empty()) {
            cout << "\nNo active students!\n";
            pauseScreen();
            return;
        }

        sort(activeStudents.begin(), activeStudents.end(),
             [](const Student &a, const Student &b)
             {
                 return a.getPercentage() > b.getPercentage();
             });

        cout << "\n"
             << string(60, '=') << "\n";
        cout << "                     TOPPER STUDENTS\n";
        cout << string(60, '=') << "\n\n";

        // Show top 3
        int topCount = min(3, (int)activeStudents.size());
        cout << "TOP " << topCount << " STUDENTS:\n";
        cout << string(40, '-') << "\n";
        
        for (int i = 0; i < topCount; i++) {
            cout << "\nRank " << (i + 1) << ":\n";
            cout << "Name: " << activeStudents[i].getName() << "\n";
            cout << "Roll: " << activeStudents[i].getRoll() << "\n";
            cout << "Percentage: " << fixed << setprecision(2) 
                 << activeStudents[i].getPercentage() << "%\n";
            cout << "Grade: " << activeStudents[i].getGrade() << "\n";
        }

        pauseScreen();
    }

    void showGroupReport()
    {
        clearScreen();

        map<string, vector<Student> > groupStudents;
        for (size_t i = 0; i < students.size(); i++)
        {
            if (students[i].getIsActive()) {
                groupStudents[students[i].getGroup()].push_back(students[i]);
            }
        }

        for (map<string, vector<Student> >::iterator it = groupStudents.begin(); 
             it != groupStudents.end(); ++it)
        {
            cout << "\n"
                 << string(90, '=') << "\n";
            cout << "                     " << it->first << " GROUP\n";
            cout << string(90, '=') << "\n";
            cout << left << setw(25) << "NAME"
                 << setw(15) << "ROLL"
                 << setw(12) << "PERCENTAGE"
                 << setw(8) << "GRADE"
                 << setw(15) << "ADMISSION DATE" << "\n";
            cout << string(90, '-') << "\n";

            for (size_t i = 0; i < it->second.size(); i++)
            {
                it->second[i].displaySummary();
            }

            // Group statistics
            double total = 0;
            for (size_t i = 0; i < it->second.size(); i++)
            {
                total += it->second[i].getPercentage();
            }
            cout << string(90, '=') << "\n";
            cout << "Group Average: " << fixed << setprecision(2)
                 << total / it->second.size() << "%\n";
            cout << "Students in group: " << it->second.size() << "\n";
        }

        pauseScreen();
    }

    void showGradeDistribution()
    {
        clearScreen();
        
        map<char, int> gradeCount;
        map<string, map<char, int> > groupGradeCount;
        
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getIsActive()) {
                gradeCount[students[i].getGrade()]++;
                groupGradeCount[students[i].getGroup()][students[i].getGrade()]++;
            }
        }
        
        cout << "\n" << string(60, '=') << "\n";
        cout << "               GRADE DISTRIBUTION\n";
        cout << string(60, '=') << "\n\n";
        
        cout << "OVERALL GRADE DISTRIBUTION:\n";
        cout << string(40, '-') << "\n";
        for (char grade = 'A'; grade <= 'F'; grade++) {
            if (gradeCount.find(grade) != gradeCount.end()) {
                double percentage = (gradeCount[grade] * 100.0) / students.size();
                cout << "Grade " << grade << ": " << gradeCount[grade] 
                     << " students (" << fixed << setprecision(1) 
                     << percentage << "%)\n";
            }
        }
        
        cout << "\nGROUP-WISE GRADE DISTRIBUTION:\n";
        for (map<string, map<char, int> >::iterator it = groupGradeCount.begin();
             it != groupGradeCount.end(); ++it) {
            cout << "\n" << it->first << ":\n";
            for (char grade = 'A'; grade <= 'F'; grade++) {
                if (it->second.find(grade) != it->second.end()) {
                    cout << "  Grade " << grade << ": " << it->second[grade] << "\n";
                }
            }
        }
        
        pauseScreen();
    }

    void showAttendanceReport()
    {
        clearScreen();
        
        int total = students.size();
        int active = 0;
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getIsActive()) active++;
        }
        
        double attendanceRate = (active * 100.0) / total;
        
        cout << "\n" << string(60, '=') << "\n";
        cout << "               ATTENDANCE REPORT\n";
        cout << string(60, '=') << "\n\n";
        
        cout << "Total Students: " << total << "\n";
        cout << "Active Students: " << active << "\n";
        cout << "Inactive Students: " << (total - active) << "\n";
        cout << "Attendance Rate: " << fixed << setprecision(2) 
             << attendanceRate << "%\n";
        
        if (attendanceRate < 80) {
            cout << "\nWarning: Low attendance rate!\n";
        }
        
        pauseScreen();
    }

    void backupRestore()
    {
        clearScreen();
        cout << "\n"
             << string(50, '=') << "\n";
        cout << "           BACKUP & RESTORE\n";
        cout << string(50, '=') << "\n\n";

        cout << "1. Create Backup\n";
        cout << "2. Restore from Backup\n";
        cout << "3. View Backup Info\n";
        cout << "4. Back\n";
        cout << "\nEnter choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            createBackup();
            break;
        case 2:
            restoreFromBackup();
            break;
        case 3:
            viewBackupInfo();
            break;
        case 4:
            return;
        default:
            cout << "Invalid choice!\n";
            pauseScreen();
        }
    }

    void createBackup()
    {
        string timestamp = getCurrentTimestamp();
        string backupName = "backup_" + timestamp + ".dat";
        
        ofstream backup(backupName.c_str());
        if (backup.is_open())
        {
            for (size_t i = 0; i < students.size(); i++)
            {
                backup << students[i].toFileString() << "\n";
            }
            backup.close();
            
            cout << "\nBackup created: " << backupName << "\n";
        }
        else
        {
            cout << "\nFailed to create backup!\n";
        }
        pauseScreen();
    }

    // ==================== PUBLIC ACCESS FUNCTIONS ====================

    void viewStudentResult()
    {
        clearScreen();
        cout << "\n"
             << string(50, '=') << "\n";
        cout << "         VIEW STUDENT RESULT\n";
        cout << string(50, '=') << "\n\n";

        string roll;
        cout << "Enter Roll Number: ";
        getline(cin, roll);

        int index = findStudentByRoll(roll);
        if (index == -1)
        {
            cout << "\nStudent not found!\n";
            pauseScreen();
            return;
        }

        clearScreen();
        students[index].displayDetailed();

        // Print option
        cout << "\nDo you want to print this result? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore();
        if (tolower(choice) == 'y')
        {
            printResult(students[index]);
        }

        pauseScreen();
    }

    void printStudentResult()
    {
        clearScreen();
        cout << "\n"
             << string(50, '=') << "\n";
        cout << "         PRINT STUDENT RESULT\n";
        cout << string(50, '=') << "\n\n";

        string roll;
        cout << "Enter Roll Number: ";
        getline(cin, roll);

        int index = findStudentByRoll(roll);
        if (index == -1)
        {
            cout << "\nStudent not found!\n";
            pauseScreen();
            return;
        }

        printResult(students[index]);
        cout << "\nResult printed successfully!\n";
        pauseScreen();
    }

private:
    // ==================== HELPER FUNCTIONS ====================

    int findStudentByRoll(const string &roll)
    {
        string rollUpper = roll;
        for (size_t i = 0; i < rollUpper.length(); i++) 
            rollUpper[i] = toupper(rollUpper[i]);
        
        for (size_t i = 0; i < students.size(); i++)
        {
            if (students[i].getRoll() == rollUpper)
            {
                return i;
            }
        }
        return -1;
    }

    void restoreFromBackup()
    {
        cout << "\nWarning: This will replace all current data!\n";
        cout << "Are you sure? (yes/no): ";
        string confirm;
        getline(cin, confirm);

        if (confirm != "yes")
        {
            cout << "Restore cancelled.\n";
            pauseScreen();
            return;
        }

        ifstream backup(backupFile.c_str());
        if (!backup.is_open())
        {
            cout << "\nCannot open backup file!\n";
            pauseScreen();
            return;
        }

        vector<Student> newStudents;
        string line;
        while (getline(backup, line))
        {
            if (!line.empty())
            {
                newStudents.push_back(Student::fromFileString(line));
            }
        }
        backup.close();
        
        students = newStudents;
        saveToFile();
        
        initializeRollNumberCounters();
        cout << "\nData restored successfully!\n";
        pauseScreen();
    }

    void viewBackupInfo()
    {
        cout << "\nBackup Information:\n";
        cout << string(40, '-') << "\n";
        
        // Check file sizes
        ifstream file(dataFile.c_str(), ios::binary | ios::ate);
        if (file.is_open()) {
            streamsize size = file.tellg();
            file.close();
            cout << "Main data file: " << size << " bytes\n";
        } else {
            cout << "Main data file: 0 bytes (not found)\n";
        }
        
        ifstream backup(backupFile.c_str(), ios::binary | ios::ate);
        if (backup.is_open()) {
            streamsize size = backup.tellg();
            backup.close();
            cout << "Backup file: " << size << " bytes\n";
        } else {
            cout << "Backup file: 0 bytes (not found)\n";
        }
        
        cout << "Total students: " << students.size() << "\n";
        
        pauseScreen();
    }

    void displayStatistics()
    {
        if (students.empty()) return;

        double totalPercentage = 0;
        map<char, int> gradeCount;
        map<string, int> groupCount;
        int passed = 0;
        int active = 0;

        for (size_t i = 0; i < students.size(); i++)
        {
            totalPercentage += students[i].getPercentage();
            gradeCount[students[i].getGrade()]++;
            groupCount[students[i].getGroup()]++;
            if (students[i].getGrade() != 'F') passed++;
            if (students[i].getIsActive()) active++;
        }

        double avgPercentage = totalPercentage / students.size();
        double passRate = (passed * 100.0) / students.size();
        double activeRate = (active * 100.0) / students.size();

        cout << "\n" << string(60, '-') << "\n";
        cout << "STATISTICS:\n";
        cout << string(60, '-') << "\n";
        cout << fixed << setprecision(2);
        cout << "Average Percentage: " << avgPercentage << "%\n";
        cout << "Pass Rate: " << passRate << "%\n";
        cout << "Active Students: " << activeRate << "%\n";
        cout << "Total Students: " << students.size() << "\n\n";

        // Find top performer
        if (!students.empty()) {
            Student maxStudent = students[0];
            for (size_t i = 1; i < students.size(); i++) {
                if (students[i].getPercentage() > maxStudent.getPercentage()) {
                    maxStudent = students[i];
                }
            }
            cout << "Top Performer: " << maxStudent.getName() 
                 << " (" << maxStudent.getPercentage() << "%)\n";
        }
    }

    void showStatistics()
    {
        clearScreen();
        displayStatistics();
        pauseScreen();
    }

    void showRollNumberReport()
    {
        clearScreen();

        cout << "\n"
             << string(90, '=') << "\n";
        cout << "                     ROLL NUMBER REPORT\n";
        cout << string(90, '=') << "\n";
        cout << left << setw(25) << "STUDENT NAME"
             << setw(15) << "ROLL NUMBER"
             << setw(20) << "GROUP"
             << setw(15) << "STATUS"
             << setw(20) << "ADMISSION DATE" << "\n";
        cout << string(90, '-') << "\n";

        // Sort by roll number
        vector<Student> sortedStudents = students;
        sort(sortedStudents.begin(), sortedStudents.end(),
             [](const Student &a, const Student &b)
             {
                 return a.getRoll() < b.getRoll();
             });

        for (size_t i = 0; i < sortedStudents.size(); i++)
        {
            cout << left << setw(25) << sortedStudents[i].getName()
                 << setw(15) << sortedStudents[i].getRoll()
                 << setw(20) << sortedStudents[i].getGroup()
                 << setw(15) << (sortedStudents[i].getIsActive() ? "Active" : "Inactive")
                 << setw(20) << sortedStudents[i].getAdmissionDate() << "\n";
        }

        cout << string(90, '=') << "\n";
        cout << "Total Students: " << students.size() << "\n\n";

        // Display roll number information
        displayRollNumberStatistics();

        pauseScreen();
    }

    void displayRollNumberStatistics()
    {
        map<string, int> groupCount;
        for (size_t i = 0; i < students.size(); i++)
        {
            if (students[i].getIsActive()) {
                groupCount[students[i].getGroup()]++;
            }
        }

        cout << "\n"
             << string(60, '-') << "\n";
        cout << "ROLL NUMBER STATISTICS:\n";
        cout << string(60, '-') << "\n";

        cout << "Active Students by Group:\n";
        for (map<string, int>::iterator it = groupCount.begin(); it != groupCount.end(); ++it)
        {
            cout << "  " << it->first << ": " << it->second << " students\n";
        }

        cout << "\nNext Available Roll Numbers:\n";
        cout << "  Pre-Medical: " << generateRollNumber("Pre-Medical") << "\n";
        cout << "  Pre-Engineering: " << generateRollNumber("Pre-Engineering") << "\n";
        cout << "  Computer Science: " << generateRollNumber("Computer Science") << "\n";
    }

    void exportToCSV()
    {
        string timestamp = getCurrentTimestamp();
        string filename = "students_report_" + timestamp + ".csv";
        
        ofstream csvFile(filename.c_str());
        if (!csvFile.is_open())
        {
            cout << "\nError creating CSV file!\n";
            pauseScreen();
            return;
        }

        // Write header
        csvFile << "Name,Roll Number,Group,Subject1,Subject2,Subject3,Total,Percentage,Grade,"
                << "Email,Phone,Admission Date,Last Modified,Status\n";

        // Write data
        for (size_t i = 0; i < students.size(); i++)
        {
            csvFile << "\"" << students[i].getName() << "\","
                    << students[i].getRoll() << ","
                    << students[i].getGroup() << ","
                    << students[i].getMark(0) << ","
                    << students[i].getMark(1) << ","
                    << students[i].getMark(2) << ","
                    << students[i].getTotalMarks() << ","
                    << students[i].getPercentage() << ","
                    << students[i].getGrade() << ","
                    << students[i].getEmail() << ","
                    << students[i].getPhone() << ","
                    << students[i].getAdmissionDate() << ","
                    << students[i].getLastModified() << ","
                    << (students[i].getIsActive() ? "Active" : "Inactive") << "\n";
        }

        csvFile.close();
        cout << "\nData exported to " << filename << " successfully!\n";
        pauseScreen();
    }

    void printResult(const Student &s)
    {
        ofstream printFile("print_result.txt");
        if (printFile.is_open())
        {
            printFile << "\n"
                      << string(60, '=') << "\n";
            printFile << "              OFFICIAL RESULT CARD\n";
            printFile << string(60, '=') << "\n\n";

            printFile << "Student Name    : " << s.getName() << "\n";
            printFile << "Roll Number     : " << s.getRoll() << "\n";
            printFile << "Group           : " << s.getGroup() << "\n";
            printFile << "Admission Date  : " << s.getAdmissionDate() << "\n\n";

            printFile << string(60, '-') << "\n";
            printFile << "MARKS OBTAINED:\n";
            printFile << string(60, '-') << "\n";

            vector<string> subjects;
            if (s.getGroup() == "Pre-Medical")
            {
                subjects.push_back("Biology");
                subjects.push_back("Chemistry");
                subjects.push_back("Physics");
            }
            else if (s.getGroup() == "Pre-Engineering")
            {
                subjects.push_back("Mathematics");
                subjects.push_back("Chemistry");
                subjects.push_back("Physics");
            }
            else
            {
                subjects.push_back("Computer");
                subjects.push_back("Mathematics");
                subjects.push_back("Physics");
            }

            for (int i = 0; i < 3; i++)
            {
                printFile << left << setw(20) << subjects[i] << ": "
                          << s.getMark(i) << "/100\n";
            }

            printFile << "\n"
                      << string(60, '-') << "\n";
            printFile << "Total Marks     : "
                      << s.getTotalMarks()
                      << "/300\n";
            printFile << "Percentage      : " << fixed << setprecision(2)
                      << s.getPercentage() << "%\n";
            printFile << "Grade           : " << s.getGrade() << "\n";
            printFile << string(60, '=') << "\n";

            printFile << "\nIssued Date: " << getCurrentDate() << "\n";
            printFile << "This is a computer generated result.\n";

            printFile.close();
            cout << "\nResult saved to print_result.txt\n";
        }
    }

    string getCurrentDate()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%B %d, %Y", ltm);
        return string(buffer);
    }

    string getCurrentTimestamp()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", ltm);
        return string(buffer);
    }

    void loadFromFile()
    {
        ifstream file(dataFile.c_str());
        if (!file.is_open()) {
            return;
        }

        students.clear();
        string line;
        int count = 0;
        while (getline(file, line))
        {
            if (!line.empty())
            {
                try {
                    students.push_back(Student::fromFileString(line));
                    count++;
                } catch (...) {
                    // Ignore errors
                }
            }
        }
        file.close();
    }

    void saveToFile()
    {
        ofstream file(dataFile.c_str());
        if (!file.is_open())
        {
            cout << "Error saving data!\n";
            return;
        }

        for (size_t i = 0; i < students.size(); i++)
        {
            file << students[i].toFileString() << "\n";
        }
        file.close();
    }

    void loadAdminCredentials()
    {
        ifstream file(configFile.c_str());
        if (!file.is_open())
        {
            // Default admin account
            adminCredentials["admin"] = "admin123";
            saveAdminCredentials();
            return;
        }

        string line;
        while (getline(file, line))
        {
            size_t pos = line.find(':');
            if (pos != string::npos)
            {
                string username = line.substr(0, pos);
                string password = line.substr(pos + 1);
                adminCredentials[username] = password;
            }
        }
        file.close();
    }

    void saveAdminCredentials()
    {
        ofstream file(configFile.c_str());
        if (file.is_open())
        {
            for (map<string, string>::iterator it = adminCredentials.begin(); 
                 it != adminCredentials.end(); ++it)
            {
                file << it->first << ":" << it->second << "\n";
            }
            file.close();
        }
    }
};

// ==================== MAIN MENU FUNCTIONS ====================

void displayMainMenu()
{
    clearScreen();
    cout << "\n"
         << string(70, '=') << "\n";
    cout << "       STUDENT RESULT MANAGEMENT SYSTEM v4.0\n";
    cout << "                ENHANCED EDITION\n";
    cout << "           Developed by: RAYYAN\n";
    cout << string(70, '=') << "\n";
    cout << "  1. Admin Login\n";
    cout << "  2. View Student Result\n";
    cout << "  3. Print Result\n";
    cout << "  4. About System\n";
    cout << "  5. Exit\n";
    cout << string(70, '=') << "\n";
}

void displayAdminMenu()
{
    clearScreen();
    cout << "\n"
         << string(60, '=') << "\n";
    cout << "               ADMIN PANEL v4.0\n";
    cout << "           Developed by: RAYYAN\n";
    cout << string(60, '=') << "\n";
    cout << "  1. Add New Student\n";
    cout << "  2. Edit Student\n";
    cout << "  3. Delete Student\n";
    cout << "  4. Search Student\n";
    cout << "  5. View All Students\n";
    cout << "  6. Generate Reports\n";
    cout << "  7. Change Admin Password\n";
    cout << "  8. Add Admin Account\n";
    cout << "  9. Backup & Restore\n";
    cout << " 10. System Log\n";
    cout << " 11. Logout\n";
    cout << string(60, '=') << "\n";
}

void displayAbout()
{
    clearScreen();
    cout << "\n"
         << string(70, '=') << "\n";
    cout << "               ABOUT SYSTEM v4.0\n";
    cout << string(70, '=') << "\n";
    cout << "Student Result Management System - Enhanced Edition\n";
    cout << "Version: 4.0\n";
    cout << "Developed by: RAYYAN\n";
    cout << "\nENHANCED FEATURES:\n";
    cout << "  ✓ Enhanced input validation\n";
    cout << "  ✓ Student status tracking (Active/Inactive)\n";
    cout << "  ✓ Advanced search with multiple criteria\n";
    cout << "  ✓ Auto roll number generation\n";
    cout << "  ✓ Multiple report types\n";
    cout << "  ✓ Backup and restore functionality\n";
    cout << "  ✓ CSV export with timestamps\n";
    cout << "  ✓ Grade distribution analysis\n";
    cout << "\nROLL NUMBER SYSTEM:\n";
    cout << "  PMXXX: Pre-Medical (e.g., PM001, PM002)\n";
    cout << "  PEXXX: Pre-Engineering (e.g., PE001, PE002)\n";
    cout << "  CSXXX: Computer Science (e.g., CS001, CS002)\n";
    cout << string(70, '=') << "\n";
    cout << "\nPress Enter to continue...";
    cin.get();
}

void viewSystemLog()
{
    ifstream logFile("system_log.txt");
    if (!logFile.is_open())
    {
        cout << "\nNo system log found!\n";
        return;
    }

    clearScreen();
    cout << "\n"
         << string(90, '=') << "\n";
    cout << "                     SYSTEM LOG\n";
    cout << "                Developed by: RAYYAN\n";
    cout << string(90, '=') << "\n\n";

    string line;
    while (getline(logFile, line))
    {
        cout << line << "\n";
    }
    logFile.close();

    cout << "\n"
         << string(90, '=') << "\n";
    cout << "\nPress Enter to continue...";
    cin.get();
}

// ==================== MAIN FUNCTION ====================

int main()
{
    // For Windows, set console to UTF-8
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif
    
    StudentResultSystem studentSystem;
    int choice;

    while (true)
    {
        displayMainMenu();
        cout << "\nEnter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Please enter a number.\n";
            cout << "\nPress Enter to continue...";
            cin.get();
            continue;
        }
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            if (studentSystem.adminLogin())
            {
                int adminChoice;
                while (true)
                {
                    displayAdminMenu();
                    cout << "\nEnter your choice: ";

                    if (!(cin >> adminChoice))
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    cin.ignore();

                    switch (adminChoice)
                    {
                    case 1:
                        studentSystem.addStudent();
                        break;
                    case 2:
                        studentSystem.editStudent();
                        break;
                    case 3:
                        studentSystem.deleteStudent();
                        break;
                    case 4:
                        studentSystem.searchStudent();
                        break;
                    case 5:
                        studentSystem.viewAllStudents();
                        break;
                    case 6:
                        studentSystem.generateReports();
                        break;
                    case 7:
                        studentSystem.changeAdminPassword();
                        break;
                    case 8:
                        studentSystem.addAdminAccount();
                        break;
                    case 9:
                        studentSystem.backupRestore();
                        break;
                    case 10:
                        viewSystemLog();
                        break;
                    case 11:
                        break;
                    default:
                        cout << "\nInvalid choice!\n";
                        cout << "\nPress Enter to continue...";
                        cin.get();
                    }

                    if (adminChoice == 11)
                        break;
                }
            }
            break;
        }
        case 2:
            studentSystem.viewStudentResult();
            break;
        case 3:
            studentSystem.printStudentResult();
            break;
        case 4:
            displayAbout();
            break;
        case 5:
            cout << "\nThank you for using Student Result Management System v4.0!\n";
            cout << "Developed by: RAYYAN\n";
            cout << "Goodbye!\n";
            return 0;
        default:
            cout << "\nInvalid choice! Please try again.\n";
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    }

    return 0;
}