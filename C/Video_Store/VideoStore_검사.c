#include "VideoStore_head.h"

bool check_Userdp(Us_info* p, in_data temp) //사용자 중복 검사
{
	Us_info* dup = p->next;
	for (dup; dup != NULL; dup = dup->next)
	{
		if (strcmp(temp.input_Username, dup->name) == 0 || strcmp(temp.input_phoneNumber, dup->phone_number) == 0) // 동명이인과 같은 핸드폰 번호는 허용하지 않는다.
		{
			printf("중복된 사용자가 존재합니다.\n");
			return true; //참값 반환
		}
	}
	return false; //거짓값 반환
}

bool check_Videodp(Vd_info* p, in_data temp) //비디오 중복 검사
{
	Vd_info* dup = p->next; 
	for (dup; dup != NULL; dup = dup->next)
	{
		if (strcmp(temp.input_Videoname, dup->name) == 0) //중복된 비디오가 존재하는지 확인
		{
			return true;// 참값 반환
		}
	}
	return false; //거짓값 반환
}

bool check_form(in_data temp) // 핸드폰 번호가 11자리인지 검사
{
	if (strlen(temp.input_phoneNumber) == 11) // 전화번호가 11자리이면 통과, 아닐 경우 입력하지 않음.
	{
		return false; //거짓값 반환
	}
	else
	{
		printf("11자리 미만 혹은 초과하는 번호는 입력할 수 없습니다.\n");
		return true;//참값 반환
	}
}
