# Text Encryption & Decryption Tool

**Course:** Software Development Fundamentals – 1

**Batch:** F21

**Instructor:** Dr. Shariq Murtuza

## Team

| Name | Roll Number |
| :--- | :--- |
| Chetan Sharma | 992601030398 |
| Agrim Rastogi | 992601030401 |
| Priyansh Joshi | 992601030391 |
| Mohd. Shaan | 992601030392 |

---

## I. Introduction

The proposed project implements a Text Encryption and Decryption Tool developed in C. It will use the Caesar Cipher encryption algorithm. The tool will read text from a user-specified file and use a key stored in a separate key file to perform encryption or decryption.

## II. Problem Statement

Plain text stored in files is directly readable by anyone who can access it. The project aims to develop a simple program that processes a text file using a key provided through a separate key file. The file and key file will be supplied to the program through command-line arguments.

## III. Objectives

- To implement the Caesar Cipher in C for encryption and decryption of text stored in a file.
- To accept command-line arguments for user interaction.

## IV. Proposed Methodology

The program will receive two command-line arguments: the path of the text file and the path of the key file. For example, the program may be invoked as:

```bash
./a.out file.txt main.key
```

The key file will contain the key/shift value used by the Caesar Cipher.

The program will open the input text file, read its contents into a character buffer, and obtain the key from the key file. During processing, the program will traverse the character data and shift alphabetic characters. Encryption will shift characters forward, whereas decryption will apply the reverse shift.

Example with shift = 3:

```
HELLO -> KHOOR
KHOOR -> HELLO
```

### C Concepts Used

| Concept | Use in the Project / Application |
| :--- | :--- |
| Arrays | Character arrays/buffers store text read from the input file so the program can process the data one character at a time. |
| Structures | A structure groups encryption-related settings such as the key and processing information into one logical unit. |
| Pointers | Pointers are used to access/pass character buffers and work with file data, demonstrating direct memory-based data access. |
| Control Flow | if/else statements, loops and argument checks control file processing, character transformation, wrap-around and program execution. |
| Functions | Separate user-defined functions can handle file operations, key reading, encryption/decryption and validation, keeping the program modular. |
| File Handling | File handling is a core part of the project: the program reads the input text from a file and obtains the encryption/decryption key from a separate key file. |

## VI. System and Functional Requirements

- The program shall accept the input text file path as a command-line argument.
- The program shall accept the key file path as a command-line argument.
- The program shall provide encryption and decryption operations using the supplied key.
- The program shall read and process the contents of the input file.
- The program shall handle invalid arguments and file-access errors appropriately; the implementation shall use arrays, structures, pointers and file handling.

## VII. Design / Control Flow

The planned control flow begins by validating the two command-line arguments, opening the input text file and key file, reading the key, processing the text using the Caesar Cipher, and completing the selected encryption/decryption operation. The flow also includes validation and file-error handling.

```mermaid
flowchart TD
    A([Start]) --> B[Read command-line arguments<br>file.txt + main.key]
    B --> C[Open text file and key file<br>Validate file access]
    C --> D[Read key / shift value<br>Read text into character buffer]
    D --> E[Encrypt / Decrypt text<br>Apply Caesar shift with wrap-around]
```

## VIII. Expected Outcomes

The completed project is expected to provide a working console-based application that reads text from a file and uses a separately supplied key file to perform Caesar Cipher encryption and decryption. It will demonstrate practical use of character arrays, structures, pointers, functions, file handling, loops and conditional statements while implementing a simple text transformation algorithm.

The project will also provide a clear understanding of the relationship between an algorithm, command-line arguments, files, key management, data representation and program control flow in a C application.

## IX. Limitations and Future Scope

The Caesar cipher is a basic classical encryption technique and should not be considered secure for protecting sensitive or confidential information. It is not cryptographically secure.

The project can be extended in future by adding other encryption techniques, a graphical user interface, or stronger modern cryptographic algorithms.

## X. Conclusion

The Text Encryption and Decryption Tool provides a compact practical application of the Caesar Cipher while demonstrating fundamental C programming concepts. By combining arrays, structures, pointers, functions, file handling and control flow, the project connects core programming concepts with a simple file-based text transformation use case.

## XI. References

1. B. W. Kernighan and D. M. Ritchie, *The C Programming Language*, 2nd ed. Prentice Hall, 1988.
2. B. Schneier, *Applied Cryptography: Protocols, Algorithms, and Source Code in C*, 2nd ed. John Wiley & Sons, 1996.
3. Course material and laboratory notes for SDF–1, Department of Computer Science and Engineering, JIIT Noida.

---

## Build and Run

**Requirements:** GCC or Clang.

**Compile**

```bash
gcc main.c cipher.c -o a.out
```

**Run**

```bash
echo "HELLO WORLD" > file.txt
echo "3" > main.key
./a.out file.txt main.key
```
