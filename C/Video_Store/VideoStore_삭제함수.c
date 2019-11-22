#include "VideoStore_head.h"

void delete_user(Us_info* Ushead, Vd_info* Vdhead, in_data temp)
{
	bool user = true;
	if (Ushead->next == NULL) //ù �����Ϳ� ���� ���� ��� ����
	{
		return;
	}

	Us_info* ptemp;
	Us_info* remove;
	if (strcmp(Ushead->name, temp.input_Username) == 0) //ù ��尡 ���� ���� ��
	{
		if (strlen(Ushead->borrow_video_1) == 0 && strlen(Ushead->borrow_video_2) == 0 && strlen(Ushead->borrow_video_3) == 0) //������ ������ ���� ������
		{
			remove = Ushead;
			Ushead = remove->next;
			free(remove); //����� ��� ����
			printf("�����߽��ϴ�.");
			user = false; //����ڸ� �߰�����.
		}
		else //������ �ϳ��� ������ ���� ��
		{
			Return_Video(Ushead, Vdhead, temp); //�ݳ� �Լ� ȣ��
			remove = Ushead;
			Ushead = remove->next;
			free(remove); //����� ����
			printf("�����߽��ϴ�.");
			user = false; //����ڸ� �߰�����
		}
	}
	for (Ushead; Ushead->next != NULL; Ushead = Ushead->next)// ������ ����ڸ� ã�� ���� ����� ��� ��ȯ
	{
		ptemp = Ushead;
		remove = Ushead->next;
		if (strcmp(remove->name, temp.input_Username) == 0) //����� ����Ʈ���� ���� �̸��� ã���� ��
		{
			if (remove->next != NULL) //�߰��� ����
			{
				if (strlen(Ushead->borrow_video_1) == 0 && strlen(Ushead->borrow_video_2) == 0 && strlen(Ushead->borrow_video_3) == 0) //������ ������ ���� ������
				{
					ptemp = Ushead;
					ptemp->next = remove->next;
					free(remove); //����� ����
					printf("����ڸ� �����߽��ϴ�.\n");
					user = false; //����ڸ� �߰�����
					break;
				}
				else //������ �ϳ��� ������ ���� ��
				{
					Return_Video(Ushead, Vdhead, temp); // �ݳ� �Լ� ȣ��
					ptemp = Ushead;
					ptemp->next = remove->next;
					free(remove); //����� ����
					printf("����ڸ� �����߽��ϴ�.\n");
					user = false;//����ڸ� �߰�����
					break;
				}
			}
			else //�������� ����
			{
				if (strlen(Ushead->borrow_video_1) == 0 && strlen(Ushead->borrow_video_2) == 0 && strlen(Ushead->borrow_video_3) == 0) //������ ������ ���� ������
				{
					ptemp->next = NULL;
					free(remove);//����� ����
					printf("����ڸ� �����߽��ϴ�.\n");
					user = false;//����ڸ� �߰�����
					break;
				}
				else//������ �ϳ��� ������ ���� ��
				{
					Return_Video(Ushead, Vdhead, temp); //�ݳ��Լ� ȣ��
					ptemp->next = NULL;
					free(remove);//����� ����
					printf("����ڸ� �����߽��ϴ�.\n");
					user = false;//����ڸ� �߰�����
					break;
				}
			}
		}
	}
	if (user) //�����޽���
	{
		printf("�ش� ����ڰ� �������� �ʽ��ϴ�.\n");
	}
}

