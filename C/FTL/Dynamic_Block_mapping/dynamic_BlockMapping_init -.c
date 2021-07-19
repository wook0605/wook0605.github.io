#include "dynamic_blockmapping_head.h"

void init(FILE* Flash_memory, unsigned int value)
{
	Flash_memory = fopen("Block_Mapping_FM.txt", "w+"); //쓰기모드로 연다.
	unsigned int offset = 0;
	unsigned int nob = ((value * 1024 * 1024) / 512) / 32; // 블록 개수
	fpos_t pos = 0;
	mtable.nob = nob;
	mtable.nos = nob * 32;
	mtable.table = (unsigned int*)malloc(sizeof(unsigned int) * nob); //섹터의 개수만큼 테이블 할당
	mtable.FP_loc = (unsigned long long*)malloc(sizeof(unsigned long long) * mtable.nos); //파일 포인터 위치 할당
	if (spare.LSN != 0)
	{
		spare.LSN = 0;
		spare.status = 0;
	}
	for (int i = 0; i < nob; i++)
	{
		mtable.table[i] = i; //매핑테이블 구성
	}

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
				fgetpos(Flash_memory, &pos);
				mtable.FP_loc[(i * NOS) + j] = pos;
				for (int k = 0; k < SS; k++) //섹터의 크기만큼 (512)
				{
					fprintf(Flash_memory, " ");
				}
					fprintf(Flash_memory, "\t%d\t%d\t%d\t%d\n", spare.status, spare.LSN, spare.erase_count, spare.write_count);
				spare.LSN++;
			}
		}
		spare.LSN = 0;
	}
	fclose(Flash_memory);
}