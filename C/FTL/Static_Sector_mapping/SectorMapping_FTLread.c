#include "SectorMapping.h"

int FTL_read(int LSN)
{
	int PSN = mtable.table[LSN]; //LSN�� PSN���� ��ȯ
	return PSN;
}