#include "dynamic_blockmapping_head.h"

unsigned int ext_num(char* Commend, char* write_data)
{
	int len = 0; //���ڿ� ����
	int pv = 0; // �ڸ����� ���߱� ���� ����
	char buf[10]; //������ ���� �迭 10�ڸ� �������� ���� �� �ִ�. (int������ ��� ����)
	int storage = 0; //��ȯ�� ��
	int data = 0;
	unsigned int digit = 0; //���� �ڸ������� ���� ����
	unsigned int stop = digit + 1;

	len = strlen(Commend);

	for (digit = 0; digit < len; digit++)
	{
		if (Commend[digit] > 47 && Commend[digit] < 58) //ASCII�󿡼� ���� �߰�
		{
			buf[pv] = Commend[digit]; //�߰��� ���ڸ� �ڸ����� �°� �迭�� �Է�
			pv++; //�ڸ��� ����
		}
		else
		{
			if (digit >5)
			{
				write_data[data] = Commend[digit];
				data++;
			}
		}
	}
	storage = atoi(buf); // ���� ��Ҹ� ������ ��ȯ
	return storage;
}

void print_table() //���̺� ���
{
	for (int i = 0; i < mtable.nob; i++)
	{
		printf("LBN : %d\t PBN : %d\n", i,mtable.table[i]);
	}
}


void load_table(FILE* Flash_memory) //�������̺� �о����
{
	Flash_memory = fopen("Block_Mapping_FM.txt", "r");
	unsigned int count = 0;
	fpos_t pos = 0;
	if (Flash_memory == NULL)
	{
		printf("������ �� �� �����ϴ�.\n");
	}

	else //������ ������ ��
	{
		while (!feof(Flash_memory))
		{
			++mtable.nos;
			fgets(temp_B.temp_, sizeof(temp_B.temp_), Flash_memory); //���پ� �б�
		}
		rewind(Flash_memory);
		mtable.nob = mtable.nos / NOS;
		mtable.FP_loc = (unsigned long long*) malloc(sizeof(unsigned long long) * (mtable.nos)); //���ͺ� ���� ������ ��ġ �����ϱ� ����.
		mtable.table = (int*)malloc(sizeof(int) * mtable.nob); //��ϰ�����ŭ �Ҵ�
		for (int i = 0; i < mtable.nos; i++) //�÷��� �޸� ��ü ��ĵ
		{
			fgetpos(Flash_memory, &pos);
			mtable.FP_loc[i] = pos;
			fgets(temp_B.temp_, SS, Flash_memory); //������ ���� �б�
			fscanf(Flash_memory, "\t%d\t%d\t%d\t%d", &spare.status, &spare.LSN, &spare.write_count, &spare.erase_count); //����� ���� �б�
			fgetc(Flash_memory);//���� ������ ��ġ ��ĭ �б�
			count = spare.LSN / NOS;
			mtable.table[i / NOS] = count;
		}
		fclose(Flash_memory);
	}
}