#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define _CRT_SECURE_NO_WARNINGS
#define SS 512 // ������ ũ�� 512
#define NOS 32 //������ ���� 32
#define CL 542// ���ڿ� ���� (��ɾ� (30��) + ����ũ��(512)��ŭ)

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
	unsigned int erase_count; //���� ī��Ʈ
	unsigned int write_count; //���� ī��Ʈ
}Spare_area;

MTable mtable;
TEMP temp_B;
TEMP_1 temp_B_1;
Spare_area spare;

void init(FILE* Flash_memory, unsigned int  value); // �ش� ũ�⸸ŭ �÷��ø޸� �Ҵ�. (MB����) ����� 32���� ���ͷ� �����Ǿ��ִ�.

void Flash_read(FILE* Flash_memory, unsigned int  LSN); //�ش� ���������� �����͸� �о��.

void Flash_write(FILE* Flash_memory, unsigned int  LSN, char* write_data); // �ش� �������Ϳ� �����͸� ����.

void Flash_erase(FILE* Flash_memory); // �ش� ����� �����͸� ����.

int FTL_read(unsigned int  LSN); // �������̺��� �̿��� LSN�� PBN���� ��ȯ

void FTL_write(FILE* Flash_memory, unsigned int  LSN, unsigned int PBN, char* write_data, unsigned int  overwrite_offset, unsigned int nob, fpos_t pos); //����Ⱑ �Ͼ�� FTL�� �����ؼ� ����.

void print_table(); //�������̺� ���

void load_table(FILE* Flash_memory); //�������̺� �ε�

unsigned int ext_num(char* Commend, char* write_data); // ��ɾ ���Ե� ���� �����ϴ� �Լ