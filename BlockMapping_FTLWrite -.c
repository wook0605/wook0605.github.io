#include "BlockMapping_head.h"

void FTL_write(FILE* Flash_memory, int LSN, int PBN, char* write_data, int owb, int owo)
{
	int LBN = LSN / NOS;
	int file_end = 0;
	int write_sum = 0;
	char read_data[SS];

	memset(temp.temp_blcok, NULL, sizeof(temp)); //임시블록 초기화
	memset(read_data, NULL, SS); //읽어온 데이터 저장하는 배열 초기화
	for (int i = 0; i < NOS; i++) //오프셋 증가
	{
		fseek(Flash_memory, ((PBN*NOS)+i)*SS, SEEK_SET); // 해당 블록의 오프셋으로 파일 포인터 옮기기
		if (owb == mtable.table[LBN] && owo == i)
		{
			fgets(read_data, SS, Flash_memory);
			strcpy(temp.temp_blcok[i], write_data); // 덮어쓰기가 일어난 지점의 데이터만 새로 써준다.
		}

		else
		{
			fgets(read_data, SS, Flash_memory); // 해당 블록의 해당 섹터 읽어오기
			strcpy(temp.temp_blcok[i], read_data); // erase는 블록단위로 일어나기 때문에 해당 블록의 유효데이터 전부 복사
		}
	}
	Flash_erase(Flash_memory, LBN); //해당 블록 삭제
	rewind(Flash_memory);
	for (int i = 0; i < NOS; i++) //다시 블록에 적어줌
	{
		fseek(Flash_memory, ((PBN*NOS)+i)*SS, SEEK_SET); //블록의 각 오프셋에 접근
		fputs(temp.temp_blcok[i], Flash_memory);
		if (strlen(temp.temp_blcok[i]) == SS - 1 && strspn(temp.temp_blcok[i], " ") == SS - 1) //빈 공간은 쓰기카운트가 올라가지 않음
		{

		}
		else
		{
			mtable.write_count[(PBN * NOS) + i]++;
			write_sum++;
		}
	}
	printf("쓰기 완료\n");
	printf("write의 횟수 : %d\n", write_sum);
}