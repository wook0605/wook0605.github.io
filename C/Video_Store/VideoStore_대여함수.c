#include "VideoStore_head.h"

void Borrow_Video(Us_info* Ushead, Vd_info* Vdhead, in_data temp)
{
	Us_info* Us_list = Ushead->next;
	bool user = true; // true�� ���������ʴ°�, false�� �����ϴ°�
	Vd_info* Vd_list = Vdhead->next;
	bool video = true; // true�� ���������ʴ°�, false�� �����ϴ°�
	int cash = 0;

	for (Us_list; Us_list != NULL; Us_list = Us_list->next) //����ڸ� ã������ ��� ��� ��ȯ
	{
		if (strcmp(Us_list->name, temp.input_Username) == 0) // ����� ã���� ��
		{
			user = false; //����ڰ� ������
			for (Vd_list; Vd_list != NULL; Vd_list = Vd_list->next) //����ڸ� ã���� �뿩�� ������ ã�´�.
			{
				if (strcmp(Vd_list->name, temp.input_Videoname) == 0) //�뿩�� ������ ã����, �ش� ������ ���� ���̰�, ������� borrow_Video�� �̸��� �ִ´�.
				{
					video = false; //������ �����Ѵ�.
					if (Vd_list->number_of_Video == 0) //������ ��� ���� ��
					{
						video = true; //������ ������������.
					}
					else //������ ��� ���� ��
					{
						cash = Us_list->Money - Vd_list->price; //�ܾ� Ȯ��
						if (strcmp(Us_list->borrow_video_1, Vd_list->name) == 0 || strcmp(Us_list->borrow_video_2, Vd_list->name) == 0 || strcmp(Us_list->borrow_video_3, Vd_list->name) == 0)
						{ //�Ȱ��� ������ ���� ��
							printf("�ش� ������ �̹� ������ �ֽ��ϴ�.\n");
							return; //��� ����
						}
						else if (strlen(Us_list->borrow_video_1) == 0) // ������ ������ ���� ���� ����
						{
							if (Us_list->Money > Vd_list->price || cash >= 0) //������ �ִ� �ݾ��� ������ ���ݺ��� ũ��, �� ���̰� 0�̻��϶�
							{
								strcpy(Us_list->borrow_video_1, Vd_list->name); // ���� �뿩
								Vd_list->number_of_Video -= 1; // ������ ��� ���δ�
								printf("������ �뿩�߽��ϴ�.\n");
								Us_list->Money -= Vd_list->price; // ���� �ݾ׿��� ����� ����.
								return; //��� ����
							}
							else //�ܾ��� ���ڸ� ���
							{
								printf("�ܾ��� ���ڶ��ϴ�. ĳ�ø� �������ּ���.\n");
								return;//��� ����
							}
						}
						else if (strlen(Us_list->borrow_video_2) == 0) // ������ ������ ���� ���� ����
						{
							if (Us_list->Money > Vd_list->price || cash >= 0) //������ �ִ� �ݾ��� ������ ���ݺ��� ũ��, �� ���̰� 0�̻��϶�
							{
								strcpy(Us_list->borrow_video_2, Vd_list->name); //���� �뿩
								Vd_list->number_of_Video -= 1; //������ ��� ���δ�.
								printf("������ �뿩�߽��ϴ�.\n");
								Us_list->Money -= Vd_list->price; // ���� �ݾ׿��� ����� ����.
								return; //��� ����
							}
							else //�ܾ��� ���ڸ� ���
							{
								printf("�ܾ��� ���ڶ��ϴ�. ĳ�ø� �������ּ���.\n");
								return;//��� ����
							}

						}
						else if (strlen(Us_list->borrow_video_3) == 0) //������ ������ ���� ���� ����
						{
							if (Us_list->Money > Vd_list->price || cash >= 0) //������ �ִ� �ݾ��� ������ ���ݺ��� ũ��, �� ���̰� 0�̻��϶�
							{
								strcpy(Us_list->borrow_video_3, Vd_list->name); //���� �뿩
								Vd_list->number_of_Video -= 1; //������ �� ��� ���δ�.
								printf("������ �뿩�߽��ϴ�.\n");
								Us_list->Money -= Vd_list->price; // ���� �ݾ׿��� ����� ����.
								return; //��� ����
							}
							else // �ܾ��� ���ڸ� ���
							{
								printf("�ܾ��� ���ڶ��ϴ�. ĳ�ø� �������ּ���.\n");
								return;//��� ����
							}
						}
						else //����ڰ� ���� �� �ִ� �ѵ��� �Ѿ����
						{
							printf("�ش� ����ڴ� �뿩 �ѵ��� ����á���ϴ�.\n");
						}
					}
				}
			}
		}
	}

	if (user)
	{
		printf("�ش� ����ڴ� �������� �ʽ��ϴ�.\n");
	}
	if (video)
	{
		printf("�ش� ��ǰ�� �������� �ʽ��ϴ�.\n");
	}
}