# CeaserCLI : Text Encryption and Decryption Tool

**Course:** Software Development Fundamentals – 1  
**Batch:** F21  
**Instructor:** Dr. Shariq Murtuza  

---

## Team

| Name | Roll Number |
| :--- | :--- |
| Chetan Sharma | 992601030398 |
| Agrim Rastogi | 992601030401 |
| Priyansh Joshi | 992601030391 |
| Mohd. Shaan | 992601030392 |

---

## Table of Contents
1. [Introduction](#1-introduction)  
2. [Problem Statement](#2-problem-statement)  
3. [Objectives](#3-objectives)  
4. [Proposed Methodology](#4-proposed-methodology)  
5. [System and Functional Requirements](#5-system-and-functional-requirements)  
6. [Design and Implementation](#6-design-and-implementation)  
7. [Usage and Compilation](#7-usage-and-compilation)  
8. [Screenshots](#8-screenshots)  
9. [Limitations and Future Scope](#9-limitations-and-future-scope)  
10. [Conclusion](#10-conclusion)  
11. [References](#11-references)  

---

## 1. Introduction
This project implements a file-based encryption and decryption tool developed in C. It uses a multi-shift Caesar cipher approach to transform the contents of a text/csv file using a public key and restore the original content using a corresponding private key.

The project provides both a command-line interface (CLI) for scripted execution and an interactive, menu-driven CLI (`ceaserCLI`) for interactive use.

---

## 2. Problem Statement
Plain text stored in files can be easily read by anyone who has access to the storage system. This project aims to provide a reliable, modular educational tool to encrypt the contents of a file and decrypt it back to its original form using a generated key pair.

---

## 3. Objectives
- Implement file-based Caesar Cipher encryption and decryption of text files in C.
- Demonstrate fundamental C programming concepts: structures, arrays, pointers, functions, and file I/O.
- Support both command-line arguments with `--help` flags and an interactive menu-driven interface.
- Provide key-pair generation with optional custom naming prefixes (`Public<Name>.key` / `Private<Name>.key`).
- Structure the project cleanly into `src/` and `include/` directories without relying on a Makefile.

---

## 4. Proposed Methodology
The program supports both direct command-line arguments and an interactive terminal menu:

In CLI mode, the tool is invoked as:
```bash
./cipher <encrypt|decrypt> <input file> <key file>
```

Key pairs are generated via:
```bash
./create_keys [NAME]
```

Interactive menu mode is launched via:
```bash
./ceaserCLI
```

The algorithm reads the text file character by character. For each alphabetic character, it applies a modular Caesar shift from the key file with wrap-around, preserving character case (uppercase and lowercase). Non-alphabetic characters (spaces, punctuation, digits) remain unmodified.

```
Example (Shift = 3):
HELLO -> KHOOR  |  KHOOR -> HELLO
```

---

## 5. System and Functional Requirements

### Functional Requirements
- **Command-Line Arguments & Flags:** Support `encrypt`, `decrypt`, and `--help` / `-h` flags for comprehensive usage instructions.
- **Menu-Driven Interface:** Provide an interactive menu driver (`ceaserCLI`) allowing users to encrypt files, decrypt files, or read help instructions without memorizing command-line syntax.
- **Key Generation:** Standalone key generator (`create_keys`) to generate 8-byte multi-shift binary key pairs with optional user naming (`Public<Name>.key` and `Private<Name>.key`).
- **File Encryption:** Encrypt text using the generated public key, outputting to `<name>_encrypted.<ext>`.
- **File Decryption:** Restore encrypted text using the matching private key, outputting to `<name>_decrypted.<ext>`.
- **Robust Error Handling:** Validate command-line arguments, verify file existence, handle missing or malformed keys, and report user-friendly error messages.

### Public Key and Private Key
- **Public Key (`Public<Name>.key`):** A binary file containing a sequence of shift values $S_i$ ($1 \le S_i \le 25$). Used during encryption:
  $$C = (P - \text{base} + S_i) \pmod{26} + \text{base}$$
- **Private Key (`Private<Name>.key`):** A binary file containing the inverse shift values $S'_i = (26 - S_i) \pmod{26}$. Used during decryption:
  $$P = (C - \text{base} + S'_i) \pmod{26} + \text{base}$$

Data encrypted using the public key can only be correctly restored using the matching private key.

---

## 6. Design and Implementation

### 6.1 C Programming Concepts Demonstrated
- **Header Files and Modularity:** Common definitions and function prototypes are declared in [`include/cipher.h`](include/cipher.h).
- **Structures:** Group related configuration data such as file paths, key buffers, key lengths, and operation mode into `CipherConfig`.
- **Arrays:** Store multi-shift sequences read from binary key files.
- **Pointers:** Pass configuration structures and memory buffers to functions efficiently by reference.
- **File Handling:** Binary file operations (`fread`, `fwrite`, `fopen`, `fclose`) for key management and stream I/O (`fgetc`, `fputc`) for text transformation.

### 6.2 Control Flow Diagram

```mermaid
flowchart TD
    Start([Start]) --> Mode{Select Mode}
    Mode -->|Interactive Menu| Menu[Launch ceaserCLI Menu]
    Mode -->|CLI Arguments| ParseArgs[Parse CLI Arguments & Flags]
    
    ParseArgs -->|--help / -h| ShowHelp[Display Help Screen] --> Exit([Exit])
    ParseArgs -->|create_keys [NAME]| GenKey[Generate 8-byte Shifts]
    GenKey --> WriteKeys[Save Public&lt;Name&gt;.key & Private&lt;Name&gt;.key] --> Exit
    
    ParseArgs -->|cipher &lt;encrypt/decrypt&gt;| LoadFiles[Open Input & Key File]
    LoadFiles --> Validate{Valid Files?}
    Validate -->|No| FileErr[Display Error Message] --> Exit
    Validate -->|Yes| ReadKey[Read Key Shifts into Buffer]
    
    ReadKey --> OpType{Operation?}
    OpType -->|encrypt| ApplyShift[Shift chars: +shift mod 26]
    OpType -->|decrypt| ApplyInverse[Shift chars: +inverse mod 26]
    
    ApplyShift --> WriteOut[Write &lt;name&gt;_encrypted.&lt;ext&gt;] --> Done([Done])
    ApplyInverse --> WriteOutRestored[Write &lt;name&gt;_decrypted.&lt;ext&gt;] --> Done
```

---

## 7. Usage and Compilation

The project does not use or require any Makefile. Compile the unified tool using the build script:

### 7.1 Compilation
```bash
./build.sh
```
Or directly with `gcc`:
```bash
gcc src/cipher.c src/ceaserCLI.c -Iinclude -o ceaserCLI
```

---

### 7.2 Standalone Key Generator (`create_keys`)
`create_keys.c` is completely standalone in the root directory and has no external dependencies:
```bash
gcc create_keys.c -o create_keys
./create_keys Chetan
```

---

### 7.3 Unified Interface (`ceaserCLI`)

The application decides what to do based on arguments:
- **No arguments (`./ceaserCLI`)**: Launches the interactive menu (Encrypt, Decrypt, Help, Exit).
- **Arguments (`./ceaserCLI <encrypt|decrypt> <file> <key>`)**: Runs the operation directly.
- **Invalid arguments / `--help`**: Displays the help menu.

```bash
# 1. Interactive Menu Mode (no arguments)
./ceaserCLI

# 2. File Encryption
./ceaserCLI encrypt input.csv PublicChetan.key
# Output: done, encrypted is input_encrypted.csv

# 3. File Decryption
./ceaserCLI decrypt input_encrypted.csv PrivateChetan.key
# Output: done, decrypted is input_decrypted.csv

# 4. Display Help
./ceaserCLI --help
```

---

## 8. Screenshots

### 8.1 Compilation
![Compilation](screenshots/compile.png)

---

### 8.2 Key Pair Generation
![Key Pair Generation](screenshots/keys.png)

---

### 8.3 File Encryption
![File Encryption](screenshots/encrypt.png)

---

### 8.4 File Decryption & Restoration
![File Decryption](screenshots/decrypt.png)

---

## 9. Limitations and Future Scope

- **Security:** The Caesar cipher is an elementary classical substitution cipher and is not cryptographically secure against frequency analysis or brute-force cryptanalysis. It is intended strictly for educational purposes.
- **File Types:** While non-alphabetic characters are preserved, binary file formats (e.g., images, compiled binaries) are not encrypted.
- **Future Enhancements:**
  - Support for modern symmetric and asymmetric algorithms (AES, RSA).
  - Cross-platform graphical user interface (GUI).
  - Support for full-byte stream encryption covering all byte values 0–255.

---

## 10. Conclusion

The Text Encryption and Decryption Tool provides a compact practical application of the Caesar Cipher while demonstrating fundamental C programming concepts. By combining arrays, structures, pointers, functions, file handling, and modular code organization across `src/` and `include/`, the project bridges foundational programming concepts with a practical file security application.

---

## 11. References

1. B. W. Kernighan and D. M. Ritchie, *The C Programming Language*, 2nd ed. Prentice Hall, 1988.
2. B. Schneier, *Applied Cryptography: Protocols, Algorithms, and Source Code in C*, 2nd ed. John Wiley & Sons, 1996.
3. Course material and laboratory notes for SDF–1, Department of Computer Science and Engineering, JIIT Noida.
