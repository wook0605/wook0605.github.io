#include "SectorMapping.h"

int main()
{
	FILE* Flash_Memory = NULL; //�÷��ø޸�
	char Commend[CL]; //��ɾ ���� ���ڿ� �迭
	int LSN = 0; //����� ���� ���� ����
	char Write_data[SS]; // �Է��� ������

	memset(Commend, NULL, CL);
	memset(Write_data, NULL, SS);

	load_table(Flash_Memory);

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

		if (strstr(Commend, "?") != NULL) // ? ���ڸ� �߰��� ���
		{
			printf("? : ����  ���\n");
			printf("init X MegaByte : X MB ũ���� �÷��� �޸� ����\n");
			printf("read: 5 : �����͸� �о�� ���� ����\n");
			printf("write: 5 : �����͸� �������� ���� ����\n");
			printf("quit : ���α׷��� ����\n");
		}

		else if (strstr(Commend, "init") != NULL) // �÷��� �޸� ����
		{
			LSN = ext_num(Commend);//������ ���� ������ �Է�
			init(Flash_Memory, LSN);
		}

		else if (strstr(Commend, "read") != NULL) // �ش� ������ ������ �о����
		{
			LSN = ext_num(Commend); //������ ���� ������ �Է�
			Flash_read(Flash_Memory, LSN);
		}

		else if (strstr(Commend, "write") != NULL) // �ش� ���Ϳ� ������ ����
		{
			printf("������ :");
			fgets(Write_data, SS, stdin); //������ �Է�
			LSN = ext_num(Commend); //������ ���� ������ �Է�
			Flash_write(Flash_Memory, LSN, Write_data);
		}

		else if (strstr(Commend, "printtable") != NULL)
		{
			print_table();
		}

		else if (strstr(Commend, "quit") != NULL) // ����
		{
			quit(Flash_Memory);
			break;
		}

		else // �߸��� ��ɾ �Է����� ���
		{
			printf("�߸��� ��ɾ��Դϴ�.\n");
		}
	}
	return 0;
}