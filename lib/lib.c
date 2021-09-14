#include "lib.h"

char *bin(uint32_t x)
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
	while ((x & BIT_32) == 0)
	{
		x = x << 1;
		offset++;
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

	tmp = bin(x);
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
	bin_s = bin(x);
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
	bin_s = bin(x);
	char *fi1_s;
	fi1_s = fi1(strlen(bin_s));

	strcpy(output, fi1_s);
	strcat(output, bint_s);
	free(bint_s);
	free(bin_s);
	free(fi1_s);

	return output;
}

int bin_str_to_bin(char *bin_str, uint32_t *array_pos)
{
	size_t str_len = strlen(bin_str);
	int bit = 1;
	for (int i = str_len-1; i >= 0; i--)
	{
		if  (bin_str[i] == '1')
		{
			*array_pos = *array_pos | bit;
		}

		bit = bit << 1;
	}

	return 0;
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
			bin_str_to_bin(bin_str, &k1);
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

int get_key_from_val(ABC_t *abc, size_t size, char value)
{
	for (int i = 0; i < size; ++i)
	{
		if (abc[i].value == value)
		{
			return abc[i].key;
		}
	}

	printf("<%s:%d> Can't find value '%c' in alphabet", __func__, __LINE__, value);
	return -1;
}

char get_val_from_key(ABC_t *abc, size_t size, int key)
{
	for (int i = 0; i < size; ++i)
	{
		if (abc[i].key == key)
		{
			return abc[i].value;
		}
	}

	printf("<%s:%d> Can't find key '%d' in alphabet", __func__, __LINE__, key);
	return -1;
}

int abc_mtf_helper(ABC_t *abc, size_t size, char value)
{
	int tmp_key = get_key_from_val(abc, size, value);
	for (int i = 0; i < size; ++i)
	{
		if (abc[i].value == value)
		{
			abc[i].key = 0;	
		}
		else if (abc[i].key < tmp_key)
			abc[i].key++;
	}

	return 0;
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

int abc_mtf(ABC_t *abc, size_t abc_size, const char *input_data, uint32_t **array, size_t *array_size)
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

		output[i] = get_key_from_val(abc, abc_size, tmp_char);
		if (output[i] == -1)
		{
			printf("<%s:%d> get_key_from_val failed!", __func__, __LINE__);
			return -1;
		}
		abc_mtf_helper(abc, abc_size, tmp_char);
	}

	*array = output;

	return 0;
}

char *decode_mtf(ABC_t *abc, size_t abc_size, uint32_t *array, size_t array_size)
{
	char *output = (char *)malloc(sizeof(char) * array_size);
	if (output == NULL)
	{
		printf("<%s:%d> malloc failed!\n", __func__, __LINE__);
		return NULL;
	}

	for (int i = 0; i < array_size; ++i)
	{
		output[i] = get_val_from_key(abc, abc_size, array[i]);
		abc_mtf_helper(abc, abc_size, output[i]);
	}

	return output;
}
