#include "VideoStore_head.h"

void sort_Uslist(Us_info* Ushead) //����� ���� (��������)
{
	Us_info* temp = (Us_info*)malloc(sizeof(Us_info)); //�����͸� �ű� �� ����� �ӽ� ��� ����
	Us_info* s_change;
	Us_info* s_change_1;

	for (s_change = Ushead; s_change != NULL; s_change = s_change->next) //����� ��� ��ȯ(��� ������)
	{
		for (s_change_1 = Ushead->next; s_change_1 != NULL; s_change_1 = s_change_1->next) //����� ��� ��ȯ(�����  ����������)
		{
			if (strcmp(s_change->name, s_change_1->name) < 0) //s_change�� �̸��� s_change_1�� �̸����� �ƽ�Ű �ڵ� ���� ���� ��
			{
				strcpy(temp->name, s_change->name); //�ӽó�忡 ������ ����
				strcpy(temp->phone_number, s_change->phone_number); //�ӽó�忡 ������ ����
				temp->Money = s_change->Money; //�ӽó�忡 ������ ����
				strcpy(temp->borrow_video_1, s_change->borrow_video_1); //�ӽó�忡 ������ ����
				strcpy(temp->borrow_video_2, s_change->borrow_video_2); //�ӽó�忡 ������ ����
				strcpy(temp->borrow_video_3, s_change->borrow_video_3); //�ӽó�忡 ������ ����

				strcpy(s_change->name, s_change_1->name); // �Ű��� ������
				strcpy(s_change->phone_number, s_change_1->phone_number); // �Ű��� ������
				s_change->Money = s_change_1->Money; // �Ű��� ������
				strcpy(s_change->borrow_video_1, s_change_1->borrow_video_1); // �Ű��� ������
				strcpy(s_change->borrow_video_2, s_change_1->borrow_video_2); // �Ű��� ������
				strcpy(s_change->borrow_video_3, s_change_1->borrow_video_3); // �Ű��� ������

				strcpy(s_change_1->name, temp->name); //�ӽ� ��忡 ����� ������ �ű��
				strcpy(s_change_1->phone_number, temp->phone_number); //�ӽ� ��忡 ����� ������ �ű��
				s_change_1->Money = temp->Money; //�ӽ� ��忡 ����� ������ �ű��
				strcpy(s_change_1->borrow_video_1, temp->borrow_video_1); //�ӽ� ��忡 ����� ������ �ű��
				strcpy(s_change_1->borrow_video_2, temp->borrow_video_2); //�ӽ� ��忡 ����� ������ �ű��
				strcpy(s_change_1->borrow_video_3, temp->borrow_video_3); //�ӽ� ��忡 ����� ������ �ű��
			}
		}
	}
	free(temp); //�ӽó�� ����
}


void sort_Vdlist(Vd_info* Vdhead) //���� ���� (��������)
{
	Vd_info* temp = (Vd_info*)malloc(sizeof(Vd_info)); //�����͸� �ű� �� ����� �ӽ� ��� ����
	Vd_info* s_change;
	Vd_info* s_change_1;

	for (s_change = Vdhead; s_change != NULL; s_change = s_change->next)//���� ��� ��ȯ(��������)
	{
		for (s_change_1 = Vdhead->next; s_change_1 != NULL; s_change_1 = s_change_1->next) //���� ��� ��ȯ(����� ���� ������)
		{
			if (strcmp(s_change->name, s_change_1->name) < 0)//s_change�� �̸��� s_change_1�� �̸����� �ƽ�Ű �ڵ� ���� ���� ��
			{
				strcpy(temp->name, s_change->name); //�ӽó�忡 ������ ����
				temp->price = s_change->price; //�ӽ� ��忡 ������ ����
				temp->number_of_Video = s_change->number_of_Video; //�ӽ� ��忡 ������ ����
				temp->total_of_Video = s_change->total_of_Video; //�ӽ� ��忡 ������ ����

				strcpy(s_change->name, s_change_1->name); //�Ű��� ������
				s_change->price = s_change_1->price; //�Ű��� ������
				s_change->number_of_Video = s_change_1->number_of_Video; //�Ű��� ������
				s_change->total_of_Video = s_change_1->total_of_Video; //�Ű��� ������
				
				strcpy(s_change_1->name, temp->name); //�ӽ� ��忡 ����� ������ �ű��
				s_change_1->price = temp->price; //�ӽ� ��忡 ����� ������ �ű��
				s_change_1->number_of_Video = temp->number_of_Video; //�ӽ� ��忡 ����� ������ �ű��
				s_change_1->total_of_Video = temp->total_of_Video; //�ӽ� ��忡 ����� ������ �ű��
			}
		}
	}
	free(temp); //�ӽó�� ����
}


