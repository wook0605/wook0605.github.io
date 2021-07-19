#include "SectorMapping.h"

void Flash_write(FILE* Flash_memory, int LSN, char* write_data)
{
	int PSN = mtable.table[LSN];  // ������ ���͸� ����Ű�� ���� ��
	int file_end = 0;
	int owp = 0;
	int write_sum = 0;
	char read_data[SS];
	bool OverWrite = false;

	Flash_memory = fopen("Sector_Mapping_FM.txt", "r+"); //������ �б�/���� ���� ����.

	if (Flash_memory == NULL)
	{
		printf("������ ������ �ʾҽ��ϴ�.\n");
	}

	else
	{
		fseek(Flash_memory, 0, SEEK_END); //������ ������ ����.
		file_end = ftell(Flash_memory); //������ ������ �ִ� ������ ���̸� ���.
		rewind(Flash_memory);// ���� �����͸� �ٽ� �Ǿ�����

		if (file_end / SS <= LSN) //������ �ʰ��ؼ� �д� ���
		{
			printf("������ �ʰ��߽��ϴ�.\n");
		}

		else
		{
			fseek(Flash_memory, PSN * SS, SEEK_SET); // ���� ã��
			fgets(read_data, SS, Flash_memory);// �����Ͱ� �ִ��� ������ �˻��ϱ� ���� �б�

			for (int i = 0; i < SS; i++)
			{
				if (read_data[i] != 32 && read_data[i] != 0) // �����̽��ٿ� NULL���� �ܿ� ������ ����� ��������Ʈ.
				{
					OverWrite = true;
					if (OverWrite)
					{
						owp = PSN;
						break;
					}
				}
			}

			if (OverWrite) //��������Ʈ �����϶�
			{
				FTL_write(Flash_memory, LSN, write_data, owp);
			}

			else // �����͸� �� �� ������
			{
				rewind(Flash_memory);
				fseek(Flash_memory, PSN*SS, SEEK_SET); //�����͸� �� ���� ��ġ
				fputs(write_data, Flash_memory); //������ ����
				mtable.write_count[LSN]++; //����ī���� ����
				printf("Done!\n");
			}
		}
		fclose(Flash_memory); //������ �ݴ´�.
	}
}