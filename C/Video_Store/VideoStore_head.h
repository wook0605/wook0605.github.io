#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define Second 30

typedef struct User_info
{
	char name[Second]; //����� �̸�
	char phone_number[Second]; // �ڵ��� ��ȣ
	char borrow_video_1[Second]; //�뿩�ѵ� 1
	char borrow_video_2[Second]; //�뿩�ѵ� 2
	char borrow_video_3[Second]; //�뿩�ѵ� 3
	unsigned int Money; // ������ ĳ��
	struct Us_info* next;
}Us_info;

typedef struct Video_info
{
	char name[Second]; // ������ �̸�
	unsigned int price; // ������ ����
	int number_of_Video; //���� ������ ����
	int total_of_Video; //��ü ������ ����
	struct Vd_info* next;
}Vd_info;

typedef struct input_data
{
	char input_Username[Second]; 
	char input_Videoname[Second];
	char input_phoneNumber[Second];
	int number;
	unsigned int Money;
}in_data;


void Add_user(Us_info* Usinput, in_data temp); // ����ڸ� �߰��ϴ� �Լ�

void Add_Video(Vd_info* Vdinput, in_data temp); // ������ �߰��ϴ� �Լ�

void Cash_Recharge(Us_info* Ushead, in_data temp); // ���� ���� �Լ�

void delete_user(Us_info* Ushead, Vd_info* Vdhead, in_data temp); //����� ���� �Լ�

void delete_Video(Vd_info* Vdhead, Us_info* Ushead, in_data temp); //���� ���� �Լ�

bool check_Userdp(Us_info* Up, in_data temp); // �ߺ��� ����ڰ� �����ϴ��� Ȯ���ϴ� �Լ�

bool check_Videodp(Vd_info* Vp, in_data temp); // �ߺ��� ������ �����ϴ��� Ȯ���ϴ� �Լ�

bool check_form(in_data temp); // ����� ������, �ڵ��� ��ȣ�� ���Ŀ� �°� �ԷµǾ����� Ȯ���ϴ� �Լ�

void sort_Uslist(Us_info* Ushead); //����� �̸��� ����

void sort_Vdlist(Vd_info* Vdhead); // ���� �̸��� ����

void Search_Video(Vd_info* Vdhead, in_data temp); // ������ �˻��ϴ� �Լ�

void Search_User(Us_info* Ushead, in_data temp); // ����ڸ� �˻��ϴ� �Լ�

void print_AllUser(Us_info* Ushead); // ����� ��ü ����� ����ϴ� �Լ�

void print_AllVideo (Vd_info* Vdhead); // ���� ��ü ����� ����ϴ� �Լ�

void change_info(Us_info* Ushead, Vd_info* Vdhead, in_data temp); // ��������� ���� or ���� ���� ����

void Borrow_Video(Us_info* Ushead, Vd_info* Vdhead, in_data temp); // ������ �뿩�ϴ� �Լ�

void Return_Video(Us_info* Ushead, Vd_info* Vdhead, in_data temp); // ������ �ݳ��ϴ� �Լ�

void Save_UsData(FILE* UsDB, Us_info* Ushead); //����� �����͸� �����ϴ� �Լ�

void Save_VdData(FILE* VdDB, Vd_info* Vdhead); //���� �����͸� �����ϴ� �Լ�

void Load_Usdata(FILE* UsDB, Us_info* Ushead); //����� �����͸� �ҷ����� �Լ�

void Load_Vddata(FILE* VdDB, Vd_info* Vdhead); // ���� �����͸� �ҷ����� �Լ�

void free_Usmem(Us_info* Ushead); // ������ �� ��� ����� ���Ḯ��Ʈ�� �����ϴ� �Լ�

void free_Vdmem(Vd_info* Vdhead); // ������ �� ��� ���� ���Ḯ��Ʈ�� �����ϴ� �Լ