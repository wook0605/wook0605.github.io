#include "FlashMemory_head.h"

void Flash_erase(FILE* Flash_memory, int erase_block)
{
	int first_block = (((erase_block) * SS) * NOS);
	int file_end = 0;

	Flash_memory = fopen("Flash_Memory.txt", "r+"); // �б�/���� ���� ������ ����.


	if (Flash_memory == NULL) //������ �������ʾ��� ��
	{
		printf("������ ������ �ʾҽ��ϴ�.\n");
	}

	else
	{
		fseek(Flash_memory, 0, SEEK_END); //������ ������ ����.
		file_end = ftell(Flash_memory); //������ ������ �ִ� ������ ���̸� ���.
		rewind(Flash_memory);// ���� �����͸� �ٽ� �Ǿ�����

		if (erase_block == 0) // ù ����� ��
		{
			for (int i = 0; i < NOS; i++) // NOS = 32��, ������ ����. ���� ����
			{
				for (int  j = 0; j < SS; j++) //���� ũ�⸸ŭ
				{
					fprintf(Flash_memory, " ");
				}
			}
		}


		else //ù ����� �ƴ� ��
		{
			if ((file_end / 512) / 32 <= erase_block) //������ ����� ������ ��� ������ ũ�ų� ���� ���
			{
				printf("������ �ʰ��߽��ϴ�.\n");
			}
			else
			{
				fseek(Flash_memory, first_block, SEEK_SET); // �ش� ����� ��ġ�� �����͸� �̵�
				for (int i = 0; i < NOS; i++) //���� ����
				{
					for (int j = 0; j < SS; j++)
					{
						fprintf(Flash_memory, " ");
					}
				}
			}
		}
			
		printf("Erase %dth Block\n", erase_block);
	}
	fclose(Flash_memory);
}