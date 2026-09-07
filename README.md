# Software Development Training Showcase

Welcome to my **Software Development Training Showcase** repository. This repository documents my practical training journey, hands-on projects, and problem-solving exercises in modern **C++**, backend software engineering, networking, concurrency, software design, file systems, databases, and RESTful web services.

---

## What I Learned

### C++ & Modern C++

* Applied modern C++ standards (C++11/C++17) for clean memory management and type safety.
* Leveraged STL containers and algorithms to build efficient and maintainable applications.
* Used modern language features such as smart pointers, lambdas, move semantics, and filesystem utilities.
* Structured modular applications with clear separation between interfaces and implementations.

### Object-Oriented Programming (OOP) & SOLID Principles

* Implemented encapsulation, inheritance, polymorphism, and abstraction.
* Applied SOLID principles to improve maintainability and extensibility.
* Built modular systems using abstract interfaces and factory-based object creation.

### Multithreading & Concurrency

* Developed concurrent systems using `std::thread`, `std::mutex`, `std::lock_guard`, and `std::scoped_lock`.
* Implemented thread-safe shared state management.
* Utilized `std::condition_variable` and `std::atomic` for synchronization and coordination.
* Applied concurrency concepts in both banking and networking applications.

### Networking & TCP Systems

* Built asynchronous TCP networking applications using **Boost.Asio**.
* Designed custom TCP protocols with length-prefixed message framing.
* Implemented client session management, broadcasting, private messaging, and command handling.
* Applied thread pools and asynchronous I/O to support multiple concurrent clients.
* Developed modular networking architectures separating transport, business logic, and session management.

### Design Patterns

* Implemented commonly used design patterns to solve recurring software design challenges:

  * **Behavioral**: Strategy, Observer
  * **Creational**: Factory, Builder, Singleton
  * **Structural**: Adapter, Decorator

### File Systems & I/O Operations

* Built file management utilities using C++17 `<filesystem>`.
* Implemented directory traversal, recursive navigation, file creation, and file manipulation.
* Utilized standard file streams for reading, writing, and parsing structured data.

### Database Concepts & Normalization

* Simulated relational database systems in memory.
* Modeled primary and foreign key relationships.
* Applied database normalization concepts (1NF, 2NF, 3NF) to reduce redundancy and improve data organization.

### REST APIs

* Implemented lightweight HTTP servers and clients in C++.
* Built RESTful endpoints using GET, POST, PUT, and DELETE operations.
* Handled JSON serialization and deserialization using `nlohmann/json`.
* Applied request validation and proper HTTP response handling.

---

## Projects & Practical Work

### 1. Multithreaded Asynchronous TCP Chat Server

* **Description**: A real-time chat server supporting multiple concurrent TCP clients using asynchronous networking and custom protocol design.
* **Main Technologies / Concepts**: C++, Boost.Asio, TCP/IP, Socket Programming, Thread Pools, Message Framing.
* **Key Skills Practiced**:

  * Designing custom TCP protocols.
  * Implementing asynchronous networking.
  * Managing multiple concurrent clients.
  * Broadcasting and private messaging.
  * Session and client lifecycle management.
  * Modular backend architecture design.

### 2. Multi-Threaded Banking System

* **Description**: A concurrent banking application designed to safely process transactions across multiple threads.
* **Main Technologies / Concepts**: Modern C++, Multithreading, Synchronization Primitives.
* **Key Skills Practiced**: Thread safety, race-condition prevention, deadlock avoidance, and transaction coordination.

### 3. C++ REST API Client & Server

* **Description**: A lightweight user management backend service and HTTP client.
* **Main Technologies / Concepts**: C++, cpp-httplib, nlohmann/json, REST APIs.
* **Key Skills Practiced**: HTTP communication, endpoint implementation, request processing, and JSON handling.

### 4. Design Patterns Case Suite

