#ifndef CIPHER_H
#define CIPHER_H

#define BUFFER_SIZE 1024

/* Reads integer shift key from key file and normalizes it to 0-25 */
int read_shift_key(const char* key_path, int* shift);

/* Shifts a single character (is_decrypt: 0 for encrypt, 1 for decrypt) */
char shift_char(char c, int shift, int is_decrypt);

/* Processes input file and writes result to output file (or stdout if output_path is NULL) */
int process_file(const char* input_path, const char* key_path, const char* output_path, int is_decrypt);

#endif
