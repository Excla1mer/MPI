#include "lib.h"

char *bin(uint32_t x, int no_full)
{
	char *output = (char *)malloc(MAX_BIN_LEN * sizeof(char));
	if (output == NULL)
	{
		printf("<%s:%d> malloc failed!\n", __func__, __LINE__);
		return NULL;
	}

	if (x == 0)
	{
		strcpy(output, "0\0");
		return output;
	}

	int offset = 0;
	if (no_full)
	{
		while ((x & BIT_32) == 0)
		{
			x = x << 1;
			offset++;
		}
	}

	int bin_str_len = 0;
	for (int i = offset; i < 32; i++)
	{
		if ((x & BIT_32) == 0)
		{
			output[bin_str_len] = '0';
			bin_str_len++;
		}
		else
		{
			output[bin_str_len] = '1';
			bin_str_len++;
		}

		x = x << 1;
	}

	output[bin_str_len] = '\0';

	return output;
}

char *bint(uint32_t x)
{
	char *output = (char *)malloc(MAX_BIN_LEN * sizeof(char));
	if (output == NULL)
	{
		printf("<%s:%d> malloc failed!\n", __func__, __LINE__);
		return NULL;
	}

	char *tmp = (char *)malloc(MAX_BIN_LEN * sizeof(char));
	if (tmp == NULL)
	{
		printf("<%s:%d> malloc failed!\n", __func__, __LINE__);
		return NULL;
	}

	tmp = bin(x, 1);
	strcpy(output, tmp+1);
	free(tmp);

	return output;
}

int array_add(uint32_t value, uint32_t **array, size_t *array_count)
{
	*array_count = *array_count + 1;
	uint32_t *tmp_ptr = (uint32_t *)realloc(*array, *array_count * (sizeof(uint32_t)));
	if (tmp_ptr == NULL)
	{
		printf("<%s:%d> realloc failed!\n", __func__, __LINE__);
		free(*array);
		return -1;
	}

	*array = tmp_ptr;
	(*array)[*array_count - 1] = value;

	return 0;
}

char *fi0(uint32_t x)
{
	char *output = (char *)calloc(MAX_BIN_LEN, sizeof(char));
	if (output == NULL)
	{
		printf("<%s:%d> malloc failed!\n", __func__, __LINE__);
		return NULL;
	}

	for (int i = 0; i < x; i++)
	{
		strcat(output, "0");
	}

	strcat(output, "1");

	return output;
}

char *fi1(uint32_t x)
{
	char *output = (char *)calloc(MAX_BIN_LEN, sizeof(char));
	if (output == NULL)
	{
		printf("<%s:%d> malloc failed!\n", __func__, __LINE__);
		return NULL;
	}

	if (0 == x)
	{
		strcpy(output, "1");
		return output;
	}

	char *bint_s;
	bint_s = bint(x);
	char *bin_s;
	bin_s = bin(x, 1);
	char *fi0_s;
	fi0_s = fi0(strlen(bin_s));

	strcpy(output, fi0_s);
	strcat(output, bint_s);
	free(bint_s);
	free(bin_s);
	free(fi0_s);

	return output;
}

char *fi2(uint32_t x)
{
	char *output = (char *)calloc(MAX_BIN_LEN, sizeof(char));
	if (output == NULL)
	{
		printf("<%s:%d> malloc failed!\n", __func__, __LINE__);
		return NULL;
	}

	if (0 == x)
	{
		strcpy(output, "1");
		return output;
	}

	char *bint_s;
	bint_s = bint(x);
	char *bin_s;
	bin_s = bin(x, 1);
	char *fi1_s;
	fi1_s = fi1(strlen(bin_s));

	strcpy(output, fi1_s);
	strcat(output, bint_s);
	free(bint_s);
	free(bin_s);
	free(fi1_s);

	return output;
}

// int bin_str_to_bin(char *bin_str, uint32_t *array_pos)
// {
// 	size_t str_len = strlen(bin_str);
// 	int max_uint = 32;
// 	int bit = 1;
// 	for (int i = str_len-1; i >= 0; i--)
// 	{
// 		if (max_uint < 0)
// 		{
// 			//bin_str[i+1] = '\0';
// 			break;
// 		}
// 		if  (bin_str[i] == '1')
// 		{
// 			*array_pos = *array_pos | bit;
// 		}

// 		bit = bit << 1;
// 	}

// 	return 0;
// }

int bin_str_to_bin_l(char *bin_str, uint32_t *array_pos)
{
	size_t str_len = strlen(bin_str);
	int max_uint = 32;
	uint32_t bit_l = 0x80000000;
	uint32_t bit_r = 1;
	int start;
	int rc;

	if (str_len > max_uint)
	{
		start = max_uint-1;
		rc = 0;
	}
	else
	{
		start = str_len-1;
		rc = 1;
	}

	for (int i = start; i >= 0; i--)
	{
		if  (bin_str[i] == '1')
		{
			*array_pos = *array_pos | bit_r;
		}

		bit_r = bit_r << 1;
	}

	return rc;
}

