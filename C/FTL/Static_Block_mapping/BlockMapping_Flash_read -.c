#include "BlockMapping_head.h"

void Flash_read(FILE* Flash_memory, int LSN)
{
	int PBN = FTL_read(LSN);
	int offset = LSN % NOS;
	int file_end = 0; //������ ������ �� ������ Ȯ��
	int len = 0; //�о�� �迭�� ����
	char read_Sdata[513]; // 512�� �ε����� ���� �б� ���ؼ� 513ũ��� �����Ѵ�.

	Flash_memory = fopen("Block_Mapping_FM.txt", "r"); //������ �б� ���� ����

	if (Flash_memory == NULL) //������ ������ �ʾ�����
	{
		printf("������ ������ �ʾҽ��ϴ�.\n");
	}

	else
	{
			fseek(Flash_memory, ((PBN * NOS)+offset)*SS, SEEK_SET); //������ �ش� ����� ������ ��ġ�� ���� ������ �̵�
			fgets(read_Sdata, 513, Flash_memory);
			len = strlen(read_Sdata);

			if (len == SS && strspn(read_Sdata, " ") == SS) //���ڿ� ���̰� 512 AND �����̽��� ������ 512�� �϶�
			{
				printf("PBN %d�� offset : %d\nDATA :EMPTY\n",PBN, offset);
			}
			else
			{
				printf("PBN %d�� offset : %d\nDATA : %s", PBN, offset, read_Sdata);
			}
		}
			
		fclose(Flash_memory);
	}