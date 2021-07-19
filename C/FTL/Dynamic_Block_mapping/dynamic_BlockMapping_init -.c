#include "dynamic_blockmapping_head.h"

void init(FILE* Flash_memory, unsigned int value)
{
	Flash_memory = fopen("Block_Mapping_FM.txt", "w+"); //������� ����.
	unsigned int offset = 0;
	unsigned int nob = ((value * 1024 * 1024) / 512) / 32; // ��� ����
	fpos_t pos = 0;
	mtable.nob = nob;
	mtable.nos = nob * 32;
	mtable.table = (unsigned int*)malloc(sizeof(unsigned int) * nob); //������ ������ŭ ���̺� �Ҵ�
	mtable.FP_loc = (unsigned long long*)malloc(sizeof(unsigned long long) * mtable.nos); //���� ������ ��ġ �Ҵ�
	if (spare.LSN != 0)
	{
		spare.LSN = 0;
		spare.status = 0;
	}
	for (int i = 0; i < nob; i++)
	{
		mtable.table[i] = i; //�������̺� ����
	}

	if (Flash_memory == NULL) //������ ������ �ʴ� ���
	{
		printf("������ ������ �ʽ��ϴ�.\n");
	}

	else //������ ���������� ���� ���
	{
		for (int i = 0; i < nob; i++) //����� ������ŭ (�� �ݺ��� �Է¹��� ���� ���� �޶�����.)
		{
			for (int j = 0; j < NOS; j++) //������ ������ŭ (32)
			{
				fgetpos(Flash_memory, &pos);
				mtable.FP_loc[(i * NOS) + j] = pos;
				for (int k = 0; k < SS; k++) //������ ũ�⸸ŭ (512)
				{
					fprintf(Flash_memory, " ");
				}
					fprintf(Flash_memory, "\t%d\t%d\t%d\t%d\n", spare.status, spare.LSN, spare.erase_count, spare.write_count);
				spare.LSN++;
			}
		}
		spare.LSN = 0;
	}
	fclose(Flash_memory);
}