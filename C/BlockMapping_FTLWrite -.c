#include "BlockMapping_head.h"

void FTL_write(FILE* Flash_memory, int LSN, int PBN, char* write_data, int owb, int owo)
{
	int LBN = LSN / NOS;
	int file_end = 0;
	int write_sum = 0;
	char read_data[SS];

	memset(temp.temp_blcok, NULL, sizeof(temp)); //�ӽú�� �ʱ�ȭ
	memset(read_data, NULL, SS); //�о�� ������ �����ϴ� �迭 �ʱ�ȭ
	for (int i = 0; i < NOS; i++) //������ ����
	{
		fseek(Flash_memory, ((PBN*NOS)+i)*SS, SEEK_SET); // �ش� ����� ���������� ���� ������ �ű��
		if (owb == mtable.table[LBN] && owo == i)
		{
			fgets(read_data, SS, Flash_memory);
			strcpy(temp.temp_blcok[i], write_data); // ����Ⱑ �Ͼ ������ �����͸� ���� ���ش�.
		}

		else
		{
			fgets(read_data, SS, Flash_memory); // �ش� ����� �ش� ���� �о����
			strcpy(temp.temp_blcok[i], read_data); // erase�� ��ϴ����� �Ͼ�� ������ �ش� ����� ��ȿ������ ���� ����
		}
	}
	Flash_erase(Flash_memory, LBN); //�ش� ��� ����
	rewind(Flash_memory);
	for (int i = 0; i < NOS; i++) //�ٽ� ��Ͽ� ������
	{
		fseek(Flash_memory, ((PBN*NOS)+i)*SS, SEEK_SET); //����� �� �����¿� ����
		fputs(temp.temp_blcok[i], Flash_memory);
		if (strlen(temp.temp_blcok[i]) == SS - 1 && strspn(temp.temp_blcok[i], " ") == SS - 1) //�� ������ ����ī��Ʈ�� �ö��� ����
		{

		}
		else
		{
			mtable.write_count[(PBN * NOS) + i]++;
			write_sum++;
		}
	}
	printf("���� �Ϸ�\n");
	printf("write�� Ƚ�� : %d\n", write_sum);
}