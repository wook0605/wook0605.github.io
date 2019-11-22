#include "VideoStore_head.h"

void Add_Video(Vd_info* Vdinput, in_data temp)
{
	Vd_info* vp = (Vd_info*)malloc(sizeof(Vd_info)); // �����͸� ������ ��忡 �޸� �Ҵ�
	memset(vp, NULL, sizeof(Vd_info));
	
	if (Vdinput->next == NULL) //ù ������ ������ ��
	{
		strcpy(vp->name, temp.input_Videoname); //�̸� �Է�
		vp->price = temp.Money; // ���� ���� �Է�
		vp->number_of_Video = temp.number; // ���� ���� �Է�
		vp->total_of_Video = temp.number;//���� �ѷ� �Է�
		vp->next = Vdinput->next; //��� ����
		Vdinput->next = vp; //��� ����
	}

	else // ù �����ͻ��� ������ ��
	{
		if (check_Videodp(Vdinput, temp)) // �ߺ�üũ�Լ� : false (�ߺ� �ƴ�) true (�ߺ�)  
		{
			free(vp); // �ߺ��̱� ������ ��尡 �ʿ��� ���� ���� ��� ����
			for (Vdinput; Vdinput != NULL; Vdinput = Vdinput->next)
			{
				if (strcmp(Vdinput->name, temp.input_Videoname) == 0)
				{
					Vdinput->number_of_Video += temp.number; // �ߺ��� ������ ������ �÷��ش�.
					Vdinput->total_of_Video += temp.number; // �� ���� ���� �÷��ش�
				}
			}
		}

		else
		{
			strcpy(vp->name, temp.input_Videoname); //�̸� �Է�
			vp->price = temp.Money; // ���� �Է�
			vp->number_of_Video = temp.number; //���� ���� �Է�
			vp->total_of_Video = temp.number; //�� ���� �Է�
			vp->next = Vdinput->next; //��� ����
			Vdinput->next = vp; //��� ����
			sort_Vdlist(Vdinput); //���� �̸������� ����
		}
	}
}

void Add_user(Us_info* Usinput, in_data temp)
{
	if (Usinput->next == NULL) //ù ������ ������ ��
	{
		if (check_form(temp)) //�ڵ��� ��ȣ�� 11�ڸ� �̸��� �� �Է����� ����
		{
			
		}

		else
		{
			Us_info* up = (Us_info*)malloc(sizeof(Us_info)); // �����͸� ������ ��忡 �޸� �Ҵ�
			memset(up, NULL, sizeof(Us_info)); // ��� NULL�� �ʱ�ȭ
			strcpy(up->phone_number, temp.input_phoneNumber); //��ȣ �Է�
			strcpy(up->name, temp.input_Username); //�̸� �Է�
			up->next = Usinput->next; //��� ����
			Usinput->next = up; //��� ����
		}
	}

	else //ù ������ ���� ����
	{
		if (check_form(temp) || check_Userdp(Usinput, temp)) // �ߺ�üũ�Լ� : false (�ߺ� �ƴ�) true (�ߺ�)  
		{

		}
		else
		{
			Us_info* up = (Us_info*)malloc(sizeof(Us_info)); // �����͸� ������ ��忡 �޸� �Ҵ�
			memset(up, NULL, sizeof(Us_info)); //��� NULL�� �ʱ�ȭ
			strcpy(up->phone_number, temp.input_phoneNumber); //��ȣ �Է�
			strcpy(up->name, temp.input_Username); //�̸� �Է�
			up->next = Usinput->next; //��� ����
			Usinput->next = up;
			sort_Uslist(Usinput);

		}
	}
}

void Cash_Recharge(Us_info* Ushead, in_data temp)
{
	int menu;
	for (Ushead; Ushead != NULL; Ushead = Ushead->next) //����� ��� ��ȯ
	{
		if (strcmp(Ushead->name, temp.input_Username) == 0) //����ڸ� ã���� ��
		{
				printf("�󸶸� �����Ͻðڽ��ϱ�?\n");
				printf("1. 1000��\t2. 2000��\t3. 3000��\t 4. 5000��\t 5. 10000��\n");
				scanf("%d", &menu); //�޴� ����
				switch (menu)
				{

				case 1:
				{
					Ushead->Money += 1000; // �ܾ� + ������ �ݾ�
					printf("������ �Ϸ��߽��ϴ�.\n");
					printf("���� �ݾ� : %d\n", Ushead->Money); //�ܾ� ���
					break;
				}

				case 2:
				{
					Ushead->Money += 2000; // �ܾ� + ������ �ݾ�
					printf("������ �Ϸ��߽��ϴ�.\n");
					printf("���� �ݾ� : %d\n", Ushead->Money);//�ܾ� ���
					break;
				}

				case 3:
				{
					Ushead->Money += 3000; // �ܾ� + ������ �ݾ�
					printf("������ �Ϸ��߽��ϴ�.\n");
					printf("���� �ݾ� : %d\n", Ushead->Money);//�ܾ� ���
					break;
				}

				case 4:
				{ 
					Ushead->Money += 5000; // �ܾ� + ������ �ݾ�
					printf("������ �Ϸ��߽��ϴ�.\n");
					printf("���� �ݾ� : %d\n", Ushead->Money);//�ܾ� ���
					break;
				}

				case 5:
				{
					Ushead->Money += 10000; // �ܾ� + ������ �ݾ�
					printf("������ �Ϸ��߽��ϴ�.\n");
					printf("���� �ݾ� : %d\n", Ushead->Money);//�ܾ� ���
					break;
				}
				default:
				{
					scanf("%*c", &menu); // �Է¹��� �ʱ�ȭ
					printf("�߸��� �޴��Դϴ�.\n");
					break;
				}
					
				}
		}
	}
}