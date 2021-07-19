#include "SectorMapping.h"

void FTL_write(FILE* Flash_memory, int LSN, char* write_data, int owp)
{
	int LBN = LSN / NOS;
	int PBN = LBN * NOS; // 매핑테이블을 블록단위로 접근하기 위한 값
	int file_end = 0;
	int write_sum = 0;
	char read_data[SS];

	memset(temp.temp_blcok, NULL, sizeof(temp)); //임시블록 초기화
	memset(read_data, NULL, SS); //읽어온 데이터 저장하는 배열 초기화
	for (int i = PBN; i < PBN+NOS; i++)
	{
		fseek(Flash_memory, mtable.table[i]*SS, SEEK_SET); // 섹터로 파일 포인터 옮기기
		if (owp == mtable.table[i])
		{
			fgets(read_data, SS, Flash_memory);
			strcpy(temp.temp_blcok[i-PBN], write_data); // 덮어쓰기가 일어난 지점의 데이터만 새로 써준다.(i-PBN은 i를 0부터 31까지 쓰기위함)
		}

		else
		{
			fgets(read_data, SS, Flash_memory); // 해당 블록의 섹터 읽어오기
			strcpy(temp.temp_blcok[i-PBN], read_data); // erase는 블록단위로 일어나기 때문에 해당 블록의 유효데이터 전부 복사
		}
	}
	Flash_erase(Flash_memory, LBN); //해당 블록 삭제
	rewind(Flash_memory);
	for (int i = PBN; i < PBN + NOS; i++) //블록 다시 쓰기
	{
		fseek(Flash_memory, mtable.table[i]*SS, SEEK_SET); //해당 섹터의 위치
		fputs(temp.temp_blcok[i - PBN], Flash_memory);
		if (strlen(temp.temp_blcok[i - PBN]) == SS - 1 && strspn(temp.temp_blcok[i - PBN], " ") == SS - 1) //빈 공간은 쓰기카운트가 올라가지 않음
		{

		}
		else
		{
			mtable.write_count[i]++;
			write_sum++;
		}
	}
	printf("쓰기 완료\n");
	printf("write의 횟수 : %d\n", write_sum);
}