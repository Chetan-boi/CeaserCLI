#include "cipher.h"

#include <cstdio>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    printf("HelloWorld!\n");
    // For encrypt
    FILE *publicKey = fopen("public.key","r");
    if (publicKey == NULL) {
        perror("Error opening Public Key\n");
        return 1;
    }

    int shift = 0;
    if (fscanf(publicKey,"%d",&shift) != 1) {
        fprintf(stderr, "Failed to read shift key\n");
        fclose(publicKey);
        return 1;
    }
    fclose(publicKey);

    // Implement same for privateKey
    // write using fprintf(file,text,data)

    return 0;
}
