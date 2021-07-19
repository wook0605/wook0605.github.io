#include "SectorMapping.h"

int ext_num(char* Commend)
{
	int len; //���ڿ� ����
	int pv = 0; // �ڸ����� ���߱� ���� ����
	char buf[10]; //������ ���� �迭 10�ڸ� �������� ���� �� �ִ�.
	int storage = 0; //��ȯ�� ��

	len = strlen(Commend);

	for (int i = 0; i < len; i++)
	{
		if (Commend[i] > 47 && Commend[i] < 58) //ASCII�󿡼� ���� �߰�
		{
			buf[pv] = Commend[i]; //�߰��� ���ڸ� �ڸ����� �°� �迭�� �Է�
			pv++; //�ڸ��� ����
		}
	}
	storage = atoi(buf); // ���� ��Ҹ� ������ ��ȯ

	return storage;
}

void print_table()
{
	for (int i = 0; i < mtable.num_sec; i++)
	{
		printf("LSN : %d\t PSN : %d\n", i,mtable.table[i]);
		printf("PSN %d �� Erase_Count : %d\n", mtable.table[i], mtable.erase_count[i]);
		printf("PSN %d �� Write_Count : %d\n", mtable.table[i], mtable.write_count[i]);
	}
}

void quit(FILE* Flash_memory)
{
	Flash_memory = fopen("SectorMapping_table.txt", "w");

	if (Flash_memory == NULL)
	{
		printf("������ �� �� �����ϴ�.\n");
	}

	else //������ ������ ��
	{
		fprintf(Flash_memory, "%d\n", mtable.num_sec);//ù�ٿ� ���Ͱ��� ����
		for(int i = 0; i<mtable.num_sec; i++) //���Ͽ� �������̺�� ����,���� ī��Ʈ ����
		{
			fprintf(Flash_memory, "%d\t", mtable.table[i]);
			fprintf(Flash_memory, "%d\t", mtable.erase_count[i]);
			fprintf(Flash_memory, "%d\t", mtable.write_count[i]);
		}
		free(mtable.table); //�Ҵ� ����
		free(mtable.erase_count); //�Ҵ� ����
		free(mtable.write_count); //�Ҵ� ����
	}
	fclose(Flash_memory);//���� �ݱ�
}

void load_table(FILE* Flash_memory)
{
	Flash_memory = fopen("SectorMapping_table.txt", "r");
	int place = 0;
	int len = 0;

	if (Flash_memory == NULL)
	{
		printf("������ �� �� �����ϴ�.\n");
	}

	else //������ ������ ��
	{
		fscanf(Flash_memory, "%d", &len); //���� ù�� �о ���Ͱ��� �˾Ƴ���
		mtable.num_sec = len; //���Ͱ��� ����
		mtable.table = (int*)malloc(sizeof(int) * len); //���� ������ŭ �Ҵ�
		mtable.erase_count = (int*)malloc(sizeof(int) * len); //���� ������ŭ �Ҵ�
		mtable.write_count = (int*)malloc(sizeof(int) * len); //���� ������ŭ �Ҵ�
		for (place = 0; place < len; place++) //������ �о�ͼ� �Ҵ��� ������ �Է�
		{
			fscanf(Flash_memory, "%d", &mtable.table[place]);
			fscanf(Flash_memory, "%d", &mtable.erase_count[place]);
			fscanf(Flash_memory, "%d", &mtable.write_count[place]);
		}
		fclose(Flash_memory);
	}

}