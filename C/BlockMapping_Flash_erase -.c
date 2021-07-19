#include "BlockMapping_head.h"

void Flash_erase(FILE* Flash_memory, int LBN)
{
	int PBN = mtable.table[LBN];
	int offset = (LBN * NOS) % NOS;
	int file_end = 0;

	Flash_memory = fopen("Block_Mapping_FM.txt", "r+"); // �б�/���� ���� ������ ����.

	if (Flash_memory == NULL) //������ �������ʾ��� ��
	{
		printf("������ ������ �ʾҽ��ϴ�.\n");
	}

	else
	{
		fseek(Flash_memory, 0, SEEK_END); //������ ������ ����.
		file_end = ftell(Flash_memory); //������ ������ �ִ� ������ ���̸� ���.
		rewind(Flash_memory);// ���� �����͸� �ٽ� �Ǿ�����

		if ((file_end / 512) / 32 <= LBN) //������ ����� ������ ��� ������ ũ�ų� ���� ���
		{
			printf("������ �ʰ��߽��ϴ�.\n");
		}
		else
		{
			for (int i = 0; i < NOS; i++) //������ �������Ѽ� ���� ����(��Ͽ� ���Ͱ� �־, ���������� ����̱⶧���� �����Ѵ�.)
			{
				fseek(Flash_memory, ((mtable.table[LBN]*NOS)+i)*SS, SEEK_SET); // ������ �ش� ����� ������ ��ġ�� �̵�
				for (int j = 0; j < SS; j++)//����� ù ���ͺ��� ������ ���ͱ���
				{
					fprintf(Flash_memory, " ");
				}
			}
		}
		mtable.erase_count[LBN]++; //����� ����ī��Ʈ ����
		printf("Erase %dth Block\n", LBN);
		printf("erase�� Ƚ�� : %d\n", mtable.erase_count[LBN]); //�ش� ����� ���� ī��Ʈ ���
		printf("PBN : %d\n", PBN);
	}
	fclose(Flash_memory);
}