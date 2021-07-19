#include "SectorMapping.h"

int FTL_read(int LSN)
{
	int PSN = mtable.table[LSN]; //LSN을 PSN으로 변환
	return PSN;
}