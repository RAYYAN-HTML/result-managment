# Architecture Documentation

## System Overview

The Student Result Management System follows a **layered architecture** pattern with clear separation of concerns. This document outlines the architectural design and component interactions.

## Architecture Layers

```
┌─────────────────────────────────────────────┐
│         PRESENTATION LAYER                  │
│  (main.cpp - Application & UI)              │
└──────────────────┬──────────────────────────┘
                   │
┌──────────────────▼──────────────────────────┐
│      BUSINESS LOGIC LAYER                   │
│  (ResultManager - Core Operations)          │
└──────────────────┬──────────────────────────┘
                   │
      ┌────────────┼────────────┐
      │            │            │
┌─────▼────┐ ┌────▼──────┐ ┌──▼────────┐
│ Student  │ │ResultCalc │ │ User Auth │
│ Manager  │ │ulator     │ │ Manager   │
└─────┬────┘ └────┬──────┘ └──┬────────┘
      │           │           │
      └───────────┼───────────┘
                  │
┌─────────────────▼──────────────────────────┐
│      DATA ACCESS LAYER                      │
│  (DatabaseManager - Persistence)           │
└──────────────────┬──────────────────────────┘
                   │
      ┌────────────┼────────────┐
      │            │            │
  ┌───▼──┐  ┌─────▼────┐  ┌────▼─────┐
  │File  │  │Credentials│  │ Backups  │
  │I/O   │  │Storage   │  │Storage   │
  └──────┘  └──────────┘  └──────────┘
```

## Component Responsibilities

### 1. **Presentation Layer** (`src/main.cpp`)

**Responsibility**: User interface and interaction

```cpp
class Application
- run()                    // Main application loop
- loginScreen()           // Authentication UI
- mainMenu()             // Main menu navigation
- viewAllStudents()      // Display students
- addStudent()           // Add new student UI
- editStudent()          // Modify student UI
- deleteStudent()        // Remove student UI
- viewStatistics()       // Display reports
- searchStudents()       // Search interface
- createBackup()         // Backup UI
- changePassword()       // Password change UI
```

**Dependencies**: ResultManager, AuthenticationManager, Utils

---

### 2. **Business Logic Layer** (`src/ResultManager.cpp`)

**Responsibility**: Core business operations and workflows

```cpp
class ResultManager
// Student Operations
- addStudent()           // Create new student
- getStudentByRoll()     // Retrieve student
- updateStudentName()    // Modify name
- updateStudentMarks()   // Update marks
- updateStudentEmail()   // Modify email
- deleteStudent()        // Remove student

// Search & Filter
- searchByRoll()         // Find by roll number
- searchByName()         // Find by name
- searchByGroup()        // Find by group
- searchByGrade()        // Find by grade
- searchByStatus()       // Find by status

// Sorting
- sortByPercentage()     // Sort by percentage
- sortByName()           // Sort by name
- sortByRoll()           // Sort by roll
- sortByGrade()          // Sort by grade

// Analytics
- getStatistics()        // Overall statistics
- getGroupStatistics()   // Group-wise stats

// Utility
- generateRollNumber()   // Auto-generate roll
- save()                 // Persist data
- load()                 // Load data
- createBackup()         // Backup system
- restoreFromBackup()    // Restore system
```

**Dependencies**: Student, DatabaseManager, ResultCalculator, Utils

---

### 3. **Student Model** (`src/Student.cpp`)

**Responsibility**: Student data representation and validation

```cpp
class Student
// Core Data
- name, roll, group
- marks[3] (array for 3 subjects)
- percentage, grade
- email, phone
- admissionDate, lastModified
- isActive (boolean)

// Operations
- getMark()              // Get individual mark
- getTotalMarks()        // Calculate total
- setName()              // Validate & set name
- setMark()              // Validate & set mark
- setEmail()             // Validate & set email
- calculateResult()      // Auto-calculate grade
- toFileString()         // Serialize to file
- fromFileString()       // Deserialize from file
```

**Dependencies**: ResultCalculator, Utils, iostream

---

### 4. **Calculation Engine** (`src/ResultCalculator.cpp`)

**Responsibility**: Pure calculation logic (stateless)

```cpp
class ResultCalculator (static methods only)
- calculatePercentage()  // Marks → percentage
- calculateGrade()       // Percentage → grade
- calculateGPA()         // Percentage → GPA
- isPassed()             // Check pass/fail
- isValidMarks()         // Validate mark range
- getGradeDescription()  // Grade → description
- displayGradingScale()  // Show grading rules
```

**Key Feature**: Stateless utility class - pure functions

---

### 5. **Authentication System** (`src/User.cpp`)

**Responsibility**: User authentication and authorization

```cpp
class User
- username, passwordHash
- role (ADMIN, TEACHER, STUDENT, GUEST)
- isActive, createdDate, lastLogin

// Permissions
- canAddStudent()        // Check permission
- canEditStudent()       // Check permission
- canDeleteStudent()     // Check permission
- canViewAllResults()    // Check permission
- canEnterMarks()        // Check permission
- canModifyResults()     // Check permission
- canManageUsers()       // Check permission
- canCreateBackup()      // Check permission

class AuthenticationManager
- login()                // Authenticate user
- logout()               // Clear session
- addUser()              // Create user (admin)
- removeUser()           // Delete user (admin)
- updateUserRole()       // Change role (admin)
- changePassword()       // Modify password
```

