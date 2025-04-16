#ifndef MAIN_H
#define MAIN_H

typedef struct _polynom
{
	int degree; //степень
	int coeff; //коэфициент
	struct _polynom* next; //указатель на след элемент списка
} polynom;

typedef enum _functions
{
	create = 1,
	print,
	sort,
	func25,
	exit1
}functions;

void menu(void);

polynom* create_node(int degree, int coeff);

void add_node(polynom** head, int degree, int coeff);

int check_degree(int degree, int** ptr, int* size);

void print_node(polynom* head);

void function25(polynom** head);

void sort_node(polynom** head);
#endif
