#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define _CRT_SECURE_NO_WARNINGS
#define SS 512 // 섹터의 크기 512
#define NOS 32 //섹터의 갯수 32
#define CL 542// 문자열 길이 (명령어 (30줄) + 섹터크기(512)만큼)

typedef struct mtable
{
	unsigned int* table;
	unsigned long long* FP_loc;
	unsigned int nob;
	unsigned int nos;
	unsigned int write_count;
	unsigned int erase_count;
	unsigned int no_block;
}MTable;

typedef struct temp
{
	unsigned char temp_[528];
	unsigned char temp_blcok[NOS][513];
	unsigned char offset;
	unsigned char temp_spare_status[NOS];
	unsigned int  temp_spare_LSN[NOS];
	unsigned int temp_spare_write_count[NOS];
	unsigned int temp_spare_erase_count[NOS];
}TEMP;

typedef struct temp_1
{
	unsigned char temp_[528];
	unsigned char temp_blcok[NOS][513];
	unsigned char offset;
	unsigned char temp_spare_status[NOS];
	unsigned int  temp_spare_LSN[NOS];
	unsigned int temp_spare_write_count[NOS];
	unsigned int temp_spare_erase_count[NOS];
}TEMP_1;

typedef struct spare
{
	unsigned char status;  //free(0), valid(1), invalid(2)
	unsigned int LSN; //4byte
	unsigned int erase_count; //삭제 카운트
	unsigned int write_count; //쓰기 카운트
}Spare_area;

MTable mtable;
TEMP temp_B;
TEMP_1 temp_B_1;
Spare_area spare;

void init(FILE* Flash_memory, unsigned int  value); // 해당 크기만큼 플래시메모리 할당. (MB단위) 블록은 32개의 섹터로 구성되어있다.

void Flash_read(FILE* Flash_memory, unsigned int  LSN); //해당 물리섹터의 데이터를 읽어옴.

void Flash_write(FILE* Flash_memory, unsigned int  LSN, char* write_data); // 해당 물리섹터에 데이터를 쓴다.

void Flash_erase(FILE* Flash_memory); // 해당 블록의 데이터를 지움.

int FTL_read(unsigned int  LSN); // 매핑테이블을 이용해 LSN을 PBN으로 변환

void FTL_write(FILE* Flash_memory, unsigned int  LSN, unsigned int PBN, char* write_data, unsigned int  overwrite_offset, unsigned int nob, fpos_t pos); //덮어쓰기가 일어나면 FTL을 적용해서 쓴다.

void print_table(); //매핑테이블 출력

void load_table(FILE* Flash_memory); //매핑테이블 로드

unsigned int ext_num(char* Commend, char* write_data); // 명령어에 포함된 숫자 추출하는 함수