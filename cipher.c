#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEY_SIZE 256
#define MAX_FILENAME 200

typedef struct {
    char inputFile[MAX_FILENAME];
    char keyFile[MAX_FILENAME];
    char outputFile[MAX_FILENAME];
    unsigned char shifts[MAX_KEY_SIZE];  
    size_t keyLength;
    int isDecrypt;                       
} CipherConfig;

int loadKey(CipherConfig *config);                    
void processFile(CipherConfig *config);               
void caesarShift(char *ch, int shift);                

int main(int argc, char *argv[]) {

    if (argc != 4) {
        printf("Usage:\n");
        printf("  Encrypt : %s encrypt  <input.csv> <Public.key>\n", argv[0]);
        printf("  Decrypt : %s decrypt  <encrypted.csv> <Private.key>\n", argv[0]);
        return 1;
    }

    CipherConfig config;

    // Fill structure
    strcpy(config.inputFile, argv[2]);
    strcpy(config.keyFile, argv[3]);
    config.isDecrypt = (strcmp(argv[1], "decrypt") == 0) ? 1 : 0;

    if (config.isDecrypt) {
        snprintf(config.outputFile, MAX_FILENAME, "%sRestored.csv", config.inputFile);
    } else {
        snprintf(config.outputFile, MAX_FILENAME, "%sEncrypted.csv", config.inputFile);
    }

    if (loadKey(&config) != 0) {
        printf("Error loading key file!\n");
        return 1;
    }

    printf("Key loaded successfully (%zu bytes).\n", config.keyLength);

    processFile(&config);

    printf("%s '%s' -> '%s' using '%s'.\n",
           config.isDecrypt ? "Decrypted" : "Encrypted",
           config.inputFile, config.outputFile, config.keyFile);

    return 0;
}

int loadKey(CipherConfig *config) {
    FILE *fp = fopen(config->keyFile, "rb");
    if (fp == NULL) return -1;

    config->keyLength = fread(config->shifts, 1, MAX_KEY_SIZE, fp);
    fclose(fp);

    return (config->keyLength > 0) ? 0 : -1;
}

void processFile(CipherConfig *config) {
    FILE *in = fopen(config->inputFile, "r");
    if (in == NULL) {
        printf("Cannot open input file: %s\n", config->inputFile);
        exit(1);
    }

    FILE *out = fopen(config->outputFile, "w");
    if (out == NULL) {
        printf("Cannot create output file\n");
        fclose(in);
        exit(1);
    }

    int alpha_count = 0;
    int ch;

    while ((ch = fgetc(in)) != EOF) {
        if (isalpha(ch)) {
            
            int shift = config->shifts[alpha_count % config->keyLength];

         
            char temp = (char)ch;
            caesarShift(&temp, shift);
            ch = temp;

            alpha_count++;
        }
        fputc(ch, out);
    }

    fclose(in);
    fclose(out);
}

void caesarShift(char *ch, int shift) {
    if (isalpha(*ch)) {
        char base = islower(*ch) ? 'a' : 'A';
        *ch = ((*ch - base + shift) % 26 + 26) % 26 + base;
    }
}