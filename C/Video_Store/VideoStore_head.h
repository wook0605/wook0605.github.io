#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define Second 30

typedef struct User_info
{
	char name[Second]; //사용자 이름
	char phone_number[Second]; // 핸드폰 번호
	char borrow_video_1[Second]; //대여한도 1
	char borrow_video_2[Second]; //대여한도 2
	char borrow_video_3[Second]; //대여한도 3
	unsigned int Money; // 충전된 캐시
	struct Us_info* next;
}Us_info;

typedef struct Video_info
{
	char name[Second]; // 비디오의 이름
	unsigned int price; // 비디오의 가격
	int number_of_Video; //현재 비디오의 개수
	int total_of_Video; //전체 비디오의 개수
	struct Vd_info* next;
}Vd_info;

typedef struct input_data
{
	char input_Username[Second]; 
	char input_Videoname[Second];
	char input_phoneNumber[Second];
	int number;
	unsigned int Money;
}in_data;


void Add_user(Us_info* Usinput, in_data temp); // 사용자를 추가하는 함수

void Add_Video(Vd_info* Vdinput, in_data temp); // 비디오를 추가하는 함수

void Cash_Recharge(Us_info* Ushead, in_data temp); // 현금 충전 함수

void delete_user(Us_info* Ushead, Vd_info* Vdhead, in_data temp); //사용자 삭제 함수

void delete_Video(Vd_info* Vdhead, Us_info* Ushead, in_data temp); //비디오 삭제 함수

bool check_Userdp(Us_info* Up, in_data temp); // 중복된 사용자가 존재하는지 확인하는 함수

bool check_Videodp(Vd_info* Vp, in_data temp); // 중복된 비디오가 존재하는지 확인하는 함수

bool check_form(in_data temp); // 사용자 정보중, 핸드폰 번호가 형식에 맞게 입력되었는지 확인하는 함수

void sort_Uslist(Us_info* Ushead); //사용자 이름순 정렬

void sort_Vdlist(Vd_info* Vdhead); // 비디오 이름순 정렬

void Search_Video(Vd_info* Vdhead, in_data temp); // 비디오를 검색하는 함수

void Search_User(Us_info* Ushead, in_data temp); // 사용자를 검색하는 함수

void print_AllUser(Us_info* Ushead); // 사용자 전체 목록을 출력하는 함수

void print_AllVideo (Vd_info* Vdhead); // 비디오 전체 목록을 출력하는 함수

void change_info(Us_info* Ushead, Vd_info* Vdhead, in_data temp); // 사용자정보 변경 or 비디오 제고 변경

void Borrow_Video(Us_info* Ushead, Vd_info* Vdhead, in_data temp); // 비디오를 대여하는 함수

void Return_Video(Us_info* Ushead, Vd_info* Vdhead, in_data temp); // 비디오를 반납하는 함수

void Save_UsData(FILE* UsDB, Us_info* Ushead); //사용자 데이터를 저장하는 함수

void Save_VdData(FILE* VdDB, Vd_info* Vdhead); //비디오 데이터를 저장하는 함수

void Load_Usdata(FILE* UsDB, Us_info* Ushead); //사용자 데이터를 불러오는 함수

void Load_Vddata(FILE* VdDB, Vd_info* Vdhead); // 비디오 데이터를 불러오는 함수

void free_Usmem(Us_info* Ushead); // 종료할 때 모든 사용자 연결리스트를 해제하는 함수

void free_Vdmem(Vd_info* Vdhead); // 종료할 때 모든 비디오 연결리스트를 해제하는 함수