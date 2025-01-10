# Text-Based Facebook Simulation

A C-based project simulating a basic, text-based version of Facebook. This project involves implementing imperative programming concepts such as structures, memory allocation, and linked lists to manage users, their profiles, posts, and friendships.

## Table of Contents
1. [Features](#features)
2. [Project Overview](#project-overview)
3. [Technical Requirements](#technical-requirements)
4. [Setup and Compilation](#setup-and-compilation)
5. [Usage](#usage)
6. [File Descriptions](#file-descriptions)
7. [License](#license)

---

## Features
The application includes the following functionalities:
1. **User Registration:** Add new users with a username and password.
2. **Profile Management:** Change an existing user's password.
3. **Post Management:** Add or remove posts from a user's profile.
4. **Friend Management:** Add or remove friends from a user's profile.
5. **Post Display:** View posts from a specific user.
6. **Exit:** Quit the application.

## Project Overview
This project simulates the backend operations of a simplified social media platform:
- **User Management:** Users are stored as a sorted linked list.
- **Friend Management:** Each user's friends are maintained as a sorted linked list.
- **Post Management:** Posts are organized as a stack for each user.

### Key Concepts
- **Data Structures:** 
  - Linked lists for users and friends.
  - Stack implementation for posts.
- **Memory Management:** Efficiently manage dynamic memory for user profiles and their data.
- **Error Handling:** Input validation and appropriate feedback for invalid operations.

## Technical Requirements
- **Programming Language:** C (no C++ elements allowed).
- **Compiler:** GCC or equivalent C compiler.
- **Development Environment:** Visual Studio Code (recommended).
- **Constraints:**
  - No global variables.
  - Use only the concepts covered in the specified lectures (1–20).

## Setup and Compilation
1. Clone the repository:
   ```bash
   git clone [https://github.com/your-repo-name/text-based-facebook](https://github.com/mixtapeo/Facebook-In-C).git
   cd folder
2. Compile code:
   ```bash
   gcc -g *.c -o A02.exe
   ./A02.exe
## License
This project is for educational purposes only. Unauthorized use or plagiarism is forbidden.
