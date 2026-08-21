# Software Development Training Showcase

Welcome to my **Software Development Training Showcase** repository. This repository documents my practical training journey, hands-on tasks, and problem-solving exercises in modern **C++**, backend software engineering, object-oriented software design, multithreaded systems, file management, and RESTful web services.

---

## What I Learned

### C++ & Modern C++
* Applied modern C++ standards (C++11/C++17) for clean memory management and type safety.
* Leveraged standard library header features such as `<memory>` (`std::unique_ptr`, `std::shared_ptr`), `<filesystem>`, and modern standard container utilities.
* Structured modular programs separating declarations (`.h`) and implementations (`.cpp`).

### Object-Oriented Programming (OOP) & SOLID Principles
* Implemented core OOP concepts: encapsulation, inheritance, polymorphism, and abstract base classes.
* Designed extensible components adhering to Single Responsibility and Open/Closed principles.
* Utilized factory methods and abstract base interfaces to isolate business logic from object creation.

### Multithreading & Concurrency
* Developed concurrent execution models using `std::thread`, `std::mutex`, `std::lock_guard`, and `std::scoped_lock` for safe concurrent state access.
* Implemented deadlock-prevention strategies when operating on multiple concurrent resources simultaneously.
* Managed inter-thread coordination and metrics using `std::condition_variable` and atomic operations (`std::atomic`).

### Design Patterns
* Solved recurring design challenges by implementing foundational design patterns:
  * **Behavioral**: Strategy Pattern (dynamically interchangeable payment strategies), Observer Pattern (event notifications).
  * **Creational**: Factory Pattern (dynamic object creation), Builder Pattern (step-by-step object construction), Singleton Pattern (thread-safe global loggers).
  * **Structural**: Adapter Pattern (interface unification), Decorator Pattern (dynamic behavior decoration).

### File Systems & I/O Operations
* Built file system interaction engines using C++17 `<filesystem>` (`std::filesystem::path`, `directory_iterator`).
* Implemented recursive tree navigation, directory creation, file creation, writing, and structured text parsing using C++ standard file streams (`std::ifstream`, `std::ofstream`).

### Database Concepts & Normalization
* Simulated relational database architecture in-memory.
* Implemented relational primary and foreign key mapping across C++ `struct` collections.
* Modeled First Normal Form (**1NF**), Second Normal Form (**2NF**), and Third Normal Form (**3NF**) principles to eliminate data redundancy and partial dependencies without an external DBMS engine.

### Networking & REST APIs
* Implemented lightweight HTTP client and server applications using C++.
* Constructed RESTful HTTP endpoints (`GET`, `POST`, `PUT`, `DELETE`) with route matching and query parameters.
* Handled request validation, JSON payload serialization, deserialization (`nlohmann/json`), and appropriate HTTP response status codes (`200`, `201`, `400`, `404`).

---

## Projects & Practical Work

### 1. Multi-Threaded Banking System
* **Description**: A concurrent banking application designed to handle asynchronous client transactions safety across multiple threads.
* **Main Technologies / Concepts**: Modern C++, `std::thread`, `std::mutex`, `std::scoped_lock`, `std::atomic`, `std::condition_variable`.
* **Key Skills Practiced**: Thread safety, avoiding race conditions, preventing deadlocks during multi-account transfers, and atomic transaction counters.

### 2. C++ REST API Client & Server
* **Description**: A lightweight user management backend service and corresponding client script interacting over HTTP.
* **Main Technologies / Concepts**: C++, `cpp-httplib`, `nlohmann/json`, REST architecture, HTTP routing, JSON parsing.
* **Key Skills Practiced**: Developing RESTful HTTP service endpoints, processing incoming JSON request bodies, building custom client HTTP calls, and enforcing HTTP status conventions.

### 3. Design Patterns Case Suite
* **Description**: A collection of refactored real-world software design scenarios moving from rigid code to clean pattern implementations.
* **Main Technologies / Concepts**: Modern C++, Strategy, Factory, Singleton, Observer, Decorator, Adapter, Builder patterns.
* **Key Skills Practiced**: Writing loose-coupled, flexible code, eliminating code duplication, and applying SOLID design principles.

### 4. C++ File Manager
* **Description**: An interactive command-line utility for navigating and manipulating file system hierarchies.
* **Main Technologies / Concepts**: C++17 `<filesystem>`, File I/O Streams (`std::ifstream`, `std::ofstream`), Dynamic Directory Trees.
* **Key Skills Practiced**: Directory traversal, path manipulation, file reading/writing, and building structural composite file trees.

