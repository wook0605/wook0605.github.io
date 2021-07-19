#include "SectorMapping.h"

void Flash_erase(FILE* Flash_memory, int LBN)
{
	int LSN = LBN * NOS;
	int file_end = 0;
	char read_data[SS]; // ���� ������ ������ �迭
	int erase_sum = 0;
	memset(read_data, NULL, SS);

	Flash_memory = fopen("Sector_Mapping_FM.txt", "r+"); // �б�/���� ���� ������ ����.


	if (Flash_memory == NULL) //������ �������ʾ��� ��
	{
		printf("������ ������ �ʾҽ��ϴ�.\n");
	}

	else
	{
		fseek(Flash_memory, 0, SEEK_END); //������ ������ ����.
		file_end = ftell(Flash_memory); //������ ������ �ִ� ������ ���̸� ���.
		rewind(Flash_memory);// ���� �����͸� �ٽ� �Ǿ�����

		if ((file_end / SS) / NOS <= LBN) //������ ����� ������ ��� ������ ũ�ų� ���� ���
		{
			printf("������ �ʰ��߽��ϴ�.\n");
		}
		else
		{
			for (int i = LSN; i < LSN+NOS; i++) //���� ����
			{
				fseek(Flash_memory, mtable.table[i] * SS, SEEK_SET);
				for (int j = 0; j < SS; j++)//����� ù ���ͺ��� ������ ���ͱ���
				{
					fprintf(Flash_memory, " ");
				}
				mtable.erase_count[i]++; //�� ���� ����ī��Ʈ ����
				erase_sum++; //�� ����ī��Ʈ ����
			}
		}
		printf("Erase %dth Block\n", LBN);
		printf("erase�� Ƚ�� : %d\n", erase_sum);
	}
	fclose(Flash_memory);
}