void change_info(Us_info* Ushead, Vd_info* Vdhead, in_data temp) //���� ����
{
	int select, menu, num;
	bool user = true;
	bool video = true;
	Us_info* search_user = Ushead;
	Vd_info* search_video = Vdhead;
	
	printf("������ ������ �������ֽʽÿ�.\n");
	printf("1 : ���� ���� ����\t2 : ����� ���� ����\n");
	scanf("%d", &menu); //�޴� ����1

	switch (menu)
	{
	case 1:
	{
		printf("� ������ �����ұ��?\n");
		printf("1. ���� ��� ����\t2. ���� ���� ����\n");
		scanf("%d", &select); //�޴� ����2
		switch (select)
		{
		case 1 :
		{
			printf("��� ������ ������ �̸��� �Է����ּ���\n");
			scanf("%s", temp.input_Username); //���� �̸� �Է�
			for (search_video; search_video != NULL; search_video = search_video->next) //�Էµ� ������ ã�� ���� �ݺ�
			{
				if (strcmp(temp.input_Videoname, search_video->name) == 0) //�Էµ� ������ ã���� ��
				{
					if (search_video->number_of_Video == search_video->total_of_Video) //������ ������ �ִ� ���°� �ƴ� ��
					{
						video = false; //���� �߰�
						printf("������ �������ֽʽÿ�.\n");
						scanf("%d", &search_video->number_of_Video); //���� ���� ����
						search_video->total_of_Video = search_video->number_of_Video; //���� ���� ����
						break;
					}

					else //������ ������ �ִ� ������ ��
					{
						num = search_video->total_of_Video - search_video->number_of_Video; //�� �������� ���� ������ �� ���� �����Ѵ�.
						video = false; //���� �߰�
						printf("������ �������ֽʽÿ�.\n");
						scanf("%d", &search_video->number_of_Video); //���� ���� ����
						search_video->total_of_Video = search_video->number_of_Video + num; //������ �ٲ� ��, �� ������ ���̸� ���Ѵ�.
						break;
					}

				}
			}
			break;
		}
		case 2 : 
		{
			printf("������ ������ ������ �̸��� �Է����ּ���\n");
			scanf("%s", temp.input_Username); //���� �̸� �Է�
			for (search_video; search_video != NULL; search_video = search_video->next) //�Էµ� ������ ã�� ���� �ݺ�
			{
				if (strcmp(temp.input_Videoname, search_video->name) == 0) //������ ã���� ��
				{
					video = false; //���� �߰�
					printf("������ ������ �Է����ּ���\n");
					scanf("%d", &search_video->price); //���� ���� ����
					printf("����� ������ %d �Դϴ�.", search_video->price); //���� ���� ���
					break;
				}
			}
			break;
		}
		default:
		{
			scanf("%*c", &select); // �Է¹��� �ʱ�ȭ
			video = false;
			printf("�߸��� �Է��Դϴ�.\n");
			break;
		}
		}

		if (video) //�ݺ��� ���� ���� �ѹ��� ����ϱ� ���ؼ�
		{
			printf("�ش� ��ǰ�� �������� �ʽ��ϴ�.\n");
		}
		break;
	}

	case 2:
	{
		printf("������ ������� �̸��� �Է����ּ���\n");
		scanf("%s", temp.input_Username); //����� �̸� �Է�
		for (search_user; search_user != NULL; search_user = search_user->next) //����� �̸� ã�� ���� �ݺ�
		{
			if (strcmp(temp.input_Username, search_user->name) == 0) // ����� �̸� ã���� ��
			{
				user = false; //����� �߰�
				printf("�޴��� �����Ͻʽÿ�.\n");
				printf("1 : �̸�����\t2 : ��ȣ����\t3 : �̸�/��ȣ ����\n");
				scanf("%d", &select); //�޴� ����2
				switch (select)
				{
				case 1:
				{
					printf("������ �̸��� �Է����ּ���.\n");
					printf("�̸� >>");
					scanf("%s", temp.input_Username); //����� �̸� �Է�
					if (check_Userdp(search_user, temp)) {} //���� �Էµ� �̸��� �ߺ��� �� �Է����� ����.
					else //�ߺ��� �ƴ� ��
					{
						strcpy(search_user->name, temp.input_Username); //����� �̸� ����
						printf("�̸� ������ �Ϸ�Ǿ����ϴ�.\n");
						sort_Uslist(Ushead); //����� �̸� ����
					}
					break;
				}
				case 2:
				{
					printf("������ ��ȣ�� �Է����ּ���.\n");
					printf("��ȣ >>");
					scanf("%s", temp.input_phoneNumber); //������ �ڵ��� ��ȣ �Է�
					if (check_form(temp)) {} //�Է��� ��ȣ�� ���¿� ���� ���� ��� �Է� ����
					else//�Է��� �ڵ��� ��ȣ�� ���¿� �´� ���
					{
						strcpy(search_user->phone_number, temp.input_phoneNumber); //�ڵ��� ��ȣ ����
						printf("��ȣ ������ �Ϸ�Ǿ����ϴ�.\n");
					}
					break;
				}
				case 3:
				{
					printf("������ �̸��� ��ȣ�� �Է����ּ���.\n");
					printf("�̸� >>");
					scanf("%s", temp.input_Username); //������ �̸� �Է�
					printf("��ȣ >>");
					scanf("%s", temp.input_phoneNumber); //������ ��ȣ �Է�
					if (check_form(temp) || check_Userdp(search_user, temp)) {} //����� �̸��� �ߺ��̰ų� ��ȣ�� ���¿� ���� �ʴ� ��� �Է����� ����
					else // ����� ������ ������ ���������
					{
						strcpy(search_user->name, temp.input_Username); //����� �̸� ����
						strcpy(search_user->phone_number, temp.input_phoneNumber); //����� ��ȣ ����
						printf("��ü ������ �Ϸ�Ǿ����ϴ�.\n");
						sort_Uslist(Ushead); //����� �̸� ����
					}
					break;
				}
				default:
				{
					scanf("%*s", &select); //�Է¹��� �ʱ�ȭ
					user = false;
					printf("�߸��� �Է��Դϴ�.\n");
					break;
				}

				}
			}
		}
		break;
	}
	default:
	{
		scanf("%*c", &menu); //�Է¹��� �ʱ�ȭ
		printf("�߸��� �Է��Դϴ�.\n");
		break;
	}
	if (user)

	{
		printf("�ش� ����ڰ� �������� �ʽ��ϴ�.\n");
	}
	}

}