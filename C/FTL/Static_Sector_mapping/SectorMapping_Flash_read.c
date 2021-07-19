#include "SectorMapping.h"

void Flash_read(FILE* Flash_memory, int LSN)
{
	int PSN = FTL_read(LSN);
	int file_end = 0; //������ ������ �� ������ Ȯ��
	int len = 0; //�о�� �迭�� ����
	char read_Sdata[513]; // 512�� �ε����� ���� �б� ���ؼ� 513ũ��� �����Ѵ�.

	Flash_memory = fopen("Sector_Mapping_FM.txt", "r"); //������ �б� ���� ����

	if (Flash_memory == NULL) //������ ������ �ʾ�����
	{
		printf("������ ������ �ʾҽ��ϴ�.\n");
	}

	else
	{
		fseek(Flash_memory, 0, SEEK_END);
		file_end = ftell(Flash_memory);
		rewind(Flash_memory);
		if (file_end / SS <= LSN) //������ �ʰ��ؼ� ���� ���
		{
			printf("������ �ʰ��߽��ϴ�.\n");
		}
		else
		{
			fseek(Flash_memory, PSN * SS, SEEK_SET); //���� ���� ��ġ
			fgets(read_Sdata, 513, Flash_memory); //�����͸� �о�´�.
			len = strlen(read_Sdata);

			if (len == SS && strspn(read_Sdata, " ") == SS) //���ڿ� ���̰� 512 AND �����̽��� ������ 512�� �϶�
			{
				printf("PSN : %d\nDATA :EMPTY\n", PSN);
			}
			else
			{
				printf("PSN : %d\nDATA : %s", PSN, read_Sdata);
			}
		}
		fclose(Flash_memory);
	}
}