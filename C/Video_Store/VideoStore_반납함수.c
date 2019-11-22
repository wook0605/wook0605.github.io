#include "VideoStore_head.h"

void Return_Video(Us_info* Ushead, Vd_info* Vdhead, in_data temp)
{
	Us_info* Us_list = Ushead;
	bool user = true; // true�� ���������ʴ°�, false�� �����ϴ°�
	Vd_info* Vd_list = Vdhead;
	bool video = true; // true�� ���������ʴ°�, false�� �����ϴ°�

	int return_menu;
	printf("1 : �ѹ��� �ݳ��ϱ�.\n");
	printf("2 : �ϳ��� �ݳ��ϱ�.\n");
	
	printf("�޴� ����>>");
	scanf("%d", &return_menu); //�޴� ����

	switch (return_menu)
	{
	case 1: //�ѹ��� ��� �ݳ��ϴ� �޴�
	{
		for (Us_list; Us_list != NULL; Us_list = Us_list->next) // �̸��� ã�� ���� �ݺ�
		{
			if (strcmp(Us_list->name, temp.input_Username) == 0) // �̸��� ã���� ��
			{
				user = false;
				for (Vd_list; Vd_list != NULL; Vd_list = Vd_list->next) //������ ã�� ���� �ݺ�
				{
						if (strcmp(Us_list->borrow_video_1, Vd_list->name) == 0) // ������ ������ ã���� ��
						{
							video = false;//���� ����
							memset(&Us_list->borrow_video_1, NULL, sizeof(Us_list->borrow_video_1)); // ���� �ݳ�
							Vd_list->number_of_Video += 1; //������ �� ��� ����
							printf("������ �ݳ��߽��ϴ�.\n");
						}

						else if (strcmp(Us_list->borrow_video_2, Vd_list->name) == 0) // ������ ������ ã���� ��
						{
							video = false;//���� ����
							memset(&Us_list->borrow_video_2, NULL, sizeof(Us_list->borrow_video_2)); // ���� �ݳ�
							Vd_list->number_of_Video += 1;//������ �� ��� ����
							printf("������ �ݳ��߽��ϴ�.\n");
						}

						else if (strcmp(Us_list->borrow_video_3, Vd_list->name) == 0)// ������ ������ ã���� ��
						{
							video = false;//���� ����
							memset(&Us_list->borrow_video_3, NULL, sizeof(Us_list->borrow_video_3)); // ���� �ݳ�
							Vd_list->number_of_Video += 1;//������ �� ��� ����
							printf("������ �ݳ��߽��ϴ�.\n");
						}
				}
			}
		}
		break;
	}
	case 2:
	{
		printf("�ݳ��� ��ǰ���� �Է����ּ���.\n");
		scanf("%s", temp.input_Videoname); //�ݳ��� ���� �̸� �Է�
		for (Us_list; Us_list != NULL; Us_list = Us_list->next) //������ ������ �ִ� ����ڸ� ã�� ���� ����� ��� ��ȯ
		{
			if (strcmp(Us_list->name, temp.input_Username) == 0) //������ ������ �ִ� ����ڸ� ã���� ��
			{
				user = false;
				for (Vd_list; Vd_list != NULL; Vd_list = Vd_list->next) //���� ��� ��ȯ
				{
					if (strcmp(Vd_list->name, temp.input_Videoname) == 0) //����ڰ� ������ �ִ� ������ �Է��� ������ ������
					{
						if (strcmp(Us_list->borrow_video_1, temp.input_Videoname) == 0) // ������ ������ ã���� ��
						{
							video = false;//���� ����
							memset(&Us_list->borrow_video_1, NULL, sizeof(Us_list->borrow_video_1)); //�뿩�ѵ� ����
							Vd_list->number_of_Video += 1; //������ �ݳ��Ͽ� ���� ���� ��� ����
							printf("������ �ݳ��߽��ϴ�.\n");
							return; //��� ����
						}
						else if (strcmp(Us_list->borrow_video_2, temp.input_Videoname) == 0) // ������ ������ ã���� ��
						{
							video = false;//���� ����
							memset(&Us_list->borrow_video_2, NULL, sizeof(Us_list->borrow_video_2));//�뿩�ѵ� ����
							Vd_list->number_of_Video += 1;//������ �ݳ��Ͽ� ���� ���� ��� ����
							printf("������ �ݳ��߽��ϴ�.\n");
							return;//��� ����
						}
						else if (strcmp(Us_list->borrow_video_3, temp.input_Videoname) == 0) // ������ ������ ã���� ��
						{
							video = false;//���� ����
							memset(&Us_list->borrow_video_3, NULL, sizeof(Us_list->borrow_video_3));//�뿩�ѵ� ����
							Vd_list->number_of_Video += 1;//������ �ݳ��Ͽ� ���� ���� ��� ����
							printf("������ �ݳ��߽��ϴ�.\n");
							return;// ��� ����
						}
					}
				}
			}
		}
		break;
	}
	default:
	{
		scanf("%*c", &return_menu); //�Է¹��� �ʱ�ȭ
		printf("�߸��� �޴��Դϴ�.\n");
		user = false; //��� ����
		video = false; //��� ����
	}
		break;
	}
	if (user)// �����޽���
	{
		printf("�ش� ����ڴ� �������� �ʽ��ϴ�.\n");
	}
	if (video)//�����޽���
	{
		printf("�ش� ��ǰ�� �������� �ʰų�, ���� ������ ���� ������Դϴ�.\n");
	}
}