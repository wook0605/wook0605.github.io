#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SS 512 // 섹터의 크기 512
#define NOS 32 //섹터의 갯수 32
#define CL 542// 문자열 길이 (명령어 (30줄) + 섹터크기(512)만큼)


void init(FILE* Flash_memory,int value); // 해당 크기만큼 플래시메모리 할당. (MB단위) 블록은 32개의 섹터로 구성되어있다.

void Flash_read(FILE* Flash_memory, int read_sector); //해당 물리섹터의 데이터를 읽어옴.

void Flash_write(FILE* Flash_memory, int write_place, char* write_data); // 해당 물리섹터에 데이터를 쓴다.

void Flash_erase(FILE* Flash_memory, int erase_block); // 해당 블록의 데이터를 지움.

int ext_num(char* Commend); // 명령어에 포함된 숫자 추출하는 함수