#include "FlashMemory_head.h"

void Flash_read(FILE* Flash_memory, int read_sector)
{
	int rs = (read_sector * SS); //지정한 섹터를 가르키기
	int file_end = 0;
	int len = 0;
	char read_Sdata[513]; // 512개 인덱스를 전부 읽기 위해서 513크기로 지정한다.

	Flash_memory = fopen("Flash_Memory.txt", "r"); //파일을 읽기 모드로 연다

	if (Flash_memory == NULL) //파일이 열리지 않았을때
	{
		printf("파일이 열리지 않았습니다.\n");
	}

	else
	{
		fseek(Flash_memory, 0, SEEK_END); //파일의 끝으로 간다.
		file_end = ftell(Flash_memory); //파일이 가지고 있는 문자의 길이를 잰다.
		rewind(Flash_memory);// 파일 포인터를 다시 맨앞으로

		if (rs == 0) //첫 섹터를 읽는 경우
		{
			fgets(read_Sdata, 513, Flash_memory);
			len = strlen(read_Sdata);
			
			if (len == SS && strspn(read_Sdata, " ") == SS) //문자열 길이가 512  AND 스페이스바 개수가 512개 일때
			{
				printf("EMPTY\n");
			}

			else
			{
				printf("%s", read_Sdata);
			}
		}

		else // 첫 섹터가 아닌 경우
		{
			if (file_end / 512 <= read_sector) //영역을 초과해서 읽는 경우
			{
				printf("영역을 초과했습니다.\n");
			}

			else
			{
				fseek(Flash_memory, rs, SEEK_SET);
				fgets(read_Sdata, 513, Flash_memory);
				len = strlen(read_Sdata);

				if (len == SS && strspn(read_Sdata, " ") == SS) //문자열 길이가 512 AND 스페이스바 개수가 512개 일때
				{
					printf("EMPTY\n");
				}

				else
				{
					printf("%s", read_Sdata);
				}
			}
		}
		fclose(Flash_memory);
	}
}