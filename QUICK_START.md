# Quick Start Guide

Get up and running with the Student Result Management System in 5 minutes!

## 📋 Prerequisites

- **C++ Compiler**: g++, clang, or MSVC
- **Build Tools**: Make or CMake 3.10+
- **OS**: Linux, Windows (with WSL), or macOS

## 🚀 Quick Start (5 Minutes)

### Option 1: Using Make (Fastest)

```bash
# Clone the repository
git clone https://github.com/RAYYAN-HTML/result-managment.git
cd result-managment

# Build the project
make build

# Run the application
make run
```

### Option 2: Using CMake

```bash
# Clone and navigate
git clone https://github.com/RAYYAN-HTML/result-managment.git
cd result-managment

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run
./bin/result_management
```

## 🔑 First Login

```
Username: admin
Password: admin123
```

**⚠️ Change the default password immediately!**

## 📖 First Steps

### 1. Change Admin Password
```
Main Menu → 8. Change Password
```

### 2. Add Some Students
```
Main Menu → 2. Add New Student
Enter: Name, Group, Marks (0-100 for each subject)
```

### 3. View Results
```
Main Menu → 1. View All Students
Shows: Name, Roll, Group, Percentage, Grade
```

### 4. View Statistics
```
Main Menu → 5. View Statistics
Shows: Total, Passed, Failed, Average, Top Student
```

## 👥 User Roles

| Role    | Can Add | Can Edit | Can Delete | Can Report | Can Backup |
|---------|---------|----------|-----------|-----------|-----------|
| Admin   | ✓       | ✓        | ✓         | ✓         | ✓         |
| Teacher | ✓       | ✓        | ✗         | ✓         | ✗         |
| Student | ✗       | ✗        | ✗         | Own only  | ✗         |
| Guest   | ✗       | ✗        | ✗         | Limited   | ✗         |

## 📊 Grading Scale

| Grade | Percentage |
|-------|-----------|
| A     | 85-100    |
| B     | 75-84     |
| C     | 65-74     |
| D     | 55-64     |
| E     | 45-54     |
| F     | 0-44      |

## 🎓 Add a Student - Step by Step

```
1. Login as Admin
   Username: admin
   Password: admin123

2. Select "2. Add New Student" from menu

3. Enter Details:
   Name: John Ahmed
   Group: Pre-Medical
   Mark 1 (Biology): 85
   Mark 2 (Chemistry): 92
   Mark 3 (Physics): 78

4. Student is added with:
   - Auto-generated Roll Number
   - Auto-calculated Percentage: 85%
   - Auto-calculated Grade: A
   - Timestamp recorded
```

## 🔍 Search Features

### By Name
```
Main Menu → 6. Search Students → 1. Search by Name
Enter: "John"
Shows: All students with "John" in name
```

### By Roll Number
```
Main Menu → 6. Search Students → 2. Search by Roll
Enter: "2024001"
Shows: Exact roll number match
```

### By Grade
```
Main Menu → 6. Search Students → 3. Search by Grade
Enter: "A"
Shows: All students with A grade
```

## 💾 Backup & Restore

### Create Backup
```
Main Menu → 7. Create Backup
Creates: backup_YYYYMMDD_HHMMSS.dat
```

### Restore Backup
```
Note: Restore requires manual file replacement
1. Backup current students.dat
2. Replace with backup_YYYYMMDD_HHMMSS.dat
3. Restart application
```

## 📁 Data Files

Located in the application directory:

```
students.dat          # Student records (pipe-delimited)
system_config.dat     # User credentials
backup_*.dat          # Timestamped backups
```

## 🛠️ Common Commands

```bash
# Build only
make build

# Build and run
make run

# Clean build artifacts
make clean

# Show all commands
make help

# With CMake
cmake ..              # Configure
make                  # Build
./bin/result_management  # Run
```

## ⚡ Tips & Tricks

### Efficient Navigation
- Use numeric input for menu selection
- Press Enter to confirm input
- Use 'q' or '0' to go back/exit

### Marks Input
- Valid range: 0-100
- Decimal marks supported (e.g., 85.5)
- Invalid marks rejected with error message

### Performance Tips
- Create backups regularly
- Manage students count (works best with <1000 records)
- Clean old backup files periodically

## 🐛 Troubleshooting

### Build Issues

**Error: "g++: command not found"**
```bash
# Install g++ (Linux)
sudo apt-get install g++

# Or use clang
clang++ --version
```

**Error: "cmake: command not found"**
```bash
# Install CMake
sudo apt-get install cmake
```

### Runtime Issues

**Error: "Failed to load credentials"**
- Delete system_config.dat
- Application will recreate with default admin account

**Error: "No students found"**
- Add new students first
- Check if students.dat is accessible

**Login fails**
- Default: username=admin, password=admin123
- Check capslock
- Verify file permissions

## 📚 Learn More

- **README.md** - Full feature documentation
- **ARCHITECTURE.md** - System design details
- **CONTRIBUTING.md** - Development guidelines

## 🚨 Important Notes

1. **Default Password**: Change immediately after first login
2. **File-based Storage**: Not suitable for very large datasets (>10k records)
3. **No Encryption**: Data stored in plain text files
4. **Single User**: Only one user can run simultaneously
5. **Backups**: Manual backup management required

## 💡 Next Steps

After setup, explore:

1. ✓ Add sample students
2. ✓ View statistics dashboard
3. ✓ Search for specific records
4. ✓ Create your first backup
5. ✓ Change admin password
6. ✓ Add new users (Admin only)

## 📞 Need Help?

- Check **ARCHITECTURE.md** for system design
- Review **README.md** for all features
- Open an issue on GitHub

---

**Happy Result Management! 🎉**
