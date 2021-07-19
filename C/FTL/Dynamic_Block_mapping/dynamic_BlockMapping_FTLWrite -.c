#include "dynamic_blockmapping_head.h"

void FTL_write(FILE* Flash_memory, unsigned int LSN, unsigned int PBN, char* write_data, unsigned int overwrite_offset, unsigned int nob, fpos_t pos)
{
	unsigned int  LBN = LSN / NOS;
	unsigned int free_count = 0;
	unsigned int new_block = 0;
	unsigned int temp_loc = 0;
	float no_block_value = 0;
	unsigned int offset_count = 0;
	unsigned char read_data[513] = { NULL, };
	float threshhold = 80.0;
	fpos_t pos_2 = 0;
	fpos_t temp_pos = 0;
	memset(temp_B.temp_blcok, NULL, sizeof(temp_B)); //�ӽú�� �ʱ�ȭ
	memset(temp_B_1.temp_blcok, NULL, sizeof(temp_B_1)); //�ӽú�� �ʱ�ȭ
	rewind(Flash_memory);
	mtable.nob = nob;
	fsetpos(Flash_memory, &pos);//����� �Ͼ ����� ù���ͺ��� �б�
	for (offset_count = 0; offset_count < NOS; offset_count++) //����� �Ͼ ���� �б�.
	{
		fgets(read_data, SS, Flash_memory); //������ ���� �б�
		fscanf(Flash_memory, "%d\t%d\t%d\t%d", &temp_B.temp_spare_status[offset_count], &temp_B.temp_spare_LSN[offset_count], &temp_B.temp_spare_write_count[offset_count], &temp_B.temp_spare_erase_count[offset_count]); //������ �б�
		fgetc(Flash_memory);//���� ������ ��ĭ �̵� (�����ٷ�)
		if (overwrite_offset == offset_count)  //��ϰ� offset�� overwrite�� �Ͼ �κп� ��ġ�ϴ� ���
		{
			strcpy(temp_B.temp_blcok[overwrite_offset], write_data); // ����Ⱑ �Ͼ ������ �����͸� ���� ���ش�.
		}

		else if (overwrite_offset != offset_count && temp_B.temp_spare_status[offset_count] == 1) //��ȿ�� �������϶� (��ȿ�ϰų� �� �����ʹ� ���� �ʴ´�.)
		{
			strcpy(temp_B.temp_blcok[offset_count], read_data); // erase�� ��ϴ����� �Ͼ�� ������ �ش� ����� ��ȿ������ ���� ����
		}
	}
	rewind(Flash_memory);
	for (new_block = 0; new_block < mtable.nob; new_block++) //�� ����� ã�´�.
	{
		printf("���� ã�� ��\n");
		pos_2 = mtable.FP_loc[new_block * NOS]; //����� ������ ���������� ��ġ �Ҵ�
		fsetpos(Flash_memory, &pos_2); //�ش� ����� �����¿� ���� ������ ��ġ��Ŵ.
		for (int i = 0; i < NOS; i++) //offset �б�
		{
			fgets(read_data, SS, Flash_memory); //������ ���� �б�
			fscanf(Flash_memory, "%d\t%d\t%d\t%d", &temp_B_1.temp_spare_status[i], &temp_B_1.temp_spare_LSN[i], &temp_B_1.temp_spare_write_count[i], &temp_B_1.temp_spare_erase_count[i]); //spare ���� �б�
			fgetc(Flash_memory);//���� ������ ��ĭ �̵� (���� �ٷ�)
			if (temp_B_1.temp_spare_status[i] == 0) //������ �� ����� ��
			{
				free_count++;
			}
			else //�����Ͱ� �����ϴ� ����� ��
			{
				free_count = 0;
				break;
			}
		}
		if (free_count == 32) //������ �� ����� ������.
		{
			mtable.no_block = 0;
			break;
		}
		else if (free_count != 32)
		{
			mtable.no_block++;
		}
		no_block_value = (mtable.no_block / mtable.nob) * 100;
		if (no_block_value > threshhold) // free ����� ���� �Ӱ谪 ���� ���� ������ ��
		{
			Flash_erase(Flash_memory);
			new_block = 0; //�ٽ� �ݺ��Ͽ� �� ����� ã�´�.
			mtable.no_block = 0;
		}
	}
	//pos_2 = mtable.FP_loc[(new_block * NOS)];
	fsetpos(Flash_memory, &pos_2); //���ο� ����� ��ġ�� �̵�
	for (int i = 0; i < NOS; i++) //���ο� ��Ͽ� ������ �̵�
	{
		if (temp_B.temp_spare_status[i] == 1) //��ȿ�� �������� ���� ���
		{
			temp_B_1.temp_spare_status[i] = 1;
			temp_B_1.temp_spare_write_count[i]++; //���� ī��Ʈ ����
			mtable.write_count++; //���� ī��Ʈ ����
			fprintf(Flash_memory, "%512s\t%d\t%d\t%d\t%d\n", temp_B.temp_blcok[i], temp_B_1.temp_spare_status[i], temp_B.temp_spare_LSN[i], temp_B_1.temp_spare_write_count[i], temp_B_1.temp_spare_erase_count[i]);
		}
		else
		{
			fprintf(Flash_memory, "%512s\t%d\t%d\t%d\t%d\n", temp_B.temp_blcok[i], temp_B.temp_spare_status[i], temp_B.temp_spare_LSN[i], temp_B_1.temp_spare_write_count[i], temp_B_1.temp_spare_erase_count[i]);
		}

	}
	fsetpos(Flash_memory, &pos); //��ȿȭ�ؾ��� ������� �̵�
	for (int i = 0; i < NOS; i++)
	{
		if (temp_B.temp_spare_status[i] == 0) //free page�� ��
		{
			fprintf(Flash_memory, "%512s\t%d\t%d\t%d\t%d\n", temp_B.temp_blcok[i], temp_B.temp_spare_status[i], temp_B_1.temp_spare_LSN[i], temp_B.temp_spare_write_count[i], temp_B.temp_spare_erase_count[i]);
		}

		else //valid page�� ��
		{
			temp_B.temp_spare_status[i] = 2; //��ȿȭ
			fprintf(Flash_memory, "%512s\t%d\t%d\t%d\t%d\n", temp_B.temp_blcok[i], temp_B.temp_spare_status[i], temp_B_1.temp_spare_LSN[i], temp_B.temp_spare_write_count[i], temp_B.temp_spare_erase_count[i]);
		}
	}

	for (int i = 0; i < NOS; i++) //���� ������ ��ġ ����
	{
		temp_pos = mtable.FP_loc[(new_block * NOS) + i];
		mtable.FP_loc[(new_block * NOS) + i] = mtable.FP_loc[(LBN * NOS) + i];
		mtable.FP_loc[(LBN * NOS) + i] = temp_pos;
	}
	temp_loc = mtable.table[new_block];
	mtable.table[new_block] = PBN;
	mtable.table[LBN] = temp_loc;
	printf("DONE!!\n");
}