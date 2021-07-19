#include "BlockMapping_head.h"

int FTL_read(int LSN)
{
	int LBN = LSN / NOS; //LBN 구하기
	int PBN = mtable.table[LBN]; //LBN을 PBN으로 변환
	return PBN;
}