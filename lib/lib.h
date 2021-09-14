#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_BIN_LEN 128
#define BIT_32      0x80000000

char *bin(uint32_t x);
char *bint(uint32_t x);

int array_add(uint32_t value, uint32_t **array, size_t *array_count);

char *fi0(uint32_t x);
char *fi1(uint32_t x);
char *fi2(uint32_t x);

int bin_str_to_bin(char *bin_str, uint32_t *array_pos);

int decode_fi0(char *input_str, uint32_t **array, size_t *array_size);
int decode_fi1(char *input_str, uint32_t **array, size_t *array_size);
int decode_fi2(char *input_str, uint32_t **array, size_t *array_size);
