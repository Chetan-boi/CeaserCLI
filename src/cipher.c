#if __has_include("../include/cipher.h")
#include "../include/cipher.h"
#else
#include "cipher.h"
#endif

void cshift(char *ch, int s) {
    if (isalpha((unsigned char)*ch)) {
        char b = islower((unsigned char)*ch) ? 'a' : 'A';
        *ch = (char)(((*ch - b + s) % 26 + 26) % 26 + b);
    }
}

int load_key(Cfg *c) {
    FILE *fp = fopen(c->key, "rb");
    if (!fp) return -1;

    c->len = fread(c->s, 1, MAX_KEY, fp);
    fclose(fp);

    return (c->len > 0) ? 0 : -1;
}

void proc_file(Cfg *c) {
    FILE *in = fopen(c->in, "r");
    if (!in) {
        printf("cant open %s\n", c->in);
        exit(1);
    }

    FILE *out = fopen(c->out, "w");
    if (!out) {
        printf("cant write %s\n", c->out);
        fclose(in);
        exit(1);
    }

    size_t cnt = 0;
    int ch;

    while ((ch = fgetc(in)) != EOF) {
        if (isalpha(ch)) {
            int s = c->s[cnt % c->len];
            char t = (char)ch;
            cshift(&t, s);
            ch = t;
            cnt++;
        }
        fputc(ch, out);
    }

    fclose(in);
    fclose(out);
}

static void make_out_name(const char *in, int dec, char *out, size_t sz) {
    const char *dot = strrchr(in, '.');
    if (dot) {
        int base_len = (int)(dot - in);
        if (dec) {
            if (base_len >= 10 && strncmp(dot - 10, "_encrypted", 10) == 0) {
                snprintf(out, sz, "%.*s_decrypted%s", base_len - 10, in, dot);
            } else {
                snprintf(out, sz, "%.*s_decrypted%s", base_len, in, dot);
            }
        } else {
            snprintf(out, sz, "%.*s_encrypted%s", base_len, in, dot);
        }
    } else {
        snprintf(out, sz, "%s_%s", in, dec ? "decrypted" : "encrypted");
    }
}

int do_cipher(const char *mode, const char *in, const char *key) {
    Cfg c;
    memset(&c, 0, sizeof(c));

    strncpy(c.in, in, sizeof(c.in) - 1);
    strncpy(c.key, key, sizeof(c.key) - 1);
    c.dec = (strcmp(mode, "decrypt") == 0);

    make_out_name(c.in, c.dec, c.out, sizeof(c.out));

    if (load_key(&c) != 0) {
        printf("error loading key %s\n", c.key);
        return 1;
    }

    proc_file(&c);
    printf("done, %s is %s\n", c.dec ? "decrypted" : "encrypted", c.out);

    return 0;
}
