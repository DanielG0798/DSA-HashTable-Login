# DSA-HashTable-Login

Developing a hash table for a login screen with encrypted user passwords.

# Start
### CLion(original)
1. Open CLion
2. Click "Get from VCS" on the welcome screen (or go to File -> New -> Project from Version Control)
3. Paste the repo URL:
```
https://github.com/DanielG0798/DSA-HashTable-Login.git
```
4. Click Clone

### Visual Studio 2022

1. Select Open a Local Folder

2. Choose the project folder (DSA-HashTable-Login)

3. Visual Studio will detect the CMakeLists.txt and auto-configure the project

4. Press Ctrl+F5 or click Run to build and execute
```
cmake --build build
```

### VS Code

1. Install the following extensions:

  - C/C++ by Microsoft

  - CMake Tools

2. Make sure you have a compiler installed (e.g. MinGW on Windows) and added to your system PATH

3. Open the project folder in VS Code

4. In the bottom status bar, select the correct CMake Kit (your compiler)

5. Click the Build button in the CMake Tools panel or run:
```
cmake --build build
```

## Disclaimer: MD5 Hashing Vulnerabilities
The MD5 hashing algorithm is considered cryptographically broken and unsuitable for further use in security-sensitive applications. It is vulnerable to various attacks, including collision and preimage attacks. For applications where security is a priority (such as password storage), it is recommended to use more secure hashing algorithms like bcrypt, scrypt, or Argon2.

In this project, MD5 is used for educational purposes to demonstrate basic hashing and user authentication. It is strongly discouraged to use MD5 in production systems for real-world applications involving sensitive data.

If you plan to use this project in a real-world setting, consider replacing MD5 with a more secure hashing function.
