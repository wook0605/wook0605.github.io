#include "BlockMapping_head.h"

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

void print_table() //테이블 출력
{
	for (int i = 0; i < mtable.num_blo; i++)
	{
		printf("LBN : %d\t PBN : %d\n", i,mtable.table[i]);
		printf("PBN %d 의 Erase_Count : %d\n", mtable.table[i], mtable.erase_count[i]);
		for (int offset = 0; offset < NOS; offset++) //각 블록의 오프셋의 쓰기카운트
		{
			printf("PBN %d offset %d의 Write_Count : %d\n", mtable.table[i],offset, mtable.write_count[(mtable.table[i]* NOS) + offset]);
		}
	}
}

void quit(FILE* Flash_memory) //종료
{
	Flash_memory = fopen("BLock_Mapping_table.txt", "w");

	if (Flash_memory == NULL)
	{
		printf("파일을 열 수 없습니다.\n");
	}

	else //파일을 열었을 때
	{
		fprintf(Flash_memory, "%d\n", mtable.num_blo); //블록의 개수 첫줄에 저장
		for(int i = 0; i<mtable.num_blo; i++) //파일에 매핑테이블과 삭제,쓰기 카운트 저장
		{
			fprintf(Flash_memory, "%d\t", mtable.table[i]);
			fprintf(Flash_memory, "%d\t", mtable.erase_count[i]);
			for (int offset = 0; offset < NOS; offset++)
			{
				fprintf(Flash_memory, "%d\t", mtable.write_count[(mtable.table[i] * NOS) + offset]); //쓰기카운트는 섹터별로 가지기 때문에, 해당 계산식으로 접근해줌.
			}
		}
		free(mtable.table); //할당 해제
		free(mtable.erase_count); //할당 해제
		free(mtable.write_count); //할당 해제
	}
	fclose(Flash_memory);//파일 닫기
}

void load_table(FILE* Flash_memory) //매핑테이블 읽어오기
{
	Flash_memory = fopen("Block_Mapping_table.txt", "r");
	int place = 0;
	int len = 0;

	if (Flash_memory == NULL)
	{
		printf("파일을 열 수 없습니다.\n");
	}

	else //파일이 열렸을 때
	{
		fscanf(Flash_memory, "%d", &len); //매핑테이블을 읽어오기 위해 저장해둔 블록의 개수를 읽어옴
		mtable.num_blo = len;
		mtable.table = (int*)malloc(sizeof(int) * len); //블록개수만큼 할당
		mtable.erase_count = (int*)malloc(sizeof(int) * len); //블록 개수만큼 할당
		mtable.write_count = (int*)malloc(sizeof(int) * len * NOS); //섹터 개수만큼 할당
		for (place = 0; place < len; place++)
		{
			fscanf(Flash_memory, "%d", &mtable.table[place]);
			fscanf(Flash_memory, "%d", &mtable.erase_count[place]);
			for (int  i = 0; i < NOS; i++)
			{
				fscanf(Flash_memory, "%d", &mtable.write_count[(mtable.table[place]*NOS)+i]); //쓰기카운트는 섹터별로 가지기 때문에, 해당 계산식으로 접근해줌.
			}
		}
		fclose(Flash_memory);
	}

}