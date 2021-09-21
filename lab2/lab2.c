#include "../lib/lib.h"

char *ABC = "abcdefghijklmnopqrstuvwxyz_";


#define BLOCK   4096
#define ARCHIVE 1
#define UNZIP   2

int start_msg()
{
	int tmp;
	printf("======================\n");
	printf("[1] Archive file\n");
	printf("[2] Unzip file\n");
	printf("======================\n");
	scanf("%d", &tmp);

	return tmp;
}

int main(int argc, char const *argv[])
{

	FILE *fr;
	FILE *fw;

	int option;
	char filename[255];
	char new_filename[255];
	char buffer[BLOCK+1] = "";
	while (1)
	{
		option = start_msg();
		printf("Enter file name: ");
		scanf("%s", filename);
		fr = fopen(filename, "r");

		strcpy(new_filename, filename);

		

		ABC_t *abc = abc_init_list();
		if (abc == NULL)
		{
			printf("<%s:%d> abc_init failed!\n", __func__, __LINE__);
			return -1;
		}

		if (option == ARCHIVE)
		{
			strcat(new_filename, "_archive");
			fw = fopen(new_filename, "w+");

			while (fread(buffer, sizeof(char), BLOCK, fr) != 0)
			{
				uint32_t *array;
				size_t array_count;
				abc_mtf(&abc, buffer, &array, &array_count);

				// printf("Mtf: ");
				// for (int i = 0; i < array_count; ++i)
				// {
				// 	printf("%d ", array[i]);
				// }
				// printf("\n");

				char *tmp_ptr;
				char code[2048 * BLOCK];
				for (int i = 0; i < array_count; ++i)
				{
					tmp_ptr = fi2(array[i]);
					strcat(code, tmp_ptr);
					free(tmp_ptr);
				}

				uint32_t code_uint32;
				while (strlen(code) > 1)
				{
					code_uint32 = 0;
					bin_str_to_bin(code, &code_uint32);
					fwrite(&code_uint32, sizeof(uint32_t), 1, fw);
				}
				// printf("Coded fi2: '%s'\n", code);
				
			}

		}
		else if (option == UNZIP)
		{

		}
	
		return 0;

	}

	// if (argc != 2)
	// {
	// 	printf("<%s:%d> Wrong count of args\n", __func__, __LINE__);
	// 	return -1;
	// }

	// const char *input_data = argv[1];

	// printf("input_data: '%s'\n", input_data);

	/*size_t abc_count;
	ABC_t *abc = abc_init(ABC, &abc_count);
	if (abc == NULL)
	{
		printf("<%s:%d> abc_init failed!\n", __func__, __LINE__);
		return -1;
	}*/

	// ABC_t *abc = abc_init_list();
	// if (abc == NULL)
	// {
	// 	printf("<%s:%d> abc_init failed!\n", __func__, __LINE__);
	// 	return -1;
	// }

	// uint32_t *array;
	// size_t array_count;
	// abc_mtf(&abc, input_data, &array, &array_count);

	// printf("Mtf: ");
	// for (int i = 0; i < array_count; ++i)
	// {
	// 	printf("%d ", array[i]);
	// }
	// printf("\n");

	// char *tmp_ptr;
	// char code[2048] = "";
	// for (int i = 0; i < array_count; ++i)
	// {
	// 	tmp_ptr = fi2(array[i]);
	// 	strcat(code, tmp_ptr);
	// 	free(tmp_ptr);
	// }

	// printf("Coded fi2: '%s'\n", code);
	// uint32_t *array2;
	// size_t array_count2;
	// decode_fi2(code, &array2, &array_count2);

	// printf("decoded_fi2: ");
	// for (int i = 0; i < array_count2; ++i)
	// {
	// 	printf("%d ", array2[i]);
	// }
	// printf("\n");

	/*ABC_t *abc_copy = abc_init(ABC, &abc_count);
	if (abc == NULL)
	{
		printf("<%s:%d> abc_init failed!\n", __func__, __LINE__);
		return -1;
	}*/

	// ABC_t *abc_copy = abc_init_list();
	// if (abc_copy == NULL)
	// {
	// 	printf("<%s:%d> abc_init failed!\n", __func__, __LINE__);
	// 	return -1;
	// }

	// char *decoded_mtf_str = decode_mtf(abc_copy, array2, array_count2);

	// printf("decoded_mtf_str: '%s'\n", decoded_mtf_str);
	// free(array);
	// free(array2);

	
	
	//abc_list_printf(abc, 255);
	
	return 0;
}