int bin_str_to_bin(char *bin_str, uint32_t *array_pos)
{
	size_t str_len = strlen(bin_str);
	int max_uint = 32;
	uint32_t bit_l = 0x80000000;
	uint32_t bit_r = 1;
	int start;
	int rc;

	if (str_len > max_uint)
	{
		for (int i = 0; i < max_uint; i++)
		{
			if (bin_str[i] == '1')
			{
				*array_pos = *array_pos | bit_l;
			}

			bit_l = bit_l >> 1;
		}

		rc = 0;
	}
	else
	{
		for (int i = 0; i < str_len; i++)
		{
			if (bin_str[i] == '1')
			{
				*array_pos = *array_pos | bit_l;
			}

			bit_l = bit_l >> 1;
		}

		rc = 1;
	}

	return rc;
}

int decode_fi0(char *input_str, uint32_t **array, size_t *array_size)
{
       size_t str_len = strlen(input_str);
       *array_size = 0;
       for (int i = 0; i < str_len; i++)
       {
               if (input_str[i] == '1')
                       *array_size = *array_size + 1;
       }

       uint32_t *output = (uint32_t*)malloc((*array_size) * sizeof(uint32_t));
       if (output == NULL)
       {
               printf("<%s:%d> malloc failed!\n", __func__, __LINE__);
               return -1;
       }

       int value = 0;
       int j = 0;
       for (int i = 0; i < str_len; i++)
       {
               if (input_str[i] == '1')
               {
                       output[j] = value;
                       value = 0;
                       j++;
               }
               else
               {
                       value++;
               }
       }

       *array = output;

       return 0;
}

int decode_fi1(char *input_str, uint32_t **array, size_t *array_size)
{
	size_t str_len = strlen(input_str);
	*array_size = 0;
	uint32_t *output = (uint32_t*)malloc(sizeof(uint32_t));
	if (output == NULL)
	{
		printf("<%s:%d> malloc failed!\n", __func__, __LINE__);
		return -1;
	}

	char *bin_str = (char *)calloc(MAX_BIN_LEN, sizeof(char));
	if (bin_str == NULL)
	{
		printf("<%s:%d> calloc failed!\n", __func__, __LINE__);
		return -1;
	}

	int k = 0;
	int bin_str_len =  0;
	for (int i = 0; i < str_len; i++)
	{
		if (input_str[i] == '1')
		{
			*array_size = *array_size + 1;
			uint32_t *tmp = (uint32_t*)realloc(output, *array_size * sizeof(uint32_t));
			if (tmp == NULL)
			{
				printf("<%s:%d> realloc failed!\n", __func__, __LINE__);
				return -1;
			}

			output = tmp;
			for (int j = i; j < i+k; j++)
			{
				bin_str[bin_str_len] = input_str[j];
				bin_str_len++;
			}

			output[*array_size - 1] = 0;
			if (k == 0)
				continue;
			else
				i = i + k - 1;

			bin_str_to_bin(bin_str, &output[*array_size - 1]);
			memset(bin_str, 0, sizeof(bin_str));
			bin_str_len =  0;
			k = 0;
			continue;
		}

		k++;
	}

	*array = output;

	return 0;
}

int decode_fi2(char *input_str, uint32_t **array, size_t *array_size)
{
	size_t str_len = strlen(input_str);
	*array_size = 0;
	uint32_t *output = (uint32_t*)malloc(sizeof(uint32_t));
	if (output == NULL)
	{
		printf("<%s:%d> malloc failed!\n", __func__, __LINE__);
		return -1;
	}

	char *bin_str = (char *)calloc(MAX_BIN_LEN, sizeof(char));
	if (bin_str == NULL)
	{
		printf("<%s:%d> calloc failed!\n", __func__, __LINE__);
		return -1;
	}

	int k = 0;
	int bin_str_len =  0;
	for (int i = 0; i < str_len; i++)
	{
		if (input_str[i] == '1')
		{
			*array_size = *array_size + 1;
			uint32_t *tmp = (uint32_t*)realloc(output, *array_size * sizeof(uint32_t));
			if (tmp == NULL)
			{
				printf("<%s:%d> realloc failed!\n", __func__, __LINE__);
				return -1;
			}

			output = tmp;
			for (int j = i; j < i+k; j++)
			{
				bin_str[bin_str_len] = input_str[j];
				bin_str_len++;
			}

			output[*array_size - 1] = 0;
			if (k == 0)
				continue;
			else
				i = i + k - 1;


			uint32_t k1 = 0;
			bin_str_to_bin_l(bin_str, &k1);
			memset(bin_str, 0, sizeof(bin_str));
			bin_str_len =  0;
			k = 0;
			bin_str[bin_str_len] = '1';
			bin_str_len++;
			for (int j = i+1; j < i+k1; j++)
			{
				bin_str[bin_str_len] = input_str[j];
				bin_str_len++;
			}

			bin_str_to_bin(bin_str, &output[*array_size - 1]);
			memset(bin_str, 0, sizeof(bin_str));
			bin_str_len =  0;
			i = i + k1 - 1;
			continue;
		}

		k++;
	}

	*array = output;

	return 0;
}

