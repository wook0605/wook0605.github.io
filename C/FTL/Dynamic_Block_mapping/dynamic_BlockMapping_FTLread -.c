#include "dynamic_blockmapping_head.h"

int FTL_read(unsigned int  LSN)
{
	unsigned int  LBN = LSN / NOS; //LBN ���ϱ�
	unsigned int  PBN = mtable.table[LBN]; //LBN�� PBN���� ��ȯ
	temp_B.offset = LBN % NOS; //offset ���ϱ�
	return PBN;
}