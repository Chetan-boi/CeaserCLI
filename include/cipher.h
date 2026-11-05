#ifndef CIPHER_H
#define CIPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEY 256
#define MAX_PATH 256

typedef struct {
    char in[MAX_PATH];
    char key[MAX_PATH];
    char out[MAX_PATH];
    unsigned char s[MAX_KEY];  
    size_t len;
    int dec;                      
} Cfg;

int load_key(Cfg *c);                  
void proc_file(Cfg *c);            
void cshift(char *ch, int s);
int do_cipher(const char *mode, const char *in, const char *key);

#endif
