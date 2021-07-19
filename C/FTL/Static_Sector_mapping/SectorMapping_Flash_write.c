#include "SectorMapping.h"

void Flash_write(FILE* Flash_memory, int LSN, char* write_data)
{
	int PSN = mtable.table[LSN];  // 지정한 섹터를 가르키기 위한 값
	int file_end = 0;
	int owp = 0;
	int write_sum = 0;
	char read_data[SS];
	bool OverWrite = false;

	Flash_memory = fopen("Sector_Mapping_FM.txt", "r+"); //파일을 읽기/쓰기 모드로 연다.

	if (Flash_memory == NULL)
	{
		printf("파일이 열리지 않았습니다.\n");
	}

	else
	{
		fseek(Flash_memory, 0, SEEK_END); //파일의 끝으로 간다.
		file_end = ftell(Flash_memory); //파일이 가지고 있는 문자의 길이를 잰다.
		rewind(Flash_memory);// 파일 포인터를 다시 맨앞으로

		if (file_end / SS <= LSN) //영역을 초과해서 읽는 경우
		{
			printf("영역을 초과했습니다.\n");
		}

		else
		{
			fseek(Flash_memory, PSN * SS, SEEK_SET); // 섹터 찾기
			fgets(read_data, SS, Flash_memory);// 데이터가 있는지 없는지 검사하기 위해 읽기

			for (int i = 0; i < SS; i++)
			{
				if (read_data[i] != 32 && read_data[i] != 0) // 스페이스바와 NULL문자 외에 데이터 존재시 오버라이트.
				{
					OverWrite = true;
					if (OverWrite)
					{
						owp = PSN;
						break;
					}
				}
			}

			if (OverWrite) //오버라이트 에러일때
			{
				FTL_write(Flash_memory, LSN, write_data, owp);
			}

			else // 데이터를 쓸 수 있을때
			{
				rewind(Flash_memory);
				fseek(Flash_memory, PSN*SS, SEEK_SET); //데이터를 쓸 섹터 위치
				fputs(write_data, Flash_memory); //데이터 쓰기
				mtable.write_count[LSN]++; //쓰기카운터 증가
				printf("Done!\n");
			}
		}
		fclose(Flash_memory); //파일을 닫는다.
	}
}