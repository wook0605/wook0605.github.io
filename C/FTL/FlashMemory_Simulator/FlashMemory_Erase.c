#include "FlashMemory_head.h"

void Flash_erase(FILE* Flash_memory, int erase_block)
{
	int first_block = (((erase_block) * SS) * NOS);
	int file_end = 0;

	Flash_memory = fopen("Flash_Memory.txt", "r+"); // 읽기/쓰기 모드로 파일을 연다.


	if (Flash_memory == NULL) //파일이 열리지않았을 때
	{
		printf("파일이 열리지 않았습니다.\n");
	}

	else
	{
		fseek(Flash_memory, 0, SEEK_END); //파일의 끝으로 간다.
		file_end = ftell(Flash_memory); //파일이 가지고 있는 문자의 길이를 잰다.
		rewind(Flash_memory);// 파일 포인터를 다시 맨앞으로

		if (erase_block == 0) // 첫 블록일 때
		{
			for (int i = 0; i < NOS; i++) // NOS = 32개, 섹터의 개수. 삭제 시작
			{
				for (int  j = 0; j < SS; j++) //섹터 크기만큼
				{
					fprintf(Flash_memory, " ");
				}
			}
		}


		else //첫 블록이 아닐 때
		{
			if ((file_end / 512) / 32 <= erase_block) //삭제할 블록이 파일의 블록 수보다 크거나 같은 경우
			{
				printf("영역을 초과했습니다.\n");
			}
			else
			{
				fseek(Flash_memory, first_block, SEEK_SET); // 해당 블록의 위치로 포인터를 이동
				for (int i = 0; i < NOS; i++) //삭제 시작
				{
					for (int j = 0; j < SS; j++)
					{
						fprintf(Flash_memory, " ");
					}
				}
			}
		}
			
		printf("Erase %dth Block\n", erase_block);
	}
	fclose(Flash_memory);
}