#include "FlashMemory_head.h"

void init(FILE* Flash_memory, int value)
{
	Flash_memory = fopen("Flash_Memory.txt","w"); //쓰기모드로 연다.

	int nob = ((value * 1024 * 1024) / 512) / 32; // 블록 개수

	if (Flash_memory == NULL) //파일이 열리지 않는 경우
	{
		printf("파일이 열리지 않습니다.\n");
	}

	else //파일이 정상적으로 열린 경우
	{
		for (int i = 0; i < nob; i++) //블록의 개수만큼 (이 반복은 입력받은 수에 따라 달라진다.)
		{
			for (int j = 0; j < NOS; j++) //섹터의 개수만큼 (32)
			{
				for (int k = 0; k < SS; k++) //섹터의 크기만큼 (512)
				{
					fprintf(Flash_memory, " ");
				}
			}
		}
	}

	fclose(Flash_memory);
}