* **Description**: A collection of software design scenarios refactored using design patterns.
* **Main Technologies / Concepts**: Strategy, Factory, Builder, Singleton, Observer, Adapter, Decorator.
* **Key Skills Practiced**: Flexible architecture design and clean code practices.

### 5. C++ File Manager

* **Description**: A command-line utility for navigating and manipulating file system structures.
* **Main Technologies / Concepts**: C++17 Filesystem, File I/O.
* **Key Skills Practiced**: Directory traversal, path handling, and file management.

### 6. Simulated Normalized Bank Database

* **Description**: An in-memory relational database model built to practice database design concepts.
* **Main Technologies / Concepts**: C++ Structs, Vectors, Database Normalization.
* **Key Skills Practiced**: Schema organization and relational data modeling.

### 7. OOP Bank System

* **Description**: A modular banking system built using object-oriented design principles.
* **Main Technologies / Concepts**: OOP, Polymorphism, Factory Pattern.
* **Key Skills Practiced**: System modeling and object-oriented architecture.

### 8. Student Grade Management System

* **Description**: A console application for managing student records and academic statistics.
* **Main Technologies / Concepts**: Procedural C++, Validation Logic.
* **Key Skills Practiced**: Input validation and structured program design.

---

## Technical Skills

* **Languages**: C++ (C++11, C++17)
* **Libraries & Frameworks**: STL, Boost.Asio, cpp-httplib, nlohmann/json
* **Networking**: TCP/IP, Socket Programming, Asynchronous Networking, Message Framing, Client-Server Architecture
* **Software Design & Architecture**: OOP, SOLID Principles, Design Patterns
* **Concurrent Programming**: std::thread, std::mutex, std::scoped_lock, std::atomic, std::condition_variable, Thread Pools
* **Memory Management**: Smart Pointers (unique_ptr, shared_ptr, weak_ptr), RAII
* **Data Structures & Algorithms**: Arrays, Vectors, Maps, Hash Tables, Trees, BST, AVL Trees, Ternary Search Trees
* **Generic Programming**: Templates, STL Algorithms, Lambda Expressions

* **Systems & Backend**: RESTful APIs, HTTP, Real-Time Systems, File System Management, Database Normalization
* **Tools**: Git, GitHub

---

## Problem Solving

The repository includes algorithmic problem-solving exercises focused on data structures and algorithms:

### Arrays & Two-Pointer Techniques

* Two Sum
* 3Sum

### Trees & Recursion

* Symmetric Tree
* Count Good Nodes in Binary Tree
* Sum Root to Leaf Numbers
* Kth Smallest Element in a BST
* Path Sum
* Path Sum II

### Dynamic Programming & Strings

* Longest Palindromic Substring
* Triangle

---

## Key Takeaways

* **Clean & Maintainable Code**: Improved code organization through modular architecture and proper separation of concerns.
* **Concurrency Management**: Practiced safe multithreaded programming and synchronization techniques.
* **Real-Time Networking**: Built asynchronous TCP systems capable of handling multiple simultaneous clients.
* **Protocol Design**: Implemented custom message framing for reliable communication over TCP streams.
* **Backend Development**: Developed REST APIs and networking services from request handling to business logic implementation.
* **Architectural Thinking**: Applied design patterns and SOLID principles to create scalable and maintainable systems.
* **Problem Solving**: Strengthened algorithmic thinking through practical data structure and algorithm challenges.

---

## Repository Structure

```text
├── Problem Solving/          # Algorithm and data structure solutions
├── Project/
│   └── Multithreaded Asynchronous Tcp Server/
│       └── Real-time TCP chat server using Boost.Asio
└── Tasks/
    ├── Task 1 - Student Grade Management System/
    ├── Task 2 - OOP Bank System/
    ├── Task 3 - Multi-Threaded Banking System/
    ├── Task 4 - Desing Patterns Cases Level 1/
    ├── Task 5 - CPP File Manager/
    ├── Task 6 - Simulated Normalized Bank Database/
    └── Task 7 - Learn C++ REST API/
```
