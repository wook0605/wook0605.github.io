#include "FlashMemory_head.h"

int main()
{	
	FILE* Flash_Memory = NULL; //�÷��ø޸�
	char Commend[CL]; //��ɾ ���� ���ڿ� �迭
	int value = 0; //����� ���� ���� ����
	int len = 0; //���ڿ� ����
	char Write_data[SS];
	memset(Commend, NULL, CL);
	memset(Write_data, NULL, SS);

	printf("���� : �Է��� �� �ִ� ��ɾ�� ������ �����ϴ�.\n");
	printf("init X MegaByte : X MB ũ���� �÷��� �޸� ����\n");
	printf("r 5 : �����͸� �о�� ���� ����\n");
	printf("W 5 : �����͸� �������� ���� ����\n");
	printf("E 5 : �����͸� ���� ��� ����\n");
	printf("quit : ���α׷��� ����\n");
	while (true)
	{
		printf("��ɾ �Է����ּ���>>");
		fgets(Commend,CL,stdin); // ��ɾ� �Է�
		strlwr(Commend); // �Է¹��� ���� �ҹ��ڷ� �ٲپ��ֱ�

		if (strstr(Commend,"?") != NULL) // ? ���ڸ� �߰��� ���
		{
			printf("���� : �Է��� �� �ִ� ��ɾ�� ������ �����ϴ�.\n");
			printf("init X MegaByte : X MB ũ���� �÷��� �޸� ����\n");
			printf("R 5 : 5�� ������ �����͸� �о�´�.\n");
			printf("W 5 A : 5�� ���Ϳ� A�� ���´�.\n");
			printf("E 5 : 5�� ����� �����.\n");
		}

		else if (strstr(Commend, "init") != NULL) // �÷��� �޸� ����
		{
			value = ext_num(Commend);//������ ���� ������ �Է�
			init(Flash_Memory,value);
		}

		else if (strstr(Commend, "r") != NULL) // �ش� ������ ������ �о����
		{
			value = ext_num(Commend); //������ ���� ������ �Է�
			Flash_read(Flash_Memory, value);
		}

		else if (strstr(Commend, "w") != NULL) // �ش� ���Ϳ� ������ ����
		{
			printf("������ :");
			fgets(Write_data,SS,stdin); //������ �Է�
			value = ext_num(Commend); //������ ���� ������ �Է�
			Flash_write(Flash_Memory, value, Write_data);
		}

		else if (strstr(Commend, "e") != NULL) // �ش� ��� �����ϱ�
		{
			value = ext_num(Commend, value); //������ ���� ������ �Է�
			Flash_erase(Flash_Memory, value);
		}

		else if (strstr(Commend, "quit") != NULL) // ����
		{
			return 0;
		}

		else // �߸��� ��ɾ �Է����� ���
		{
			printf("�߸��� ��ɾ��Դϴ�.\n");
		}
	}
	return 0;
}