#include "BlockMapping_head.h"

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

void print_table() //���̺� ���
{
	for (int i = 0; i < mtable.num_blo; i++)
	{
		printf("LBN : %d\t PBN : %d\n", i,mtable.table[i]);
		printf("PBN %d �� Erase_Count : %d\n", mtable.table[i], mtable.erase_count[i]);
		for (int offset = 0; offset < NOS; offset++) //�� ����� �������� ����ī��Ʈ
		{
			printf("PBN %d offset %d�� Write_Count : %d\n", mtable.table[i],offset, mtable.write_count[(mtable.table[i]* NOS) + offset]);
		}
	}
}

void quit(FILE* Flash_memory) //����
{
	Flash_memory = fopen("BLock_Mapping_table.txt", "w");

	if (Flash_memory == NULL)
	{
		printf("������ �� �� �����ϴ�.\n");
	}

	else //������ ������ ��
	{
		fprintf(Flash_memory, "%d\n", mtable.num_blo); //����� ���� ù�ٿ� ����
		for(int i = 0; i<mtable.num_blo; i++) //���Ͽ� �������̺�� ����,���� ī��Ʈ ����
		{
			fprintf(Flash_memory, "%d\t", mtable.table[i]);
			fprintf(Flash_memory, "%d\t", mtable.erase_count[i]);
			for (int offset = 0; offset < NOS; offset++)
			{
				fprintf(Flash_memory, "%d\t", mtable.write_count[(mtable.table[i] * NOS) + offset]); //����ī��Ʈ�� ���ͺ��� ������ ������, �ش� �������� ��������.
			}
		}
		free(mtable.table); //�Ҵ� ����
		free(mtable.erase_count); //�Ҵ� ����
		free(mtable.write_count); //�Ҵ� ����
	}
	fclose(Flash_memory);//���� �ݱ�
}

void load_table(FILE* Flash_memory) //�������̺� �о����
{
	Flash_memory = fopen("Block_Mapping_table.txt", "r");
	int place = 0;
	int len = 0;

	if (Flash_memory == NULL)
	{
		printf("������ �� �� �����ϴ�.\n");
	}

	else //������ ������ ��
	{
		fscanf(Flash_memory, "%d", &len); //�������̺��� �о���� ���� �����ص� ����� ������ �о��
		mtable.num_blo = len;
		mtable.table = (int*)malloc(sizeof(int) * len); //��ϰ�����ŭ �Ҵ�
		mtable.erase_count = (int*)malloc(sizeof(int) * len); //��� ������ŭ �Ҵ�
		mtable.write_count = (int*)malloc(sizeof(int) * len * NOS); //���� ������ŭ �Ҵ�
		for (place = 0; place < len; place++)
		{
			fscanf(Flash_memory, "%d", &mtable.table[place]);
			fscanf(Flash_memory, "%d", &mtable.erase_count[place]);
			for (int  i = 0; i < NOS; i++)
			{
				fscanf(Flash_memory, "%d", &mtable.write_count[(mtable.table[place]*NOS)+i]); //����ī��Ʈ�� ���ͺ��� ������ ������, �ش� �������� ��������.
			}
		}
		fclose(Flash_memory);
	}

}