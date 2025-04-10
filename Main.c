#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Main.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	menu();
	return 0;
}

void menu(void)
{
	functions sw = create;
	int degree;
	int coeff;
	int* ptr = NULL;
	int size = 0;
	polynom* head = NULL;
	do
	{
		printf("Choose function from list:\n"
			"1 - Create polynom\n"
			"2 - Print polynom\n"
			"3 - Remove all elements with even degree\n"
			"4 - Exit out of program\n");
		scanf("%d", &sw);
		switch (sw)
		{
		case create:
			printf("Enter the degree and coefficient before and after the space\n");
			if (scanf("%d %d", &degree, &coeff) != 2 || check_degree(degree, &ptr, &size) != 0 || coeff == 0)
			{
				while (getchar() != '\n');
				printf("Input error!\n");
				break;
			}
			add_node(&head, degree, coeff);
			break;
		case print:
			print_node(head);
			break;
		case func25:
			function25(&head);
			break;
		case exit1:
		{
			free(ptr);
			polynom* tmp;
			while (head != NULL)
			{
				tmp = head;
				head = head->next;
				free(tmp);
			}
			return;
		}
		default:
			printf("Input error!\n");
			break;
		}
	} while (sw != exit1);
}

polynom* create_node(int degree, int coeff)
{
	polynom* Node = (polynom*)malloc(sizeof(polynom));
	if (Node == NULL)
	{
		printf("Malloc erorr!\n");
		return NULL;
	}
	Node->coeff = coeff;
	Node->degree = degree;
	Node->next = NULL;
	return Node;
}

void add_node(polynom** head, int degree, int coeff)
{
	polynom* next_node = create_node(degree, coeff);
	if (next_node == NULL)
	{
		printf("Create node error!\n");
		return;
	}
	next_node->next = *head; 
	*head = next_node; 
	return;
}

int check_degree(int degree, int** ptr, int* size) 
{
	if (*ptr != NULL) 
	{
		for (int i = 0; i < *size; i++) 
		{
			if ((*ptr)[i] == degree) 
			{
				printf("Degree %d already exists!\n", degree);
				return 1;
			}
		}
	}
	int new_size = *size + 1;
	int* temp = realloc(*ptr, new_size * sizeof(int));
	if (temp == NULL) 
	{
		printf("Realloc error!\n");
		return 1;
	}
	*ptr = temp;
	(*ptr)[*size] = degree; 
	(*size)++; 
	return 0;
}

void print_node(polynom* head) 
{
	int first = 1;
	if (head == NULL) 
	{
		printf("Polynomial is empty!\n");
		return;
	}
	while (head != NULL) 
	{
		int coeff = head->coeff;
		int degree = head->degree;

		if (first == 1) 
		{
			if (coeff < 0) 
			{
				printf("-");
				coeff = -coeff;
			}
		}
		else 
		{
			if (coeff < 0) 
			{
				printf(" - ");
				coeff = -coeff;
			}
			else 
			{
				printf(" + ");
			}
		}
		if (coeff != 1 && degree == 0) 
		{
			printf("%d", coeff);
		}
		else
		{
			printf("x^%d", degree);
		}
		first++;
		head = head->next;
	}
	printf("\nAmount of monomials: %d\n", first - 1);
}

void function25(polynom** head)
{
	if (*head == NULL)
	{
		printf("Polynomial is empty!\n");
		return;
	}
	polynom* curr = *head;
	polynom* prev = NULL;
	polynom* next = NULL;
	int count = 0;
	while (curr != NULL)
	{
		next = curr->next;
		if (curr->degree % 2 == 0)
		{
			if (prev == NULL)
			{
				*head = next;
			}
			else
			{
				prev->next = next;
			}
			free(curr);
			count++;
		}
		else
		{
			prev = curr;
		}
		curr = next;
	}
	if (count == 0)
	{
		printf("There are no monomials with even degrees\n");
	}
	else
	{
		printf("Deleled %d monomials\n", count);
	}
}