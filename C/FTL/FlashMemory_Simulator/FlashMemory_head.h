#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SS 512 // ������ ũ�� 512
#define NOS 32 //������ ���� 32
#define CL 542// ���ڿ� ���� (��ɾ� (30��) + ����ũ��(512)��ŭ)


void init(FILE* Flash_memory,int value); // �ش� ũ�⸸ŭ �÷��ø޸� �Ҵ�. (MB����) ����� 32���� ���ͷ� �����Ǿ��ִ�.

void Flash_read(FILE* Flash_memory, int read_sector); //�ش� ���������� �����͸� �о��.

void Flash_write(FILE* Flash_memory, int write_place, char* write_data); // �ش� �������Ϳ� �����͸� ����.

void Flash_erase(FILE* Flash_memory, int erase_block); // �ش� ����� �����͸� ����.

int ext_num(char* Commend); // ��ɾ ���Ե� ���� �����ϴ� �Լ