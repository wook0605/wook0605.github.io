#include "dynamic_blockmapping_head.h"

void Flash_erase(FILE* Flash_memory)
{
	unsigned int LBN = 0;
	unsigned int offset = 0;
	float iv_count = 0; //��ȿ���� ����
	unsigned char read_data[513] = { NULL, };
	float* iv_ratio = 0;
	float threshold = 20.0;
	unsigned int victim = 0;
	unsigned int free_b = 0;
	fpos_t free_b_pos = 0;
	fpos_t pos_2 = 0;
	iv_ratio = (float*)malloc(sizeof(float) * mtable.nob); //��� ��ȿȭ���� ����
	memset(read_data, 32, sizeof(read_data));
	printf("���� ����");
	for (LBN = 0; LBN < mtable.nob; LBN++) //�÷��� �޸� ��ȸ
	{
		pos_2 = mtable.FP_loc[LBN * NOS];
		fsetpos(Flash_memory, &pos_2);
		for (offset = 0; offset < NOS; offset++) // �� ����� ��ȿ�� ����
		{
			fgets(temp_B_1.temp_blcok[offset], SS, Flash_memory); //������ ���� �б�
			fscanf(Flash_memory, "%d\t%d\t%d\t%d",&temp_B_1.temp_spare_status[offset], &temp_B_1.temp_spare_LSN[offset], &temp_B_1.temp_spare_write_count[offset], &temp_B_1.temp_spare_erase_count[offset]); // ����� ���� �б�
			fgetc(Flash_memory); //���� ������ ��ġ �ٲٱ�
			if (temp_B_1.temp_spare_status[offset] == 2) //��ȿ ������ ��
			{
				iv_count++; //��ȿ�� ����
			}
		}
		iv_ratio[LBN] = ((iv_count / NOS) * 100);
		iv_count = 0;
		if (iv_ratio[LBN] > iv_ratio[victim]) //victim ���� (��ȿ�� �ִ밪 : 100)
		{
			victim = LBN; //������ ��� ��ġ
			printf("������ ����� ��ġ : %d\t ��ȿ�� : %f", victim, iv_ratio[victim]);
		}
		if (iv_ratio[LBN] < iv_ratio[free_b]) //(��ȿ�� �ּҰ� (0))
		{
			free_b = LBN; //free_b ��� ��ġ
			printf("��������� ��ġ : %d\t ��ȿ�� : %f", free_b, iv_ratio[free_b]);
		}
	}

	if (iv_ratio[victim] == 100) //���� ��ȿȭ ����� ��
	{
		pos_2 = mtable.FP_loc[(victim * NOS)]; //��ȿ����� ù��° ������ ��ġ ��������
		fsetpos(Flash_memory, &pos_2); //��ȿ ����� ù��° ������ ��ġ�� �̵�
		for (offset = 0; offset < NOS; offset++) //����� �� �������� Ȯ��
		{
			fgets(temp_B_1.temp_blcok[offset], SS, Flash_memory);//������ �б�
			fscanf(Flash_memory, "%d\t%d\t%d\t%d", &temp_B_1.temp_spare_status[offset], &temp_B_1.temp_spare_LSN[offset], &temp_B_1.temp_spare_write_count[offset], &temp_B_1.temp_spare_erase_count[offset]); //�ش� ������ ����� �б�
			fgetc(Flash_memory);//���� ������ �̵�
		}
		fsetpos(Flash_memory, &pos_2); //������ ������� �̵�
		for (offset = 0; offset < NOS; offset++) //����
		{	
			temp_B_1.temp_spare_erase_count[offset]++;//���� ī��Ʈ ����
			temp_B_1.temp_spare_status[offset] = 0;
			fprintf(Flash_memory, "%512s\t%d\t%d\t%d\t%d\n", read_data, temp_B_1.temp_spare_status[offset], temp_B_1.temp_spare_LSN[offset], temp_B_1.temp_spare_write_count[offset], temp_B_1.temp_spare_erase_count[offset]); //�ش� ������ ����
		}
		fsetpos(Flash_memory, &pos_2);
		for (offset = 0; offset < NOS; offset++)
		{
			fgets(temp_B_1.temp_blcok[offset], SS, Flash_memory);
			fscanf(Flash_memory, "%d\t%d\t%d\t%d", &temp_B_1.temp_spare_status[offset], &temp_B_1.temp_spare_LSN[offset], &temp_B_1.temp_spare_write_count[offset], &temp_B_1.temp_spare_erase_count[offset]);
			fgetc(Flash_memory);
			printf("offset : %d\tspare area : %d\t%d\t%d\t%d\n", offset, temp_B_1.temp_spare_status[offset], temp_B_1.temp_spare_LSN[offset], temp_B_1.temp_spare_write_count[offset], temp_B_1.temp_spare_erase_count[offset]);
		}
		mtable.erase_count++;
	}

	else if (iv_ratio[victim] > threshold) // victim ������ ����� iv_ratio�� 20.0 ���� Ŭ ��
	{
		pos_2 = mtable.FP_loc[(victim * NOS)];
		fsetpos(Flash_memory, &pos_2);
		for (offset = 0; offset < NOS; offset++) //����� �� �������� Ȯ��
		{
			fgets(temp_B_1.temp_blcok[offset], SS, Flash_memory);//������ �б�
			fscanf(Flash_memory, "%d\t%d\t%d\t%d", &temp_B_1.temp_spare_status[offset], &temp_B_1.temp_spare_LSN[offset], &temp_B_1.temp_spare_write_count[offset], &temp_B_1.temp_spare_erase_count[offset]); //�ش� ������ ����� �о����.
			fgetc(Flash_memory);//���� ������ �̵�
		}
		fsetpos(Flash_memory, &pos_2); //������ ������� �̵�
		for (offset = 0; offset < NOS; offset++)
		{
			if (temp_B_1.temp_spare_status[offset] == 1) //���� �������� ��ȿ�� �����͸� �����ϴ� ��� ��ȿ �����ʹ� RAM�� ��� �÷��ΰ�, ���� ���� �� ���� ��ȿ �����͸� �ٽ� ���ش�.
			{
				temp_B_1.temp_spare_erase_count[offset]++;//���� ī��Ʈ ����
				temp_B_1.temp_spare_write_count[offset]++;//���� ī��Ʈ ����
				temp_B_1.temp_spare_status[offset] = 1;
				for (int i = 0; i < SS; i++)
				{
					fprintf(Flash_memory, " ");
				}
				fprintf(Flash_memory, "\t%d\t%d\t%d\t%d\n", temp_B_1.temp_spare_status[offset], temp_B_1.temp_spare_LSN[offset], temp_B_1.temp_spare_write_count[offset], temp_B_1.temp_spare_erase_count[offset]);
			}

			else //���� �������� ��ȿ�ϰų� ����ִ� ���
			{
				temp_B_1.temp_spare_erase_count[offset]++; //���� ī��Ʈ ����
				temp_B_1.temp_spare_status[offset] = 0;
				fprintf(Flash_memory, "%512s\t%d\t%d\t%d\t%d\n", read_data, temp_B_1.temp_spare_status[offset], temp_B_1.temp_spare_LSN[offset], temp_B_1.temp_spare_write_count[offset], temp_B_1.temp_spare_erase_count[offset]); //�ش� ������ ����
			}
		}
		fsetpos(Flash_memory, &pos_2);
		for (offset = 0; offset < NOS; offset++)
		{
			fgets(temp_B_1.temp_blcok[offset], SS, Flash_memory);
			fscanf(Flash_memory, "%d\t%d\t%d\t%d", &temp_B_1.temp_spare_status[offset], &temp_B_1.temp_spare_LSN[offset], &temp_B_1.temp_spare_write_count[offset], &temp_B_1.temp_spare_erase_count[offset]);
			fgetc(Flash_memory);
			printf("offset : %d\tspare area : %d\t%d\t%d\t%d\n", offset, temp_B_1.temp_spare_status[offset], temp_B_1.temp_spare_LSN[offset], temp_B_1.temp_spare_write_count[offset], temp_B_1.temp_spare_erase_count[offset]);
		}
		mtable.erase_count++;
	}
	else
	{
		printf("victim���� ��ȿ ����� ��ȿ���� �Ӱ谪 �Ʒ��Դϴ�.\n");
	}
	printf("���� ����");
	free(iv_ratio);
}