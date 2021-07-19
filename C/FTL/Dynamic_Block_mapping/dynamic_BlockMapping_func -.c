#include "dynamic_blockmapping_head.h"

unsigned int ext_num(char* Commend, char* write_data)
{
	int len = 0; //문자열 길이
	int pv = 0; // 자리값을 맞추기 위한 변수
	char buf[10]; //정수를 받을 배열 10자리 정수까지 받을 수 있다. (int형으로 뱉기 때문)
	int storage = 0; //변환한 값
	int data = 0;
	unsigned int digit = 0; //숫자 자릿수만을 위한 변수
	unsigned int stop = digit + 1;

	len = strlen(Commend);

	for (digit = 0; digit < len; digit++)
	{
		if (Commend[digit] > 47 && Commend[digit] < 58) //ASCII상에서 숫자 발견
		{
			buf[pv] = Commend[digit]; //발견한 숫자를 자릿수에 맞게 배열에 입력
			pv++; //자릿수 증가
		}
		else
		{
			if (digit >5)
			{
				write_data[data] = Commend[digit];
				data++;
			}
		}
	}
	storage = atoi(buf); // 버퍼 요소를 정수로 변환
	return storage;
}

void print_table() //테이블 출력
{
	for (int i = 0; i < mtable.nob; i++)
	{
		printf("LBN : %d\t PBN : %d\n", i,mtable.table[i]);
	}
}


void load_table(FILE* Flash_memory) //매핑테이블 읽어오기
{
	Flash_memory = fopen("Block_Mapping_FM.txt", "r");
	unsigned int count = 0;
	fpos_t pos = 0;
	if (Flash_memory == NULL)
	{
		printf("파일을 열 수 없습니다.\n");
	}

	else //파일이 열렸을 때
	{
		while (!feof(Flash_memory))
		{
			++mtable.nos;
			fgets(temp_B.temp_, sizeof(temp_B.temp_), Flash_memory); //한줄씩 읽기
		}
		rewind(Flash_memory);
		mtable.nob = mtable.nos / NOS;
		mtable.FP_loc = (unsigned long long*) malloc(sizeof(unsigned long long) * (mtable.nos)); //섹터별 파일 포인터 위치 저장하기 위함.
		mtable.table = (int*)malloc(sizeof(int) * mtable.nob); //블록개수만큼 할당
		for (int i = 0; i < mtable.nos; i++) //플래시 메모리 전체 스캔
		{
			fgetpos(Flash_memory, &pos);
			mtable.FP_loc[i] = pos;
			fgets(temp_B.temp_, SS, Flash_memory); //데이터 영역 읽기
			fscanf(Flash_memory, "\t%d\t%d\t%d\t%d", &spare.status, &spare.LSN, &spare.write_count, &spare.erase_count); //스페어 영역 읽기
			fgetc(Flash_memory);//파일 포인터 위치 한칸 밀기
			count = spare.LSN / NOS;
			mtable.table[i / NOS] = count;
		}
		fclose(Flash_memory);
	}
}