#include "phoneBook_head.h"


int main()
{
	PB_list* head = (PB_list*)malloc(sizeof(PB_list)); // ����� ����
	head->link = NULL; //��� ���� �����͸� �������� ����.
	person temp;
	int menu;
	int select;
	while (1)
	{
		printf("=====================================================\n");
		printf("|              �޴��� �����Ͻʽÿ�.                  |\n");
		printf("| 1. ��ȭ��ȣ �߰�                                   |\n");
		printf("| 2. ��ȭ��ȣ �˻�                                   |\n");
		printf("| 3. ��ȭ��ȣ ��ü����                               |\n");
		printf("| 4. ��ȭ��ȣ ����                                   |\n");
		printf("| 5. ��ȭ��ȣ ����                                   |\n");
		printf("| 6. ��ȭ��ȣ�� ����                                 |\n");
		printf("=====================================================\n");
		printf("�޴� ����>>");
		scanf("%d", &menu);

		switch (menu)
		{

		case 1:
		{
			printf("�߰��� ������� ������ �Է����ֽʽÿ�.\n");

			printf("�̸� :");
			scanf("%s", temp.input_name);
			printf("��ȣ :");
			scanf("%s", temp.input_number);
			printf("\n");

			Add_user(head, temp);

			break;
		}

		case 2:
		{
			printf(" 1 : ��ȣ�� ã�� / 2 : �̸����� ã��\n");
			scanf("%d", &select);
			switch (select)
			{
			case 1:
			{
				printf("�˻��� ������� ��ȣ�� �Է����ֽʽÿ�.\n");
				printf("��ȣ :");
				scanf("%s", temp.input_number);
				Search_user(head, temp);
				break;
			}
			case 2:
			{
				printf("�˻��� ������� �̸��� �Է����ֽʽÿ�.\n");
				printf("�̸� :");
				scanf("%s", temp.input_name);
				Search_user(head, temp);
				break;
			}
			default:
			{
				scanf("%*c", &select);
				printf("�߸��� �Է��Դϴ�.\n");
				break;
			}
			}
		}

		case 3:
		{
			print_Book(head);
			break;
		}

		case 4:
		{
			printf("������ ������� �̸��� �Է����ֽʽÿ�\n");
			scanf("%s", temp.input_name);
			delete_user(head, temp);
			break;
		}

		case 5:
		{
			printf("������ ������� �̸��� �Է����ּ���.\n");
			scanf("%s", temp.input_name);
			change_userinfo(head, temp);
			break;
		}

		case 6:
		{
			printf("��ȭ��ȣ�θ� �����մϴ�.\n");
			free_mem(head);
			return 0;
		}

		default:
		{
			scanf("%*c", &menu); //�Է¹��� �ʱ�ȭ
			printf("�ش� �޴��� �������� �ʽ��ϴ�. �ٽ� �Է����ֽʽÿ�.\n");
			break;
		}
		}
		}
		return 0;
	}