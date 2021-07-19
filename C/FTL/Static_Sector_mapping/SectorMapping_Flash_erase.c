#include "SectorMapping.h"

void Flash_erase(FILE* Flash_memory, int LBN)
{
	int LSN = LBN * NOS;
	int file_end = 0;
	char read_data[SS]; // 읽은 데이터 저장할 배열
	int erase_sum = 0;
	memset(read_data, NULL, SS);

	Flash_memory = fopen("Sector_Mapping_FM.txt", "r+"); // 읽기/쓰기 모드로 파일을 연다.


	if (Flash_memory == NULL) //파일이 열리지않았을 때
	{
		printf("파일이 열리지 않았습니다.\n");
	}

	else
	{
		fseek(Flash_memory, 0, SEEK_END); //파일의 끝으로 간다.
		file_end = ftell(Flash_memory); //파일이 가지고 있는 문자의 길이를 잰다.
		rewind(Flash_memory);// 파일 포인터를 다시 맨앞으로

		if ((file_end / SS) / NOS <= LBN) //삭제할 블록이 파일의 블록 수보다 크거나 같은 경우
		{
			printf("영역을 초과했습니다.\n");
		}
		else
		{
			for (int i = LSN; i < LSN+NOS; i++) //삭제 시작
			{
				fseek(Flash_memory, mtable.table[i] * SS, SEEK_SET);
				for (int j = 0; j < SS; j++)//블록의 첫 섹터부터 마지막 섹터까지
				{
					fprintf(Flash_memory, " ");
				}
				mtable.erase_count[i]++; //각 섹터 삭제카운트 증가
				erase_sum++; //총 삭제카운트 증가
			}
		}
		printf("Erase %dth Block\n", LBN);
		printf("erase의 횟수 : %d\n", erase_sum);
	}
	fclose(Flash_memory);
}