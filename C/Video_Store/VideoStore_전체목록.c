#include "VideoStore_head.h"

void print_AllUser(Us_info* Ushead)
{
	Us_info* up = Ushead->next;
	for (up; up != NULL; up = up->next) //����� ��� ��ȯ
	{
		printf("����� �̸� : %s\n", up->name);
		printf("����� �ڵ��� ��ȣ : %s\n", up->phone_number);
		if (strlen(up->borrow_video_1) == 0 && strlen(up->borrow_video_2) == 0 && strlen(up->borrow_video_3) == 0) //�뿩�ѵ��� ����ִ� ������ ��
		{
			printf("�뿩�ϰ� �ִ� ������ �����ϴ�.\n");
		}
		else //�뿩 �ѵ��� �ϳ��� ������� ���
		{
			if (strlen(up->borrow_video_1) != 0) // �뿩�ϰ� �ִ� ������ ������
			{
				if (strlen(up->borrow_video_2) != 0)// �뿩�ϰ� �ִ� ������ ������ 
				{
					if (strlen(up->borrow_video_3) != 0)// �뿩�ϰ� �ִ� ������ ������
					{
						printf("�뿩�ϰ� �ִ� ������ %s,%s,%s �Դϴ�.\n", up->borrow_video_1, up->borrow_video_2, up->borrow_video_3);
					}
					else
					{
						printf("�뿩�ϰ� �ִ� ������ %s,%s �Դϴ�.\n", up->borrow_video_1, up->borrow_video_2);
					}
				}

				else
				{
					printf("�뿩�ϰ� �ִ� ������ %s �Դϴ�.\n", up->borrow_video_1);
				}
			}

			else if (strlen(up->borrow_video_2) != 0) // �뿩�ϰ� �ִ� ������ ������
			{
				if (strlen(up->borrow_video_3) != 0) // �뿩�ϰ� �ִ� ������ ������
				{
					printf("����ڰ� �뿩�ϰ� �ִ� ������ %s,%s �Դϴ�.\n", up->borrow_video_2, up->borrow_video_3);
				}
				else
				{
					printf("����ڰ� �뿩�ϰ� �ִ� ������ %s �Դϴ�.\n", up->borrow_video_2);
				}
			}
			else 
			{
				printf("����ڰ� �뿩�ϰ� �ִ� ������ %s �Դϴ�.\n", up->borrow_video_3);
			}
		}
		printf("���� ������ ĳ�� : %d\n", up->Money);
	}
}

void print_AllVideo(Vd_info* Vdhead)
{
	Vd_info* vp = Vdhead->next;
	for (vp; vp != NULL; vp = vp->next) //������� ��ȯ
	{
		printf("���� �̸� : %s\n", vp->name);
		printf("���� ���� : %d\n", vp->price);
		printf("���� ����(���簳�� / �� ����) : %d/%d\n", vp->number_of_Video,vp->total_of_Video);
	}
}