ABC_t *abc_init(char *alphabet, size_t *size)
{
	*size = strlen(alphabet);
	ABC_t *abc = (ABC_t *)malloc(sizeof(ABC_t) * (*size));
	if (abc == NULL)
	{
		printf("<%s:%d> malloc failed!", __func__, __LINE__);
		return NULL;
	}

	for (int i = 0; i < (*size); ++i)
	{
		abc[i].key = i;
		abc[i].value = alphabet[i];
	}

	return abc;
}


ABC_t *abc_init_list()
{
	ABC_t *abc_head;
	ABC_t *abc; 

	uint32_t i = 0;
	while (1)
	{
		ABC_t *tmp = (ABC_t *)malloc(sizeof(ABC_t));
		if (tmp == NULL)
		{
			printf("<%s:%d> malloc failed!", __func__, __LINE__);
			return NULL;
		}

		if (i == 0)
		{
			tmp->value = (uint8_t)i;
			abc_head = tmp;
			abc = abc_head;
		}
		else if (i == 255)
		{
			tmp->value = (uint8_t)i;
			abc->next = tmp;
			tmp->next = NULL;
			break;
		}
		else
		{
			tmp->value = (uint8_t)i;
			abc->next = tmp;
			abc = tmp;
		}

		i++;
	} 

	return abc_head;
}

int abc_list_printf(ABC_t *abc_head, size_t count)
{
	for (int i = 0; i <= count; i++)
	{
		printf("{%d}[%p] value '%c' | next [%p]\n", i, abc_head, (char)abc_head->value, abc_head->next);
		abc_head = abc_head->next;
	}

	return 0;
}

int get_key_from_val(ABC_t *abc, char value)
{
	int key = 0;
	while (abc != NULL)
	{
		if (abc->value == (uint8_t)value)
		{
			return key;
		}
		else
		{
			abc = abc->next;
			key++;
		}
	}
/*
	for (int i = 0; i < size; ++i)
	{
		if (abc[i].value == value)
		{
			return abc[i].key;
		}
	}
*/
	printf("<%s:%d> Can't find value '%c' in alphabet", __func__, __LINE__, value);
	return -1;
}

char get_val_from_key(ABC_t *abc, int key)
{
	int i = 0;
	while (abc != NULL)
	{
		if (i == key)
		{
			return (char)abc->value;
		}
		else
		{
			abc = abc->next;
			i++;
		}
	}
	/*
	for (int i = 0; i < size; ++i)
	{
		if (abc[i].key == key)
		{
			return abc[i].value;
		}
	}*/

	printf("<%s:%d> Can't find key '%d' in alphabet", __func__, __LINE__, key);
	return -1;
}

int abc_mtf_helper(ABC_t **abc, char value)
{
	ABC_t *head = *abc;
	ABC_t *tmp = *abc;
	ABC_t *prev = NULL;

	while (tmp != NULL)
	{
		if (tmp->value == (uint8_t)value)
		{
			if (prev != NULL)
				prev->next = tmp->next;
			else
				return 0;

			tmp->next = head;
			*abc = tmp;

			return 0;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}

	/*int tmp_key = get_key_from_val(abc, value);

	for (int i = 0; i < size; ++i)
	{
		if (abc[i].value == value)
		{
			abc[i].key = 0;	
		}
		else if (abc[i].key < tmp_key)
			abc[i].key++;
	}*/

	return -1;
}

void abc_print(ABC_t *abc, size_t size)
{
	printf("=============abc_print===========\n");
	for (int i = 0; i < size; ++i)
	{
		printf("'%c': [%d]\n", abc[i].value, abc[i].key);
	}
	printf("=================================\n");

	return;
}

int abc_mtf(ABC_t **abc, const char *input_data, uint32_t **array, size_t *array_size)
{
	char tmp_char;
	*array_size = strlen(input_data);
	uint32_t *output = (uint32_t*)malloc((*array_size) * sizeof(uint32_t));
	if (output == NULL)
	{
		printf("<%s:%d> malloc failed!\n", __func__, __LINE__);
		return -1;
	}

	for (int i = 0; i < *array_size; ++i)
	{
		tmp_char = input_data[i];

		output[i] = get_key_from_val(*abc, tmp_char);
		if (output[i] == -1)
		{
			printf("<%s:%d> get_key_from_val failed!", __func__, __LINE__);
			return -1;
		}
		abc_mtf_helper(abc, tmp_char);
	}

	*array = output;

	return 0;
}

char *decode_mtf(ABC_t *abc, uint32_t *array, size_t array_size)
{
	char *output = (char *)malloc(sizeof(char) * array_size);
	if (output == NULL)
	{
		printf("<%s:%d> malloc failed!\n", __func__, __LINE__);
		return NULL;
	}

	for (int i = 0; i < array_size; ++i)
	{
		output[i] = get_val_from_key(abc, array[i]);
		abc_mtf_helper(&abc, output[i]);
	}

	return output;
}
