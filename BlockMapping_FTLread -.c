#include "BlockMapping_head.h"

int FTL_read(int LSN)
{
	int LBN = LSN / NOS; //LBN ���ϱ�
	int PBN = mtable.table[LBN]; //LBN�� PBN���� ��ȯ
	return PBN;
}