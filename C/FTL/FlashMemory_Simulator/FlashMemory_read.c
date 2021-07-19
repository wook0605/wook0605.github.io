#include "FlashMemory_head.h"

void Flash_read(FILE* Flash_memory, int read_sector)
{
	int rs = (read_sector * SS); //������ ���͸� ����Ű��
	int file_end = 0;
	int len = 0;
	char read_Sdata[513]; // 512�� �ε����� ���� �б� ���ؼ� 513ũ��� �����Ѵ�.

	Flash_memory = fopen("Flash_Memory.txt", "r"); //������ �б� ���� ����

	if (Flash_memory == NULL) //������ ������ �ʾ�����
	{
		printf("������ ������ �ʾҽ��ϴ�.\n");
	}

	else
	{
		fseek(Flash_memory, 0, SEEK_END); //������ ������ ����.
		file_end = ftell(Flash_memory); //������ ������ �ִ� ������ ���̸� ���.
		rewind(Flash_memory);// ���� �����͸� �ٽ� �Ǿ�����

		if (rs == 0) //ù ���͸� �д� ���
		{
			fgets(read_Sdata, 513, Flash_memory);
			len = strlen(read_Sdata);
			
			if (len == SS && strspn(read_Sdata, " ") == SS) //���ڿ� ���̰� 512  AND �����̽��� ������ 512�� �϶�
			{
				printf("EMPTY\n");
			}

			else
			{
				printf("%s", read_Sdata);
			}
		}

		else // ù ���Ͱ� �ƴ� ���
		{
			if (file_end / 512 <= read_sector) //������ �ʰ��ؼ� �д� ���
			{
				printf("������ �ʰ��߽��ϴ�.\n");
			}

			else
			{
				fseek(Flash_memory, rs, SEEK_SET);
				fgets(read_Sdata, 513, Flash_memory);
				len = strlen(read_Sdata);

				if (len == SS && strspn(read_Sdata, " ") == SS) //���ڿ� ���̰� 512 AND �����̽��� ������ 512�� �϶�
				{
					printf("EMPTY\n");
				}

				else
				{
					printf("%s", read_Sdata);
				}
			}
		}
		fclose(Flash_memory);
	}
}