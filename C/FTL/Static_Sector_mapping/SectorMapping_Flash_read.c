#include "SectorMapping.h"

void Flash_read(FILE* Flash_memory, int LSN)
{
	int PSN = FTL_read(LSN);
	int file_end = 0; //파일이 가지는 총 데이터 확인
	int len = 0; //읽어온 배열의 길이
	char read_Sdata[513]; // 512개 인덱스를 전부 읽기 위해서 513크기로 지정한다.

	Flash_memory = fopen("Sector_Mapping_FM.txt", "r"); //파일을 읽기 모드로 연다

	if (Flash_memory == NULL) //파일이 열리지 않았을때
	{
		printf("파일이 열리지 않았습니다.\n");
	}

	else
	{
		fseek(Flash_memory, 0, SEEK_END);
		file_end = ftell(Flash_memory);
		rewind(Flash_memory);
		if (file_end / SS <= LSN) //영역을 초과해서 읽을 경우
		{
			printf("영역을 초과했습니다.\n");
		}
		else
		{
			fseek(Flash_memory, PSN * SS, SEEK_SET); //읽을 섹터 위치
			fgets(read_Sdata, 513, Flash_memory); //데이터를 읽어온다.
			len = strlen(read_Sdata);

			if (len == SS && strspn(read_Sdata, " ") == SS) //문자열 길이가 512 AND 스페이스바 개수가 512개 일때
			{
				printf("PSN : %d\nDATA :EMPTY\n", PSN);
			}
			else
			{
				printf("PSN : %d\nDATA : %s", PSN, read_Sdata);
			}
		}
		fclose(Flash_memory);
	}
}