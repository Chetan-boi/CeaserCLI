#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATH 256
#define KLEN 8

static void show_help(const char *prog) {
    printf("usage: %s [NAME]\n", prog);
    printf("  %s Chetan -> PublicChetan.key & PrivateChetan.key\n", prog);
    printf("  %s        -> Public.key & Private.key\n", prog);
}

int main(int argc, char *argv[]) {
    if (argc > 1 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help") || !strcmp(argv[1], "help"))) {
        show_help(argv[0]);
        return 0;
    }

    const char *name = (argc > 1) ? argv[1] : NULL;
    char pub[MAX_PATH], priv[MAX_PATH];

    if (name && strlen(name)) {
        snprintf(pub, sizeof(pub), "Public%s.key", name);
        snprintf(priv, sizeof(priv), "Private%s.key", name);
    } else {
        snprintf(pub, sizeof(pub), "Public.key");
        snprintf(priv, sizeof(priv), "Private.key");
    }

    unsigned char pub_s[KLEN], priv_s[KLEN];
    srand((unsigned int)time(NULL));

    for (int i = 0; i < KLEN; i++) {
        pub_s[i] = (rand() % 25) + 1;
        priv_s[i] = (26 - pub_s[i]) % 26;
    }

    FILE *f1 = fopen(pub, "wb");
    FILE *f2 = fopen(priv, "wb");
    if (!f1 || !f2) {
        printf("cant create keys\n");
        return 1;
    }

    fwrite(pub_s, 1, KLEN, f1);
    fwrite(priv_s, 1, KLEN, f2);
    fclose(f1);
    fclose(f2);

    printf("created:\n  %s\n  %s\n", pub, priv);
    return 0;
}
