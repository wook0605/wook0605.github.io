#include "dynamic_blockmapping_head.h"

void Flash_read(FILE* Flash_memory, unsigned int  LSN)
{
	unsigned int PBN = FTL_read(LSN);
	unsigned int PBN_count = 0;
	unsigned int offset_count = 0;
	unsigned int offset = LSN % NOS;
	unsigned int spare_len = 0;
	char read_Sdata[513]; // 512개 인덱스를 전부 읽기 위해서 513크기로 지정한다.

	Flash_memory = fopen("Block_Mapping_FM.txt", "r"); //파일을 읽기 모드로 연다
	fpos_t pos;

	if (Flash_memory == NULL) //파일이 열리지 않았을때
	{
		printf("파일이 열리지 않았습니다.\n");
	}

	else
	{
		if (mtable.nos< LSN)
		{
			printf("영역을 초과했습니다.\n");
		}
		else
		{
			pos = mtable.FP_loc[LSN];
			fsetpos(Flash_memory, &pos);
			fgets(read_Sdata, SS, Flash_memory); //데이터 영역 읽기
			fscanf(Flash_memory, "%d\t%d\t%d\t%d", &spare.status, &spare.LSN, &spare.write_count, &spare.erase_count);
			if (spare.status == 0 || spare.status == 2) //Free Page일 때
			{
				printf("PBN %d의 offset : %d\tDATA : EMPTY or Invalid\n", PBN, offset);
			}

			else //valid page일 때
			{
				
				fgets(read_Sdata, SS, Flash_memory);
				printf("PBN %d의 offset : %d\nDATA : %s", PBN, offset, read_Sdata);
			}
			rewind(Flash_memory);
		}
	}

		fclose(Flash_memory);
}