#include "cipher.h"

static void get_str(char *b, size_t sz) {
    if (fgets(b, (int)sz, stdin)) {
        size_t l = strlen(b);
        while (l > 0 && (b[l - 1] == '\n' || b[l - 1] == '\r')) {
            b[--l] = '\0';
        }
    } else {
        b[0] = '\0';
    }
}

static void show_help(const char *prog) {
    printf("CeaserCLI - Caesar cipher tool\n\n");
    printf("Usage:\n");
    printf("  %s                              Interactive menu\n", prog);
    printf("  %s encrypt <file> <public_key>  Encrypt file\n", prog);
    printf("  %s decrypt <file> <private_key> Decrypt file\n", prog);
    printf("  %s -h, --help                   Show help\n\n", prog);
    printf("Commands:\n");
    printf("  encrypt    Encrypts file to <name>_encrypted.<ext>\n");
    printf("  decrypt    Decrypts file to <name>_decrypted.<ext>\n\n");
    printf("Examples:\n");
    printf("  %s\n", prog);
    printf("  %s encrypt input.csv PublicChetan.key\n", prog);
    printf("  %s decrypt input_encrypted.csv PrivateChetan.key\n\n", prog);
}

static void enc_menu(void) {
    char in[MAX_PATH], key[MAX_PATH];
    printf("\n[Encrypt]\nfile: ");
    get_str(in, sizeof(in));
    if (!strlen(in)) return;

    printf("key: ");
    get_str(key, sizeof(key));
    if (!strlen(key)) return;

    do_cipher("encrypt", in, key);
}

static void dec_menu(void) {
    char in[MAX_PATH], key[MAX_PATH];
    printf("\n[Decrypt]\nfile: ");
    get_str(in, sizeof(in));
    if (!strlen(in)) return;

    printf("key: ");
    get_str(key, sizeof(key));
    if (!strlen(key)) return;

    do_cipher("decrypt", in, key);
}

static void run_menu(void) {
    char b[32];
    int run = 1;

    while (run) {
        printf("\n1. Encrypt\n2. Decrypt\n3. Help\n4. Exit\nchoice: ");
        get_str(b, sizeof(b));
        int c = atoi(b);

        if (c == 1) enc_menu();
        else if (c == 2) dec_menu();
        else if (c == 3) show_help("ceaserCLI");
        else if (c == 4) {
            printf("bye\n");
            run = 0;
        } else {
            printf("invalid\n");
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        run_menu();
        return 0;
    }

    if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
        show_help(argv[0]);
        return 0;
    }

    if (!strcmp(argv[1], "encrypt") || !strcmp(argv[1], "decrypt")) {
        if (argc != 4) {
            printf("Usage: %s %s <file> <key>\n", argv[0], argv[1]);
            return 1;
        }
        return do_cipher(argv[1], argv[2], argv[3]);
    }

    printf("unknown cmd '%s'\n", argv[1]);
    show_help(argv[0]);
    return 1;
}
