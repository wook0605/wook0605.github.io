#include "FlashMemory_head.h"

int ext_num(char* Commend)
{
	int len; //���ڿ� ����
	int pv = 0; // �ڸ����� ���߱� ���� ����
	char buf[10]; //������ ���� �迭 10�ڸ� �������� ���� �� �ִ�.
	int storage = 0; //��ȯ�� ��

	len = strlen(Commend);

	for (int i = 0; i < len; i++)
	{
		if (Commend[i] > 47 && Commend[i] < 58) //ASCII�󿡼� ���� �߰�
		{
			buf[pv] = Commend[i]; //�߰��� ���ڸ� �ڸ����� �°� �迭�� �Է�
			pv++; //�ڸ��� ����
		}
	}
	storage = atoi(buf); // ���� ��Ҹ� ������ ��ȯ

	return storage;
}