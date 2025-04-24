#ifndef MAIN_H
#define MAIN_H

typedef struct _polynom
{
	int degree; //�������
	int coeff; //����������
	struct _polynom* next; //��������� �� ���� ������� ������
} polynom;

typedef enum _functions
{
	create = 1,
	print,
	sort,
	func25,
	lr8_2,
	exit1
}functions;

void menu(void);

polynom* create_polynom_node(int degree, int coeff);

void add_polynom_node(polynom** head, int degree, int coeff);

int check_degree(int degree, int** ptr, int* size);

void print_polynom_node(polynom* head);

void function25(polynom** head);

void sort_node(polynom** head);
#endif
