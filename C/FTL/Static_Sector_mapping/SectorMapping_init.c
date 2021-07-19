#include "SectorMapping.h"

void init(FILE* Flash_memory, int value)
{
	Flash_memory = fopen("Sector_Mapping_FM.txt", "w"); //������� ����.

	int nob = ((value * 1024 * 1024) / 512) / 32; // ���� ����
	int nos = ((value * 1024 * 1024) / 512); //���� ����

	mtable.num_sec = nos;

	mtable.table = (int*)malloc(sizeof(int) * nos); //������ ������ŭ ���̺� �Ҵ�
	mtable.erase_count = (int*)malloc(sizeof(int) * nos); //�� ���̺����� ����ī��Ʈ �������� �Ҵ�
	mtable.write_count = (int*)malloc(sizeof(int) * nos); //�� ���̺����� ����ī��Ʈ �������� �Ҵ�

	memset(mtable.erase_count, 0, _msize(mtable.erase_count));
	memset(mtable.write_count, 0, _msize(mtable.write_count));

	for (int i = 0; i < nos; i++)
	{
		mtable.table[i] = i; //�������̺� ����
	}

	if (Flash_memory == NULL) //������ ������ �ʴ� ���
	{
		printf("������ ������ �ʽ��ϴ�.\n");
	}

	else //������ ���������� ���� ���
	{
		for (int i = 0; i < nob; i++) //������ ������ŭ (�� �ݺ��� �Է¹��� ���� ���� �޶�����.)
		{
			for (int j = 0; j < NOS; j++) //������ ������ŭ (32)
			{
				for (int k = 0; k < SS; k++) //������ ũ�⸸ŭ (512)
				{
					fprintf(Flash_memory, " ");
				}
			}
		}
	}
	fclose(Flash_memory);
}