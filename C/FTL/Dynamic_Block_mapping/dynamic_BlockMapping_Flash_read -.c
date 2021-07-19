#include "dynamic_blockmapping_head.h"

void Flash_read(FILE* Flash_memory, unsigned int  LSN)
{
	unsigned int PBN = FTL_read(LSN);
	unsigned int PBN_count = 0;
	unsigned int offset_count = 0;
	unsigned int offset = LSN % NOS;
	unsigned int spare_len = 0;
	char read_Sdata[513]; // 512�� �ε����� ���� �б� ���ؼ� 513ũ��� �����Ѵ�.

	Flash_memory = fopen("Block_Mapping_FM.txt", "r"); //������ �б� ���� ����
	fpos_t pos;

	if (Flash_memory == NULL) //������ ������ �ʾ�����
	{
		printf("������ ������ �ʾҽ��ϴ�.\n");
	}

	else
	{
		if (mtable.nos< LSN)
		{
			printf("������ �ʰ��߽��ϴ�.\n");
		}
		else
		{
			pos = mtable.FP_loc[LSN];
			fsetpos(Flash_memory, &pos);
			fgets(read_Sdata, SS, Flash_memory); //������ ���� �б�
			fscanf(Flash_memory, "%d\t%d\t%d\t%d", &spare.status, &spare.LSN, &spare.write_count, &spare.erase_count);
			if (spare.status == 0 || spare.status == 2) //Free Page�� ��
			{
				printf("PBN %d�� offset : %d\tDATA : EMPTY or Invalid\n", PBN, offset);
			}

			else //valid page�� ��
			{
				
				fgets(read_Sdata, SS, Flash_memory);
				printf("PBN %d�� offset : %d\nDATA : %s", PBN, offset, read_Sdata);
			}
			rewind(Flash_memory);
		}
	}

		fclose(Flash_memory);
}