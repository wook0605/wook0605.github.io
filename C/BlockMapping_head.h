#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SS 512 // 섹터의 크기 512
#define NOS 32 //섹터의 갯수 32
#define CL 542// 문자열 길이 (명령어 (30줄) + 섹터크기(512)만큼)

typedef struct mtable
{
	int* table;
	int* erase_count;
	int* write_count;
	int num_blo;
}MTable;

typedef struct temp
{
	char temp_blcok[NOS][SS];

}TEMP;

MTable mtable;
TEMP temp;

void init(FILE* Flash_memory, int value); // 해당 크기만큼 플래시메모리 할당. (MB단위) 블록은 32개의 섹터로 구성되어있다.

void Flash_read(FILE* Flash_memory, int LSN); //해당 물리섹터의 데이터를 읽어옴.

void Flash_write(FILE* Flash_memory, int LSN, char* write_data); // 해당 물리섹터에 데이터를 쓴다.

void Flash_erase(FILE* Flash_memory, int LBN); // 해당 블록의 데이터를 지움.

int FTL_read(int LSN); // 매핑테이블을 이용해 LSN을 PBN으로 변환

void FTL_write(FILE* Flash_memory, int LSN, int PBN, char* write_data, int overwrite_Block, int overwrite_offset); //덮어쓰기가 일어나면 FTL을 적용해서 쓴다.

void quit(FILE* Flash_memory); //프로그램 종료

void print_table(); //매핑테이블 출력

void load_table(FILE* Flash_memory); //매핑테이블 로드

int ext_num(char* Commend); // 명령어에 포함된 숫자 추출하는 함수