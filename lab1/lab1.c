#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_BIN_LEN 128
#define BIT_32      0x80000000

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

// char *bint(char *bin_x)
// {
// 	char *output = (char *)malloc(MAX_BIN_LEN * sizeof(char));
// 	if (output == NULL)
// 	{
// 		printf("<%s:%d> malloc failed!\n", __func__, __LINE__);
// 		return NULL;
// 	}

// 	strcpy(output, bin_x+1);

// 	return output;
// }

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

int input_data_parser(const char *input_data, uint32_t **array, size_t *array_count)
{
	char *str = strdup(input_data);
	if (str == NULL)
	{
		printf("<%s:%d> strdup failed!\n", __func__, __LINE__);
		return -1;
	}

	*array_count = 0;
	*array = (uint32_t *)malloc(sizeof(uint32_t));

	if (*array == NULL)
	{
		free(str);
		printf("<%s:%d> malloc failed!", __func__, __LINE__);
		return -1;
	}

	char *isrt = strtok(str, ",");

	while (isrt != NULL)
	{

		uint32_t tmp;
		sscanf(isrt, "%d", &tmp);

		if (array_add(tmp, array, array_count))
		{
			printf("<%s:%d> array_add failed!", __func__, __LINE__);
			return -1;
		}

		isrt = strtok(NULL, ",");
	}

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

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		printf("<%s:%d> Wrong count of args\n", __func__, __LINE__);
		return -1;
	}

	const char *input_data = argv[1];

//TODO: Добить regex, либо написать функцию проверки входных даных
	// regex_t regex;
	// int res;

	// res = regcomp(&regex, "[0-9]{1}", 0);
	// if (res)
	// {
	// 	printf("<%s:%d> regcomp failed!\n", __func__, __LINE__);
	// 	return -1;
	// }

	// res = regexec(&regex, input_data, 0, NULL, 0);
	// if (!res)
	// {
	// 	printf("regexec Ok!\n");
	// }
	// else
	// {
	// 	printf("regexec no Ok\n");
	// 	return -1;
	// }

	printf("input_data: '%s'\n", input_data);

	size_t array_count;
	uint32_t *array;

	if (input_data_parser(input_data, &array, &array_count))
	{
		printf("<%s:%d> input_data_parser failed!\n", __func__, __LINE__);
		return -1;
	}

	char *test;
	char *test1;
	char *test2;
	char *test3;
	char *test4;

	for (int i = 0; i < array_count; i++)
	{
		printf("---------------------------\n");
		printf("[%d]: int\t%d\n", i, array[i]);
		test = bin(array[i]);
		printf("[%d]: bin\t%s\n", i, test);
		test1 = bint(array[i]);
		printf("[%d]: bint\t%s\n", i, test1);
		test2 = fi0(array[i]);
		printf("[%d]: fi0\t%s\n", i, test2);
		test3 = fi1(array[i]);
		printf("[%d]: fi1\t%s\n", i, test3);
		test4 = fi2(array[i]);
		printf("[%d]: fi2\t%s\n", i, test4);

		free(test);
		free(test1);
		free(test2);
		free(test3);
		free(test4);
	}

	uint32_t *array_test;
	size_t array_count_test;
	decode_fi0("00010000101100001", &array_test, &array_count_test);

	printf("decoded_fi0: ");
	for (int i = 0; i < array_count_test; ++i)
	{
		printf("%d ", array_test[i]);
	}
	printf("\n");
	free(array);

	return 0;
}
