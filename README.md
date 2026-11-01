# Text Encryption and Decryption Tool for CSV Files

## Table of Contents
1. Introduction  
2. Problem Statement  
3. Objectives  
4. Proposed Methodology  
5. System and Functional Requirements  
6. Design and Implementation  
7. How to Run  
8. Limitations and Future Scope  
9. Conclusion  
10. References  

---

## 1. Introduction
This project implements a file-based encryption and decryption tool in C. It is designed to protect sensitive textual data stored in CSV files using a symmetric key approach based on the Caesar cipher principle with a multi-shift key.

## 2. Problem Statement
Plain text data stored in CSV files can be easily read by unauthorized users. This project provides a simple mechanism to encrypt selected textual information using a public key and restore it using a corresponding private key.

## 3. Objectives
- To implement encryption and decryption of CSV files in C.
- To demonstrate the use of arrays, structures, and pointers.
- To use file handling for reading and writing data.
- To apply a multi-shift (Vigenère-style) Caesar cipher using binary key files.

## 4. Proposed Methodology
The program accepts command-line arguments for the operation mode (encrypt/decrypt), the input CSV file, and the key file.  

- The public key contains a sequence of shift values.  
- The private key contains the corresponding inverse shifts.  
- Only alphabetic characters are modified.  
- Numbers, commas, and special characters remain unchanged.

## 5. System and Functional Requirements

### Functional Requirements
- The program shall accept command-line arguments for mode, input file, and key file.
- The program shall encrypt alphabetic characters using the public key.
- The program shall decrypt the encrypted data using the private key.
- Non-alphabetic characters shall remain unchanged.
- The program shall generate an output file after processing.

### Concept of Public Key and Private Key
- **Public Key**: A binary file containing a sequence of shift values (1–25). It is used during encryption.
- **Private Key**: A binary file containing the inverse shift values calculated as `(26 - shift) % 26`. It is used during decryption.

This key pair allows data encrypted with the public key to be correctly restored only with the matching private key.

## 6. Design and Implementation
The project uses the following C concepts:

- **Structures**: To group configuration data (file names, key, mode).
- **Arrays**: To store the sequence of shift values from the key file.
- **Pointers**: To pass structures and modify characters efficiently.
- **File Handling**: To read CSV files and binary key files, and to write the output.

## 7. How to Run

```bash
# Compile
gcc create_keys.c -o create_keys
gcc cipher.c -o cipher
c:\Users\mohds\AppData\Local\Packages\AdobeSystemsIncorporated.AdobePhotoshopExpress_ynb6jyjzte8ga\LocalState\Share\Images\AdobeExpressPhotos_933aeb4d9046447ab06ad65a94aa54cb_CopyEdited.png

# Generate keys
./create_keys Public.key Private.key
c:\Users\mohds\AppData\Local\Packages\AdobeSystemsIncorporated.AdobePhotoshopExpress_ynb6jyjzte8ga\LocalState\Share\Images\AdobeExpressPhotos_2c15c210621c4bce987628386d2708ea_CopyEdited.png

# Encrypt
./cipher encrypt SuperPrivateData.csv Public.key
c:\Users\mohds\AppData\Local\Packages\AdobeSystemsIncorporated.AdobePhotoshopExpress_ynb6jyjzte8ga\LocalState\Share\Images\AdobeExpressPhotos_dfc4cef69ffe4b81a9be6ca8473762e4_CopyEdited.png

# Decrypt
./cipher decrypt SuperPrivateData.csvEncrypted.csv Private.key
c:\Users\mohds\AppData\Local\Packages\AdobeSystemsIncorporated.AdobePhotoshopExpress_ynb6jyjzte8ga\LocalState\Share\Images\AdobeExpressPhotos_6a6a46fa6a8b456788aad2bb3d7aa421_CopyEdited.png

8. Limitations and Future ScopeThe current implementation uses a classical multi-shift Caesar cipher, which is not cryptographically secure for real-world sensitive data.Future improvements may include stronger algorithms, better CSV parsing, and support for larger files. 

9. ConclusionThis project successfully demonstrates the practical application of arrays, structures, pointers, and file handling in C through a simple yet functional encryption-decryption system for CSV files.

10. References
Kernighan, B. W., & Ritchie, D. M. (1988). The C Programming Language (2nd ed.).
Course material – SDF-1, Department of Computer Science and Engineering.