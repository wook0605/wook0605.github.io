#include "SectorMapping.h"

int ext_num(char* Commend)
{
	int len; //문자열 길이
	int pv = 0; // 자리값을 맞추기 위한 변수
	char buf[10]; //정수를 받을 배열 10자리 정수까지 받을 수 있다.
	int storage = 0; //변환한 값

	len = strlen(Commend);

	for (int i = 0; i < len; i++)
	{
		if (Commend[i] > 47 && Commend[i] < 58) //ASCII상에서 숫자 발견
		{
			buf[pv] = Commend[i]; //발견한 숫자를 자릿수에 맞게 배열에 입력
			pv++; //자릿수 증가
		}
	}
	storage = atoi(buf); // 버퍼 요소를 정수로 변환

	return storage;
}

void print_table()
{
	for (int i = 0; i < mtable.num_sec; i++)
	{
		printf("LSN : %d\t PSN : %d\n", i,mtable.table[i]);
		printf("PSN %d 의 Erase_Count : %d\n", mtable.table[i], mtable.erase_count[i]);
		printf("PSN %d 의 Write_Count : %d\n", mtable.table[i], mtable.write_count[i]);
	}
}

void quit(FILE* Flash_memory)
{
	Flash_memory = fopen("SectorMapping_table.txt", "w");

	if (Flash_memory == NULL)
	{
		printf("파일을 열 수 없습니다.\n");
	}

	else //파일을 열었을 때
	{
		fprintf(Flash_memory, "%d\n", mtable.num_sec);//첫줄에 섹터개수 저장
		for(int i = 0; i<mtable.num_sec; i++) //파일에 매핑테이블과 삭제,쓰기 카운트 저장
		{
			fprintf(Flash_memory, "%d\t", mtable.table[i]);
			fprintf(Flash_memory, "%d\t", mtable.erase_count[i]);
			fprintf(Flash_memory, "%d\t", mtable.write_count[i]);
		}
		free(mtable.table); //할당 해제
		free(mtable.erase_count); //할당 해제
		free(mtable.write_count); //할당 해제
	}
	fclose(Flash_memory);//파일 닫기
}

void load_table(FILE* Flash_memory)
{
	Flash_memory = fopen("SectorMapping_table.txt", "r");
	int place = 0;
	int len = 0;

	if (Flash_memory == NULL)
	{
		printf("파일을 열 수 없습니다.\n");
	}

	else //파일이 열렸을 때
	{
		fscanf(Flash_memory, "%d", &len); //파일 첫줄 읽어서 섹터개수 알아내기
		mtable.num_sec = len; //섹터개수 저장
		mtable.table = (int*)malloc(sizeof(int) * len); //섹터 개수만큼 할당
		mtable.erase_count = (int*)malloc(sizeof(int) * len); //섹터 개수만큼 할당
		mtable.write_count = (int*)malloc(sizeof(int) * len); //섹터 개수만큼 할당
		for (place = 0; place < len; place++) //데이터 읽어와서 할당한 변수에 입력
		{
			fscanf(Flash_memory, "%d", &mtable.table[place]);
			fscanf(Flash_memory, "%d", &mtable.erase_count[place]);
			fscanf(Flash_memory, "%d", &mtable.write_count[place]);
		}
		fclose(Flash_memory);
	}

}