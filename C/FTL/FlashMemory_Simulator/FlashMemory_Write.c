#include "FlashMemory_head.h"

void Flash_write(FILE* Flash_memory, int write_place, char* write_data)
{
	int ws = (write_place * SS);  // ������ ���͸� ����Ű�� ���� ��
	int file_end = 0;
	char read_data[SS];
	bool OverWrite = false;

	 Flash_memory = fopen("Flash_Memory.txt","r+"); //������ �б�/���� ���� ����.

	if (Flash_memory == NULL)
	{
		printf("������ ������ �ʾҽ��ϴ�.\n");
	}

	else
	{
		fseek(Flash_memory, 0, SEEK_END); //������ ������ ����.
		file_end = ftell(Flash_memory); //������ ������ �ִ� ������ ���̸� ���.
		rewind(Flash_memory);// ���� �����͸� �ٽ� �Ǿ�����

		if (ws == 0) //ù ���Ϳ� ���� ���
		{
			fgets(read_data, SS, Flash_memory); // �����Ͱ� �ִ��� Ȯ���ϱ� ���� ������ �о����

			for (int i = 0; i < SS; i++)
			{
				if (read_data[i] != 32 && read_data[i] != 0) // �����̽��ٿ� NULL���� �ܿ� ������ ����� ��������Ʈ.
				{
					OverWrite = true;
				}
			}

			if (OverWrite) //��������Ʈ ���� �϶�
			{
				printf("OverWrite Error!!\n"); //��������Ʈ ���� ���
			}

			else //�����͸� �� �� ���� ��
			{
				rewind(Flash_memory);
				fputs(write_data, Flash_memory); //�ٷ� �Է�
				printf("Done!\n");
			}
		}

		else //ù ���Ͱ� �ƴ� ���
		{
			if (file_end / 512 <= write_place) //������ �ʰ��ؼ� �д� ���
			{
				printf("������ �ʰ��߽��ϴ�.\n");
			}

			else
			{
				fseek(Flash_memory, ws, SEEK_SET); // ���� ã��
				fgets(read_data, SS, Flash_memory);// �����Ͱ� �ִ��� ������ �˻��ϱ� ���� �б�

				for (int i = 0; i < SS; i++)
				{
					if (read_data[i] != 32 && read_data[i] != 0) // �����̽��ٿ� NULL���� �ܿ� ������ ����� ��������Ʈ.
					{
						OverWrite = true;
					}
				}

				if (OverWrite) //��������Ʈ �����϶�
				{
					printf("OverWrite error!\n"); // ��������Ʈ ���� ���
				}

				else // �����͸� �� �� ������
				{
					rewind(Flash_memory);
					fseek(Flash_memory, ws, SEEK_SET);
					fputs(write_data, Flash_memory);
					printf("Done!\n");
				}
			}
		}

		fclose(Flash_memory); //������ �ݴ´�.
	}

	

}