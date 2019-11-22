#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 15

typedef struct phoneBook_List
{
	char number[MAX];
	char name[MAX];
	struct PB_list* link;

}PB_list;

typedef struct Person
{
	char input_number[MAX];
	char input_name[MAX];
}person;


void Add_user(PB_list* input, person temp);

bool check_dp(PB_list* p, person temp);

bool check_form(person temp);

void sort_list(PB_list* head);

void Search_user(PB_list* head, person temp);

void print_Book(PB_list* head);

void delete_user(PB_list *head, person temp);

void change_userinfo(PB_list *head, person temp);

void free_mem(PB_list* head);