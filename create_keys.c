#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    const char *pub_name = (argc > 1) ? argv[1] : "Public.key";
    const char *priv_name = (argc > 2) ? argv[2] : "Private.key";
    int key_len = 8;

    unsigned char pub_shifts[key_len];
    unsigned char priv_shifts[key_len];

    srand(time(NULL));

    for (int i = 0; i < key_len; i++) {
        pub_shifts[i] = (rand() % 25) + 1;         
        priv_shifts[i] = (26 - pub_shifts[i]) % 26; 
    }

    FILE *pub = fopen(pub_name, "wb");
    FILE *priv = fopen(priv_name, "wb");

    if (!pub || !priv) {
        printf("Error creating key files\n");
        return 1;
    }

    fwrite(pub_shifts, 1, key_len, pub);
    fwrite(priv_shifts, 1, key_len, priv);

    fclose(pub);
    fclose(priv);

    printf("Created key pair:\n");
    printf("  Public  : %s\n", pub_name);
    printf("  Private : %s\n", priv_name);

    return 0;
}