### 5. Simulated Normalized Bank Database
* **Description**: An in-memory relational database model designed to practice database normalization concepts in C++.
* **Main Technologies / Concepts**: C++ `struct`, `std::vector`, Database Normalization (1NF, 2NF, 3NF), Relational Keys.
* **Key Skills Practiced**: Organizing data schema into normalized relational entities and maintaining relational integrity with primary/foreign key mappings.

### 6. OOP Bank System
* **Description**: A modular bank account management system built using object-oriented principles and creational factory patterns.
* **Main Technologies / Concepts**: Polymorphism, Abstract Base Classes, Header/Implementation Separation, Factory Pattern.
* **Key Skills Practiced**: Object-oriented system modeling, class inheritance hierarchies, and dynamic object initialization.

### 7. Student Grade Management System
* **Description**: A foundational console application for recording student records, validating input, and performing statistical calculations.
* **Main Technologies / Concepts**: Procedural C++, Dynamic Arrays, Input Validation Functions.
* **Key Skills Practiced**: Input sanitization, buffer error handling, and structured console application flow.

---

## Technical Skills

* **Languages**: C++ (C++11, C++17)
* **Libraries & Frameworks**: C++ Standard Template Library (STL), `cpp-httplib`, `nlohmann/json`
* **Software Design & Architecture**: Object-Oriented Programming (OOP), SOLID Principles, Design Patterns (Strategy, Factory, Singleton, Observer, Decorator, Adapter, Builder)
* **Concurrent Programming**: Multithreading (`std::thread`), Mutex Locking (`std::mutex`, `std::scoped_lock`), Atomic Operations (`std::atomic`), Synchronization (`std::condition_variable`)
* **Systems & Backend**: RESTful API Design, HTTP Method Handling, File System Management (`std::filesystem`), Database Normalization (1NF, 2NF, 3NF)
* **Tools**: Git, GitHub

---

## Problem Solving

The repository features algorithmic solutions targeting data structures, array manipulation, tree traversal, and dynamic programming techniques:

* **Arrays & Two-Pointer Methods**:
  * `Two Sum`: Finding pair indices meeting target totals.
  * `3Sum`: Solving tri-number zero-sum problems with multi-pointer techniques.
* **Trees & Recursion**:
  * `Symmetric Tree`: Recursive tree symmetry evaluation.
  * `Count Good Nodes in Binary Tree`: Path traversal tracking maximum values.
  * `Sum Root to Leaf Numbers`: Accumulating root-to-leaf path values.
  * `Kth Smallest Element in a BST`: In-order binary search tree traversal.
* **Strings & Dynamic Programming**:
  * `Longest Palindromic Substring`: String expansion and substring analysis.
  * `Triangle Array`: Dynamic path minimization across multi-level arrays.

---

## Key Takeaways

* **Clean & Maintainable Code**: Shifted from monolithic procedural functions to modular, cleanly separated header and implementation files.
* **Robust Concurrency Management**: Gained practical knowledge in preventing data races and deadlocks while coordinating shared state across threads.
* **Architectural Awareness**: Practiced selecting appropriate design patterns to keep systems flexible and maintainable when requirements change.
* **Backend Systems Development**: Understood the complete flow of web service communication, from client request serialization to server-side endpoint handling.
* **Algorithmic Proficiency**: Improved problem-solving skills by practicing data structure selection, recursive logic, and spatial complexity optimization.

---

## Repository Structure

```text
├── Problem Solving/          # Solutions to algorithmic and data structure problems (LeetCode)
└── Tasks/                    # Software engineering learning modules and practical projects
    ├── Task 1 - Student Grade Management System/   # Procedural foundation & input validation
    ├── Task 2 - OOP Bank System/                   # Object-oriented architecture & factory design
    ├── Task 3 - Multi-Threaded Banking System/     # Thread safety & concurrent transaction engine
    ├── Task 4 - Desing Patterns Cases Level 1/     # Comprehensive design pattern refactoring suite
    ├── Task 5 - CPP File Manager/                  # File system tree navigation & filesystem operations
    ├── Task 6 - Simulated Normalized Bank Database/# In-memory database normalization (1NF-3NF)
    └── Task 7 - Learn C++ REST API/                # Client-server REST API over HTTP with JSON
```