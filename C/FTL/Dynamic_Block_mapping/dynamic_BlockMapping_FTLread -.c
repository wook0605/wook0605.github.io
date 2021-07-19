#include "dynamic_blockmapping_head.h"

int FTL_read(unsigned int  LSN)
{
	unsigned int  LBN = LSN / NOS; //LBN 구하기
	unsigned int  PBN = mtable.table[LBN]; //LBN을 PBN으로 변환
	temp_B.offset = LBN % NOS; //offset 구하기
	return PBN;
}