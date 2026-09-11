# Student Result Management System v2.0

A modern, modular C++ application for managing student results with authentication, role-based access control, and comprehensive reporting features.

## 🎯 Features

- **User Authentication & Authorization**
  - Admin, Teacher, Student, and Guest roles
  - Role-based permission system
  - Secure login with attempt limiting

- **Student Management**
  - Add, edit, delete students
  - Automatic roll number generation
  - Track admission dates and last modified timestamps
  - Contact information (email, phone)

- **Result Processing**
  - Calculate percentages and grades automatically
  - Support for multiple academic groups (Pre-Medical, Pre-Engineering, CS)
  - Subject-specific mark tracking
  - Comprehensive grading scale (A-F)

- **Search & Filter**
  - Search by name, roll number, group, or grade
  - Advanced filtering capabilities
  - Sorting by percentage, name, roll, or grade

- **Statistics & Reporting**
  - Overall statistics dashboard
  - Group-wise performance analysis
  - Top student identification
  - Pass/fail tracking

- **Data Management**
  - Persistent data storage (file-based)
  - Automatic backup creation
  - Restore from backup functionality
  - Data integrity validation

## 📁 Project Structure

```
result-managment/
├── include/                    # Header files
│   ├── Student.h              # Student data model
│   ├── Utils.h                # Validation utilities
│   ├── ResultCalculator.h     # Grade calculations
│   ├── DatabaseManager.h      # Data persistence
│   ├── ResultManager.h        # Business logic
│   └── User.h                 # Authentication
├── src/                        # Implementation files
│   ├── Student.cpp
│   ├── Utils.cpp
│   ├── ResultCalculator.cpp
│   ├── DatabaseManager.cpp
│   ├── ResultManager.cpp
│   ├── User.cpp
│   └── main.cpp               # Application entry point
├── CMakeLists.txt             # CMake build configuration
├── Makefile                   # Make build configuration
└── README.md                  # This file
```

## 🏗️ Architecture

### Layered Architecture

1. **Presentation Layer** (`main.cpp`)
   - User interface and menu system
   - Input/output handling

2. **Business Logic Layer** (`ResultManager.cpp`)
   - Student management operations
   - Search and filter logic
   - Statistical calculations

3. **Data Access Layer** (`DatabaseManager.cpp`)
   - File I/O operations
   - Data persistence
   - Backup/restore functionality

4. **Utility Layer**
   - Validation (`Utils.cpp`)
   - Calculations (`ResultCalculator.cpp`)
   - Authentication (`User.cpp`)

### Design Patterns Used

- **Separation of Concerns**: Each class has a single responsibility
- **Encapsulation**: Private members with public interfaces
- **Data Validation**: Input validation at entry points
- **Role-Based Access Control**: Permission checks before operations

## 🚀 Getting Started

### Prerequisites

- C++ compiler (g++, clang, or MSVC)
- CMake 3.10+ or Make
- Linux/Windows/macOS

### Building with Make

```bash
make build          # Build the project
make run            # Build and run
make clean          # Remove build artifacts
make help           # Show all commands
```

### Building with CMake

```bash
mkdir build
cd build
cmake ..
make
./bin/result_management
```

## 👤 Default Login Credentials

| Username | Password | Role  |
|----------|----------|-------|
| admin    | admin123 | Admin |

**⚠️ Note**: Change default credentials immediately after first login!

## 📊 Grading Scale

| Grade | Percentage Range | Description     |
|-------|-----------------|-----------------|
| A     | 85-100          | Excellent       |
| B     | 75-84           | Very Good       |
| C     | 65-74           | Good            |
| D     | 55-64           | Satisfactory    |
| E     | 45-54           | Pass            |
| F     | 0-44            | Fail            |

## 🔐 Role Permissions

### Admin
- ✓ Add/Edit/Delete Students
- ✓ View all results
- ✓ Manage user accounts
- ✓ Create backups
- ✓ Access all reports

### Teacher
- ✓ Add/Edit Students
- ✓ View all results
- ✓ Access reports
- ✗ Delete students
- ✗ Manage users

### Student
- ✓ View own results
- ✗ Add/Edit/Delete students
- ✗ Manage users

### Guest
- ✓ Limited read-only access

## 📝 File Formats

### Student Data File (`students.dat`)

Pipe-delimited format:
```
Name|Roll|Group|Mark1|Mark2|Mark3|Percentage|Grade|AdmissionDate|Email|Phone|Active|LastModified
```

### Credentials File (`system_config.dat`)

Colon-delimited format:
```
username:password
```

## 🔄 Workflow Examples

### Adding a Student

1. Login as Admin or Teacher
2. Select "Add New Student" from menu
3. Enter student details
4. Confirm marks (0-100 per subject)
5. System auto-generates roll number and calculates results

### Viewing Statistics

1. Login as Admin or Teacher
2. Select "View Statistics"
3. See aggregated performance data
4. Identify top performers and pass/fail rates

### Creating Backup

1. Login as Admin
2. Select "Create Backup"
3. Backup file created with timestamp
4. System creates `backup_YYYYMMDD_HHMMSS.dat`

## 🐛 Known Limitations

- File-based storage (not suitable for large datasets)
- Single-threaded operation
- Basic password storage (TODO: implement bcrypt hashing)
- No database backend

## 📈 Future Enhancements

- [ ] Database backend (SQLite/MySQL)
- [ ] Web-based interface
- [ ] Advanced reporting (graphs, charts)
- [ ] Email notifications
- [ ] Multi-session support
- [ ] Audit logging
- [ ] Export to PDF/Excel

## 📄 License

This project is open source and available under the MIT License.

## 👨‍💻 Development Team

- **Rayyan** - Lead Developer

## 📞 Support

For issues, questions, or suggestions, please open an issue on GitHub.

---

**Version**: 2.0  
**Last Updated**: 2026-09-11  
**Status**: Active Development
