#include "BlockMapping_head.h"

void Flash_read(FILE* Flash_memory, int LSN)
{
	int PBN = FTL_read(LSN);
	int offset = LSN % NOS;
	int file_end = 0; //파일이 가지는 총 데이터 확인
	int len = 0; //읽어온 배열의 길이
	char read_Sdata[513]; // 512개 인덱스를 전부 읽기 위해서 513크기로 지정한다.

	Flash_memory = fopen("Block_Mapping_FM.txt", "r"); //파일을 읽기 모드로 연다

	if (Flash_memory == NULL) //파일이 열리지 않았을때
	{
		printf("파일이 열리지 않았습니다.\n");
	}

	else
	{
			fseek(Flash_memory, ((PBN * NOS)+offset)*SS, SEEK_SET); //파일의 해당 블록의 오프셋 위치로 파일 포인터 이동
			fgets(read_Sdata, 513, Flash_memory);
			len = strlen(read_Sdata);

			if (len == SS && strspn(read_Sdata, " ") == SS) //문자열 길이가 512 AND 스페이스바 개수가 512개 일때
			{
				printf("PBN %d의 offset : %d\nDATA :EMPTY\n",PBN, offset);
			}
			else
			{
				printf("PBN %d의 offset : %d\nDATA : %s", PBN, offset, read_Sdata);
			}
		}
			
		fclose(Flash_memory);
	}