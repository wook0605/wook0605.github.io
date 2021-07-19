#include "dynamic_blockmapping_head.h"

void Flash_write(FILE* Flash_memory, unsigned int LSN, char* write_data)
{
	unsigned int LBN = LSN / NOS;
	unsigned int PBN = mtable.table[LBN];  // 지정한 섹터를 가르키기 위한 값
	unsigned int Block = 0;
	unsigned int offset_count = 0;
	unsigned int offset = LSN % NOS;
	unsigned char status = 0;
	unsigned int nob = 0;
	unsigned char read_data[513];
	memset(read_data, NULL, sizeof(read_data));

	Flash_memory = fopen("Block_Mapping_FM.txt", "r+"); //파일을 읽기/쓰기 모드로 연다.
	fpos_t pos = 0;

	if (Flash_memory == NULL)
	{
		printf("파일이 열리지 않았습니다.\n");
	}
	else
	{
		if (mtable.nos <= LSN) //영역을 초과해서 쓰는 경우
		{
			printf("영역을 초과했습니다.\n");
		}
		else //영역을 초과하지 않은 경우
		{
			pos = mtable.FP_loc[(LBN * NOS) + offset]; //해당 블록의 파일 포인터값 전달
			fsetpos(Flash_memory, &pos); //해당 블록의 오프셋 으로 이동
			fgets(read_data, SS, Flash_memory); //데이터 영역 확인
			fscanf(Flash_memory, "%d\t%d\t%d\t%d", &spare.status, &spare.LSN, &spare.write_count, &spare.erase_count); //해당 블록의 spare 읽기
			fgetc(Flash_memory);//파일 포인터 한칸 이동
			if (spare.status == 0) //free page일 때
			{
				spare.status = 1;
				fsetpos(Flash_memory, &pos);
				spare.write_count++; //쓰기 카운트 증가
				mtable.write_count++;
				fprintf(Flash_memory, "%512s\t%d\t%d\t%d\t%d\n", write_data, spare.status, spare.LSN, spare.write_count, spare.erase_count); //쓰기
				printf("Done!\n");
			}
			else //덮어쓰기 발생 시
			{
				pos = mtable.FP_loc[LBN * NOS];
				nob = mtable.nob;
				FTL_write(Flash_memory, LSN, PBN, write_data, offset, nob, pos);
			}
		}
		fclose(Flash_memory); //파일을 닫는다.
	}
}