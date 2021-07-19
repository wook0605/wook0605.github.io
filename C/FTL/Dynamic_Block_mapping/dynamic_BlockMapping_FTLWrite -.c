#include "dynamic_blockmapping_head.h"

void FTL_write(FILE* Flash_memory, unsigned int LSN, unsigned int PBN, char* write_data, unsigned int overwrite_offset, unsigned int nob, fpos_t pos)
{
	unsigned int  LBN = LSN / NOS;
	unsigned int free_count = 0;
	unsigned int new_block = 0;
	unsigned int temp_loc = 0;
	float no_block_value = 0;
	unsigned int offset_count = 0;
	unsigned char read_data[513] = { NULL, };
	float threshhold = 80.0;
	fpos_t pos_2 = 0;
	fpos_t temp_pos = 0;
	memset(temp_B.temp_blcok, NULL, sizeof(temp_B)); //임시블록 초기화
	memset(temp_B_1.temp_blcok, NULL, sizeof(temp_B_1)); //임시블록 초기화
	rewind(Flash_memory);
	mtable.nob = nob;
	fsetpos(Flash_memory, &pos);//덮어쓰기 일어난 블록의 첫섹터부터 읽기
	for (offset_count = 0; offset_count < NOS; offset_count++) //덮어쓰기 일어난 구역 읽기.
	{
		fgets(read_data, SS, Flash_memory); //데이터 영역 읽기
		fscanf(Flash_memory, "%d\t%d\t%d\t%d", &temp_B.temp_spare_status[offset_count], &temp_B.temp_spare_LSN[offset_count], &temp_B.temp_spare_write_count[offset_count], &temp_B.temp_spare_erase_count[offset_count]); //스페어영역 읽기
		fgetc(Flash_memory);//파일 포인터 한칸 이동 (다음줄로)
		if (overwrite_offset == offset_count)  //블록과 offset이 overwrite가 일어난 부분에 일치하는 경우
		{
			strcpy(temp_B.temp_blcok[overwrite_offset], write_data); // 덮어쓰기가 일어난 지점의 데이터만 새로 써준다.
		}

		else if (overwrite_offset != offset_count && temp_B.temp_spare_status[offset_count] == 1) //유효한 데이터일때 (무효하거나 빈 데이터는 읽지 않는다.)
		{
			strcpy(temp_B.temp_blcok[offset_count], read_data); // erase는 블록단위로 일어나기 때문에 해당 블록의 유효데이터 전부 복사
		}
	}
	rewind(Flash_memory);
	for (new_block = 0; new_block < mtable.nob; new_block++) //빈 블록을 찾는다.
	{
		printf("빈블록 찾는 중\n");
		pos_2 = mtable.FP_loc[new_block * NOS]; //블록의 오프셋 파일포인터 위치 할당
		fsetpos(Flash_memory, &pos_2); //해당 블록의 오프셋에 파일 포인터 위치시킴.
		for (int i = 0; i < NOS; i++) //offset 읽기
		{
			fgets(read_data, SS, Flash_memory); //데이터 영역 읽기
			fscanf(Flash_memory, "%d\t%d\t%d\t%d", &temp_B_1.temp_spare_status[i], &temp_B_1.temp_spare_LSN[i], &temp_B_1.temp_spare_write_count[i], &temp_B_1.temp_spare_erase_count[i]); //spare 영역 읽기
			fgetc(Flash_memory);//파일 포인터 한칸 이동 (다음 줄로)
			if (temp_B_1.temp_spare_status[i] == 0) //완전히 빈 블록일 때
			{
				free_count++;
			}
			else //데이터가 존재하는 블록일 때
			{
				free_count = 0;
				break;
			}
		}
		if (free_count == 32) //완전히 빈 블록을 선정함.
		{
			mtable.no_block = 0;
			break;
		}
		else if (free_count != 32)
		{
			mtable.no_block++;
		}
		no_block_value = (mtable.no_block / mtable.nob) * 100;
		if (no_block_value > threshhold) // free 블록의 수가 임계값 보다 적게 남았을 때
		{
			Flash_erase(Flash_memory);
			new_block = 0; //다시 반복하여 빈 블록을 찾는다.
			mtable.no_block = 0;
		}
	}
	//pos_2 = mtable.FP_loc[(new_block * NOS)];
	fsetpos(Flash_memory, &pos_2); //새로운 블록의 위치로 이동
	for (int i = 0; i < NOS; i++) //새로운 블록에 데이터 이동
	{
		if (temp_B.temp_spare_status[i] == 1) //유효한 페이지를 쓰는 경우
		{
			temp_B_1.temp_spare_status[i] = 1;
			temp_B_1.temp_spare_write_count[i]++; //쓰기 카운트 증가
			mtable.write_count++; //쓰기 카운트 증가
			fprintf(Flash_memory, "%512s\t%d\t%d\t%d\t%d\n", temp_B.temp_blcok[i], temp_B_1.temp_spare_status[i], temp_B.temp_spare_LSN[i], temp_B_1.temp_spare_write_count[i], temp_B_1.temp_spare_erase_count[i]);
		}
		else
		{
			fprintf(Flash_memory, "%512s\t%d\t%d\t%d\t%d\n", temp_B.temp_blcok[i], temp_B.temp_spare_status[i], temp_B.temp_spare_LSN[i], temp_B_1.temp_spare_write_count[i], temp_B_1.temp_spare_erase_count[i]);
		}

	}
	fsetpos(Flash_memory, &pos); //무효화해야할 블록으로 이동
	for (int i = 0; i < NOS; i++)
	{
		if (temp_B.temp_spare_status[i] == 0) //free page일 때
		{
			fprintf(Flash_memory, "%512s\t%d\t%d\t%d\t%d\n", temp_B.temp_blcok[i], temp_B.temp_spare_status[i], temp_B_1.temp_spare_LSN[i], temp_B.temp_spare_write_count[i], temp_B.temp_spare_erase_count[i]);
		}

		else //valid page일 때
		{
			temp_B.temp_spare_status[i] = 2; //무효화
			fprintf(Flash_memory, "%512s\t%d\t%d\t%d\t%d\n", temp_B.temp_blcok[i], temp_B.temp_spare_status[i], temp_B_1.temp_spare_LSN[i], temp_B.temp_spare_write_count[i], temp_B.temp_spare_erase_count[i]);
		}
	}

	for (int i = 0; i < NOS; i++) //파일 포인터 위치 변경
	{
		temp_pos = mtable.FP_loc[(new_block * NOS) + i];
		mtable.FP_loc[(new_block * NOS) + i] = mtable.FP_loc[(LBN * NOS) + i];
		mtable.FP_loc[(LBN * NOS) + i] = temp_pos;
	}
	temp_loc = mtable.table[new_block];
	mtable.table[new_block] = PBN;
	mtable.table[LBN] = temp_loc;
	printf("DONE!!\n");
}