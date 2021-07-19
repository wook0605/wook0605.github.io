#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SS 512 // ������ ũ�� 512
#define NOS 32 //������ ���� 32
#define CL 542// ���ڿ� ���� (��ɾ� (30��) + ����ũ��(512)��ŭ)

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

void init(FILE* Flash_memory, int value); // �ش� ũ�⸸ŭ �÷��ø޸� �Ҵ�. (MB����) ����� 32���� ���ͷ� �����Ǿ��ִ�.

void Flash_read(FILE* Flash_memory, int LSN); //�ش� ���������� �����͸� �о��.

void Flash_write(FILE* Flash_memory, int LSN, char* write_data); // �ش� �������Ϳ� �����͸� ����.

void Flash_erase(FILE* Flash_memory, int LBN); // �ش� ����� �����͸� ����.

int FTL_read(int LSN); // �������̺��� �̿��� LSN�� PBN���� ��ȯ

void FTL_write(FILE* Flash_memory, int LSN, int PBN, char* write_data, int overwrite_Block, int overwrite_offset); //����Ⱑ �Ͼ�� FTL�� �����ؼ� ����.

void quit(FILE* Flash_memory); //���α׷� ����

void print_table(); //�������̺� ���

void load_table(FILE* Flash_memory); //�������̺� �ε�

int ext_num(char* Commend); // ��ɾ ���Ե� ���� �����ϴ� �Լ