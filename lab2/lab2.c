#include "../lib/lib.h"

char *ABC = "abcdefghijklmnopqrstuvwxyz_";

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