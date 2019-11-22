#include "VideoStore_head.h"

void Save_UsData(FILE* UsDB, Us_info* Ushead) //�����͸� �����ϴ� �Լ�
{
	UsDB = fopen("User_DB.txt", "w"); // ����� �����͸� �����ϱ� ���ؾ��� ���� ������ ����.

	if (UsDB == NULL) // ������ ������ ���� ���
	{
		printf("������ ������ �ʾҽ��ϴ�.\n");
	}

	else
	{
		for (Ushead; Ushead != NULL; Ushead = Ushead->next) //��� �����͸� ���Ϸ� �����ϱ� ���� ��� ��ȯ
		{
			fwrite(Ushead, sizeof(Us_info), 1, UsDB);//�����͸� �Է��Ѵ�.
			fprintf(UsDB, "\n");//�����Ͽ� �����ٿ� �����Ͱ� �Էµǵ��� ��y
		}
	}
	fclose(UsDB);//���� �ݱ�

	
}

void Save_VdData(FILE* VdDB, Vd_info* Vdhead) //���� �����͸� �����ϴ� �Լ�
{
	VdDB = fopen("Video_DB.txt", "w");  // ���� �����͸� �����ϱ� ���ؾ��� ���� ������ ����.

	if (VdDB == NULL) // ������ ������ ���� ���
	{
		printf("������ ������ �ʾҽ��ϴ�.\n");
		
	}

	else //������ ���� ���
	{
		for (Vdhead; Vdhead != NULL; Vdhead = Vdhead->next) //��� �����͸� ���Ϸ� �����ϱ� ���� ��� ��ȯ
		{
			fwrite(Vdhead, sizeof(Vd_info), 1, VdDB); //�����͸� �Է��Ѵ�.
			fprintf(VdDB, "\n"); //�����Ͽ� �����ٿ� �����Ͱ� �Էµǵ��� ��
		}
	}
	fclose(VdDB); //���� �ݱ�
}

void Load_Usdata(FILE* UsDB, Us_info* Ushead) //�����͸� �ҷ����� �Լ�
{
	int size; //������ ũ�⸦ �����ϴ� ����

	UsDB = fopen("User_DB.txt", "r"); //����Ʈ�� ���� �����͸� �ҷ����� ���� ������ �б� ���� ����.

	if (UsDB == NULL) //������ ������ �ʾ��� ��
	{
		printf("������ ������ �ʾҽ��ϴ�.\n"); //���� �޽��� ���
		return; //��� ����
	}

	else
	{
		fseek(UsDB,0, SEEK_END); //������ ������� Ȯ���ϱ� ���� ������ ������ ������.
		size = ftell(UsDB); //Ŀ���� ���� ���� ��ȯ
		if (size == 0) //������ ���� �����Ͱ� ���� ��
		{
			printf("�ҷ��� �����Ͱ� �����ϴ�.\n");
		}

		else //���Ͽ� �����Ͱ� ���� ��
		{
			rewind(UsDB); // ������ Ŀ���� �� ������ ������.
			while (feof(UsDB) == 0) //������ ������ �ݺ��Ѵ�.
			{
				Us_info* up = (Us_info*)malloc(sizeof(Us_info)); //���� �����͸� ������ ��� ����
				fread(up, sizeof(Us_info), 1, UsDB); //������ �б�
				fscanf(UsDB, "\n"); //�������� �б� ���� ����
				Ushead->next = up; //��� ����
				Ushead = Ushead->next; //��� ����
				up->next = NULL; 
			}
		}
	}

	fclose(UsDB); //����� ������ �������� �ݱ�
}

void Load_Vddata(FILE* VdDB, Vd_info* Vdhead) //���� �����͸� �ҷ����� �Լ�
{
	int size; //�������� ũ�� �����ϴ� �Լ�

	VdDB = fopen("Video_DB.txt", "r"); //����Ʈ�� ���� �����͸� �ҷ����� ���� ������ �б� ���� ����.

	if (VdDB == NULL) //������ ������ ���� ���
	{
		printf("������ ������ �ʾҽ��ϴ�.\n");
		return;//��� ����
	}

	else
	{
		fseek(VdDB, 0, SEEK_END); //������ ������� Ȯ���ϱ� ���� ������ ������ ������.
		size = ftell(VdDB);//Ŀ���� ���� ���� ��ȯ
		if (size == 0) //������ ���� �����Ͱ� ���� ��
		{
			printf("�ҷ��� �����Ͱ� �����ϴ�.\n");
		}

		else //������ ���� �����Ͱ� ���� ��
		{
			rewind(VdDB); //������ Ŀ���� �� ������ ������.
			while (feof(VdDB) == 0)//������ ������ �ݺ��Ѵ�.
			{
				Vd_info* vp = (Vd_info*)malloc(sizeof(Vd_info));//���� �����͸� ������ ��带 �����Ѵ�.
				fread(vp, sizeof(Vd_info), 1, VdDB); //������ �о ��忡 ����
				fscanf(VdDB, "\n"); //���� ���� �б� ���� ����
				Vdhead->next = vp; //��� ����
				Vdhead = Vdhead->next; //��� ����
				vp->next = NULL;
			}
		}

	}
	fclose(VdDB);//���������� ���� ���� �ݱ�
}


void free_Usmem(Us_info* Ushead) //���� ��� ����
{
	Us_info* Usremove;
	while (Ushead != NULL) //��尡 �������� ���� �� ���� �ݺ�
	{
		Usremove = Ushead->next;
		Ushead->next = NULL;
		free(Usremove); //��带 �����Ѵ�.
		Ushead = Ushead->next; //���� ���� �̵�
	}
}

void free_Vdmem(Vd_info* Vdhead) // ���� ��� ����
{
	Vd_info* Vdremove;
	while (Vdhead != NULL) //��尡 �������� ���� �� ���� �ݺ�
	{
		Vdremove = Vdhead->next;
		Vdhead->next = NULL;
		free(Vdremove); //��带 �����Ѵ�.
		Vdhead = Vdhead->next; //���� ���� �̵�
	}
}