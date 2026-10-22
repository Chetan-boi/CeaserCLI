#include "cipher.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_menu(void) {
    int choice = 0;
    char file[256];
    char key[256];
    char output[256];

    while (1) {
        printf("\n===================================\n");
        printf("    Caesar Cipher - Main Menu      \n");
        printf("===================================\n");
        printf("1. Encrypt a file\n");
        printf("2. Decrypt a file\n");
        printf("3. Exit\n");
        printf("Enter your choice (1-3): ");

        if (scanf("%d", &choice) != 1) {
            break;
        }

        if (choice == 3) {
            printf("Exiting. Goodbye!\n");
            break;
        }

        if (choice != 1 && choice != 2) {
            printf("Invalid choice! Please choose 1, 2, or 3.\n");
            continue;
        }

        printf("Enter input file name: ");
        scanf("%255s", file);

        printf("Enter key file name: ");
        scanf("%255s", key);

        printf("Enter output file name (or enter '-' to print on screen): ");
        scanf("%255s", output);

        const char* out_ptr = (strcmp(output, "-") == 0) ? NULL : output;
        int is_decrypt = (choice == 2) ? 1 : 0;

        printf("\nProcessing...\n");
        int status = process_file(file, key, out_ptr, is_decrypt);

        if (status == 0) {
            if (out_ptr != NULL) {
                printf("Operation successful! Output written to: %s\n", out_ptr);
            } else {
                printf("\n--- End of Output ---\n");
            }
        } else {
            printf("Operation failed. Please verify your file names and key.\n");
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        /* Menu style when launched without arguments */
        run_menu();
        return 0;
    }
    else if (argc != 4 && argc != 5) {
        /* Usage instructions */
        printf("Usage: %s <encrypt|decrypt> <input_file> <key_file> [output_file]\n", argv[0]);
        printf("       %s -e <input_file> <key_file> [output_file]\n", argv[0]);
        printf("       %s -d <input_file> <key_file> [output_file]\n", argv[0]);
        printf("\nOr : Run without arguments for interactive menu mode:\n");
        printf("       %s\n", argv[0]);
        return 1;
    }
    else {
        /* CLI argument mode */
        char* type = argv[1];
        char* file = argv[2];
        char* key = argv[3];
        char* output = (argc == 5) ? argv[4] : NULL;

        int is_decrypt = 0;
        if (strcmp(type, "encrypt") == 0 || strcmp(type, "-e") == 0) {
            is_decrypt = 0;
        } else if (strcmp(type, "decrypt") == 0 || strcmp(type, "-d") == 0) {
            is_decrypt = 1;
        } else {
            printf("Invalid operation: '%s'. Use 'encrypt' (or -e) / 'decrypt' (or -d).\n", type);
            return 1;
        }

        int status = process_file(file, key, output, is_decrypt);
        if (status == 0 && output != NULL) {
            printf("Operation successful! Saved to: %s\n", output);
        }

        return status;
    }
}
