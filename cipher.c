#include "cipher.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int read_shift_key(const char* key_path, int* shift) {
    if (key_path == NULL || shift == NULL) {
        printf("Error: Invalid key path or pointer.\n");
        return 1;
    }

    FILE* fp = fopen(key_path, "r");
    if (fp == NULL) {
        printf("Error opening key file: %s\n", key_path);
        return 1;
    }

    if (fscanf(fp, "%d", shift) != 1) {
        printf("Error: Could not read integer shift from: %s\n", key_path);
        fclose(fp);
        return 1;
    }

    fclose(fp);

    /* Normalize shift to range 0..25 */
    *shift = *shift % 26;
    if (*shift < 0) {
        *shift += 26;
    }

    return 0;
}

char shift_char(char c, int shift, int is_decrypt) {
    if (isupper((unsigned char)c)) {
        if (!is_decrypt) {
            return (char)((c - 'A' + shift) % 26 + 'A');
        } else {
            return (char)((c - 'A' - shift + 26) % 26 + 'A');
        }
    } else if (islower((unsigned char)c)) {
        if (!is_decrypt) {
            return (char)((c - 'a' + shift) % 26 + 'a');
        } else {
            return (char)((c - 'a' - shift + 26) % 26 + 'a');
        }
    }
    /* Digits, spaces, punctuation and newlines remain unchanged */
    return c;
}

int process_file(const char* input_path, const char* key_path, const char* output_path, int is_decrypt) {
    int shift = 0;
    if (read_shift_key(key_path, &shift) != 0) {
        return 1;
    }

    FILE* fin = fopen(input_path, "r");
    if (fin == NULL) {
        printf("Error opening input file: %s\n", input_path);
        return 1;
    }

    FILE* fout = stdout;
    if (output_path != NULL && output_path[0] != '\0') {
        fout = fopen(output_path, "w");
        if (fout == NULL) {
            printf("Error opening output file: %s\n", output_path);
            fclose(fin);
            return 1;
        }
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), fin) != NULL) {
        for (int i = 0; buffer[i] != '\0'; i++) {
            buffer[i] = shift_char(buffer[i], shift, is_decrypt);
        }
        fputs(buffer, fout);
    }

    fclose(fin);
    if (fout != stdout) {
        fclose(fout);
    }

    return 0;
}
