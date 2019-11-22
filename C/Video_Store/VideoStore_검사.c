#include "VideoStore_head.h"

bool check_Userdp(Us_info* p, in_data temp) //����� �ߺ� �˻�
{
	Us_info* dup = p->next;
	for (dup; dup != NULL; dup = dup->next)
	{
		if (strcmp(temp.input_Username, dup->name) == 0 || strcmp(temp.input_phoneNumber, dup->phone_number) == 0) // �������ΰ� ���� �ڵ��� ��ȣ�� ������� �ʴ´�.
		{
			printf("�ߺ��� ����ڰ� �����մϴ�.\n");
			return true; //���� ��ȯ
		}
	}
	return false; //������ ��ȯ
}

bool check_Videodp(Vd_info* p, in_data temp) //���� �ߺ� �˻�
{
	Vd_info* dup = p->next; 
	for (dup; dup != NULL; dup = dup->next)
	{
		if (strcmp(temp.input_Videoname, dup->name) == 0) //�ߺ��� ������ �����ϴ��� Ȯ��
		{
			return true;// ���� ��ȯ
		}
	}
	return false; //������ ��ȯ
}

bool check_form(in_data temp) // �ڵ��� ��ȣ�� 11�ڸ����� �˻�
{
	if (strlen(temp.input_phoneNumber) == 11) // ��ȭ��ȣ�� 11�ڸ��̸� ���, �ƴ� ��� �Է����� ����.
	{
		return false; //������ ��ȯ
	}
	else
	{
		printf("11�ڸ� �̸� Ȥ�� �ʰ��ϴ� ��ȣ�� �Է��� �� �����ϴ�.\n");
		return true;//���� ��ȯ
	}
}
