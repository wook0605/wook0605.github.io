#include "VideoStore_head.h"


int main()
{
	Us_info* Us_head = (Us_info*)malloc(sizeof(Us_info)); //���� �����͸� ������ ���Ḯ��Ʈ ����
	Us_head->next = NULL;
	Vd_info* Vd_head = (Vd_info*)malloc(sizeof(Vd_info)); //���� �����͸� ������ ���Ḯ��Ʈ ����
	Vd_head->next = NULL;
	in_data temp; // ���Ḯ��Ʈ�� �������� �Է��� ����ü
	memset(&temp, NULL, sizeof(in_data)); // �����͸� �Է��� ����ü�� �ʱ�ȭ
	FILE* Us_DB = NULL; // ���Ͽ� ���� �����͸� �����ϱ� ����
	FILE* Vd_DB = NULL; // ���Ͽ� ���� �����͸� �����ϱ� ����
	int menu;
	Load_Usdata(Us_DB, Us_head); // ���α׷��� �����ϸ� ����� �����͸� �ڵ����� �ҷ��´�.
	Load_Vddata(Vd_DB, Vd_head); // ���α׷��� �����ϸ� ���� �����͸� �ڵ����� �ҷ��´�.
	while (1)
	{
		printf("=====================================================\n");
		printf("|              �޴��� �����Ͻʽÿ�.                  |\n");
		printf("| 1. ����� �߰�                                     |\n");
		printf("| 2. ���� �԰�                                     |\n");
		printf("| 3. ĳ�� ����                                       |\n");
		printf("| 4. ����� ��ü���                                 |\n");
		printf("| 5. ���� ��ü���                                 |\n");
		printf("| 6. ���� ����                                       |\n");
		printf("| 7. ���� �˻�                                     |\n");
		printf("| 8. ����� �˻�                                     |\n");
		printf("| 9. ����� ����                                     |\n");
		printf("| 10. ���� ����                                    |\n");
		printf("| 11. ���� �뿩                                    |\n");
		printf("| 12. ���� �ݳ�                                    |\n");
		printf("| 13. ���� ���� ����                               |\n");
		printf("=====================================================\n");
		printf("�޴� ����>>");
		scanf("%d", &menu);

		switch (menu)
		{
		case 1:
		{
			memset(&temp,NULL, sizeof(in_data)); // ������ �Է��ϴ� ����ü �ʱ�ȭ
			printf("�߰��� ������� ������ �Է����ֽʽÿ�.\n");
			printf("����� �̸� :");
			scanf("%s", temp.input_Username); //����� �̸� �Է�
			printf("�ڵ��� ��ȣ :");
			scanf("%s", temp.input_phoneNumber);// ����� �ڵ�����ȣ �Է�
			printf("\n"); //����
			Add_user(Us_head, temp); //����� �߰�
			break;
		}

		case 2:
		{
			memset(&temp, NULL, sizeof(in_data)); // ������ �Է��ϴ� ����ü �ʱ�ȭ
			printf("�԰�� ������ ������ �Է����ֽʽÿ�.\n");
			printf("��ǰ �� :");
			scanf("%s", temp.input_Videoname); //���� �̸� �Է�
			printf("���� : ");
			scanf("%d", &temp.Money); // ���� ���� �Է�
			printf("���� : ");
			scanf("%d", &temp.number); // ���� ���� �Է�
			Add_Video(Vd_head, temp); //���� �԰�
			break;
		}

		case 3:
		{
			printf("�ݾ��� ������ ����ڸ� �Է����ּ���.\n");
			scanf("%s", temp.input_Username); //������ ����� �̸� �Է�
			Cash_Recharge(Us_head, temp); //ĳ�� ����
			break;
		}

		case 4:
		{
			print_AllUser(Us_head); //����� ��ü��� ���
			break;
		}

		case 5:
		{
			print_AllVideo(Vd_head); //���� ��ü��� ���
			break;
		}
		case 6:
		{
			change_info(Us_head, Vd_head, temp); //����� ���� ���� or ���� ���� ����
			break;
		}
		case 7:
		{
			printf("�˻��� ��ǰ �̸��� �Է����ּ���.\n");
			scanf("%s", temp.input_Videoname); //�˻��� ���� �̸� �Է�
			Search_Video(Vd_head, temp); //���� �˻�
			break;
		}

		case 8:
		{
			printf("�˻��� ������� �̸��� �Է����ּ���.\n");
			scanf("%s", temp.input_Username); //�˻��� ����� �̸� �Է�
			Search_User(Us_head, temp); //����� �˻�
			break;
		}

		case 9:
		{
			printf("������! ����ڸ� �����ϸ� �����ִ� ĳ�ô� ��ȯ���� �ʽ��ϴ�.��\n");
			printf("������ ������� �̸��� �Է��ϼ���\n");
			scanf("%s", temp.input_Username); // ������ ����� �̸� �Է�
			delete_user(Us_head,Vd_head, temp); //����� ����
			break;
		}

		case 10:
		{
			printf("������ ������ �̸��� �Է��ϼ���\n");
			scanf("%s", temp.input_Videoname); //������ ���� �̸� �Է�
			delete_Video(Vd_head, Us_head, temp);//���� ����
			break;
		}

		case 11:
		{
			printf("����� �̸� :");
			scanf("%s", temp.input_Username);
			printf("�뿩�� ��ǰ �̸� :");
			scanf("%s", temp.input_Videoname);
			Borrow_Video(Us_head, Vd_head, temp); //���� �뿩
			break;

		}
		case 12:
		{
			printf("����� �̸� :");
			scanf("%s", temp.input_Username);
			Return_Video(Us_head, Vd_head, temp); //���� �ݳ�
			break;
		}
		case 13:
		{
			printf("���� ���Ը� �����մϴ�.\n");
			Save_UsData(Us_DB, Us_head->next);//���Ͽ� ����� ������ ����
			Save_VdData(Vd_DB, Vd_head->next);//���Ͽ� ���� ������ ����
			free_Usmem(Us_head); //����� ��� ����
			free_Vdmem(Vd_head); //���� ��� ����
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