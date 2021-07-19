#include "BlockMapping_head.h"

void Flash_erase(FILE* Flash_memory, int LBN)
{
	int PBN = mtable.table[LBN];
	int offset = (LBN * NOS) % NOS;
	int file_end = 0;

	Flash_memory = fopen("Block_Mapping_FM.txt", "r+"); // 읽기/쓰기 모드로 파일을 연다.

	if (Flash_memory == NULL) //파일이 열리지않았을 때
	{
		printf("파일이 열리지 않았습니다.\n");
	}

	else
	{
		fseek(Flash_memory, 0, SEEK_END); //파일의 끝으로 간다.
		file_end = ftell(Flash_memory); //파일이 가지고 있는 문자의 길이를 잰다.
		rewind(Flash_memory);// 파일 포인터를 다시 맨앞으로

		if ((file_end / 512) / 32 <= LBN) //삭제할 블록이 파일의 블록 수보다 크거나 같은 경우
		{
			printf("영역을 초과했습니다.\n");
		}
		else
		{
			for (int i = 0; i < NOS; i++) //오프셋 증가시켜서 삭제 시작(블록에 빈섹터가 있어도, 삭제단위는 블록이기때문에 삭제한다.)
			{
				fseek(Flash_memory, ((mtable.table[LBN]*NOS)+i)*SS, SEEK_SET); // 파일의 해당 블록의 오프셋 위치로 이동
				for (int j = 0; j < SS; j++)//블록의 첫 섹터부터 마지막 섹터까지
				{
					fprintf(Flash_memory, " ");
				}
			}
		}
		mtable.erase_count[LBN]++; //블록의 삭제카운트 증가
		printf("Erase %dth Block\n", LBN);
		printf("erase의 횟수 : %d\n", mtable.erase_count[LBN]); //해당 블록의 삭제 카운트 출력
		printf("PBN : %d\n", PBN);
	}
	fclose(Flash_memory);
}