void delete_Video(Vd_info* Vdhead, Us_info* Ushead, in_data temp)
{
	bool Video = true;
	if (Vdhead->next == NULL) //ù �����Ϳ� ���� ���� ��� ����
	{
		return;
	}

	Vd_info* ptemp;
	Vd_info* remove;

	if (strcmp(Vdhead->name, temp.input_Videoname) == 0) //ù ��尡 ���� ���� ��
	{
		if (Vdhead->number_of_Video == Vdhead->total_of_Video) // �ش� ������ �ƹ��� ������ ���� ���� ��
		{
			remove = Vdhead;
			Vdhead = remove->next;
			free(remove);//���� ��� ����
			printf("�����߽��ϴ�.");
			Video = false; //���� �߰�
		}
		else //������ �ش� ������ ������ ���� ��
		{
			for (Ushead; Ushead != NULL; Ushead = Ushead->next) //����� ��� ��ȯ
			{
				if (strcmp(Ushead->borrow_video_1, Vdhead->name) == 0) // ������ ������ �ִ� ����ڸ� ã���� ��
				{
					memset(Ushead->borrow_video_1, NULL, sizeof(Ushead->borrow_video_1)); //�뿩�ѵ� �ʱ�ȭ
					remove = Vdhead;
					Vdhead = remove->next;
					free(remove);//���� ��� ����
					printf("�����߽��ϴ�.");
					Video = false;//���� �߰�
				}
				else if (strcmp(Ushead->borrow_video_2, Vdhead->name) == 0)// ������ ������ �ִ� ����ڸ� ã���� ��
				{
					memset(Ushead->borrow_video_2, NULL, sizeof(Ushead->borrow_video_2)); //�뿩�ѵ� �ʱ�ȭ
					remove = Vdhead;
					Vdhead = remove->next;
					free(remove);//���� ��� ����
					printf("�����߽��ϴ�.");
					Video = false;//���� �߰�
				}
				else if (strcmp(Ushead->borrow_video_3, Vdhead->name) == 0)// ������ ������ �ִ� ����ڸ� ã���� ��
				{
					memset(Ushead->borrow_video_3, NULL, sizeof(Ushead->borrow_video_3)); //�뿩�ѵ� �ʱ�ȭ
					remove = Vdhead;
					Vdhead = remove->next;
					free(remove);//���� ��� ����
					printf("�����߽��ϴ�.");
					Video = false;//���� �߰�
				}
			}
		}
	}
	for (Vdhead; Vdhead != NULL; Vdhead = Vdhead->next) //������ ������ ã�� ���� ���� ��� ��ȯ
	{
		ptemp = Vdhead;
		remove = Vdhead->next;
		if (strcmp(remove->name, temp.input_Videoname) == 0) //����� ����Ʈ���� ���� �̸��� ã���� ��
		{
			if (remove->next != NULL) //�߰��� ����
			{
				if (remove->number_of_Video == remove->total_of_Video) // �ش� ������ �ƹ��� ������ ���� ���� ��
				{
					ptemp = Vdhead;
					ptemp->next = remove->next; // ������ ��� ������ ����� ������ ��� ������ ��带 ������ ���������ʵ�����.
					free(remove); //�����Ǵ� �κ�
					printf("������ �����߽��ϴ�.\n");
					Video = false; //���� �߰�
					break;
				}
				else// �ش� ���� �ϳ��� ������ �ִ� ���
				{
					for (Ushead; Ushead != NULL; Ushead = Ushead->next) //������ �������ִ� ����ڸ� ã�� ���� ��ȯ
					{
						if (strcmp(Ushead->borrow_video_1, remove->name) == 0) //�ش� ������ ������ �ִ� ����ڸ� ã���� ��
						{
							memset(Ushead->borrow_video_1, NULL, sizeof(Ushead->borrow_video_1)); //�뿩���� �ݳ�
							ptemp = Vdhead;
							ptemp->next = remove->next; // ������ ��� ������ ����� ������ ��� ������ ��带 ������ ���������ʵ�����.
							free(remove); //�����Ǵ� �κ�
							printf("������ �����߽��ϴ�.\n");
							Video = false;//���� �߰�
							break;
						}
						else if (strcmp(Ushead->borrow_video_2, remove->name) == 0) //�ش� ������ ������ �ִ� ����ڸ� ã���� ��
						{
							memset(Ushead->borrow_video_2, NULL, sizeof(Ushead->borrow_video_2));//�뿩���� �ݳ�
							ptemp = Vdhead;
							ptemp->next = remove->next; // ������ ��� ������ ����� ������ ��� ������ ��带 ������ ���������ʵ�����.
							free(remove); //�����Ǵ� �κ�
							printf("������ �����߽��ϴ�.\n");
							Video = false;//���� �߰�
							break;
						}
						else if (strcmp(Ushead->borrow_video_3, remove->name) == 0) //�ش� ������ ������ �ִ� ����ڸ� ã���� ��
						{
							memset(Ushead->borrow_video_3, NULL, sizeof(Ushead->borrow_video_3));//�뿩���� �ݳ�
							ptemp = Vdhead;
							ptemp->next = remove->next; // ������ ��� ������ ����� ������ ��� ������ ��带 ������ ���������ʵ�����.
							free(remove); //�����Ǵ� �κ�
							printf("������ �����߽��ϴ�.\n");
							Video = false;//���� �߰�
							break;
						}
					}
				}

			}
			else //�������� ����
			{
				if (remove->number_of_Video == remove->total_of_Video) // �ش� ������ �ƹ��� ������ ���� ���� ��
				{
					ptemp->next = NULL;
					free(remove); // ���� ����
					printf("������ �����߽��ϴ�.\n");
					Video = false;//���� �߰�
					break;
				}

				else
				{
					for (Ushead; Ushead != NULL; Ushead = Ushead->next)
					{
						if (strcmp(Ushead->borrow_video_1, remove->name) == 0) //�ش� ������ ������ �ִ� ����ڸ� ã���� ��
						{
							memset(Ushead->borrow_video_1, NULL, sizeof(Ushead->borrow_video_1));//�뿩���� �ݳ�
							ptemp->next = NULL;
							free(remove); // ���� ����
							printf("������ �����߽��ϴ�.\n");
							Video = false;//���� �߰�
							break;
						}
						else if (strcmp(Ushead->borrow_video_2, remove->name) == 0) //�ش� ������ ������ �ִ� ����ڸ� ã���� ��
						{
							memset(Ushead->borrow_video_2, NULL, sizeof(Ushead->borrow_video_2));//�뿩���� �ݳ�
							ptemp->next = NULL;
							free(remove); // ���� ����
							printf("������ �����߽��ϴ�.\n");
							Video = false;//���� �߰�
							break;
						}
						else if (strcmp(Ushead->borrow_video_3, remove->name) == 0) //�ش� ������ ������ �ִ� ����ڸ� ã���� ��
						{
							memset(Ushead->borrow_video_3, NULL, sizeof(Ushead->borrow_video_3));//�뿩���� �ݳ�
							ptemp->next = NULL;
							free(remove); // ���� ����
							printf("������ �����߽��ϴ�.\n");
							Video = false;//���� �߰�
							break;
						}
					}
				}
			}
		}
	}
	if (Video)
	{
		printf("�ش� ������ �������� �ʽ��ϴ�.\n");
	}
}