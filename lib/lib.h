#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/in.h>

#define MAX_BIN_LEN 128
#define BIT_32      0x80000000
#define MAX_U_CHAR    255

typedef struct ABC_s
{
	int  key;
	uint8_t value;
	struct ABC_s *next;
} ABC_t;

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

ABC_t *abc_init(char *alphabet, size_t *size);
ABC_t *abc_init_list();
int abc_list_printf(ABC_t *abc_head, size_t count);

int get_key_from_val(ABC_t *abc, char value);
char get_val_from_key(ABC_t *abc, int key);

int abc_mtf_helper(ABC_t **abc, char value);
void abc_print(ABC_t *abc, size_t size);
int abc_mtf(ABC_t **abc, const char *input_data, uint32_t **array, size_t *array_size);

char *decode_mtf(ABC_t *abc, uint32_t *array, size_t array_size);
