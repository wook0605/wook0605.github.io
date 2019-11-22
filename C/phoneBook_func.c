#include "phoneBook_head.h"

void Add_user(PB_list* input, person temp)
{
	PB_list* p = (PB_list*)malloc(sizeof(PB_list)); // �����͸� ������ ��忡 �޸� �Ҵ�


	if (input->link == NULL) //ù ������ ����
	{
		if (check_form(temp))
		{
			free(p);
		}

		else
		{
			strcpy(p->number, temp.input_number); //��ȣ �Է�
			strcpy(p->name, temp.input_name); //�̸� �Է�
			p->link = input->link; //��� ����
			input->link = p;
		}
	}

	else
	{
			if (check_form(temp) || check_dp(input, temp)) // �ߺ�üũ�Լ� : false (�ߺ� �ƴ�) true (�ߺ�)  
			{
				free(p);
			}

			else
			{
				strcpy(p->number, temp.input_number); //��ȣ �Է�
				strcpy(p->name, temp.input_name); //�̸� �Է�
				p->link = input->link; //��� ����
				input->link = p;
				sort_list(input); //����
			}
	}
}

bool check_dp (PB_list* p, person temp)
{
	PB_list* dup = p;
	for (dup; dup!= NULL; dup = dup->link)
		{
			if (strcmp(temp.input_name, dup->name) == 0 || strcmp(temp.input_number, dup->number) == 0)
			{
				printf("�ߺ��� ����ڰ� �����մϴ�.\n");
					return true;
			}
		}
	return false;
}

bool check_form(person temp)
{
		if (strlen(temp.input_number) == 11)
		{
			return false;
		}
		else
		{
			printf("11�ڸ� �̸��� ��ȣ�� �Է��� �� �����ϴ�.\n");
			return true;
		}
}

void sort_list(PB_list* head)
{
	PB_list* temp = (PB_list*)malloc(sizeof(PB_list));
	PB_list* s_change;
	PB_list* s_change_1;

		for (s_change = head; s_change!= NULL; s_change = s_change->link)
		{
			for (s_change_1 = head->link; s_change_1 != NULL; s_change_1 = s_change_1->link)
			{
				if (strcmp(s_change->name, s_change_1->name) < 0)
				{
					strcpy(temp->name, s_change->name);
					strcpy(temp->number, s_change->number);
					strcpy(s_change->name, s_change_1->name);
					strcpy(s_change->number, s_change_1->number);
					strcpy(s_change_1->name, temp->name);
					strcpy(s_change_1->number, temp->number);
				}
			}
		}
	free(temp);
}

void Search_user(PB_list* head, person temp)
{
	bool user = false;
	PB_list* search = head;
	for (search; search != NULL; search = search->link)
	{
		if (strcmp(search->name, temp.input_name) == 0) //����� ����Ʈ���� ���� �̸��� ã���� ��
		{
			printf("%s ������� ��ȣ�� %s�Դϴ�.\n", temp.input_name, search->number);
			user = true;
		}

		else if (strcmp(search->number, temp.input_number) == 0)
		{
			printf("%s ��ȣ�� %s������� ��ȣ �Դϴ�.\n", temp.input_number, search->name);
			user = true;
		}
	}
	if (user != true)
	{
		printf("�ش� ����ڸ� ã�� ���߽��ϴ�.\n");
	}
}

void print_Book(PB_list* head)
{
	PB_list* p = head->link;
	for (p; p != NULL; p = p->link) //��� ���� ��忡�� ����Ͽ� �� ��尡 ���� �� ���� �ݺ��Ѵ�.
	{
		printf("�̸� : %s", p->name);
		printf("\n��ȣ : %s\n", p->number);
	}
}


void delete_user(PB_list* head, person temp)
{
	bool user = false;
	if (head->link == NULL) //ù �����Ϳ� ���� ���� ��� ����
	{
		return;
	}

	PB_list* ptemp;
	PB_list* remove;

	if (strcmp(head->name, temp.input_name) == 0) //ù ��尡 ���� ���� ��
	{
		remove = head;
		head = remove->link;
		printf("�����߽��ϴ�.");
		free(remove);
		user = true;
	}
	for (head; head->link != NULL; head = head->link)
	{
		ptemp = head;
		remove = head->link;
		if (strcmp(remove->name, temp.input_name) == 0) //����� ����Ʈ���� ���� �̸��� ã���� ��
		{
			if (remove->link != NULL) //�߰��� ����
			{
				ptemp = head;
				ptemp->link = remove->link;
				free(remove);
				printf("����ڸ� �����߽��ϴ�.\n");
				user = true;
				break;
			}
			else //�������� ����
			{
				ptemp->link = NULL;
				free(remove);
				printf("����ڸ� �����߽��ϴ�.\n");
				user = true;
				break;
			}
		}
	}
	if (user != true)
	{
		printf("�ش� ����ڰ� �������� �ʽ��ϴ�.\n");
	}
}

void change_userinfo(PB_list* head, person temp)
{
	int select;
	bool user = false;
	PB_list* search = head;
	for (head; head != NULL; head = head->link)
	{
		if (strcmp(temp.input_name, head->name) == 0)
		{
			user = true;
			printf("������ ������ ����ּ���.\n");
			printf("1. �̸� ���� / 2. ��ȣ ���� / 3. ��ü ����\n");
			scanf("%d", &select);
			switch (select)
			{
			case 1:
			{
				printf("������ �̸��� �Է����ּ���.\n");
				printf("�̸� >>");
				scanf("%s", temp.input_name);
				if (check_dp(head, temp)) {}
				else
				{
				strcpy(head->name, temp.input_name);
				printf("�̸� ������ �Ϸ�Ǿ����ϴ�.\n");
				sort_list(head);
				}
				break;
			}
			case 2 :
			{
				printf("������ ��ȣ�� �Է����ּ���.\n");
				printf("��ȣ >>");
				scanf("%s", temp.input_number);
				if (check_form(temp)) {}
				else
				{
					strcpy(head->number, temp.input_number);
					printf("��ȣ ������ �Ϸ�Ǿ����ϴ�.\n");
				}
				break;
			}
			case 3 :
			{
				printf("������ �̸��� ��ȣ�� �Է����ּ���.\n");
				printf("�̸� >>");
				scanf("%s", temp.input_name);
				printf("��ȣ >>");
				scanf("%s", temp.input_number);
				if (check_form(temp) || check_dp(head, temp)) {}
				else
				{
					strcpy(head->name, temp.input_name);
					strcpy(head->number, temp.input_number);
					printf("��ü ������ �Ϸ�Ǿ����ϴ�.\n");
					sort_list(head);
				}
				break;
			}
			default:
				scanf("%*c", &select); //�Է¹��� �ʱ�ȭ
				printf("�߸��� �Է��Դϴ�. �ٽ� �������ֽʽÿ�.\n");
				break;
			}
		}
	}
	if (user != true)
	{
		printf("�ش� ����ڰ� �������� �ʽ��ϴ�.\n");
	}
}

void free_mem(PB_list* head)
{
	PB_list* remove;
	while(head!= NULL)
	{
		remove = head->link;
		head->link = NULL;
		free(remove);
		head = head->link;
	}
	free(head);
}