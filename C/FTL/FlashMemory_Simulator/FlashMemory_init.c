#include "FlashMemory_head.h"

void init(FILE* Flash_memory, int value)
{
	Flash_memory = fopen("Flash_Memory.txt","w"); //������� ����.

	int nob = ((value * 1024 * 1024) / 512) / 32; // ��� ����

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
				for (int k = 0; k < SS; k++) //������ ũ�⸸ŭ (512)
				{
					fprintf(Flash_memory, " ");
				}
			}
		}
	}

	fclose(Flash_memory);
}