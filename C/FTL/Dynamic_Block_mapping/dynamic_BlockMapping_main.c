#include "dynamic_blockmapping_head.h"

int main()
{
	FILE* Flash_Memory = NULL; //�÷��ø޸�
	FILE* Trace = NULL;
	char Commend[CL]; //��ɾ ���� ���ڿ� �迭
	int LSN = 0; //����� ���� ���� ����
	char Write_data[513]; // �Է��� ������
	mtable.write_count = 0;
	mtable.erase_count = 0;
	mtable.no_block = 0;
	mtable.nob = 0;
	mtable.nos = 0;

	memset(Commend, NULL, CL);
	memset(Write_data, NULL, SS);
	load_table(Flash_Memory); //���� ���̺��� �ҷ���

	printf("���� : �Է��� �� �ִ� ��ɾ�� ������ �����ϴ�.\n");
	printf("? : ����  ���\n");
	printf("init X MegaByte : X MB ũ���� �÷��� �޸� ����\n");
	printf("read: 5 : �����͸� �о�� ���� ����\n");
	printf("write: 5 : �����͸� �������� ���� ����\n");
	printf("quit : ���α׷��� ����\n");
	while (true)
	{
		printf("��ɾ �Է����ּ���>>");
		fgets(Commend, CL, stdin); // ��ɾ� �Է�
		strlwr(Commend);

		if (Commend[0] == '?') // ? ���ڸ� �߰��� ���
		{
			printf("���� : �Է��� �� �ִ� ��ɾ�� ������ �����ϴ�.\n");
			printf("init X MegaByte : X MB ũ���� �÷��� �޸� ����\n");
			printf("r 5 : 5�� ������ �����͸� �о�´�.\n");
			printf("w 5 A : 5�� ���Ϳ� A�� ���´�.\n");
			printf("printtable : ���� ���̺��� ����Ѵ�.\n");
			printf("quit : ���α׷� ����\n");
		}

		else if (Commend[0] == 'i' && strstr(Commend, "init") != NULL) // �÷��� �޸� ����
		{
			LSN = ext_num(Commend, Write_data);//������ ���� ������ �Է�
			init(Flash_Memory, LSN);
		}

		else if (Commend[0] == 't' && strstr(Commend, "trace") != NULL) //Trace ����
		{
			printf("������ Ʈ���̽������� �����ϼ���.\n");
			printf("0 : Copy of KODAK-total\n1: kodak-pattern\n2: kodak-pattern-rule\n3: linux\n4: NIKON-SS32\n");
			fgets(Commend, CL, stdin);
			if (Commend[0] == '0')
			{
				Trace = fopen("Copy of KODAK-total.txt", "r");
				while (!feof(Trace)) //Ʈ���̽� ������ �о� ������.
				{
					fgets(Commend, CL, Trace);
					LSN = ext_num(Commend, Write_data); //������ ���� ������ �Է�
					printf("LSN : %d\n", LSN);
					memset(Write_data, 32, sizeof(char));
					Flash_write(Flash_Memory, LSN, Write_data);
				}
				printf("���� ī��Ʈ : %d\t ���� ī��Ʈ : %d\n", mtable.write_count, mtable.erase_count);
				//fclose(Trace);
			}
			else if (Commend[0] == '1')
			{
				Trace = fopen("kodak-pattern.txt", "r");
				while (!feof(Trace)) //Ʈ���̽� ������ �о� ������.
				{
					fgets(Commend, CL, Trace);
					LSN = ext_num(Commend, Write_data); //������ ���� ������ �Է�
					printf("LSN : %d\n", LSN);
					memset(Write_data, 32, sizeof(char));
					Flash_write(Flash_Memory, LSN, Write_data);
				}
				printf("���� ī��Ʈ : %d\t ���� ī��Ʈ : %d\n", mtable.write_count, mtable.erase_count);
				//fclose(Trace);
			}

			else if (Commend[0] == '2')
			{
				Trace = fopen("kodak-pattern-rule.txt", "r");
				while (!feof(Trace)) //Ʈ���̽� ������ �о� ������.
				{
					fgets(Commend, CL, Trace);
					LSN = ext_num(Commend, Write_data); //������ ���� ������ �Է�
					printf("LSN : %d\n", LSN);
					memset(Write_data, 32, sizeof(char));
					Flash_write(Flash_Memory, LSN, Write_data);
				}
				printf("���� ī��Ʈ : %d\t ���� ī��Ʈ : %d\n", mtable.write_count, mtable.erase_count);
				//fclose(Trace);
			}
		
			else if (Commend[0] == '3')
			{
				Trace = fopen("linux.txt", "r");
				while (!feof(Trace)) //Ʈ���̽� ������ �о� ������.
				{
					fgets(Commend, CL, Trace);
					LSN = ext_num(Commend, Write_data); //������ ���� ������ �Է�
					printf("LSN : %d\n", LSN);
					memset(Write_data, 32, sizeof(char));
					Flash_write(Flash_Memory, LSN, Write_data);
				}
				printf("���� ī��Ʈ : %d\t ���� ī��Ʈ : %d\n", mtable.write_count, mtable.erase_count);
				//fclose(Trace);
			}

			else if (Commend[0] == '4')
			{
				Trace = fopen("NIKON-SS32.txt", "r");
				while (!feof(Trace)) //Ʈ���̽� ������ �о� ������.
				{
					fgets(Commend, CL, Trace);
					LSN = ext_num(Commend, Write_data); //������ ���� ������ �Է�
					printf("LSN : %d\n", LSN);
					memset(Write_data, 32, sizeof(char));
					Flash_write(Flash_Memory, LSN, Write_data);
				}
				printf("���� ī��Ʈ : %d\t ���� ī��Ʈ : %d\n", mtable.write_count, mtable.erase_count);
				//fclose(Trace);
			}
		}

		else if (Commend[0] == 'r' && strstr(Commend, "read") != NULL) // �ش� ������ ������ �о����
		{
			LSN = ext_num(Commend, Write_data); //������ ���� ������ �Է�
			Flash_read(Flash_Memory, LSN);
		}

		else if (Commend[0] == 'w' && strstr(Commend, "write") != NULL) // �ش� ���Ϳ� ������ ����
		{
			LSN = ext_num(Commend, Write_data); //������ ���� ������ �Է�
			if (strlen(Write_data) == 0)
			{
				memset(Write_data, " ", sizeof(Write_data));
			}
			Flash_write(Flash_Memory, LSN, Write_data);
		}

		else if (Commend[0] == 'p' && strstr(Commend, "printtable") != NULL) //���̺� ���
		{
			print_table();
		}

		else if (Commend[0] == 'q' && strstr(Commend, "quit") != NULL) // ����
		{
		free(mtable.table);
		free(mtable.FP_loc);
			break;
		}

		else // �߸��� ��ɾ �Է����� ���
		{
			printf("�߸��� ��ɾ��Դϴ�.\n");
		}
	}
	return 0;
}