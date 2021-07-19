#include "BlockMapping_head.h"

void Flash_write(FILE* Flash_memory, int LSN, char* write_data)
{
	int LBN = LSN / NOS;
	int PBN = mtable.table[LBN];  // ������ ���͸� ����Ű�� ���� ��
	int file_end = 0;
	int owb = 0; //����Ⱑ �Ͼ ���
	int owo = 0; //����Ⱑ �Ͼ offset
	int offset = LSN % NOS;
	char read_data[SS];
	bool OverWrite = false;

	Flash_memory = fopen("Block_Mapping_FM.txt", "r+"); //������ �б�/���� ���� ����.

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
			fseek(Flash_memory, ((PBN * NOS)+(offset))*SS, SEEK_SET); // ����� ������ ã��
			fgets(read_data, SS, Flash_memory);// �����Ͱ� �ִ��� ������ �˻��ϱ� ���� �б�

			for (int i = 0; i < SS; i++)
			{
				if (read_data[i] != 32 && read_data[i] != 0) // �����̽��ٿ� NULL���� �ܿ� ������ ����� ��������Ʈ.
				{
					OverWrite = true;
					if (OverWrite)
					{
						owb = PBN;
						owo = offset;
						break;
					}
				}
			}

			if (OverWrite) //��������Ʈ �����϶�
			{
				FTL_write(Flash_memory, LSN, PBN, write_data, owb, owo);
			}

			else // �����͸� �� �� ������
			{
				rewind(Flash_memory);
				fseek(Flash_memory, ((PBN*NOS)+offset)*SS, SEEK_SET); //�ش� ����� ���������� �����Ѵ�.
				fputs(write_data, Flash_memory);
				mtable.write_count[(PBN * NOS) + offset]++; //�ش� ��� �������� ���� ī���� ����
				printf("Done!\n");
			}
		}
		fclose(Flash_memory); //������ �ݴ´�.
	}
}