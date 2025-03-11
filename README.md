# 📚 Library Management System

## 📂 Project Structure

```
📂 LibraryManagementSystem/
│── 📄 main.c             // Entry point (login & menu)
│── 📄 admin.c            // Admin functions (book management, reports)
│── 📄 student.c          // Student functions (borrow, return, reserve)
│── 📄 transactions.c     // Issue/Return books, Fine calculation
│── 📄 utils.c            // UI, validation, loading effects
│── 📄 database.c         // File operations (read/write books, users, transactions)
│── 📄 headers.h          // Common structs & function prototypes
│── 📂 backup/            // Automatic backup directory
│── 📄 books.dat          // Stores book data (binary file)
│── 📄 users.dat          // Stores user data (binary file)
│── 📄 transactions.dat   // Stores transactions (borrow/return logs)
│── 📄 fines.dat          // Stores fine-related data
│── 📄 reports.csv        // Inventory & overdue reports
```

# 📜 Description

The **Library Management System** is a C-based program that helps manage books, users, transactions, and fines efficiently. It includes administrative controls, student access, and real-time transaction handling.

### 📌 Features:

- **Admin Functions**: Add, remove, or update books, generate reports.
- **Student Functions**: Borrow, return, and reserve books.
- **Transaction Handling**: Logs borrow/return activities and calculates fines.
- **Statistics & Reports**: Tracks popular books, generates fine revenue reports.
- **Data Management**: Uses binary files for efficient data storage and retrieval.

---

🚀 _Developed with C for 1st semester project of Computer Programming!_
