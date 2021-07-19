#include "dynamic_blockmapping_head.h"

void Flash_erase(FILE* Flash_memory)
{
	unsigned int LBN = 0;
	unsigned int offset = 0;
	float iv_count = 0; //무효섹터 개수
	unsigned char read_data[513] = { NULL, };
	float* iv_ratio = 0;
	float threshold = 20.0;
	unsigned int victim = 0;
	unsigned int free_b = 0;
	fpos_t free_b_pos = 0;
	fpos_t pos_2 = 0;
	iv_ratio = (float*)malloc(sizeof(float) * mtable.nob); //블록 무효화비율 저장
	memset(read_data, 32, sizeof(read_data));
	printf("삭제 시작");
	for (LBN = 0; LBN < mtable.nob; LBN++) //플래시 메모리 순회
	{
		pos_2 = mtable.FP_loc[LBN * NOS];
		fsetpos(Flash_memory, &pos_2);
		for (offset = 0; offset < NOS; offset++) // 각 블록의 무효도 조사
		{
			fgets(temp_B_1.temp_blcok[offset], SS, Flash_memory); //데이터 영역 읽기
			fscanf(Flash_memory, "%d\t%d\t%d\t%d",&temp_B_1.temp_spare_status[offset], &temp_B_1.temp_spare_LSN[offset], &temp_B_1.temp_spare_write_count[offset], &temp_B_1.temp_spare_erase_count[offset]); // 스페어 영역 읽기
			fgetc(Flash_memory); //파일 포인터 위치 바꾸기
			if (temp_B_1.temp_spare_status[offset] == 2) //무효 섹터일 때
			{
				iv_count++; //무효도 증가
			}
		}
		iv_ratio[LBN] = ((iv_count / NOS) * 100);
		iv_count = 0;
		if (iv_ratio[LBN] > iv_ratio[victim]) //victim 선정 (무효도 최대값 : 100)
		{
			victim = LBN; //삭제할 블록 위치
			printf("삭제할 블록의 위치 : %d\t 무효도 : %f", victim, iv_ratio[victim]);
		}
		if (iv_ratio[LBN] < iv_ratio[free_b]) //(무효도 최소값 (0))
		{
			free_b = LBN; //free_b 블록 위치
			printf("프리블록의 위치 : %d\t 무효도 : %f", free_b, iv_ratio[free_b]);
		}
	}

	if (iv_ratio[victim] == 100) //완전 무효화 블록일 때
	{
		pos_2 = mtable.FP_loc[(victim * NOS)]; //무효블록의 첫번째 오프셋 위치 가져오기
		fsetpos(Flash_memory, &pos_2); //무효 블록의 첫번째 오프셋 위치로 이동
		for (offset = 0; offset < NOS; offset++) //블록의 각 오프셋을 확인
		{
			fgets(temp_B_1.temp_blcok[offset], SS, Flash_memory);//데이터 읽기
			fscanf(Flash_memory, "%d\t%d\t%d\t%d", &temp_B_1.temp_spare_status[offset], &temp_B_1.temp_spare_LSN[offset], &temp_B_1.temp_spare_write_count[offset], &temp_B_1.temp_spare_erase_count[offset]); //해당 오프셋 스페어 읽기
			fgetc(Flash_memory);//파일 포인터 이동
		}
		fsetpos(Flash_memory, &pos_2); //삭제할 블록으로 이동
		for (offset = 0; offset < NOS; offset++) //삭제
		{	
			temp_B_1.temp_spare_erase_count[offset]++;//삭제 카운트 증가
			temp_B_1.temp_spare_status[offset] = 0;
			fprintf(Flash_memory, "%512s\t%d\t%d\t%d\t%d\n", read_data, temp_B_1.temp_spare_status[offset], temp_B_1.temp_spare_LSN[offset], temp_B_1.temp_spare_write_count[offset], temp_B_1.temp_spare_erase_count[offset]); //해당 오프셋 삭제
		}
		fsetpos(Flash_memory, &pos_2);
		for (offset = 0; offset < NOS; offset++)
		{
			fgets(temp_B_1.temp_blcok[offset], SS, Flash_memory);
			fscanf(Flash_memory, "%d\t%d\t%d\t%d", &temp_B_1.temp_spare_status[offset], &temp_B_1.temp_spare_LSN[offset], &temp_B_1.temp_spare_write_count[offset], &temp_B_1.temp_spare_erase_count[offset]);
			fgetc(Flash_memory);
			printf("offset : %d\tspare area : %d\t%d\t%d\t%d\n", offset, temp_B_1.temp_spare_status[offset], temp_B_1.temp_spare_LSN[offset], temp_B_1.temp_spare_write_count[offset], temp_B_1.temp_spare_erase_count[offset]);
		}
		mtable.erase_count++;
	}

	else if (iv_ratio[victim] > threshold) // victim 선정된 블록의 iv_ratio가 20.0 보다 클 떄
	{
		pos_2 = mtable.FP_loc[(victim * NOS)];
		fsetpos(Flash_memory, &pos_2);
		for (offset = 0; offset < NOS; offset++) //블록의 각 오프셋을 확인
		{
			fgets(temp_B_1.temp_blcok[offset], SS, Flash_memory);//데이터 읽기
			fscanf(Flash_memory, "%d\t%d\t%d\t%d", &temp_B_1.temp_spare_status[offset], &temp_B_1.temp_spare_LSN[offset], &temp_B_1.temp_spare_write_count[offset], &temp_B_1.temp_spare_erase_count[offset]); //해당 오프셋 스페어 읽어오기.
			fgetc(Flash_memory);//파일 포인터 이동
		}
		fsetpos(Flash_memory, &pos_2); //삭제할 블록으로 이동
		for (offset = 0; offset < NOS; offset++)
		{
			if (temp_B_1.temp_spare_status[offset] == 1) //읽은 오프셋이 유효한 데이터를 포함하는 경우 유효 데이터는 RAM에 잠시 올려두고, 전부 삭제 한 다음 유효 데이터만 다시 써준다.
			{
				temp_B_1.temp_spare_erase_count[offset]++;//삭제 카운트 증가
				temp_B_1.temp_spare_write_count[offset]++;//쓰기 카운트 증가
				temp_B_1.temp_spare_status[offset] = 1;
				for (int i = 0; i < SS; i++)
				{
					fprintf(Flash_memory, " ");
				}
				fprintf(Flash_memory, "\t%d\t%d\t%d\t%d\n", temp_B_1.temp_spare_status[offset], temp_B_1.temp_spare_LSN[offset], temp_B_1.temp_spare_write_count[offset], temp_B_1.temp_spare_erase_count[offset]);
			}

			else //읽은 오프셋이 무효하거나 비어있는 경우
			{
				temp_B_1.temp_spare_erase_count[offset]++; //삭제 카운트 증가
				temp_B_1.temp_spare_status[offset] = 0;
				fprintf(Flash_memory, "%512s\t%d\t%d\t%d\t%d\n", read_data, temp_B_1.temp_spare_status[offset], temp_B_1.temp_spare_LSN[offset], temp_B_1.temp_spare_write_count[offset], temp_B_1.temp_spare_erase_count[offset]); //해당 오프셋 삭제
			}
		}
		fsetpos(Flash_memory, &pos_2);
		for (offset = 0; offset < NOS; offset++)
		{
			fgets(temp_B_1.temp_blcok[offset], SS, Flash_memory);
			fscanf(Flash_memory, "%d\t%d\t%d\t%d", &temp_B_1.temp_spare_status[offset], &temp_B_1.temp_spare_LSN[offset], &temp_B_1.temp_spare_write_count[offset], &temp_B_1.temp_spare_erase_count[offset]);
			fgetc(Flash_memory);
			printf("offset : %d\tspare area : %d\t%d\t%d\t%d\n", offset, temp_B_1.temp_spare_status[offset], temp_B_1.temp_spare_LSN[offset], temp_B_1.temp_spare_write_count[offset], temp_B_1.temp_spare_erase_count[offset]);
		}
		mtable.erase_count++;
	}
	else
	{
		printf("victim선정 무효 블록의 무효도가 임계값 아래입니다.\n");
	}
	printf("삭제 종료");
	free(iv_ratio);
}