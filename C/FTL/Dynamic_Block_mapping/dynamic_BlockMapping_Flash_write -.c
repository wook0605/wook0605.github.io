#include "dynamic_blockmapping_head.h"

void Flash_write(FILE* Flash_memory, unsigned int LSN, char* write_data)
{
	unsigned int LBN = LSN / NOS;
	unsigned int PBN = mtable.table[LBN];  // ������ ���͸� ����Ű�� ���� ��
	unsigned int Block = 0;
	unsigned int offset_count = 0;
	unsigned int offset = LSN % NOS;
	unsigned char status = 0;
	unsigned int nob = 0;
	unsigned char read_data[513];
	memset(read_data, NULL, sizeof(read_data));

	Flash_memory = fopen("Block_Mapping_FM.txt", "r+"); //������ �б�/���� ���� ����.
	fpos_t pos = 0;

	if (Flash_memory == NULL)
	{
		printf("������ ������ �ʾҽ��ϴ�.\n");
	}
	else
	{
		if (mtable.nos <= LSN) //������ �ʰ��ؼ� ���� ���
		{
			printf("������ �ʰ��߽��ϴ�.\n");
		}
		else //������ �ʰ����� ���� ���
		{
			pos = mtable.FP_loc[(LBN * NOS) + offset]; //�ش� ����� ���� �����Ͱ� ����
			fsetpos(Flash_memory, &pos); //�ش� ����� ������ ���� �̵�
			fgets(read_data, SS, Flash_memory); //������ ���� Ȯ��
			fscanf(Flash_memory, "%d\t%d\t%d\t%d", &spare.status, &spare.LSN, &spare.write_count, &spare.erase_count); //�ش� ����� spare �б�
			fgetc(Flash_memory);//���� ������ ��ĭ �̵�
			if (spare.status == 0) //free page�� ��
			{
				spare.status = 1;
				fsetpos(Flash_memory, &pos);
				spare.write_count++; //���� ī��Ʈ ����
				mtable.write_count++;
				fprintf(Flash_memory, "%512s\t%d\t%d\t%d\t%d\n", write_data, spare.status, spare.LSN, spare.write_count, spare.erase_count); //����
				printf("Done!\n");
			}
			else //����� �߻� ��
			{
				pos = mtable.FP_loc[LBN * NOS];
				nob = mtable.nob;
				FTL_write(Flash_memory, LSN, PBN, write_data, offset, nob, pos);
			}
		}
		fclose(Flash_memory); //������ �ݴ´�.
	}
}