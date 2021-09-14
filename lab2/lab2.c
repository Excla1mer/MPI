#include "../lib/lib.h"

char *ABC = "abcdefghijklmnopqrstuvwxyz_";

typedef struct ABC_s
{
	int  key;
	char value;
} ABC_t;

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

	printf("<%s:%d> Can't find value '%c' in alphabet '%s'", __func__, __LINE__, value, ABC);
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

	//printf("<%s:%d> Can't find value '%c' in alphabet '%s'", __func__, __LINE__, value, ABC);
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

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		printf("<%s:%d> Wrong count of args\n", __func__, __LINE__);
		return -1;
	}

	const char *input_data = argv[1];

	printf("input_data: '%s'\n", input_data);

	size_t abc_count;
	ABC_t *abc = abc_init(ABC, &abc_count);
	if (abc == NULL)
	{
		printf("<%s:%d> abc_init failed!\n", __func__, __LINE__);
		return -1;
	}

	uint32_t *array;
	size_t array_count;
	abc_mtf(abc, abc_count, input_data, &array, &array_count);

	printf("Mtf: ");
	for (int i = 0; i < array_count; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");

	char *tmp_ptr;
	char code[2048] = "";
	for (int i = 0; i < array_count; ++i)
	{
		tmp_ptr = fi2(array[i]);
		strcat(code, tmp_ptr);
		free(tmp_ptr);
	}

	printf("Coded fi2: '%s'\n", code);
	uint32_t *array2;
	size_t array_count2;
	decode_fi2(code, &array2, &array_count2);

	printf("decoded_fi2: ");
	for (int i = 0; i < array_count2; ++i)
	{
		printf("%d ", array2[i]);
	}
	printf("\n");

	ABC_t *abc_copy = abc_init(ABC, &abc_count);
	if (abc == NULL)
	{
		printf("<%s:%d> abc_init failed!\n", __func__, __LINE__);
		return -1;
	}

	char *decoded_mtf_str = decode_mtf(abc_copy, abc_count, array2, array_count2);

	printf("decoded_mtf_str: '%s'\n", decoded_mtf_str);
	free(array);
	free(array2);
	
	return 0;
}