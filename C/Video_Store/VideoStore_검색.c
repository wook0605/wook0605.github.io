#include "VideoStore_head.h"

void Search_User(Us_info* Ushead, in_data temp) //����� �˻� �Լ�
{
	bool user = true; //����� �����ϴ��� Ȯ���ϴ� ����
	Us_info* search = Ushead; 
	for (search; search != NULL; search = search->next) //����ڸ� ã�� �� ���� ����� ��� ��ȯ
	{
		if (strcmp(search->name, temp.input_Username) == 0) //����� ����Ʈ���� ���� �̸��� ã���� ��
		{
			if (strlen(search->borrow_video_1) == 0 && strlen(search->borrow_video_2) == 0 && strlen(search->borrow_video_3) == 0) // �뿩�ϰ� �ִ� ������ �ϳ��� ���� ��
			{
				printf("%s ����ڰ� ������ �ִ� ������ �����ϴ�.\n", search->name); 
				user = false;
			}
			else // NULL�� �ʱ�ȭ�Ͽ�, ȸ���� �������ִ� ������ ���ڿ��� 0�� �ƴϸ� �������ִ� ������ �ִ°�.
			{
				if (strlen(search->borrow_video_1) != 0) //����ڰ� ������ ������ ���� ��
				{
					if (strlen(search->borrow_video_2) != 0) //����ڰ� ������ ������ ���� ��
					{
						if (strlen(search->borrow_video_3) != 0)//����ڰ� ������ ������ ���� ��
						{
							printf("%s ����ڰ� ������ �ִ� ������ %s\t%s\t%s �Դϴ�.\n", search->name, search->borrow_video_1, search->borrow_video_2, search->borrow_video_3);
						}
						else //����ڰ� ������ 2���� ������ ���� ��
						{
							printf("%s ����ڰ� ������ �ִ� ������ %s\t%s �Դϴ�.\n", search->name, search->borrow_video_1, search->borrow_video_2);
						}
					}

					else //����ڰ� ������ 1���� ������ ���� ��
					{
						printf("%s ����ڰ� ������ �ִ� ������ %s �Դϴ�.\n", search->name, search->borrow_video_1);
					}
				}

				else if (strlen(search->borrow_video_2) != 0)
				{
					if (strlen(search->borrow_video_3) != 0) //����ڰ� ������ 2�� ������ ���� ��
					{
						printf("%s ����ڰ� �뿩�ϰ� �ִ� ������ %s\t%s\t �Դϴ�.\n", search->name, search->borrow_video_2, search->borrow_video_3);
					}
					else//����ڰ� ������ 1���� ������ ���� ��
					{
						printf("%s ����ڰ� �뿩�ϰ� �ִ� ������ %s\t�Դϴ�.\n", search->name, search->borrow_video_2);
					}
				}
				else //����ڰ� ������ 1���� ������ ���� ��
				{
					printf("%s����ڰ� �뿩�ϰ� �ִ� ������ %s�Դϴ�.\n", search->name, search->borrow_video_3);
				}
				user = false; //����ڰ� ������
			}

		}
	}
	if (user)
	{
		printf("�ش� ����ڸ� ã�� ���߽��ϴ�.\n");
	}
}

void Search_Video(Vd_info* Vdhead, in_data temp)
{
	bool Video = true; //���� ���� �Ǵ� ����
	Vd_info* search = Vdhead->next;
	for (search; search != NULL; search = search->next) //������ ã������ ���� ��� ��ȯ
	{
		if (strcmp(search->name, temp.input_Videoname) == 0) //����� ����Ʈ���� ���� �̸��� ã���� ��
		{
			printf("%s ��ǰ�� ����� %d / %d�̸�, ������ %d�Դϴ�.\n", search->name, search->number_of_Video, search->total_of_Video, search->price);
			Video = false; //������ ������
		}
	}
	if (Video)
	{
		printf("�ش� ��ǰ�� �������� �ʽ��ϴ�.\n");
	}
}