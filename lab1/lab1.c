#include "../lib/lib.h"

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

	uint32_t *array_test1;
	size_t array_count_test1;
	decode_fi0("00010000101100001", &array_test1, &array_count_test1);
	printf("decoded_fi0: ");
	for (int i = 0; i < array_count_test1; ++i)
	{
		printf("%d ", array_test1[i]);
	}
	printf("\n");

	uint32_t *array_test;
	size_t array_count_test;
	decode_fi1("0001110010001111111100001010", &array_test, &array_count_test);

	printf("decoded_fi1: ");
	for (int i = 0; i < array_count_test; ++i)
	{
		printf("%d ", array_test[i]);
	}
	printf("\n");

	uint32_t *array_test2;
	size_t array_count_test2;
	decode_fi2("010110010101101001100", &array_test2, &array_count_test2);

	printf("decoded_fi2: ");
	for (int i = 0; i < array_count_test2; ++i)
	{
		printf("%d ", array_test2[i]);
	}
	printf("\n");
	free(array);

	return 0;
}
