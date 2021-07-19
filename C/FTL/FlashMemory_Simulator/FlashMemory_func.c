#include "FlashMemory_head.h"

int ext_num(char* Commend)
{
	int len; //문자열 길이
	int pv = 0; // 자리값을 맞추기 위한 변수
	char buf[10]; //정수를 받을 배열 10자리 정수까지 받을 수 있다.
	int storage = 0; //변환한 값

	len = strlen(Commend);

	for (int i = 0; i < len; i++)
	{
		if (Commend[i] > 47 && Commend[i] < 58) //ASCII상에서 숫자 발견
		{
			buf[pv] = Commend[i]; //발견한 숫자를 자릿수에 맞게 배열에 입력
			pv++; //자릿수 증가
		}
	}
	storage = atoi(buf); // 버퍼 요소를 정수로 변환

	return storage;
}