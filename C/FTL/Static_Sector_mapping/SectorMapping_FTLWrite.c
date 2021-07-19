#include "SectorMapping.h"

void FTL_write(FILE* Flash_memory, int LSN, char* write_data, int owp)
{
	int LBN = LSN / NOS;
	int PBN = LBN * NOS; // �������̺��� ��ϴ����� �����ϱ� ���� ��
	int file_end = 0;
	int write_sum = 0;
	char read_data[SS];

	memset(temp.temp_blcok, NULL, sizeof(temp)); //�ӽú�� �ʱ�ȭ
	memset(read_data, NULL, SS); //�о�� ������ �����ϴ� �迭 �ʱ�ȭ
	for (int i = PBN; i < PBN+NOS; i++)
	{
		fseek(Flash_memory, mtable.table[i]*SS, SEEK_SET); // ���ͷ� ���� ������ �ű��
		if (owp == mtable.table[i])
		{
			fgets(read_data, SS, Flash_memory);
			strcpy(temp.temp_blcok[i-PBN], write_data); // ����Ⱑ �Ͼ ������ �����͸� ���� ���ش�.(i-PBN�� i�� 0���� 31���� ��������)
		}

		else
		{
			fgets(read_data, SS, Flash_memory); // �ش� ����� ���� �о����
			strcpy(temp.temp_blcok[i-PBN], read_data); // erase�� ��ϴ����� �Ͼ�� ������ �ش� ����� ��ȿ������ ���� ����
		}
	}
	Flash_erase(Flash_memory, LBN); //�ش� ��� ����
	rewind(Flash_memory);
	for (int i = PBN; i < PBN + NOS; i++) //��� �ٽ� ����
	{
		fseek(Flash_memory, mtable.table[i]*SS, SEEK_SET); //�ش� ������ ��ġ
		fputs(temp.temp_blcok[i - PBN], Flash_memory);
		if (strlen(temp.temp_blcok[i - PBN]) == SS - 1 && strspn(temp.temp_blcok[i - PBN], " ") == SS - 1) //�� ������ ����ī��Ʈ�� �ö��� ����
		{

		}
		else
		{
			mtable.write_count[i]++;
			write_sum++;
		}
	}
	printf("���� �Ϸ�\n");
	printf("write�� Ƚ�� : %d\n", write_sum);
}