**Key Features**:
- Role-based access control (RBAC)
- Default admin account
- Session management

---

### 6. **Database Layer** (`src/DatabaseManager.cpp`)

**Responsibility**: Persistent data storage

```cpp
class DatabaseManager
// File Management
- loadStudents()         // Read from file
- saveStudents()         // Write to file
- createBackup()         // Create timestamped backup
- restoreFromBackup()    // Restore from backup

// Credentials
- loadAdminCredentials() // Read credentials
- saveAdminCredentials() // Write credentials

// Utility
- fileExists()           // Check file presence
- getFileSize()          // Get file size
- deleteFile()           // Remove file
- getCurrentTimestamp()  // Generate timestamp
```

**Data Format**: Pipe-delimited text files

---

### 7. **Utility Library** (`src/Utils.cpp`)

**Responsibility**: Common helper functions

```cpp
class InputValidator (static methods)
- isValidName()          // Name validation
- isValidMark()          // Mark range check
- isValidRollNumber()    // Roll format check
- isValidEmail()         // Email validation
- isValidPhone()         // Phone validation
- capitalizeName()       // Proper case
- toLowercase()          // Convert to lowercase
- toUppercase()          // Convert to uppercase

class SystemUtils (static methods)
- clearScreen()          // Clear console
- pauseScreen()          // Wait for input
- getPassword()          // Read password
```

**Key Feature**: All validation logic in one place

---

## Data Flow

### Adding a New Student

```
User Interface (main.cpp)
    ↓
Input Validation (Utils.cpp)
    ↓
ResultManager::addStudent()
    ↓
Student::Student() constructor
    ↓
ResultCalculator::calculatePercentage()
    ↓
ResultCalculator::calculateGrade()
    ↓
DatabaseManager::saveStudents()
    ↓
File I/O (students.dat)
```

### Searching for Students

```
User Interface (main.cpp)
    ↓
ResultManager::searchBy*()
    ↓
Linear search through student vector
    ↓
Filter matching students
    ↓
Return results to UI
    ↓
Display in formatted table
```

### Authentication Flow

```
Login Screen (main.cpp)
    ↓
Input Validation (Utils.cpp)
    ↓
AuthenticationManager::login()
    ↓
User::verifyPassword()
    ↓
Set currentUser session
    ↓
Load restricted menu options
```

---

## Design Patterns Used

### 1. **Separation of Concerns**
Each class has a single, well-defined responsibility:
- Model classes (Student, User)
- Business logic (ResultManager)
- Data access (DatabaseManager)
- Utilities (Utils)

### 2. **Encapsulation**
- Private member variables
- Public getter/setter methods
- Input validation at boundaries

### 3. **Role-Based Access Control (RBAC)**
Permission methods check user role before allowing operations

### 4. **Static Utility Classes**
Stateless helper methods in Utils and ResultCalculator

### 5. **File-Based Repository Pattern**
DatabaseManager encapsulates all persistence logic

---

## Scalability Considerations

### Current Limitations
- In-memory student vector (not suitable for >10k records)
- File-based storage (performance degradation with size)
- No database indexing
- Single-threaded operations

### Future Improvements
- **Database Backend**: Replace file I/O with SQLite/MySQL
- **Caching Layer**: Cache frequently accessed data
- **Async Operations**: Non-blocking I/O for large datasets
- **API Layer**: REST API for external integrations
- **Microservices**: Separate authentication and calculation services

---

## Security Considerations

### Current Implementation
- ⚠️ Plain-text password storage (TODO)
- ⚠️ No encryption of data files (TODO)
- ⚠️ No audit logging (TODO)
- ✓ Input validation
- ✓ Permission checking

### Recommended Enhancements
1. **Password Security**
   - Implement bcrypt or PBKDF2 hashing
   - Add salt to stored passwords

2. **Data Encryption**
   - Encrypt sensitive files at rest
   - Use HTTPS for network communication

3. **Audit Logging**
   - Log all user actions
   - Track data modifications

4. **Access Control**
   - Implement row-level security
   - Add data ownership tracking

---

## Testing Strategy

### Unit Tests (Recommended)
- `ResultCalculator` - Pure function testing
- `InputValidator` - Boundary condition testing
- `Student` - Data model integrity

### Integration Tests (Recommended)
- ResultManager operations
- DatabaseManager I/O
- AuthenticationManager workflows

### System Tests (Recommended)
- Complete user workflows
- Data persistence and recovery
- Performance under load

---

## Deployment Architecture

```
Development Machine
    ↓
Source Code (Git)
    ↓
Compile (Make/CMake)
    ↓
Unit Tests (CTest)
    ↓
Binary Executable
    ↓
Deployment Directory
    ↓
Runtime Data Files (students.dat, backups/)
```

---

## Conclusion

This architecture provides a clean, maintainable foundation for the Student Result Management System. Clear separation of concerns allows for easy testing, modification, and future enhancements without affecting other components.
